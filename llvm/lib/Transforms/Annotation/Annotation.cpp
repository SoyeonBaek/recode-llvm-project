#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/DynamicLibrary.h"
#include "llvm/IR/InstIterator.h"
#include <algorithm>
#include <set>
#include <vector>

using namespace llvm;

namespace {
struct Annotation : public ModulePass {
   static char ID;
   Annotation() : ModulePass(ID) {}

   bool runOnModule(Module &M) override {
   // Set to keep track of the variables that have been annotated
   std::set<Value*> annotatedVars;
   // Set to keep track of the functions that use the annotated variables
   std::set<Function*> usingFunctions;

   // Load the shared library
   std::string error;
//   sys::DynamicLibrary lib = sys::DynamicLibrary::getPermanentLibrary("./libexample.so", &error);
//   if (!lib.isValid()) {
//      errs() << "Error loading shared library: " << error << "\\n";
//      return false;
//   }

   // Get the address of the "foo" function
//   void *foo_address = lib.getAddressOfSymbol("foo");
//   if (!foo_address) {
//   errs() << "Error getting address of symbol 'foo': " << error << "\\n";
//   return false;
//   }

   //std::vector<Instruction*> worklist;
   for (auto &F : M) {
      // Iterate over all functions in the module
      for (auto &BB : F) {
         for (auto &I : BB) {
            // Check if the instruction is a call instruction
            if (auto *CI = dyn_cast<CallInst>(&I)) {
               // Get the called function
               Function *Callee = CI->getCalledFunction();
               if (!Callee) continue;
               if (CI->getNumArgOperands()>=2){
                  if(ConstantExpr *pCE = dyn_cast<ConstantExpr>(CI->getArgOperand(1))){
                     errs() << *pCE << "\n";
                     if(GlobalVariable *pGV = dyn_cast<GlobalVariable>(pCE->getOperand(0))){
                        errs() << *(pGV->getOperand(0)) << "\n";
                        StringRef SR = cast<ConstantDataArray>(pGV->getOperand(0))->getAsCString();
                        if(SR.contains("secret")){
                           errs() << "Found!!\n";
                         errs() << "Current Function : " << I.getFunction()->getName() << "\n";
                          errs() << "function name: " << CI->getCalledFunction()->getName() << "\n";
                           errs() << "find annotation operand 0: " << *(CI->getArgOperand(0)) << "\n";
                           Instruction *inst = dyn_cast<Instruction>(CI->getArgOperand(0));
                           errs() << "find annotation operand 0: " << inst->getOperand(0)->getName() << "\n";
                        }
                     }
                  }
               }
            }
         }
      }
   }

   return false;
   }
};

}

char Annotation::ID = 0;
static RegisterPass<Annotation> X("annotation", "Annotation Pass", false, false);
