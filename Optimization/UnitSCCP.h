#ifndef INCLUDE_UNIT_SCCP_H
#define INCLUDE_UNIT_SCCP_H
#include "llvm/IR/PassManager.h"

using namespace llvm;

namespace cs426 {
/// Sparse Conditional Constant Propagation Optimization Pass
struct UnitSCCP : PassInfoMixin<UnitSCCP> {
  PreservedAnalyses run(Function& F, FunctionAnalysisManager& FAM);
};
} // namespace

#endif // INCLUDE_UNIT_SCCP_H
