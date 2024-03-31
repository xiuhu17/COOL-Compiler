//===- ScalarReplAggregates.cpp - Scalar Replacement of Aggregates --------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file was developed by the LLVM research group and is distributed under
// the University of Illinois Open Source License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This transformation implements the well known scalar replacement of
// aggregates transformation.  This xform breaks up alloca instructions of
// structure type into individual alloca instructions for
// each member (if possible).  Then, if possible, it transforms the individual
// alloca instructions into nice clean scalar SSA form.
//
// This combines an SRoA algorithm with Mem2Reg because they
// often interact, especially for C++ programs.  As such, this code
// iterates between SRoA and Mem2Reg until we run out of things to promote.
//
//===----------------------------------------------------------------------===//

#define DEBUG_TYPE "scalarrepl"
#include <iostream>
#include "llvm/Transforms/Scalar.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Pass.h"
#include "llvm/Transforms/Utils/PromoteMemToReg.h"
#include "llvm/Support/Debug.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/ADT/DenseSet.h"
#include "llvm/IR/Dominators.h"
#include "llvm/IR/IRBuilder.h"

using namespace llvm;

STATISTIC(NumReplaced,  "Number of aggregate allocas broken up");
STATISTIC(NumPromoted,  "Number of scalar allocas promoted to register");

namespace {
  struct SROA : public FunctionPass {
    static char ID; // Pass identification
    SROA() : FunctionPass(ID) { }

    // Entry point for the overall scalar-replacement pass
    bool runOnFunction(Function &F);

    // getAnalysisUsage - List passes required by this pass.  We also know it
    // will not alter the CFG, so say so.
    virtual void getAnalysisUsage(AnalysisUsage &AU) const {
      AU.setPreservesCFG();
      AU.addRequired<DominatorTreeWrapperPass>();
    }

  private:
    // Add fields and helper functions for this pass here.
    // worklist: remove from worklist  
    // marked_worklist: add to worklist; only which not in the makred_worklist could be inside the worklist)
    // executed:                         only not in executed could executre
    // collect all the alloca instructions
    DenseSet<AllocaInst *> worklist_alloca;
    DenseSet<AllocaInst *> marked_worklist_alloca;


    // insert the alloca function at the beginning of the funciton
    AllocaInst* Insert_Alloca_At_Head(Function& F, Type *ty);
    bool Promotable(AllocaInst* Value_Def);
    bool Is_Expandable_LoadStore(llvm::Value* Value_Def);
    bool Is_Expandable_U1U2(llvm::Value* Value_Def); 
    inline bool Is_Expandable_Entry(AllocaInst* Value_Def);
    void Do_Scalar_Expand(Function& F, AllocaInst* Value_Def);
    void Do_Scalar_Expand_Arr(Function& F, AllocaInst* Value_Def);
    void Transform_Scalar(Function &F); 
    void Transform_Mem2Reg(Function& F, DominatorTree& DT);
    void Update_Wrapper(Function& F, DominatorTree& DT);
    void Reinitialize_WL(Function& F);
  };
}

// Create the initializer and register the pass
char SROA::ID = 0;
// Public interface to create the ScalarReplAggregates pass.
// This function is provided to you.
static RegisterPass<SROA> X("scalarrepl-zhihaow6",
			    "Scalar Replacement of Aggregates (by zhihaow6)",
			    false /* does not modify the CFG */,
			    false /* transformation, not just analysis */);
FunctionPass *createMyScalarReplAggregatesPass() { return new SROA(); }

//===----------------------------------------------------------------------===//
//                      SKELETON FUNCTION TO BE IMPLEMENTED
//===----------------------------------------------------------------------===//
//
// Function runOnFunction:
// Entry point for the overall ScalarReplAggregates function pass.
// This function is provided to you.


AllocaInst* SROA::Insert_Alloca_At_Head(Function& F, Type *ty) {
  BasicBlock &entry_bb = F.getEntryBlock();
  if (entry_bb.empty()) {
    // Insert "at the end" of this bb
    return new AllocaInst(ty, 0, "", &entry_bb);
  } else {
    // Insert before the first instruction of this bb
    return new AllocaInst(ty, 0, "", &entry_bb.front());
  }
}

