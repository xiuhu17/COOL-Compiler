## COOL-Compiler
Realize a Compiler for COOL language

### Front End(Scanner&Parser): MP1_Handout
- Implement Scanner, use Flex as scanner generator to generate scanner which supports Error Detector. 
- Implement Parser, use Bison as parser generator to generate scanner which supports Error Recovery.

### Middle End(CodeGen): MP2_Handout & MP3_Handout
- Implement Intermediate Code Generation phase of the compiler: Under Type Checking and Access Control in Semantic Analysis, use AST data structure built in Parser stage and LLVM MiddleEnd API(Context, Module, IRBuilder, Function, Opaque Pointer...) to generate LLVM three-address assembly code.
- With the Runtime Library, the LLVM IR generator supports full language features:
  - Inheritance, Virtual Function, Polymorphism(classes, objects) 
  - Type Conformation, Boxing/Unboxing(support harware acceleration)
  - Runtime Error Handling
  - Run-time Garbage Collection using Mark-and-Sweep algorithm.

### Back End(RegAlloc): MP4_Handout
  - Implement Register Allocation, using a Greedy and BasicBlock Level Local allocation algorithm, with predicting potential storing and loading. Implement using LLVM BackEnd API(TargetRegisterInfo, MachineBasicblock, MachineRegisterInfo ...).
