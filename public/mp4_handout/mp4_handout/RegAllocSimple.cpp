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
#define NOT_USE(phy_num) (((LiveVirtRegs_Phys.find((phy_num))) == (LiveVirtRegs_Phys.end())) && ((UsedInInstr_Phys.find((phy_num))) == (UsedInInstr_Phys.end())))

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
    DenseSet<MCPhysReg> LiveVirtRegs_Phys; 

    void Add_Use(DenseSet<MCPhysReg>& input, MCRegister phys_reg) {
      auto phy_reg_iter = MCRegUnitIterator(phys_reg, TRI);
      while (phy_reg_iter.isValid()) {
        
        assert(input.find(*phy_reg_iter) == input.end());
        input.insert(*phy_reg_iter);

        ++ phy_reg_iter;
      }
    }
    void Erase_Use(DenseSet<MCPhysReg>& input, MCRegister phys_reg) {
      auto phy_reg_iter = MCRegUnitIterator(phys_reg, TRI);
      while (phy_reg_iter.isValid()) {
        
        assert(input.find(*phy_reg_iter) != input.end());
        input.erase(*phy_reg_iter);

        ++ phy_reg_iter;
      }
    }

    // Allocate physical register for virtual register operand
    // for UsedInInstr_Phys, if eax is allocated, al, ah also marked as allocated
    PhysicalReg allocateOperand(MachineOperand &MO, Register VirtReg, bool is_use, DenseSet<MCPhysReg>& UsedInInstr_Phys) {
      // TODO: allocate physical register for a virtual register

      // if the virtual register is in the LiveVirtRegs
      if (LiveVirtRegs.find(VirtReg) != LiveVirtRegs.end()) {
        return LiveVirtRegs[VirtReg];
      }

      // find an unused physical register
      const llvm::TargetRegisterClass* tar_reg_cls = MRI->getRegClass(VirtReg);
      auto virt_reg_sz = TRI->getSpillSize(*tar_reg_cls);
      auto arr_phy_reg = RegClassInfo.getOrder(tar_reg_cls);

      // subreg
      auto virt_subreg = MO.getSubReg();

      // not empty
      if (!arr_phy_reg.empty()) { 
        // not allocated 
        // size must be correct 
        for (auto& phy_num: arr_phy_reg) {
          if (NOT_USE(phy_num)) {
            auto phy_reg_iter = MCRegUnitIterator(MCRegister(phy_num), TRI);
            while (phy_reg_iter.isValid()) {
              
              
              
              ++phy_reg_iter;
            }
          }
        }
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
