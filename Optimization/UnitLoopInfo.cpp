#include "llvm/ADT/PostOrderIterator.h"
#include "llvm/IR/Dominators.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"


#include "UnitLoopInfo.h"

using namespace llvm;
using namespace cs426;
AnalysisKey UnitLoopAnalysis::Key;


/// Main function for running the Loop Identification analysis. This function
/// returns information about the loops in the function via the UnitLoopInfo
/// object


void printNestedLoops(Loop *L, unsigned depth) {
    for (unsigned i = 0; i < depth; ++i) {
        dbgs() << "--> ";
    }
    dbgs() << "Loop at depth " << depth << "\n";

    // 递归地打印子循环
    for (Loop *SubLoop : L->getSubLoops()) {
        printNestedLoops(SubLoop, depth + 1);
    }
}

void analyzeFunctionLoops(LoopInfo &LI) {
    for (Loop *L : LI) {
        // 只打印最顶层的循环
        if (L->getParentLoop() == nullptr) {
            printNestedLoops(L, 0);
        }
    }
}

void recur_forest(UnitLoopInfo& Loops, BasicBlock* curr_node, unsigned curr_level) {
  for (unsigned i = 0; i < curr_level; ++i) {
        dbgs() << "--> ";
  }
  dbgs() << "Loop at depth " << curr_level << "\n";
  for (auto children: Loops.forest[curr_node]) {
    recur_forest(Loops, children, curr_level + 1);
  }
}

void print_forest(UnitLoopInfo& Loops) {
  for (auto it: Loops.forest) {
    if (Loops.header_to_parent.find(it.first) == Loops.header_to_parent.end()) {
      recur_forest(Loops, it.first, 0);
    }
  }
}

// check whether exists a path from curr->one latch inside latches without getting through header
// simple BFS
bool is_inside_loop(DominatorTree &DT, BasicBlock* header, DenseSet<BasicBlock*>& latches, BasicBlock* curr) {
  // trivial case that the curr node itself is header or latch
  if (curr == header) return true;
  if (latches.find(curr) != latches.end()) return true; // itself is the latch

  // precolor for the basic block we are checking for
  DenseSet<BasicBlock*> color;
  color.insert(curr);
  std::queue<BasicBlock*> q;
  q.push(curr);

  while (!q.empty()) {
    auto current_block = q.front();
    q.pop();

    for (auto iter = succ_begin(current_block); iter != succ_end(current_block); ++ iter) {
      if (*iter != header && DT.dominates(header, *iter)) {
        if (color.find(*iter) == color.end()) {
          color.insert(*iter);
          q.push(*iter);
          if (latches.find(*iter) != latches.end()) { // fins inside the latches
            return true;
          }
        }
      }
    }
  }

  return false;
}

// build the loop forest: header -----> set of the closest loop header without itself
// for example, A contains B C D E F, B contains D, C contains E F, the forest will be:
//  A -> B, C; B -> D; C -> E, F
// curr itself must be the header
void build_forest(DenseSet<BasicBlock*>& headers, UnitLoopInfo& Loops, BasicBlock* curr) {
  Loops.forest[curr] = DenseSet<BasicBlock*>();
  for (auto child: Loops.header_to_body[curr]) {
    if (headers.find(child) != headers.end() && child != curr) {
      Loops.forest[curr].insert(child);
    }
  }
  for (auto child: Loops.header_to_body[curr]) {
    if (headers.find(child) != headers.end() && child != curr) {
      for (auto grand_child: Loops.header_to_body[child]) {
        if (headers.find(grand_child) != headers.end() && grand_child != child) {
          Loops.forest[curr].erase(grand_child);
        }
      }
    }
  }
  for (auto child: Loops.forest[curr]) {
    Loops.header_to_parent[child] = curr;
  }
}

UnitLoopInfo UnitLoopAnalysis::run(Function &F, FunctionAnalysisManager &FAM) {
  dbgs() << "UnitLoopAnalysis running on " << F.getName() << "\n";
  // Acquires the Dominator Tree constructed by LLVM for this function. You may
  // find this useful in identifying the natural loops
  DominatorTree &DT = FAM.getResult<DominatorTreeAnalysis>(F);
  LoopInfo& LLVM_LOOPINFO = FAM.getResult<LoopAnalysis>(F);
  
  
  UnitLoopInfo Loops;
  // Fill in appropriate information

  // Traverse the CFG to find edges (src, dst) such that the source BB src is dominated by the destination BB dst  
  for (DomTreeNode* Node: post_order(DT.getRootNode())) {
    BasicBlock *BB = Node->getBlock();
    std::vector<BasicBlock*> BackEdges;
    for (BasicBlock* Pred: predecessors(BB)) if (DT.dominates(BB, Pred)) BackEdges.push_back(Pred);
    if (BackEdges.size() > 0) {
      // TODO: Add the loop (contains dst and all nodes that can reach src from dst) to the list
      // building the loop latch
      for (BasicBlock* latches: BackEdges) {
        Loops.header_to_latch[BB].insert(latches);
      }
    }
  }

  // building the loop body
  for (auto header_iter: Loops.header_to_latch) {
    SmallVector<BasicBlock*, 5> all_dominate_children;
    DT.getDescendants(header_iter.first, all_dominate_children);
    for (llvm::BasicBlock* dominate_children_block: all_dominate_children) {
      if (is_inside_loop(DT, header_iter.first, header_iter.second, dominate_children_block)) {
        Loops.header_to_body[header_iter.first].insert(dominate_children_block);
      }
    }
  }

  // setting up the exiting 
  for (auto header_iter: Loops.header_to_body) {
    for (auto body_block: header_iter.second) {
      for (auto body_block_succ_iter = succ_begin(body_block); body_block_succ_iter != succ_end(body_block); ++ body_block_succ_iter) {
        // if one of the loop body block contains a successor which does not belong to the loop body, can not find
        // existing edge: existing block(inside) -> exit block(outside)
        if (header_iter.second.find(*body_block_succ_iter) == header_iter.second.end()) { 
          Loops.header_to_exiting[header_iter.first].insert(body_block);
        }
      }
    }
  }

  // setting up the forest
  DenseSet<BasicBlock*> headers;
  for (auto header_iter: Loops.header_to_body) {
    headers.insert(header_iter.first);
  }
  for (auto header_iter: headers) {
    build_forest(headers, Loops, header_iter);
  }
  for (auto it: Loops.header_to_body) {
    int count = 0;
    for (auto itt: it.second) {
      if (headers.find(itt) != headers.end() && itt != it.first) {
        count ++;
      }
    }
    dbgs() << "Nested count is: " << count << "\n";
  }

  //
  dbgs() << "-----------------SELF--------------\n"; 
  print_forest(Loops);
  dbgs() << "\n-----------------SELF------------\n";  

  dbgs() << "-----------------LLVM--------------\n"; 
  analyzeFunctionLoops(LLVM_LOOPINFO);
  dbgs() << "\n-----------------LLVM------------\n"; 

  return Loops;
}



