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
#include "llvm/Transforms/Utils/Cloning.h"


#include <vector>
#include <tuple>
#include <set>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


using namespace llvm;
using namespace std;

static cl::opt<string> Input("i2", cl::desc("file to analyze"), cl::value_desc("filename to analyze"), cl::Required);

vector<tuple<BasicBlock*, string, string>> v;
set<string> s;

namespace {
  struct Deob : public FunctionPass {
    static char ID;
    Deob() : FunctionPass(ID) {}

    bool has_ctxt(BasicBlock* bb, string ctxt)
    {
      return true;
    }

    template<typename T>
    void pop_front(vector<T> &v)
    {
      if (v.size() > 0) {
        v.erase(v.begin());
      }
    }

    string find_next_ctxt (string bb_name, string ctxt){

      return "";
    }

    BasicBlock* clone (BasicBlock* bb)
    {
      ValueToValueMapTy vmap;
      return CloneBasicBlock(bb, vmap);
    }

	bool runOnFunction(Function &F) override 
	{
	  //insert tuple <cloned_entry_bb, entry_ctxt> into queue
	  BasicBlock *entry_bb = clone(&F.getEntryBlock());
	  string entry_ctxt = "";
	  tuple<BasicBLock*, string> t(entry_bb, entry_ctxt, &F.getEntryBlock().getName());
	  v.push_back(t);


	  //loop until the queue empty
	  while(v.empty())
	  {
		//pop current bb and ctxt from queue
		tuple<BasicBlock*, string, string> t = v.front();
		pop_front(v);
		//current bb
		BasicBlock* bb = get<0>(t);
		//current ctxt
		auto ctxt = get<1>(t);


		//continue if the current_bb already visited
		//should check original bb not cloned one
		if(s.find(get<2>(t)) != s.end())
		  continue;
		s.insert(get<2>(t));
		
		


		//search next_bbs of the current_bb
		Instruction* i = bb->getTerminator();
		int n = i->getNumSuccessors();
		for (int k = 0; k < n; k++)
		{
		  BasicBlock* bb_next = i->getSuccessor(n);
		  bool flag = false;
	  
		  //if <bb_next, current_ctxt> exist
		  //clone bb_next and insert as a successor of the current_bb
		  //and push it into the queue
		  if(has_ctxt(bb_next, ctxt))
		  {
			BasicBlock* next = clone(bb_next);
			i->setTerminator(k, next);
			tuple<BasicBlock*, string, string> t(next, ctxt, bb_next.getName());
			v.push_back(t);
			flag = true;
		  }
		}
		
		//if no <bb_next, current_ctxt> matched
		//get next_ctxt via abstract memory
		if(!flag)
		{
		  
		}
		

	  }
	  


	  

	  return true;
	}

char Deob::ID = 0;
static RegisterPass<Deob> X("deob", "Flattened bitcode deobfuscating Pass");




    bool runOnFunction(Function &F) override {
      bool Changed = false;

      //<entry block, entry ctxt> queue에 넣음          
      BasicBlock *entry_bb = clone(&F.getEntryBlock());
      string entry_ctxt = "";
      tuple<BasicBlock*, string> t(entry_bb, entry_ctxt);
      v.push_back(t);

      

      //queue가 빌 때까지 반복.
      while(v.empty()){
        tuple<BasicBlock*, string> t = v.front();
        pop_front(v);
        BasicBlock* bb = get<0>(t);
        auto ctxt = get<1>(t);


        //다음 basicblock들 탐색.
        Instruction* i = bb->getTerminator();
        int n = i->getNumSuccessors();
        for (int k = 0; k< n; k++)
        {
          BasicBlock* bb_next = i->getSuccessor(n);
          bool flag = false;

          //현재 ctxt와 동일한 ctxt를 갖은 bb를 연결(= )
          if(has_ctxt(bb_next, ctxt))
          {
            BasicBlock* next = clone(bb_next);
            tuple<BasicBlock*, string> t(next, ctxt);
            i->setSuccessor(k, next);
            //연결한 bb들(그때의 ctxt)를 queue에 추가
            v.push_back(t);
            flag = true;
          }
          //bb clone 후 동일한 ctxt가 없는 bb와 연결 끊기
          else {
            
          }

          //동일한 ctxt가 아예 없는 경우 -> memory에서 switch 변수를 확인하여 변경된 ctxt 예측 후 연결
          if (!flag)
          {
            string ctxt_ = find_next_ctxt(bb);
            if(has_ctxt(bb_next, ctxt_))
            {
              BasicBlock* next = clone(bb_next);
              tuple<BasicBlock*, string> t(next, ctxt_);
              //연결한 bb들(그때의 ctxt)를 queue에 추가
              v.push_back(t);
            }
          }
        }

      }



      return Changed;
        
    }
  };
}













//    bool runOnFunction(Function &F) override {
//      printf("53");
      
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
