//===----------------------------------------------------------------------===//
//
/// A register allocator simplified from RegAllocFast.cpp
//
//===----------------------------------------------------------------------===//

#include "llvm/ADT/Statistic.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/RegAllocRegistry.h"
#include "llvm/CodeGen/RegisterClassInfo.h"
#include "llvm/CodeGen/TargetInstrInfo.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/InitializePasses.h"
#include "llvm/Pass.h"

#include "llvm/CodeGen/LiveIntervals.h"
#include "llvm/CodeGen/SlotIndexes.h"

#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

using namespace llvm;

#define DEBUG_TYPE "regalloc"
#define SYSTEM_SAVE_REG 0 // argument or ret val

STATISTIC(NumStores, "Number of stores added");
STATISTIC(NumLoads , "Number of loads added");

namespace {
  /// This is class where you will implement your register allocator in
  class RegAllocSimple : public MachineFunctionPass {
  public:
    static char ID;
    RegAllocSimple() : MachineFunctionPass(ID) {}

  private:
    /// Some information that might be useful for register allocation
    /// They are initialized in runOnMachineFunction
    MachineFrameInfo *MFI;
    MachineRegisterInfo *MRI;
    const TargetRegisterInfo *TRI;
    const TargetInstrInfo *TII;
    RegisterClassInfo RegClassInfo;

    // TODO: maintain information about live registers

  public:
    StringRef getPassName() const override { return "Simple Register Allocator"; }

    void getAnalysisUsage(AnalysisUsage &AU) const override {
      AU.setPreservesCFG();
      // At -O1/-O2, llc fails to schedule some required passes if this pass
      // does not preserve these anlyses; these are preserved by recomputing
      // them at the end of runOnFunction(), you can safely ignore these
      AU.addRequired<LiveIntervals>();
      AU.addPreserved<LiveIntervals>();
      AU.addRequired<SlotIndexes>();
      AU.addPreserved<SlotIndexes>();
      MachineFunctionPass::getAnalysisUsage(AU);
    }

    /// Ask the Machine IR verifier to check some simple properties
    /// Enabled with the -verify-machineinstrs flag in llc
    MachineFunctionProperties getRequiredProperties() const override {
      return MachineFunctionProperties().set(
          MachineFunctionProperties::Property::NoPHIs);
    }

    MachineFunctionProperties getSetProperties() const override {
      return MachineFunctionProperties().set(
          MachineFunctionProperties::Property::NoVRegs);
    }

    MachineFunctionProperties getClearedProperties() const override {
      return MachineFunctionProperties().set(
        MachineFunctionProperties::Property::IsSSA);
    }

  private:

    // rename
    using VirtualReg = Register;
    using PhysicalReg = MCRegister;
    using FrameIndex = int;

    // build lookup map
    DenseMap<VirtualReg, FrameIndex> SpillVirtRegs;
    DenseMap<VirtualReg, PhysicalReg>  LiveVirtRegs;
    DenseMap<VirtualReg, MachineOperand> LiveVirtualRegs_Status;// virtual registser -> last exists Machineoperand

    DenseMap<PhysicalReg, VirtualReg> Live_Phy_to_Vir;  // used physical reg // for LiveVirtRegs_Phys, if eax is allocated, al, ah also marked as allocated
    // DenseMap<PhysicalReg, VirtualReg>& Instr_Phy_to_Vir

    DenseMap<PhysicalReg, VirtualReg> Arg_Ret;

    // helper function for set
    // if eax is added to use, then eax add use
    inline bool CAN_USE(DenseMap<PhysicalReg, VirtualReg>& used_phys, MCRegister phys_reg) {
      for (auto i = used_phys.begin(); i != used_phys.end();  ++ i) {
        if (TRI->regsOverlap(i->first, phys_reg)) {
          return false;
        }
      }
      return true;
    }
    inline void Add_Use(DenseMap<PhysicalReg, VirtualReg>& used_phys, MCRegister phys_reg, Register virt_reg) {
      assert(CAN_USE(used_phys, phys_reg));
      used_phys[phys_reg] = virt_reg;
    }
    inline void Erase_Use(DenseMap<PhysicalReg, VirtualReg>& used_phys, MCRegister phys_reg) {
      assert(used_phys.find(phys_reg) != used_phys.end());
      used_phys.erase(phys_reg);
    }

