## COOL-Compiler
Implement a Compiler for COOL language which is an imperative, object-oriented, type safe language that is a model of the Java language. (COOL Program ---> X86 Assembly)

### Front End(Scanner&Parser):
- Implement Scanner, use Flex as scanner generator to generate scanner which supports Error Detector. 
- Implement Parser, use Bison as parser generator to generate cpp parser which supports Error Recovery.

### Middle End(CodeGen):
- Implement IR Code Generation. Under Semantic Analysis, use AST data structure built in Parser stage and LLVM MiddleEnd API to generate LLVM three-address assembly code.
- With the Runtime Library, the LLVM IR generator supports full language features:
  - Inheritance, Virtual Function, Polymorphism(classes, objects) 
  - Type Conformation, Boxing/Unboxing(support harware acceleration)
  - Runtime Error Handling
  - Run-time Garbage Collection using Mark-and-Sweep algorithm.

### Back End(RegAlloc):
  - Implement Register Allocation, using a Greedy and BasicBlock Level Local allocation algorithm, optimized with storing register live across function-calls into callee-saved. Implement using LLVM BackEnd API(TargetRegisterInfo, MachineBasicblock, MachineRegisterInfo ...).

## Analysis & Transformation(Optimization)
  - Implement Loop Identification
  - Implement Loop Invariant Code Motion(LICM)
  - Implement Conditional Constant Propagation(SCCP)
  - Implement Scalar Expansion, also supports expanding small C struct array
  - Implement Mem2Reg

