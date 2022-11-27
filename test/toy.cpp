#include "llvm/IR/IRBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"


using namespace llvm;
	static LLVMContext &Context = getGlobalContext();
	static Module *ModuleOb = new Module("my compiler", Context);
	Function *createFunc(IRBuilder<> &Builder, std::string Name) {
		FunctionType *funcType = llvm::FunctionType::get(Builder.getInt32Ty(),
		false);
		Function *fooFunc = llvm::Function::Create(
		funcType, llvm::Function::ExternalLinkage, Name, ModuleOb);
		return fooFunc;
	}
	BasicBlock *createBB(Function *fooFunc, std::string Name) {
		return BasicBlock::Create(Context, Name, fooFunc);
	}

int main(int argc, char *argv[]) {
	static IRBuilder<> Builder(Context);
	Function *fooFunc = createFunc(Builder, "foo");
	BasicBlock *entry = createBB(fooFunc, "entry");
	Builder.SetInsertPoint(entry);
	verifyFunction(*fooFunc);
	ModuleOb->dump();
	return 0;
}
