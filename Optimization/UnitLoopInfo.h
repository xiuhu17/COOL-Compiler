#ifndef INCLUDE_UNIT_LOOP_INFO_H
#define INCLUDE_UNIT_LOOP_INFO_H
#include "llvm/IR/PassManager.h"
#include <vector>

using namespace llvm;

namespace cs426 {
/// An object holding information about the (natural) loops in an LLVM
/// function. At minimum this will need to identify the loops, may hold
/// additional information you find useful for your LICM pass
class UnitLoopInfo {
  // Define this class to provide the information you need in LICM
  public:
    DenseMap<BasicBlock*, DenseSet<BasicBlock*>> header_to_body;
    DenseMap<BasicBlock*, DenseSet<BasicBlock*>> header_to_latch;
    DenseMap<BasicBlock*, DenseSet<BasicBlock*>> header_to_exiting;
    DenseMap<BasicBlock*, BasicBlock*> header_to_parent; // null means it is the top; closet parent in the hieracy
    DenseMap<BasicBlock*, DenseSet<BasicBlock*>> forest;  // 
};

/// Loop Identification Analysis Pass. Produces a UnitLoopInfo object which
/// should contain any information about the loops in the function whic h is
/// needed for your implementation of LICM
class UnitLoopAnalysis : public AnalysisInfoMixin<UnitLoopAnalysis> {
  friend AnalysisInfoMixin<UnitLoopAnalysis>;
  static AnalysisKey Key;

public:
  typedef UnitLoopInfo Result;

  UnitLoopInfo run(Function &F, FunctionAnalysisManager &AM);
};

} // namespace

#endif // INCLUDE_UNIT_LOOP_INFO_H
