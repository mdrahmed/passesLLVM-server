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

#include "llvm/IR/LLVMContext.h"

using namespace std;
using namespace llvm;

namespace {

  class AFLCoverage : public ModulePass {

    public:

      static char ID;
      AFLCoverage() : ModulePass(ID) { }

      bool runOnModule(Module &M) override;

      // StringRef getPassName() const override {
      //  return "American Fuzzy Lop Instrumentation";
      // }

  };

}

char AFLCoverage::ID = 0;

LLVMContext &getGlobalContext() {
  static LLVMContext context;
  return context;
}



bool AFLCoverage::runOnModule(Module &M) {

        LLVMContext &context = M.getContext();
	//LLVMContext *context = &getGlobalContext();
        //IRBuilder<> builder(CallInst);

	ArrayRef<Type *> paramTypes = {Type::getInt8Ty(context)};
	Type *retType = Type::getVoidTy(context);
	FunctionType *funcType = FunctionType::get(retType, paramTypes, false);

	FunctionCallee callee = M.getOrInsertFunction("foo", funcType);

	


	// Modified	
	//static IRBuilder<> builder(getGlobalContext());	
	//Value *str = builder.CreateGlobalStringPtr("test\n", "str");

        //std::vector<Value *> argsV({str});
        //builder.CreateCall(printfFunc, argsV, "calltmp");

        for (auto &F : M){
               for (auto &BB : F) {
                        BasicBlock::iterator IP = BB.getFirstInsertionPt();
                        IRBuilder<> builder(&(*IP));

                        // The format string for the printf function, declared as a global literal
                        Value *str = builder.CreateGlobalStringPtr("test\n", "str");
			//Value *str = builder.CreateGlobalStringPtr(builder.CreateCall(foo,"calltmp"), "str");
                        std::vector<Value *> argsV({str});
                        //builder.CreateCall(printfFunc, argsV, "calltmp");
			builder.CreateCall(foo,argsV,"calltmp");
                }
        }
        return true;

}


static void registerAFLPass(const PassManagerBuilder &,
                            legacy::PassManagerBase &PM) {

  PM.add(new AFLCoverage());

}


static RegisterStandardPasses RegisterAFLPass(
    PassManagerBuilder::EP_ModuleOptimizerEarly, registerAFLPass);

static RegisterStandardPasses RegisterAFLPass0(
    PassManagerBuilder::EP_EnabledOnOptLevel0, registerAFLPass);
