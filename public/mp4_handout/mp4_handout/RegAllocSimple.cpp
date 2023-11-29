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
    
    // stk struct
    struct STK{
      MachineBasicBlock* mbb;
      MachineBasicBlock::iterator* mbbi;
      Register* drg;
      int fidx;
      const TargetRegisterClass* rc;
      const TargetRegisterInfo* tri;
      Register vreg;
    };

    // build lookup map
    DenseMap<VirtualReg, STK> SpillVirtRegs;
    DenseMap<VirtualReg, PhysicalReg>  LiveVirtRegs;
    // used physical reg
    // for LiveVirtRegs_Phys, if eax is allocated, al, ah also marked as allocated
    DenseSet<PhysicalReg> LiveVirtRegs_Phys; 
    // virtual registser -> last exists Machineoperand
    DenseMap<VirtualReg, MachineOperand*> VirtualReg_Status;

    // helper function for set
    // if eax is added to use, then eax add use
    inline bool CAN_USE(DenseSet<PhysicalReg>& used_phys, MCRegister& phys_reg) {
      for (auto i = used_phys.begin(); i != used_phys.end();  ++ i) {
        if (TRI->regsOverlap(*i, phys_reg)) {
          return false;
        }
      }
      return true;
    }
    inline void Add_Use(DenseSet<PhysicalReg>& used_phys, MCRegister& phys_reg) {
      assert(CAN_USE(used_phys, phys_reg));
      used_phys.insert(phys_reg);
    }
    inline void Erase_Use(DenseSet<PhysicalReg>& used_phys, MCRegister& phys_reg) {
      assert(used_phys.find(phys_reg) != used_phys.end());
      used_phys.erase(phys_reg);
    }

    // helper function for size
    inline unsigned int Size(Register& input) {
      return TRI->getSpillSize(*(MRI->getRegClass(input)));
    }
    inline unsigned int SpillSize(Register& input) {
      return TRI->getSpillSize(*(MRI->getRegClass(input)));
    }
    inline llvm::Align SpillAlignment(Register& input) {
      return TRI->getSpillAlign(*(MRI->getRegClass(input)));
    } 
    // helper function for checking whether need spill
    // if dead/kill, no later use
    // if the register is already on stack, and is only for use
    inline bool Need_Spill_Action(Register& vreg) { 

      auto MO = VirtualReg_Status[vreg];
      return !(MO->isKill() || MO->isDead() || (SpillVirtRegs.find(vreg) != SpillVirtRegs.end() && MO->isUse()));
    }

    /* HELPER FUNCTION */
    // Allocate physical register for virtual register operand
    // for UsedInInstr_Phys, if eax is allocated, al, ah also marked as allocated
    // after this function, we need to call MachineOperand::setReg, MachineOperand::setSubReg
    void allocateOperand(MachineOperand &MO, Register VirtReg, bool is_use, DenseSet<PhysicalReg>& UsedInInstr_Phys) {
      // TODO: allocate physical register for a virtual register

      // if the virtual register is in the LiveVirtRegs
      if (LiveVirtRegs.find(VirtReg) != LiveVirtRegs.end()) {
        auto physical_reg = LiveVirtRegs[VirtReg];
        MO.setReg(physical_reg);
        MO.setSubReg(0);
        return;
      }

      // find an unused physical register
      auto virt_reg_sz = Size(VirtReg);
      auto arr_phy_reg = RegClassInfo.getOrder((MRI->getRegClass(VirtReg)));
      // subreg
      auto virt_subreg = MO.getSubReg();

      // need subreg
      if (virt_subreg) {
          // not allocated 
          // may need to compare the size
          for (auto phy_num: arr_phy_reg) {
            if (NOT_USE(UsedInInstr_Phys, phy_num)) {
              auto phy_sub_reg = TRI->getSubReg(MCRegister(phy_num), virt_subreg);

              auto phy_reg_iter = MCRegUnitIterator(MCRegister(phy_num), TRI);
              while (phy_reg_iter.isValid()) {
                auto phy_sub_reg = TRI->getSubReg(*phy_reg_iter, virt_subreg);
                if (NOT_USE(UsedInInstr_Phys, phy_sub_reg)) {
                  Add_Use(UsedInInstr_Phys, phy_sub_reg);
                  Add_Use(LiveVirtRegs_Phys, phy_sub_reg);
                  return phy_sub_reg; 
                }
                ++ phy_reg_iter;
              }
            }
          }

          // not allocated in UsedInInstr_Phys
          // select spill
          // allocate as previous code, may reuse the previous for-loop code
          for (auto phy_num: arr_phy_reg) {
            if (UsedInInstr_Phys.find(phy_num) == UsedInInstr_Phys.end()) {
              auto phy_reg_iter = MCRegUnitIterator(MCRegister(phy_num), TRI);
              while (phy_reg_iter.isValid()) {
                auto phy_sub_reg = TRI->getSubReg(*phy_reg_iter, virt_subreg);
                
                ++ phy_reg_iter;
              }
            }
          }
      } else { // no subreg

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
