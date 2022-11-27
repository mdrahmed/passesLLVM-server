
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
//#include "basic_log.h"
//#include "hello.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"


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


bool AFLCoverage::runOnModule(Module &M) {
  	
	LLVMContext &context = M.getContext();	
	
	//IRBuilder<> builder(CallInst);
	Type *intType = Type::getInt32Ty(context);
	
	

	// Declare C standard library printf 
	//std::vector<Type *> printfArgsTypes({Type::getInt8PtrTy(context)});
	//FunctionType *printfType = FunctionType::get(intType, printfArgsTypes, true);
	//auto printfFunc = M.getOrInsertFunction("printf", printfType);

	//std::vector<Type *> fooTypes({Type::getInt8Ty(context)});
	Type *retType = Type::getVoidTy(context);
	FunctionType *funcType = FunctionType::get(retType,true);
	//llvm::Function* foofunc = llvm::Function::Create(funcType, llvm::GlobalValue::ExternalLinkage, llvm::Twine("foo"), &M);
	// auto callee = M.getOrInsertFunction("foo", funcType);
	llvm::Function* foofunc = llvm::Function::Create(funcType, llvm::GlobalValue::ExternalLinkage, llvm::Twine("our_log"), &M);
	
	//llvm::Function* foo = llvm::Function::Create(funcType, llvm::GlobalValue::ExternalLinkage, llvm::Twine("foo"), &M);

	 for (auto &F : M){
    		for (auto &BB : F) {
			BasicBlock::iterator IP = BB.getFirstInsertionPt();
			IRBuilder<> builder(&(*IP));
			
			//log();
			//foo();
			// The format string for the printf function, declared as a global literal
			// Value *str = builder.CreateGlobalStringPtr("test\n", "str");
			
			// std::vector<Value *> argsV({str});
			// builder.CreateCall(printfFunc, argsV, "calltmp");

			builder.CreateCall(foofunc);
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