    // helper function for size
    inline unsigned int Size(Register input) {
      return TRI->getSpillSize(*(MRI->getRegClass(input)));
    }
    inline unsigned int SpillSize(Register input) {
      return TRI->getSpillSize(*(MRI->getRegClass(input)));
    }
    inline llvm::Align SpillAlignment(Register input) {
      return TRI->getSpillAlign(*(MRI->getRegClass(input)));
    } 
    // helper function for checking whether need spill
    // if dead/kill, no later use
    // if the register is already on stack, and is only for use
    inline bool Need_Store_Back(DenseMap<PhysicalReg, VirtualReg>& used_phys, Register reg) { 
      Register vreg;
      if (reg.isPhysical()) {
        assert(used_phys.find(reg) != used_phys.end());
        vreg = used_phys[reg];
      } else if (reg.isVirtual()) {
        vreg = reg;
      } else {
        assert(false);
      }
      auto MO = LiveVirtualRegs_Status[vreg];
      // return !(MO.isKill() || MO.isDead() || (SpillVirtRegs.find(vreg) != SpillVirtRegs.end() && MO.isUse()));
      return !(MO.isKill() || MO.isDead() || (SpillVirtRegs.find(vreg) != SpillVirtRegs.end()));
    }
     
    // spill one with lowest store/load
    int Find_Reg_Spill(DenseMap<PhysicalReg, VirtualReg>& used_phys, SmallVector<MCRegister, 5>& Spill_Candidate) {
      int i = 0, idx = 0;
      int comp = used_phys.size() * 2;
      for (auto& phy_for_using: Spill_Candidate) {
        int count_load = 0, count_store = 0;
        for (auto iter = used_phys.begin(); iter != used_phys.end();  ++ iter) {
          auto phys_intefere = iter->first;
          if (TRI->regsOverlap(phy_for_using, phys_intefere)) {
            count_load ++;
            if (Need_Store_Back(used_phys, phys_intefere)) {
              count_store ++;
            }
          }
        }
        if (count_load + count_store <= comp) {
          comp = count_load + count_store;
          idx = i;
        }
        i ++;
      }

      return idx;
    }

    inline int Do_Store(MachineBasicBlock& MBB, MachineInstr& MI, MachineOperand& MO, MCRegister physical_intefere) {
      auto spill_sz = SpillSize(physical_intefere);
      auto spill_al = SpillAlignment(physical_intefere);
      auto stk_idx = MFI->CreateSpillStackObject(spill_sz, spill_al);
      TII->storeRegToStackSlot(MBB, MI, physical_intefere, MO.isKill(), stk_idx, MRI->getRegClass(physical_intefere), TRI);
      return stk_idx;
    }

    inline void Do_Load(MachineBasicBlock& MBB, MachineInstr& MI, MachineOperand& MO, Register vert_reg) {
      auto phy_reg = LiveVirtRegs[vert_reg];
      assert(SpillVirtRegs.find(vert_reg) != SpillVirtRegs.end());
      auto stk_idx = SpillVirtRegs[vert_reg];
      TII->loadRegFromStackSlot(MBB, MI, phy_reg, stk_idx, MRI->getRegClass(phy_reg), TRI);
    }

    void Do_Spill(DenseMap<PhysicalReg, VirtualReg>& used_phys, MachineBasicBlock& MBB, MachineInstr& MI, MachineOperand& MO, MCRegister physical_intefere) {
      auto reclaim_vreg = used_phys[physical_intefere];
      if (Need_Store_Back(used_phys, physical_intefere)) {
        auto stk_idx = Do_Store(MBB, MI, MO, physical_intefere);      
        SpillVirtRegs[reclaim_vreg] = stk_idx;
      } 
      
      LiveVirtRegs.erase(reclaim_vreg);
      LiveVirtualRegs_Status.erase(reclaim_vreg);
      Erase_Use(used_phys, physical_intefere);
    }

