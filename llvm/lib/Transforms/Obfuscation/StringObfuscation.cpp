#define DEBUG_TYPE "objdiv"
#include <string>
#include <strstream>

#include "llvm/ADT/Statistic.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/AbstractCallSite.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Obfuscation/CryptoUtils.h"
#include "llvm/Transforms/Obfuscation/StringObfuscation.h"
#include "llvm/IR/Instructions.h"

using namespace llvm;

STATISTIC(GlobalsEncoded, "Counts number of global variables encoded");

namespace llvm {

  
  class StringObfuscationPass: public llvm::ModulePass {
    public:
    static char ID; // pass identification
    bool is_flag = false;
    StringObfuscationPass() : ModulePass(ID) {}
    StringObfuscationPass(bool flag) : ModulePass(ID)
    {
      is_flag = flag;
    }

    virtual bool runOnModule(Module &M) override {
        if(!is_flag)
            return false;
    
        Function* funcToRemoved = NULL;

        for(auto& F : M) {
          const char *fname = F.getName().data();
          if(strcmp(fname, "main") == 0){
            funcToRemoved = &F;
            continue;
          }
        }

        if(funcToRemoved != NULL)
          funcToRemoved->eraseFromParent();
        return 0;
    }
  

  };

}

char StringObfuscationPass::ID = 0;
static RegisterPass<StringObfuscationPass> X("GVDiv", "Global variable (i.e., const char*) diversification pass", false, true);

Pass * llvm::createStringObfuscationPass(bool flag) {
    return new StringObfuscationPass(flag);
}