bool SROA::Promotable(AllocaInst* Value_Def) {
  if (!Value_Def) {
    return false;
  }

  if (!(Value_Def->getAllocatedType()->isFPOrFPVectorTy() || Value_Def->getAllocatedType()->isIntOrIntVectorTy() || Value_Def->getAllocatedType ()->isPtrOrPtrVectorTy())) {
    return false;
  }

  for (auto& Value_Use: Value_Def->uses()) {
    auto User = Value_Use.getUser();
    if (User && llvm::isa<llvm::Instruction>(User)) {
      auto User_Inst = llvm::cast<llvm::Instruction>(User);
      if (llvm::isa<llvm::LoadInst>(User_Inst)) {
        auto Load_Inst = llvm::cast<llvm::LoadInst>(User_Inst);
        if (Load_Inst->isVolatile()) {
          return false;
        } else {
          if (Load_Inst->getPointerOperand() != Value_Def) {  
            return false;
          }
        }
      } else if (llvm::isa<llvm::StoreInst>(User_Inst)) {
        auto Store_Inst = llvm::cast<llvm::StoreInst>(User_Inst);
        if (Store_Inst->isVolatile()) {
          return false;
        } else {
          if (Store_Inst->getPointerOperand() != Value_Def) {
            return false;
          }
        }
      } else {
        return false;
      }
    }
  }

  return true;
}

// by default the Value_Def do no need to be Struct Type
bool SROA::Is_Expandable_LoadStore(llvm::Value* Value_Def) {
  for (auto& Value_Use: Value_Def->uses()) {
    auto User = Value_Use.getUser();
    if (User && llvm::isa<llvm::Instruction>(User)) {
      auto User_Inst = llvm::cast<llvm::Instruction>(User);
      if (llvm::isa<llvm::LoadInst>(User_Inst)) {
        auto Load_Inst = llvm::cast<llvm::LoadInst>(User_Inst);
        if (Load_Inst->isVolatile()) {
          return false;
        } else {
          if (Load_Inst->getPointerOperand() != Value_Def) {  
            return false;
          }
        }
      } else if (llvm::isa<llvm::StoreInst>(User_Inst)) {
        auto Store_Inst = llvm::cast<llvm::StoreInst>(User_Inst);
        if (Store_Inst->isVolatile()) {
          return false;
        } else {
          if (Store_Inst->getPointerOperand() != Value_Def) {
            return false;
          }
        }
      } else {
        return false;
      }
    }
  }

  return true;
}

bool SROA::Is_Expandable_U1U2(llvm::Value* Value_Def) {
  if (!Value_Def) return false;

  for (auto& Value_Use: Value_Def->uses()) {
    auto User = Value_Use.getUser();
    if (User && llvm::isa<llvm::Instruction>(User)) {
      auto User_Inst = llvm::cast<llvm::Instruction>(User);
      if (llvm::isa<GetElementPtrInst>(User_Inst)) {
        auto Gep_Inst = llvm::cast<GetElementPtrInst>(User);
        auto First_Idx = Gep_Inst->getOperand(1);
        auto First_Idx_Con = dyn_cast<ConstantInt>(First_Idx)->getZExtValue();
        if (!(First_Idx_Con <= 4)) {
          return false;
        } else {
          if (!(Is_Expandable_U1U2(Gep_Inst) || Is_Expandable_LoadStore(Gep_Inst))) {
            return false;
          }
        }
      } else if (llvm::isa<CmpInst>(User_Inst)) {
        auto Cmp_Inst = llvm::cast<CmpInst>(User_Inst);
        auto lhs = Cmp_Inst->getOperand(0), rhs = Cmp_Inst->getOperand(1);
        if (!((llvm::isa<llvm::ConstantPointerNull>(lhs) || llvm::isa<llvm::ConstantPointerNull>(rhs)) && 
            (Cmp_Inst->getPredicate() == llvm::ICmpInst::ICMP_EQ || Cmp_Inst->getPredicate() == llvm::ICmpInst::ICMP_NE))) {
              return false;
        }
      } else {
        return false;
      }
    }
  }

  return true;
}

inline bool SROA::Is_Expandable_Entry(AllocaInst* Value_Def) {
  if (!Value_Def) return false;

  if (Value_Def->getAllocatedType()->isStructTy() ) return Is_Expandable_U1U2(Value_Def);
  if (Value_Def->getAllocatedType()->isArrayTy() && Value_Def->getAllocatedType()->getArrayElementType()->isStructTy()) return Is_Expandable_U1U2(Value_Def);

  return false;
}

