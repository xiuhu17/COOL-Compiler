#ifndef INCLUDE_UNIT_LICM_H
#define INCLUDE_UNIT_LICM_H
#include "llvm/IR/PassManager.h"

using namespace llvm;

namespace cs426 {
/// Loop Invariant Code Motion Optimization Pass
struct UnitLICM : PassInfoMixin<UnitLICM> {
  PreservedAnalyses run(Function& F, FunctionAnalysisManager& FAM);
};
} // namespace

#endif // INCLUDE_UNIT_LICM_H
