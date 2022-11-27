
#define AFL_LLVM_PASS
#define AFL_R(x) (random() % (x))
#define MAP_SIZE  (1 << 16)

// #include "../config.h"
// #include "../debug.h"

#include <unordered_set>
#include <unordered_map>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "llvm/ADT/Statistic.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Attributes.h"
#include "llvm/Support/Debug.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/DebugInfoMetadata.h"

using namespace llvm;

namespace {
  struct SkeletonPass : public FunctionPass {
    static char ID;
    SkeletonPass() : FunctionPass(ID) {}

    virtual bool runOnFunction(Function &F) {
      for (auto &B : F) {
        for (auto &I : B) {
          if (auto *op = dyn_cast<BinaryOperator>(&I)) {
            // Insert at the point where the instruction `op` appears.
            IRBuilder<> builder(op);

            // Make a multiply with the same operands as `op`.
            Value *lhs = op->getOperand(0);
            Value *rhs = op->getOperand(1);
            Value *mul = builder.CreateMul(lhs, rhs);

            // Everywhere the old instruction was used as an operand, use our
            // new multiply instruction instead.
            for (auto &U : op->uses()) {
              User *user = U.getUser();  // A User is anything with operands.
              user->setOperand(U.getOperandNo(), mul);
            }

            // We modified the code.
            return true;
          }
        }
      }

      return false;
    }
  };
}



//static void registerAFLPass(const PassManagerBuilder &,
//                            legacy::PassManagerBase &PM) {
//
//  PM.add(new AFLCoverage());
//
//}
//
//
//static RegisterStandardPasses RegisterAFLPass(
//    PassManagerBuilder::EP_ModuleOptimizerEarly, registerAFLPass);
//
//static RegisterStandardPasses RegisterAFLPass0(
//    PassManagerBuilder::EP_EnabledOnOptLevel0, registerAFLPass);


char SkeletonPass::ID = 0;

static void registerSkeletonPass(const PassManagerBuilder &,
                                 legacy::PassManagerBase &PM) {
  PM.add(new SkeletonPass());
}
static RegisterStandardPasses RegisterMyPass(
	PassManagerBuilder::EP_EarlyAsPossible,registerSkeletonPass);