void SROA::Do_Scalar_Expand(Function& F, AllocaInst* Value_Def) {
  if (!Is_Expandable_Entry(Value_Def)) return;

  worklist_alloca.erase(Value_Def);
  NumReplaced += 1;

  SmallVector<AllocaInst*, 5> idx_to_alloca;
  auto struct_tp = Value_Def->getAllocatedType();
  for (int i = 0; i < struct_tp->getNumContainedTypes(); ++ i) {
    auto sub_tp = struct_tp->getStructElementType(i);
    auto new_alloca = Insert_Alloca_At_Head(F, sub_tp);
    idx_to_alloca.push_back(new_alloca);
  }

  for (auto& Value_Use: Value_Def->uses()) {
    auto User = Value_Use.getUser();
    if (User && llvm::isa<GetElementPtrInst>(User)) {
      auto Gep_Inst = llvm::cast<GetElementPtrInst>(User);
      llvm::Value *Gep_Substitution;
      auto Idx = llvm::dyn_cast<ConstantInt>(Gep_Inst->getOperand(2))->getZExtValue();
      if (Gep_Inst->getNumOperands() == 3) { 
        Gep_Substitution = idx_to_alloca[Idx];
      } else {
        IRBuilder<> Builder(Gep_Inst->getContext());
        Builder.SetInsertPoint(Gep_Inst->getParent(), std::next(Gep_Inst->getIterator()));
        auto Gep_ptr = idx_to_alloca[Idx];
        SmallVector<llvm::Value*, 5> Gep_arr = {ConstantInt::get(Type::getInt32Ty(Gep_Inst->getContext()), 0)};
        for (int i = 3; i < Gep_Inst->getNumOperands(); ++ i) {
          Gep_arr.push_back(Gep_Inst->getOperand(i));
        }                                                           
        Gep_Substitution = Builder.CreateGEP(Gep_ptr->getAllocatedType(), Gep_ptr, Gep_arr);
      }
      Gep_Inst->replaceAllUsesWith(Gep_Substitution);
    } else if (User && llvm::isa<CmpInst>(User)) {
      auto Cmp_Inst = llvm::cast<CmpInst>(User);
      llvm::Value* Cmp_Substition;
      IRBuilder<> Builder(Cmp_Inst->getContext());
      Builder.SetInsertPoint(Cmp_Inst->getParent(), std::next(Cmp_Inst->getIterator()));
      if (Cmp_Inst->getPredicate() == llvm::ICmpInst::ICMP_EQ) {
        Cmp_Substition = llvm::ConstantInt::getFalse(Cmp_Inst->getContext());
      } else if (Cmp_Inst->getPredicate() == llvm::ICmpInst::ICMP_NE) {
        Cmp_Substition = llvm::ConstantInt::getTrue(Cmp_Inst->getContext());
      }
      Cmp_Inst->replaceAllUsesWith(Cmp_Substition);
    }
  }

  // add to worklist
  for (auto& iter: idx_to_alloca) {
    if (Is_Expandable_Entry(iter) && marked_worklist_alloca.find(iter) == marked_worklist_alloca.end()){
      worklist_alloca.insert(iter);
      marked_worklist_alloca.insert(iter);
    }
  }
}

