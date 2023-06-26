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

#include "llvm/Transforms/Obfuscation/Substitution.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Obfuscation/Utils.h"
#include "llvm/IR/Intrinsics.h"

#include "llvm/IR/Function.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Pass.h"
#include <iostream>

using namespace llvm;
using namespace std;


namespace {

struct Substitution : public FunctionPass {
  static char ID; // Pass identification, replacement for typeid
  

  Substitution() : FunctionPass(ID) {}

  Substitution(bool flag) : FunctionPass(ID) {
  }

  bool runOnFunction(Function &F);

};
}

bool Substitution::runOnFunction(Function &F) {
   
    for (BasicBlock &BB : F) {
        errs() << "  BasicBlock " << BB.getName() << "\n";
    }
  
  return true;
}


char Substitution::ID = 0;
static RegisterPass<Substitution> X("substitution", "operators substitution");
Pass *llvm::createSubstitutionPass() { return new Substitution(true); }
Pass *llvm::createSubstitutionPass(bool flag) { return new Substitution(flag); }