    /* HELPER FUNCTION */
    // Allocate physical register for virtual register operand
    // for UsedInInstr_Phys, if eax is allocated, al, ah also marked as allocated
    // after this function, we need to call MachineOperand::setReg, MachineOperand::setSubReg
    void allocateOperand(MachineBasicBlock& MBB, MachineInstr& MI, MachineOperand &MO, Register VirtReg, bool is_use, DenseMap<PhysicalReg, VirtualReg>& Instr_Phy_to_Vir) {
      // TODO: allocate physical register for a virtual register
      if (MO.getReg().isPhysical()) {
        MCRegister phy_reg = MO.getReg();
        if (MO.isDef()) {
          for (auto iter = Live_Phy_to_Vir.begin(); iter != Live_Phy_to_Vir.end(); ++ iter) {
            auto physical_intefere = iter->first;
            if (TRI->regsOverlap(physical_intefere, phy_reg)) {
              assert(Instr_Phy_to_Vir.find(physical_intefere) == Instr_Phy_to_Vir.end());
              // must spill
              //  do spill action
              //  directly reclaim
              Do_Spill(Live_Phy_to_Vir, MBB, MI, MO, physical_intefere);
            }
          }
          Add_Use(Arg_Ret, phy_reg, phy_reg);
         } else if (MO.isDead() || MO.isKill()) {
          Erase_Use(Arg_Ret, phy_reg);
         }
       return;
      }

      if (!is_use) {
        SpillVirtRegs.erase(VirtReg);
      } 

      // if the virtual register is in the LiveVirtRegs
      if (LiveVirtRegs.find(VirtReg) != LiveVirtRegs.end()) {
        auto physical_reg = LiveVirtRegs[VirtReg];
        MO.setReg(physical_reg);
        MO.setSubReg(0);
        LiveVirtualRegs_Status[VirtReg] = MO;
        assert(Live_Phy_to_Vir.find(physical_reg) != Live_Phy_to_Vir.end());
        Add_Use(Instr_Phy_to_Vir, physical_reg, VirtReg);   
        return;
      }

      // find an unused physical register
      auto arr_phy_reg = RegClassInfo.getOrder(MRI->getRegClass(VirtReg));
      // subreg
      auto virt_subreg = MO.getSubReg();

      // need subreg
      if (virt_subreg) {
          // not allocated 
          for (auto phy_num: arr_phy_reg) {
            auto phy_sub_reg = TRI->getSubReg(MCRegister(phy_num), virt_subreg);
            if (phy_sub_reg && CAN_USE(Arg_Ret, phy_sub_reg) && CAN_USE(Live_Phy_to_Vir, phy_sub_reg) && CAN_USE(Instr_Phy_to_Vir, phy_sub_reg)) {
              LiveVirtRegs[VirtReg] = phy_sub_reg;
              MO.setReg(phy_sub_reg);
              MO.setSubReg(0);
              LiveVirtualRegs_Status[VirtReg] = MO;
              Add_Use(Live_Phy_to_Vir, phy_sub_reg, VirtReg);
              Add_Use(Instr_Phy_to_Vir, phy_sub_reg, VirtReg);
              if (is_use) {
                Do_Load(MBB, MI, MO, VirtReg);
              }
              return;
            }
          }

          // can use in UsedInInstr_Phys
          SmallVector<MCRegister, 5> Spill_Candidate;
          for (auto phy_num: arr_phy_reg) {
            auto phy_sub_reg = TRI->getSubReg(MCRegister(phy_num), virt_subreg);
            if (phy_sub_reg && CAN_USE(Arg_Ret, phy_sub_reg) && CAN_USE(Instr_Phy_to_Vir, phy_sub_reg)) {
              Spill_Candidate.push_back(phy_sub_reg);
            }
          }
          auto idx = Find_Reg_Spill(Live_Phy_to_Vir, Spill_Candidate);
          auto phy_sub_reg = Spill_Candidate[idx];
          for (auto iter = Live_Phy_to_Vir.begin(); iter != Live_Phy_to_Vir.end(); ++ iter) {
            auto physical_intefere = iter->first;
            if (TRI->regsOverlap(physical_intefere, phy_sub_reg)) {
              assert(Instr_Phy_to_Vir.find(physical_intefere) == Instr_Phy_to_Vir.end());
              // must spill
              //  do spill action
              //  directly reclaim
              Do_Spill(Live_Phy_to_Vir, MBB, MI, MO, physical_intefere);
            }
          }
          LiveVirtRegs[VirtReg] = phy_sub_reg;
          MO.setReg(phy_sub_reg);
          MO.setSubReg(0);
          LiveVirtualRegs_Status[VirtReg] = MO;
          Add_Use(Live_Phy_to_Vir, phy_sub_reg, VirtReg);
          Add_Use(Instr_Phy_to_Vir, phy_sub_reg, VirtReg);
          if (is_use) {
            Do_Load(MBB, MI, MO, VirtReg);
          }
          return;
      } else { // no subreg
          for (auto phy_num: arr_phy_reg) {
            auto phy_no_sub_reg = MCRegister(phy_num);
            if (CAN_USE(Arg_Ret, phy_no_sub_reg) && CAN_USE(Live_Phy_to_Vir, phy_no_sub_reg) && CAN_USE(Instr_Phy_to_Vir, phy_no_sub_reg)) {
              LiveVirtRegs[VirtReg] = phy_no_sub_reg;
              MO.setReg(phy_no_sub_reg);
              MO.setSubReg(0);
              LiveVirtualRegs_Status[VirtReg] = MO;
              Add_Use(Live_Phy_to_Vir, phy_no_sub_reg, VirtReg);
              Add_Use(Instr_Phy_to_Vir, phy_no_sub_reg, VirtReg);
              if (is_use) {
                Do_Load(MBB, MI, MO, VirtReg);
              }
              return;
            }
          }

          // can use in UsedInInstr_Phys
          SmallVector<MCRegister, 5> Spill_Candidate;
          for (auto phy_num: arr_phy_reg) {
            auto phy_no_sub_reg = MCRegister(phy_num);
            if (CAN_USE(Arg_Ret, phy_no_sub_reg) && CAN_USE(Instr_Phy_to_Vir, phy_no_sub_reg)) {
              Spill_Candidate.push_back(phy_no_sub_reg);
            }
          }
          auto idx = Find_Reg_Spill(Live_Phy_to_Vir, Spill_Candidate);
          auto phy_no_sub_reg = Spill_Candidate[idx];
          for (auto iter = Live_Phy_to_Vir.begin(); iter != Live_Phy_to_Vir.end(); ++ iter) {
            auto physical_intefere = iter->first;
            if (TRI->regsOverlap(physical_intefere, phy_no_sub_reg)) {
              assert(Instr_Phy_to_Vir.find(physical_intefere) == Instr_Phy_to_Vir.end());
              // must spill
              //  do spill action
              //  directly reclaim
              Do_Spill(Live_Phy_to_Vir, MBB, MI, MO, physical_intefere);
            }
          }
          LiveVirtRegs[VirtReg] = phy_no_sub_reg;
          MO.setReg(phy_no_sub_reg);
          MO.setSubReg(0);
          LiveVirtualRegs_Status[VirtReg] = MO;
          Add_Use(Live_Phy_to_Vir, phy_no_sub_reg, VirtReg);
          Add_Use(Instr_Phy_to_Vir, phy_no_sub_reg, VirtReg);
          if (is_use) {
            Do_Load(MBB, MI, MO, VirtReg);
          }
          return;
      }

    }

