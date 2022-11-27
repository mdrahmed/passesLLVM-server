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

  class AFLCoverage : public ModulePass {

    public:

      static char ID;
      AFLCoverage() : ModulePass(ID) { }

      bool runOnModule(Module &M) override;

  };

}


char AFLCoverage::ID = 0;


bool AFLCoverage::runOnModule(Module &M) {
  	
	LLVMContext &context = M.getContext();	
	
	//IRBuilder<> builder(CallInst);
	Type *intType = Type::getInt32Ty(context);
	
	

	// Declare C standard library printf 
	std::vector<Type *> printfArgsTypes({Type::getInt8PtrTy(context)});
	FunctionType *printfType = FunctionType::get(intType, printfArgsTypes, true);
	auto printfFunc = M.getOrInsertFunction("printf", printfType);
	
	 for (auto &F : M){
    		for (auto &BB : F) {
			//BasicBlock::iterator IP = BB.getFirstInsertionPt();
			//IRBuilder<> builder(&(*IP));

			//// The format string for the printf function, declared as a global literal
			//Value *str = builder.CreateGlobalStringPtr("test\n", "str");
			//
			//std::vector<Value *> argsV({str});
			//builder.CreateCall(printfFunc, argsV, "calltmp");
			for(auto &I:BB){
				//if(isa<BranchInst>(I)){
				if(auto *BI = dyn_cast<BranchInst>(&I))	{
					if(BI->isConditional()){
						errs()<<*BI<< "\n";
						Value* condition = BI->getCondition();
						errs()<<"LLVM IR Value: "<<*condition<<"\n";
						if(auto *CI = dyn_cast<CmpInst>(condition)){
							llvm::CmpInst::Predicate pred= CI->getPredicate();
							errs() <<"Predicate: "<<pred<<"\n";
							errs() <<"Predicate Name: "<<CI->getPredicateName(pred)<<"\n";


							errs()<<"cmp inst: "<<*CI<<"\n";
							Value *lhs = CI->getOperand(0);
                                                        Value *rhs = CI->getOperand(1);
							errs()<<"value at left hand side: "<<*lhs<<"\n";
                                                        errs()<<"name of value at right hand side: "<<rhs->getName()<<"\n";
							errs()<<"value at right hand side: "<<*rhs<<"\n";
							//auto *op0 = CI->getOperand(0);
							//errs()<<"Operand 0: "<<op0->getName()<<"\n";

							//if (auto *LI = dyn_cast<StoreInst>(op0)) {
							//	for(auto op=LI->op_begin();op!=LI->op_end();op++){
							//		Value *v = op->get();
							//		StringRef name = v->getName();
							//		errs() << "* " << name << "\n";
							//	}
							//}
							
							//StringRef op_0 = CI->getOperand(0)->getValue
						}
					}
				}
				
				//if(isa<StoreInst>(&I)){
				//	for(auto op=I.op_begin();op!=I.op_end();op++){
				//		Value *v = op.get();
				//		StringRef name = v->getName();
				//	}
				//}

			}
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
