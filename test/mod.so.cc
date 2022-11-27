
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


#include "llvm/Passes/PassPlugin.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"



using namespace llvm;

namespace {

  class InjectFuncCall : public ModulePass {

    public:

      static char ID;
      InjectFuncCall() : ModulePass(ID) { }

      bool runOnModule(Module &M) override;

      // StringRef getPassName() const override {
      //  return "American Fuzzy Lop Instrumentation";
      // }

  };

}


char InjectFuncCall::ID = 0;

bool InjectFuncCall::runOnModule(Module &M) {
  bool InsertedAtLeastOnePrintf = false;

  auto &CTX = M.getContext();
  PointerType *PrintfArgTy = PointerType::getUnqual(Type::getInt8Ty(CTX));

  FunctionType *PrintfTy = FunctionType::get(
      IntegerType::getInt32Ty(CTX),
      PrintfArgTy,
      /*IsVarArgs=*/true);

  FunctionCallee Printf = M.getOrInsertFunction("printf", PrintfTy);
  
  
 //FunctionCallee Printf = M.getOrInsertFunction("printf", PrintfTy);

  // Set attributes as per inferLibFuncAttributes in BuildLibCalls.cpp
  Function *PrintfF = dyn_cast<Function>(Printf.getCallee());
  PrintfF->setDoesNotThrow();
  PrintfF->addParamAttr(0, Attribute::NoCapture);
  PrintfF->addParamAttr(0, Attribute::ReadOnly);


  // STEP 2: Inject a global variable that will hold the printf format string
  // ------------------------------------------------------------------------
  llvm::Constant *PrintfFormatStr = llvm::ConstantDataArray::getString(
      CTX, "Condition name: %s\n   number of arguments: %d\n");

  Constant *PrintfFormatStrVar =
      M.getOrInsertGlobal("PrintfFormatStr", PrintfFormatStr->getType());
  dyn_cast<GlobalVariable>(PrintfFormatStrVar)->setInitializer(PrintfFormatStr);

  // STEP 3: For each function in the module, inject a call to printf
  // ----------------------------------------------------------------
  for (auto &F : M) {
   // if (F.isDeclaration())
     // continue;
    //for(Function::iterator bb=F.begin();bb != F.end();bb++){
    for(auto &bb : F){
          errs()<<"BasicBlock name = "<<bb.getName()<<"\n";
          errs()<<"BasicBlock size = "<<bb.size()<<"\n";
  
          for(auto &I : bb){
                  if(auto *op = dyn_cast<BranchInst>(&I)){
                          IRBuilder<> Builder(op);
                          //Inject a global variable that contains the function name
                          //auto FuncName = Builder.CreateGlobalStringPtr("Function name");

                          Value* condition;
                          Value* false_dst;
                          Value* true_dst;

                          if (op->isConditional()) {
                              condition = op->getOperand(0);
                              false_dst = op->getOperand(1);
                              true_dst = op->getOperand(2);
                          } else {
                              condition = Builder.getInt32(1);
                              false_dst = op->getOperand(0);
                              true_dst = op->getOperand(0);
                          }


                           auto FuncName = Builder.CreateGlobalStringPtr(condition->getName());

                          llvm::Value *FormatStrPtr =
                              Builder.CreatePointerCast(PrintfFormatStrVar, PrintfArgTy, "formatStr");
                    
                                              // The following is visible only if you pass -debug on the command line
                          // *and* you have an assert build.
                          //LLVM_DEBUG(dbgs() << " Injecting call to printf inside " << F.getName() << "\n");

                          // Finally, inject a call to printf
                          Builder.CreateCall(Printf, {FormatStrPtr, FuncName, Builder.getInt32(F.arg_size())});
                  }
          }

    }
    // Get an IR builder. Sets the insertion point to the top of the function
    InsertedAtLeastOnePrintf = true;
  }

  return InsertedAtLeastOnePrintf;
}

//PreservedAnalyses InjectFuncCall::run(llvm::Module &M,
//                                       llvm::ModuleAnalysisManager &) {
//  bool Changed =  runOnModule(M);
//
//  return (Changed ? llvm::PreservedAnalyses::none()
//                  : llvm::PreservedAnalyses::all());
//}

//bool LegacyInjectFuncCall::runOnModule(llvm::Module &M) {
//  bool Changed = Impl.runOnModule(M);
//
//  return Changed;
//}
//char LegacyInjectFuncCall::ID = 0;
//
//
//static void registerLegacyInjectFuncCall(const PassManagerBuilder &, legacy::PassManagerBase &PM) {
//  PM.add(new LegacyInjectFuncCall());
//}
//static RegisterStandardPasses RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
//                 registerLegacyInjectFuncCall);




static void registerInjectFuncCallPass(const PassManagerBuilder &,
                            legacy::PassManagerBase &PM) {

  PM.add(new InjectFuncCall());

}


static RegisterStandardPasses RegisterInjectFuncCallPass(
    PassManagerBuilder::EP_ModuleOptimizerEarly, registerInjectFuncCallPass);

//static RegisterStandardPasses RegisterAFLPass0(
  //  PassManagerBuilder::EP_EnabledOnOptLevel0, registerAFLPass);