    void allocateInstruction(MachineInstr &MI) {
      // TODO: find and allocate all virtual registers in MI
    }

    void allocateBasicBlock(MachineBasicBlock &MBB) {
      // TODO: allocate each instruction
      // TODO: spill all live registers at the end
    }

    bool runOnMachineFunction(MachineFunction &MF) override {
      dbgs() << "simple regalloc running on: " << MF.getName() << "\n";

      outs() << "simple regalloc not implemented\n";
      abort();

      // Get some useful information about the target
      MRI = &MF.getRegInfo();
      const TargetSubtargetInfo &STI = MF.getSubtarget();
      TRI = STI.getRegisterInfo();
      TII = STI.getInstrInfo();
      MFI = &MF.getFrameInfo();
      MRI->freezeReservedRegs(MF);
      RegClassInfo.runOnMachineFunction(MF);

      // Allocate each basic block locally
      for (MachineBasicBlock &MBB : MF) {
        allocateBasicBlock(MBB);
      }

      MRI->clearVirtRegs();

      // Recompute the analyses that we marked as preserved above, you can
      // safely ignore this code
      SlotIndexes& SI = getAnalysis<SlotIndexes>();
      SI.releaseMemory();
      SI.runOnMachineFunction(MF);

      LiveIntervals& LI = getAnalysis<LiveIntervals>();
      LI.releaseMemory();
      LI.runOnMachineFunction(MF);

      return true;
    }
  };
}

/// Create the initializer and register the pass
char RegAllocSimple::ID = 0;
FunctionPass *llvm::createSimpleRegisterAllocator() { return new RegAllocSimple(); }
INITIALIZE_PASS(RegAllocSimple, "regallocsimple", "Simple Register Allocator", false, false)
static RegisterRegAlloc simpleRegAlloc("simple", "simple register allocator", createSimpleRegisterAllocator);
