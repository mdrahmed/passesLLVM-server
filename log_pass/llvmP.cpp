#include <unordered_set>
#include <unordered_map>
#include <sstream>

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

namespace{

	class CPS : public ModulePass{
		
		public:
			static char ID;
			CPS() : ModulePass(ID){ }

			bool runOnModule(Module &M) override;
		
	};

}


char CPS::ID = 0;


bool CPS::runOnModule(Module &M){
	
	LLVMContext &context = M.getContext();
	Type *intType = Type::getInt32Ty(context);
	
} 


