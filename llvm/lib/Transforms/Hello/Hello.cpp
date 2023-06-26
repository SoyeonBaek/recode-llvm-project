//===- Hello.cpp - Example code from "Writing an LLVM Pass" ---------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements two versions of the LLVM "Hello World" pass described
// in docs/WritingAnLLVMPass.html
//
//===----------------------------------------------------------------------===//

#include "llvm/ADT/Statistic.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Dominators.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Transforms/Utils/ValueMapper.h"
#include "llvm/Pass.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/FileSystem.h"
#include <caml/mlvalues.h>
#include <caml/callback.h>
#include <caml/memory.h>
#include <caml/alloc.h>

#include <vector>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


using namespace llvm;
using namespace std;

static cl::opt<string> Input("i2", cl::desc("file to analyze"), cl::value_desc("filename to analyze"), cl::Required);
#define DEBUG_TYPE "hello"
STATISTIC(HelloCounter, "Counts number of functions greeted");


vector<BasicBlock&> v;

namespace {
  // Hello - The first implementation, without getAnalysisUsage.
  struct Hello : public FunctionPass {
    static char ID; // Pass identification, replacement for typeid
    Hello() : FunctionPass(ID) {}

    bool runOnFunction(Function &F) override {
        bool Changed = false;
          
        BasicBlock &entry = F.getEntryBlock ();
        v.push_back(entry);



        return Changed;
        
    }
  };
}


char Hello::ID = 0;
static RegisterPass<Hello> X("hello", "Hello World Pass");











namespace {
  // Hello2 - The second implementation with getAnalysisUsage implemented.
  struct Hello2 : public FunctionPass {
    static char ID; // Pass identification, replacement for typeid
    Hello2() : FunctionPass(ID) {}
      
    //call ocaml library function
    //find_nexts
    //remove later
      vector<int> find_nexts (string bb_name) {
          vector<int> v = {};
          if (bb_name == "%22")
            v = {1,3};
          if (bb_name == "%9")
            v = {4};
          if (bb_name == "%10")
            v = {4};    
          if (bb_name == "%16")
            v = {4,0};    
          if (bb_name == "%23")
            v = {5};    
          return v;
      }

    bool runOnFunction(Function &F) override {
      printf("53");
      
//       if (initialized == 0) {  
//       std::error_code ec;
//       std::string passName = sys::fs::getMainExecutable(ec).get();      
//       errs() << "init : " << Input.c_str() << "\n";

//       char *argv[] = { strdup(passName), strdup(Input.c_str()), "", "", NULL };

//       // // strcpy(arg[0], );
//       // strcpy(arg[0], "~/Soyeon/ollvm-12.x/build/lib/LLVMHello.dylib");s
//       // strcpy(arg[1], Input.c_str());
//       // arg[2] = NULL;


//       errs() << "set arg\n";

//       errs() << argv[0] << "\n";
//       errs() << argv[1] << "\n";
//       // errs() << arg[2] << "\n";

//       // strcpy(arg[0], "test.bc");
//       errs() << "init arg\n";
      
      
//       }
//       // static const value * find_nexts_func = NULL;
//       // find_nexts_func = caml_name_value("get_nexts");


//         vector<string> vtr = {"%9","%10","%16","%22","%23"};;
//         ValueToValueMapTy vmap;


//         //unrechable block 만들기
//         auto *unreachableBB = BasicBlock::Create(F.getContext(), "", &F, nullptr);
//         IRBuilder<> Builder(unreachableBB);
//         Builder.CreateUnreachable();


//         for (auto &BB : F) {
//           errs() << "find : " << BB.getNameOrAsOperand() << "\n";
//           BasicBlock *SwitchBB;
//           if (BB.getTerminator()->getOpcode() == Instruction::Switch)
//             SwitchBB = &BB;

//           auto it = find(vtr.begin(), vtr.end(), BB.getNameOrAsOperand());

//           if (it == vtr.end())
//             continue;
//           else
//             errs() << "found : " << BB.getNameOrAsOperand() << "\n";

//             //switch block 복사.
//             auto *NewBB = BasicBlock::Create(F.getContext(), "", &F, nullptr);
//             for (auto &I : *SwitchBB) {
// //                break;
//               auto *NewInst = I.clone();
//               if (I.isTerminator()) {
//                   SwitchInst *NewSI = cast<SwitchInst>(NewInst);
//                   for (auto Case = NewSI->case_begin(); Case != NewSI->case_end();) {
//                     vector<int> dest = find_nexts(BB.getNameOrAsOperand());
//                     auto i = find(dest.begin(), dest.end(), Case->getCaseValue()->getSExtValue());
//                     if (i == std::end(dest))
//                     {
//                       NewSI->removeCase(Case);
//                       NewSI->setDefaultDest(unreachableBB);
//                     }
//                     else{
//                       Case++;
//                     }

//                   }
//                 //default dest unrechable로 변경
                
//               }
//               vmap[&I] = NewInst;
//               llvm::RemapInstruction(NewInst, vmap,
//               RF_NoModuleLevelChanges | RF_IgnoreMissingLocals);
//                 NewBB->getInstList().push_back(NewInst);
//             }
//             auto term = BB.getTerminator();
//             IRBuilder<> Builder(BB.getTerminator());
//             Builder.CreateBr(NewBB);
//             term->eraseFromParent();

//         }
          return false;
    }
  };
}

char Hello2::ID = 0;
static RegisterPass<Hello2>
Y("hello2", "Hello World Pass (with getAnalysisUsage implemented)");