void SROA::Do_Scalar_Expand_Arr(Function& F, AllocaInst* Value_Def) {
  if (!Is_Expandable_Entry(Value_Def)) return;

  assert(Value_Def->getAllocatedType()->isArrayTy());

  worklist_alloca.erase(Value_Def);
  NumReplaced += 1;

  auto arr_sz = Value_Def->getAllocatedType()->getArrayNumElements();
  auto element_struct_tp = Value_Def->getAllocatedType()->getArrayElementType();

  SmallVector<AllocaInst*, 5> idx_to_alloca;
  for (int i = 0; i < arr_sz; ++ i) {
    auto new_alloca = Insert_Alloca_At_Head(F, element_struct_tp);
    idx_to_alloca.push_back(new_alloca);
  }

  for (auto& Value_Use: Value_Def->uses()) {
    auto User = Value_Use.getUser();
    if (User && llvm::isa<GetElementPtrInst>(User)) {
      auto Gep_Inst = llvm::cast<GetElementPtrInst>(User);
      llvm::Value *Gep_Substitution;
      auto Idx = llvm::dyn_cast<ConstantInt>(Gep_Inst->getOperand(2))->getZExtValue();
      if (Gep_Inst->getNumOperands() == 3) { 
        Gep_Substitution = idx_to_alloca[Idx];
      } else {
        IRBuilder<> Builder(Gep_Inst->getContext());
        Builder.SetInsertPoint(Gep_Inst->getParent(), std::next(Gep_Inst->getIterator()));
        auto Gep_ptr = idx_to_alloca[Idx];
        SmallVector<llvm::Value*, 5> Gep_arr = {ConstantInt::get(Type::getInt32Ty(Gep_Inst->getContext()), 0)};
        for (int i = 3; i < Gep_Inst->getNumOperands(); ++ i) {
          Gep_arr.push_back(Gep_Inst->getOperand(i));
        }                                                           
        Gep_Substitution = Builder.CreateGEP(Gep_ptr->getAllocatedType(), Gep_ptr, Gep_arr);
      } 
      Gep_Inst->replaceAllUsesWith(Gep_Substitution);
    } else if (User && llvm::isa<CmpInst>(User)) {
      auto Cmp_Inst = llvm::cast<CmpInst>(User);
      llvm::Value* Cmp_Substition;
      IRBuilder<> Builder(Cmp_Inst->getContext());
      Builder.SetInsertPoint(Cmp_Inst->getParent(), std::next(Cmp_Inst->getIterator()));
      if (Cmp_Inst->getPredicate() == llvm::ICmpInst::ICMP_EQ) {
        Cmp_Substition = llvm::ConstantInt::getFalse(Cmp_Inst->getContext());
      } else if (Cmp_Inst->getPredicate() == llvm::ICmpInst::ICMP_NE) {
        Cmp_Substition = llvm::ConstantInt::getTrue(Cmp_Inst->getContext());
      }
      Cmp_Inst->replaceAllUsesWith(Cmp_Substition);
    }
  }
  
  // add to worklist
  for (auto& iter: idx_to_alloca) {
    if (Is_Expandable_Entry(iter) && marked_worklist_alloca.find(iter) == marked_worklist_alloca.end()){
      worklist_alloca.insert(iter);
      marked_worklist_alloca.insert(iter);
    }
  }

}
void SROA::Transform_Scalar(Function &F) {
  while (!worklist_alloca.empty()) {
    auto alloca_for_expand = *worklist_alloca.begin();
    // Choose one of the expand
    if (alloca_for_expand->getAllocatedType()->isArrayTy()) {
      Do_Scalar_Expand_Arr(F, alloca_for_expand);
    } else {
      Do_Scalar_Expand(F, alloca_for_expand);
    }
  }
}

void SROA::Transform_Mem2Reg(Function& F, DominatorTree& DT) {
  std::vector<AllocaInst*> Allocas_Promotalbe;
  for (auto &BB : F) {
    for (auto &Inst : BB) {
      if (llvm::isa<llvm::AllocaInst>(Inst)) {
        auto Alloca_Inst = llvm::cast<llvm::AllocaInst>(&Inst);
        if (Promotable(Alloca_Inst)) {
          Allocas_Promotalbe.push_back(Alloca_Inst);
          NumPromoted += 1;
        }
      }
    }
  }
  PromoteMemToReg(Allocas_Promotalbe, DT);
}

void SROA::Reinitialize_WL(Function& F) {
  for (auto &BB : F) {
    for (auto &Inst : BB) {
      if (llvm::isa<llvm::AllocaInst>(Inst)) {
        auto Alloca_Inst = llvm::cast<llvm::AllocaInst>(&Inst);
        if (Is_Expandable_Entry(Alloca_Inst) && marked_worklist_alloca.find(Alloca_Inst) == marked_worklist_alloca.end()){
          worklist_alloca.insert(Alloca_Inst);
          marked_worklist_alloca.insert(Alloca_Inst);
        }
      }
    }
  }
}

void SROA::Update_Wrapper(Function& F, DominatorTree& DT) {
  int counter = 0;
  while (!worklist_alloca.empty()) {
    Transform_Scalar(F);
    Transform_Mem2Reg(F, DT);
    Reinitialize_WL(F);
    counter ++;
  }
}

bool SROA::runOnFunction(Function &F) {
  dbgs() << F.getName() << "                               \n";

  // initialization
  worklist_alloca.clear();
  marked_worklist_alloca.clear();
  DominatorTree& DT = getAnalysis<DominatorTreeWrapperPass>().getDomTree();
  LLVMContext& Context = F.getContext();
  Transform_Mem2Reg(F, DT);
  Reinitialize_WL(F);

  // do the expansion and promotaion
  Update_Wrapper(F, DT);

  // debug
  for (auto &BB : F) {
    for (auto &Inst : BB) {
        dbgs() << Inst <<"\n";
    }
  }

  dbgs() << "NumReplaced: " << NumReplaced << " NumPromoted: "<< NumPromoted << "\n";
  dbgs() << F.getName() << "                               \n";

  return true;
} 

