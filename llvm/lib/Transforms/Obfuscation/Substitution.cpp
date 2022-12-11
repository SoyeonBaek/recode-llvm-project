//===- Substitution.cpp - Substitution Obfuscation
// pass-------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements operators substitution's pass
//
//===----------------------------------------------------------------------===//
#include "llvm/IR/Dominators.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Transforms/Obfuscation/Substitution.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Obfuscation/Utils.h"
#include "llvm/IR/Intrinsics.h"

#include "llvm/Pass.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/raw_ostream.h"

#include <fstream>
#include <iostream>

using namespace std;
using namespace llvm;


namespace llvm {

class Substitution : public llvm::FunctionPass {
  public :
  static char ID; // Pass identification, replacement for typeid
  bool flag;
    string testFunc;

  Substitution() : FunctionPass(ID) {}
  Substitution(bool flag, string testFunc) : FunctionPass(ID) {
    this->flag = flag;
      this->testFunc = testFunc;
  }
    
   virtual bool runOnFunction(Function &F) override{
       // Check if the percentage is correct
        if(!flag)
            return false;


          string filePath = F.getParent()->getSourceFileName();
          const char* fname = F.getName().data();
          
          printf("%s %s %s : ", testFunc.c_str(), fname,F.getParent()->getSourceFileName().c_str());
          if(strcmp(fname, testFunc.c_str()) != 0){
              printf("pass\n");
              return 0;
          }
          
          ofstream writeFile;
          writeFile.open(filePath.data(), std::ios_base::out | std::ios_base::app);
          if( writeFile.is_open()){
            writeFile << "\n#include <stddef.h>\n#include <stdint.h>\nint LLVMFuzzerTestOneInput(const uint32_t *Data, size_t Size) {\n";
          }

          FunctionType* func_type = F.getFunctionType();
          writeFile << "  int* iData = Data;\n";
          writeFile << "  if(Size == " << func_type->getNumParams() * 4 << ") {\n";
          writeFile << "    " << fname << "(";

          if (func_type->getNumParams() > 0)
            if(func_type->getParamType(0)->getTypeID() == 13)
              writeFile << "*iData";
            
          for(int i = 1; i < func_type->getNumParams(); i++) {
            if(func_type->getParamType(i)->getTypeID() == 13)
              writeFile << ", *(iData+" << i;
          }
          
          if (func_type->getNumParams() > 1)
            writeFile << ")";
          writeFile << ");\n  }\n";
          writeFile << "}\n";

        

        return 0;
    }


};
}


char Substitution::ID = 0;
static RegisterPass<Substitution> X("substitution", "operators substitution", false, true);
Pass *llvm::createSubstitutionPass() { return new Substitution(true, "error"); }
Pass *llvm::createSubstitutionPass(bool flag, string testFunc) { return new Substitution(flag, testFunc); }
