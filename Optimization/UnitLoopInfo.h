#ifndef INCLUDE_UNIT_LOOP_INFO_H
#define INCLUDE_UNIT_LOOP_INFO_H
#include "llvm/IR/PassManager.h"

using namespace llvm;

namespace cs426 {
/// An object holding information about the (natural) loops in an LLVM
/// function. At minimum this will need to identify the loops, may hold
/// additional information you find useful for your LICM pass
class UnitLoopInfo {
  // Define this class to provide the information you need in LICM
};

/// Loop Identification Analysis Pass. Produces a UnitLoopInfo object which
/// should contain any information about the loops in the function which is
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
