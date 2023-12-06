#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

#include "UnitLICM.h"
#include "UnitLoopInfo.h"
#include "UnitSCCP.h"

/// Registers the three passes for this project with LLVM's pass mananger
llvm::PassPluginLibraryInfo getUnitProjectPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "CS426 Unit Project", LLVM_VERSION_STRING,
          [](PassBuilder& PB) {
            // Register LoopId
            PB.registerAnalysisRegistrationCallback(
              [](FunctionAnalysisManager &FAM) {
                FAM.registerPass([&]{ return cs426::UnitLoopAnalysis(); });
              });
            // Register LICM
            PB.registerPipelineParsingCallback(
              [](StringRef Name, FunctionPassManager& FPM,
                 ArrayRef<PassBuilder::PipelineElement>) {
                if (Name == "unit-licm") {
                  FPM.addPass(cs426::UnitLICM());
                  return true;
                }
                return false;
              });
            // Register SCCP
            PB.registerPipelineParsingCallback(
              [](StringRef Name, FunctionPassManager& FPM,
                 ArrayRef<PassBuilder::PipelineElement>) {
                if (Name == "unit-sccp") {
                  FPM.addPass(cs426::UnitSCCP());
                  return true;
                }
                return false;
              });
          }};
}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return getUnitProjectPluginInfo();
}
