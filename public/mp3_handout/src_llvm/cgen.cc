/*********************************************************************
 Intermediate code generator for COOL: SKELETON

 Read the comments carefully and add code to build an LLVM program
*********************************************************************/

#define EXTERN
#include "cgen.h"
#include <sstream>
#include <string>
#include <llvm/Support/FileSystem.h>

extern int cgen_debug, curr_lineno;
using namespace llvm;

/*********************************************************************
 For convenience, a large number of symbols are predefined here.
 These symbols include the primitive type and method names, as well
 as fixed names used by the runtime system. Feel free to add your
 own definitions as you see fit.
*********************************************************************/
EXTERN Symbol
    // required classes
    Object,
    IO, String, Int, Bool, Main,

    // class methods
    cool_abort, type_name, cool_copy, out_string, out_int, in_string, in_int,
    length, concat, substr,

    // class members
    val,

    // special symbols
    No_class,  // symbol that can't be the name of any user-defined class
    No_type,   // If e : No_type, then no code is generated for e.
    SELF_TYPE, // Special code is generated for new SELF_TYPE.
    self,      // self generates code differently than other references

    // extras
    arg, arg2, newobj, Mainmain, prim_string, prim_int, prim_bool;

// Initializing the predefined symbols.
static void initialize_constants(void) {
  Object = idtable.add_string("Object");
  IO = idtable.add_string("IO");
  String = idtable.add_string("String");
  Int = idtable.add_string("Int");
  Bool = idtable.add_string("Bool");
  Main = idtable.add_string("Main");

  cool_abort = idtable.add_string("abort");
  type_name = idtable.add_string("type_name");
  cool_copy = idtable.add_string("copy");
  out_string = idtable.add_string("out_string");
  out_int = idtable.add_string("out_int");
  in_string = idtable.add_string("in_string");
  in_int = idtable.add_string("in_int");
  length = idtable.add_string("length");
  ::concat = idtable.add_string("concat");
  substr = idtable.add_string("substr");

  val = idtable.add_string("val");

  No_class = idtable.add_string("_no_class");
  No_type = idtable.add_string("_no_type");
  SELF_TYPE = idtable.add_string("SELF_TYPE");
  self = idtable.add_string("self");

  arg = idtable.add_string("arg");
  arg2 = idtable.add_string("arg2");
  newobj = idtable.add_string("_newobj");
  Mainmain = idtable.add_string("main");
  prim_string = idtable.add_string("sbyte*");
  prim_int = idtable.add_string("int");
  prim_bool = idtable.add_string("bool");
}

/*********************************************************************

  CgenClassTable methods

*********************************************************************/

// CgenClassTable constructor orchestrates all code generation
CgenClassTable::CgenClassTable(Classes classes)
    : nds(), current_tag(0), context(), builder(this->context),
      the_module("module", this->context) {
  if (cgen_debug)
    std::cerr << "Building CgenClassTable" << std::endl;
  // Make sure we have a scope, both for classes and for constants
  enterscope();

  // Create an inheritance tree with one CgenNode per class.
  install_basic_classes();
  install_classes(classes);
  build_inheritance_tree();

  // First pass
  setup();

  // Second pass
  code_module();
  // Done with code generation: exit scopes
  exitscope();
}

// Creates AST nodes for the basic classes and installs them in the class list
void CgenClassTable::install_basic_classes() {
  // The tree package uses these globals to annotate the classes built below.
  curr_lineno = 0;
  Symbol filename = stringtable.add_string("<basic class>");

  //
  // A few special class names are installed in the lookup table but not
  // the class list. Thus, these classes exist, but are not part of the
  // inheritance hierarchy.

  // No_class serves as the parent of Object and the other special classes.
  Class_ noclasscls = class_(No_class, No_class, nil_Features(), filename);
  install_special_class(new CgenNode(noclasscls, CgenNode::Basic, this));
  delete noclasscls;

#ifdef MP3
  // SELF_TYPE is the self class; it cannot be redefined or inherited.
  Class_ selftypecls = class_(SELF_TYPE, No_class, nil_Features(), filename);
  install_special_class(new CgenNode(selftypecls, CgenNode::Basic, this));
  delete selftypecls;
  //
  // Primitive types masquerading as classes. This is done so we can
  // get the necessary Symbols for the innards of String, Int, and Bool
  //
  Class_ primstringcls =
      class_(prim_string, No_class, nil_Features(), filename);
  install_special_class(new CgenNode(primstringcls, CgenNode::Basic, this));
  delete primstringcls;
#endif
  Class_ primintcls = class_(prim_int, No_class, nil_Features(), filename);
  install_special_class(new CgenNode(primintcls, CgenNode::Basic, this));
  delete primintcls;
  Class_ primboolcls = class_(prim_bool, No_class, nil_Features(), filename);
  install_special_class(new CgenNode(primboolcls, CgenNode::Basic, this));
  delete primboolcls;
  //
  // The Object class has no parent class. Its methods are
  //    cool_abort() : Object    aborts the program
  //    type_name() : Str        returns a string representation of class name
  //    copy() : SELF_TYPE       returns a copy of the object
  //
  // There is no need for method bodies in the basic classes---these
  // are already built in to the runtime system.
  //
  Class_ objcls = class_(
      Object, No_class,
      append_Features(
          append_Features(single_Features(method(cool_abort, nil_Formals(),
                                                 Object, no_expr())),
                          single_Features(method(type_name, nil_Formals(),
                                                 String, no_expr()))),
          single_Features(
              method(cool_copy, nil_Formals(), SELF_TYPE, no_expr()))),
      filename);
  install_class(new CgenNode(objcls, CgenNode::Basic, this));
  delete objcls;

  //
  // The Int class has no methods and only a single attribute, the
  // "val" for the integer.
  //
  Class_ intcls = class_(
      Int, Object, single_Features(attr(val, prim_int, no_expr())), filename);
  install_class(new CgenNode(intcls, CgenNode::Basic, this));
  delete intcls;

  //
  // Bool also has only the "val" slot.
  //
  Class_ boolcls = class_(
      Bool, Object, single_Features(attr(val, prim_bool, no_expr())), filename);
  install_class(new CgenNode(boolcls, CgenNode::Basic, this));
  delete boolcls;

#ifdef MP3
  //
  // The class String has a number of slots and operations:
  //       val                                  the string itself
  //       length() : Int                       length of the string
  //       concat(arg: Str) : Str               string concatenation
  //       substr(arg: Int, arg2: Int): Str     substring
  //
  Class_ stringcls =
      class_(String, Object,
             append_Features(
                 append_Features(
                     append_Features(
                         single_Features(attr(val, prim_string, no_expr())),
                         single_Features(
                             method(length, nil_Formals(), Int, no_expr()))),
                     single_Features(method(::concat,
                                            single_Formals(formal(arg, String)),
                                            String, no_expr()))),
                 single_Features(
                     method(substr,
                            append_Formals(single_Formals(formal(arg, Int)),
                                           single_Formals(formal(arg2, Int))),
                            String, no_expr()))),
             filename);
  install_class(new CgenNode(stringcls, CgenNode::Basic, this));
  delete stringcls;
#endif

#ifdef MP3
  //
  // The IO class inherits from Object. Its methods are
  //        out_string(Str) : SELF_TYPE          writes a string to the output
  //        out_int(Int) : SELF_TYPE               "    an int    "  "     "
  //        in_string() : Str                    reads a string from the input
  //        in_int() : Int                         "   an int     "  "     "
  //
  Class_ iocls = class_(
      IO, Object,
      append_Features(
          append_Features(
              append_Features(
                  single_Features(method(out_string,
                                         single_Formals(formal(arg, String)),
                                         SELF_TYPE, no_expr())),
                  single_Features(method(out_int,
                                         single_Formals(formal(arg, Int)),
                                         SELF_TYPE, no_expr()))),
              single_Features(
                  method(in_string, nil_Formals(), String, no_expr()))),
          single_Features(method(in_int, nil_Formals(), Int, no_expr()))),
      filename);
  install_class(new CgenNode(iocls, CgenNode::Basic, this));
  delete iocls;
#endif
}

// install_classes enters a list of classes in the symbol table.
void CgenClassTable::install_classes(Classes cs) {
  for (auto cls : cs) {
    install_class(new CgenNode(cls, CgenNode::NotBasic, this));
  }
}

// Add this CgenNode to the class list and the lookup table
void CgenClassTable::install_class(CgenNode *nd) {
  Symbol name = nd->get_name();
  if (!this->find(name)) {
    // The class name is legal, so add it to the list of classes
    // and the symbol table.
    nds.push_back(nd);
    this->insert(name, nd);
  }
}

// Add this CgenNode to the special class list and the lookup table
void CgenClassTable::install_special_class(CgenNode *nd) {
  Symbol name = nd->get_name();
  if (!this->find(name)) {
    // The class name is legal, so add it to the list of special classes
    // and the symbol table.
    special_nds.push_back(nd);
    this->insert(name, nd);
  }
}

// CgenClassTable::build_inheritance_tree
void CgenClassTable::build_inheritance_tree() {
  for (auto node : nds)
    set_relations(node);
}

// CgenClassTable::set_relations
// Takes a CgenNode and locates its, and its parent's, inheritance nodes
// via the class table. Parent and child pointers are added as appropriate.
//
void CgenClassTable::set_relations(CgenNode *nd) {
  Symbol parent = nd->get_parent();
  auto parent_node = this->find(parent);
  if (!parent_node) {
    throw std::runtime_error("Class " + nd->get_name()->get_string() +
                             " inherits from an undefined class " +
                             parent->get_string());
  }
  nd->set_parent(parent_node);
}

// Sets up declarations for extra functions needed for code generation
// You should not need to modify this code for MP2
void CgenClassTable::setup_external_functions() {
  Type *i32 = Type::getInt32Ty(this->context),
       *i8_ptr = Type::getInt8PtrTy(this->context),
       *void_ = Type::getVoidTy(this->context);
  // setup function: external int strcmp(sbyte*, sbyte*)
  create_llvm_function("strcmp", i32, {i8_ptr, i8_ptr}, false);
  // setup function: external int printf(sbyte*, ...)
  create_llvm_function("printf", i32, {i8_ptr}, true);
  // setup function: external void abort(void)
  create_llvm_function("abort", void_, {}, false);
  // setup function: external i8* malloc(i32)
  create_llvm_function("malloc", i8_ptr, {i32}, false);

#ifdef MP3
  // TODO: add code here
#endif
}

void CgenClassTable::setup_classes(CgenNode *c, int depth) {
  c->setup(current_tag++, depth);
  for (auto child : c->get_children()) {
    setup_classes(child, depth + 1);
  }
  c->set_max_child(current_tag - 1);
}

// The code generation first pass. Define these two functions to traverse
// the tree and setup each CgenNode
void CgenClassTable::setup() {
  setup_external_functions();
  setup_classes(root(), 0);
}

// The code generation second pass. Add code here to traverse the tree and
// emit code for each CgenNode
void CgenClassTable::code_module() {
  code_constants();

#ifndef MP3
  // This must be after code_constants() since that emits constants
  // needed by the code() method for expressions
  CgenNode *mainNode = getMainmain(root());
  mainNode->codeGenMainmain();
#endif
  code_main();

#ifdef MP3
  code_classes(root());
#endif
}

#ifdef MP3
void CgenClassTable::code_classes(CgenNode *c) {
  // TODO: add code here
}
#endif

// Create global definitions for constant Cool objects
void CgenClassTable::code_constants() {
#ifdef MP3
  // TODO: add code here
#endif
}

// Create LLVM entry point. This function will initiate our Cool program
// by generating the code to execute (new Main).main()
//
void CgenClassTable::code_main(){

  Type *i32 = Type::getInt32Ty(this->context),
       *i8_ptr = Type::getInt8PtrTy(this->context);

  llvm::StringRef Main_main_str = "Main.main() returned %d\x0A\x00";
  auto Main_main_val = this->builder.CreateGlobalString(Main_main_str, "main.printout.str", 0, &the_module);

  auto main_func = create_llvm_function("main", i32, {}, false);
  auto main_entry_block = llvm::BasicBlock::Create(context, "entry", main_func); // function tie with block
  builder.SetInsertPoint(main_entry_block);  // irbuilder tie with block
  
  auto Main_main_tp = FunctionType::get(i32, {}, false);
  auto Main_main_callee = the_module.getOrInsertFunction("Main.main", Main_main_tp);
  auto Main_main_ret = builder.CreateCall(Main_main_callee);

  auto Main_main_str_ptr_tp = ArrayType::get(Type::getInt8Ty(this->context), 25);
  auto ele_ptr = this->builder.CreateConstGEP2_32(Main_main_str_ptr_tp, Main_main_val, 0, 0);
  
  auto printf_tp = FunctionType::get(i32, {i8_ptr}, true);
  auto printf_callee = the_module.getOrInsertFunction("printf", printf_tp);
  builder.CreateCall(printf_callee, {ele_ptr, Main_main_ret});

  builder.CreateRet(ConstantInt::get(Type::getInt32Ty(this->context), 0));
#ifdef MP3
// MP3
#else
// MP2
// Get the address of the string "Main_main() returned %d\n" using
// getelementptr

// Call printf with the string address of "Main_main() returned %d\n"
// and the return value of Main_main() as its arguments

// Insert return 0
#endif
}

// Get the root of the class tree.
CgenNode *CgenClassTable::root() {
  auto root = this->find(Object);
  if (!root) {
    throw std::runtime_error("Class Object is not defined.");
  }
  return root;
}

#ifndef MP3
// Special-case functions used for the method Int Main::main() for
// MP2 only.
CgenNode *CgenClassTable::getMainmain(CgenNode *c) {
  if (c && !c->basic())
    return c; // Found it!
  for (auto child : c->get_children()) {
    if (CgenNode *foundMain = this->getMainmain(child))
      return foundMain; // Propagate it up the recursive calls
  }
  return 0; // Make the recursion continue
}
#endif

Function *CgenClassTable::create_llvm_function(const std::string &funcName,
                                               Type *retType,
                                               ArrayRef<Type *> argTypes,
                                               bool isVarArgs) {
  assert(retType);
  FunctionType *ft = FunctionType::get(retType, argTypes, isVarArgs);
  Function *func = Function::Create(ft, Function::ExternalLinkage, funcName,
                                    this->the_module);
  if (!func) {
    errs() << "Function creation failed for function " << funcName;
    llvm_unreachable("Function creation failed");
  }
  return func;
}

/*********************************************************************

  StrTable / IntTable methods

 Coding string, int, and boolean constants

 Cool has three kinds of constants: strings, ints, and booleans.
 This section defines code generation for each type.

 All string constants are listed in the global "stringtable" and have
 type stringEntry. stringEntry methods are defined both for string
 constant definitions and references.

 All integer constants are listed in the global "inttable" and have
 type IntEntry. IntEntry methods are defined for Int constant references only.

 Since there are only two Bool values, there is no need for a table.
 The two booleans are represented by instances of the class BoolConst,
 which defines the definition and reference methods for Bools.

*********************************************************************/

// Create definitions for all String constants
void StrTable::code_string_table(std::ostream &s, CgenClassTable *ct) {
  for (auto &[_, entry] : this->_table) {
    entry.code_def(s, ct);
  }
}

// generate code to define a global string constant
void StringEntry::code_def(std::ostream &s, CgenClassTable *ct) {
#ifdef MP3
  // TODO: add code here
#endif
}

/*********************************************************************

  CgenNode methods

*********************************************************************/

//
// Class setup. You may need to add parameters to this function so that
// the classtable can provide setup information (such as the class tag
// that should be used by this class).
//
// Things that setup should do:
//  - layout the features of the class
//  - create the types for the class and its vtable
//  - create global definitions used by the class such as the class vtable
//
void CgenNode::setup(int tag, int depth) {
  this->tag = tag;
#ifdef MP3
  layout_features();

  // TODO: add code here

#endif
}

#ifdef MP3
// Laying out the features involves creating a Function for each method
// and assigning each attribute a slot in the class structure.
void CgenNode::layout_features() {
  // TODO: add code here
}

// Class codegen. This should performed after every class has been setup.
// Generate code for each method of the class.
void CgenNode::code_class() {
  // No code generation for basic classes. The runtime will handle that.
  if (basic()) {
    return;
  }
  // TODO: add code here
}

void CgenNode::code_init_function(CgenEnvironment *env) {
  // TODO: add code here
}

#else

// code-gen function main() in class Main
void CgenNode::codeGenMainmain() {
  // In Phase 1, this can only be class Main. Get method_class for main().
  assert(std::string(this->name->get_string()) == std::string("Main"));
  method_class *mainMethod = (method_class *)features->nth(features->first());

  // TODO: add code here to generate the function `int Mainmain()`.
  // Generally what you need to do are:
  // -- setup or create the environment, env, for translating this method
  // -- invoke mainMethod->code(env) to translate the method
  CgenEnvironment env(this); // use same builder/context/module as CgenClassTable through this->get_classtable().context.builder.module
  mainMethod->code(&env);
}

#endif

/*********************************************************************

  CgenEnvironment functions

*********************************************************************/

// Look up a CgenNode given a symbol
CgenNode *CgenEnvironment::type_to_class(Symbol t) {
  return t == SELF_TYPE ? get_class()
                        : get_class()->get_classtable()->find_in_scopes(t);
}

BasicBlock *CgenEnvironment::get_or_insert_abort_block(Function *f) {
  for (auto &bb : *f) {
    if (bb.getName() == "abort") {
      return &bb;
    }
  }
  auto *abort_bb = BasicBlock::Create(this->context, "abort", f);
  Type *void_ = Type::getVoidTy(this->context);
  IRBuilder<> builder(abort_bb);
  FunctionCallee abort = this->the_module.getOrInsertFunction("abort", void_);
  builder.CreateCall(abort, {});
  builder.CreateUnreachable();
  return abort_bb;
}

AllocaInst *CgenEnvironment::insert_alloca_at_head(Type *ty) {
  BasicBlock &entry_bb = builder.GetInsertBlock()->getParent()->getEntryBlock();
  if (entry_bb.empty()) {
    // Insert "at the end" of this bb
    return new AllocaInst(ty, 0, "", &entry_bb);
  } else {
    // Insert before the first instruction of this bb
    return new AllocaInst(ty, 0, "", &entry_bb.front());
  }
}

/*********************************************************************

  APS class methods

    Fill in the following methods to produce code for the
    appropriate expression. You may add or remove parameters
    as you wish, but if you do, remember to change the parameters
    of the declarations in `cool-tree.handcode.h'.

*********************************************************************/

void program_class::cgen(const std::optional<std::string> &outfile) {
  initialize_constants();
  class_table = new CgenClassTable(classes);
  if (outfile) {
    std::error_code err;
    raw_fd_ostream s(*outfile, err, sys::fs::FA_Write);
    if (err) {
      std::cerr << "Cannot open output file " << *outfile << std::endl;
      exit(1);
    }
    s << class_table->the_module;
  } else {
    outs() << class_table->the_module;
  }
}

// Create a method body
Function *method_class::code(CgenEnvironment *env) {
  if (cgen_debug) {
    std::cerr << "method" << std::endl;
  }

  // TODO: add code here and replace `return nullptr`

  Type *i32 = Type::getInt32Ty(env->context),
       *i8_ptr = Type::getInt8PtrTy(env->context),
       *void_ = Type::getVoidTy(env->context);

  auto Main_main_func = env->create_llvm_function("Main.main", i32, {}, false);
  // set the initial block, then later can use env->new_bb_at_fend(); 
  // since builder.GetInsertBlock()->getParent() require [->getParent()] as current parent
  auto Main_main_entry_block = llvm::BasicBlock::Create(env->context, "entry", Main_main_func); // tie block with parent: Main_main_func
  // since builder.GetInsertBlock()->getParent() require [.GetInsertBlock()] as current block
  env->builder.SetInsertPoint(Main_main_entry_block);  // tie irbuilder with block : Main_main_entry_block
  // builder.GetInsertBlock()->getParent() : Main_main_entry_block->getParent() : Main_main_func // tie new_block with parent : Main_main_func // still same parent : Main_main_func
  // builder.SetInsertPoint(new_block) // tie irbuilder with new_block // different block : new_block

  auto abrt_ = env->get_or_insert_abort_block(Main_main_func);
  env->set_abrt(abrt_);

  auto Main_main_ret = expr->code(env);
  // env->builder.CreateRet(ConstantInt::get(Type::getInt32Ty(env->context), 0));
  env->builder.CreateRet(Main_main_ret);



  return Main_main_func;
}

// Codegen for expressions. Note that each expression has a value.

Value *assign_class::code(CgenEnvironment *env) {
  if (cgen_debug)
    std::cerr << "assign" << std::endl;

  // TODO: add code here and replace `return nullptr`

  // recursive call; grab info
  auto expr_val = expr->code(env);
  auto expr_tp = expr->get_expr_tp(env);
  auto [id_tp, id_addr_val] = env->find_in_scopes(name);

  // emit code
  env->builder.CreateStore(expr_val, id_addr_val);

  // settup expression_extra
  set_expr_tp(env, expr_tp);

  return expr_val;
}

Value *cond_class::code(CgenEnvironment *env) {
  if (cgen_debug)
    std::cerr << "cond" << std::endl;

  // TODO: add code here and replace `return nullptr`
  auto true_label = env->new_true_label();
  auto false_label = env->new_false_label();
  auto end_label = env->new_end_label();

  auto true_block = env->new_bb_at_fend(true_label);
  auto false_block = env->new_bb_at_fend(false_label);
  auto end_block = env->new_bb_at_fend(end_label);

  auto pred_val = pred->code(env);
  env->builder.CreateCondBr(pred_val, true_block, false_block);

  // then branch
  env->builder.SetInsertPoint(true_block);
  auto then_val = then_exp->code(env);
  auto then_tp = then_exp->get_expr_tp(env);
  if_type = then_tp;
  auto remain_true_block = env->builder.GetInsertBlock();
  
  // else branch
  env->builder.SetInsertPoint(false_block);
  auto else_val = else_exp->code(env);
  auto else_tp = else_exp->get_expr_tp(env);
  if_type = else_tp;
  auto remain_false_block = env->builder.GetInsertBlock();

  if_addr_val = env->insert_alloca_at_head(if_type); // only once

  // then branch
  env->builder.SetInsertPoint(remain_true_block);
  env->builder.CreateStore(then_val, if_addr_val);
  env->builder.CreateBr(end_block);

  // else branch
  env->builder.SetInsertPoint(remain_false_block);
  env->builder.CreateStore(else_val, if_addr_val);
  env->builder.CreateBr(end_block);

  // end block
  env->builder.SetInsertPoint(end_block);
  auto cond_res = env->builder.CreateLoad(if_type, if_addr_val);

  // set expr_extra
  set_expr_tp(env, if_type);

  return cond_res;
}

Value *loop_class::code(CgenEnvironment *env) {
  if (cgen_debug)
    std::cerr << "loop" << std::endl;

  // TODO: add code here and replace `return nullptr`
  auto loop_label = env->new_loop_label();
  auto true_label = env->new_true_label();
  auto false_label = env->new_false_label();

  auto loop_block = env->new_bb_at_fend(loop_label);
  auto true_block = env->new_bb_at_fend(true_label);
  auto false_block = env->new_bb_at_fend(false_label);

  // uncondition jump to loop
  env->builder.CreateBr(loop_block);

  // insert irbuilder
  env->builder.SetInsertPoint(loop_block);
  auto pred_ = pred->code(env);
  env->builder.CreateCondBr(pred_, true_block, false_block);

  // if true, then body
  env->builder.SetInsertPoint(true_block);
  body->code(env);
  env->builder.CreateBr(loop_block);

  // if false, then ...
  env->builder.SetInsertPoint(false_block);

  // set expr_extra
  set_expr_tp(env, Type::getInt32Ty(env->context));
  auto loop_res = ConstantInt::get(Type::getInt32Ty(env->context), 0);

  return loop_res;
}

Value *block_class::code(CgenEnvironment *env) {
  if (cgen_debug)
    std::cerr << "block" << std::endl;

  // TODO: add code here and replace `return nullptr`
  int i = 0;
  for(i = body->first(); body->more(i) && body->more(i+1); i = body->next(i)) {
    auto expr_iter = body->nth(i);
    expr_iter->code(env);
  }

  auto expr_iter = body->nth(i);
  auto block_res = expr_iter->code(env);
  auto block_tp = expr_iter->get_expr_tp(env);

  // set expr_extra
  set_expr_tp(env, block_tp);
  return block_res;
}

Value *let_class::code(CgenEnvironment *env) {
  if (cgen_debug)
    std::cerr << "let" << std::endl;

  // TODO: add code here and replace `return nullptr`
  auto init_val = init->code(env);

  auto i32_ = Type::getInt32Ty(env->context);
  auto i1_ = Type::getInt1Ty(env->context);

  auto type_name = type_decl->get_string();
  if (type_name == "Int") {
    identifier_type = i32_;
    identifier_addr_val = env->insert_alloca_at_head(i32_);
    if (init_val) {
      env->builder.CreateStore(init_val, identifier_addr_val);
    } else {
      env->builder.CreateStore(ConstantInt::get(i32_, 0), identifier_addr_val);
    }
  } else if (type_name == "Bool") {
    identifier_type = i1_;
    identifier_addr_val = env->insert_alloca_at_head(i1_);
    if (init_val) {
      env->builder.CreateStore(init_val, identifier_addr_val);
    } else {
      env->builder.CreateStore(ConstantInt::get(i1_, false), identifier_addr_val);
    }
  }
  env->var_tp_add_binding(identifier, identifier_type);
  env->add_binding(identifier, identifier_addr_val);

  env->var_tp_open_scope();
  env->open_scope();

  auto let_res_ = body->code(env);
  auto let_type_ = body->get_expr_tp(env);
  
  env->var_tp_close_scope();
  env->close_scope();

  set_expr_tp(env, let_type_);
  return let_res_;
}

Value *plus_class::code(CgenEnvironment *env) {
  if (cgen_debug)
    std::cerr << "plus" << std::endl;

  auto e1_ = e1->code(env);
  auto e2_ = e2->code(env);

  auto add_res = env->builder.CreateAdd(e1_, e2_);

  set_expr_tp(env, e1->get_expr_tp(env));
  return add_res;
}

Value *sub_class::code(CgenEnvironment *env) {
  if (cgen_debug)
    std::cerr << "sub" << std::endl;

  // TODO: add code here and replace `return nullptr`
  auto e1_ = e1->code(env);
  auto e2_ = e2->code(env);

  auto sub_res = env->builder.CreateSub(e1_, e2_);

  set_expr_tp(env, e1->get_expr_tp(env));
  return sub_res;
}

Value *mul_class::code(CgenEnvironment *env) {
  if (cgen_debug)
    std::cerr << "mul" << std::endl;

  // TODO: add code here and replace `return nullptr`
  auto e1_ = e1->code(env);
  auto e2_ = e2->code(env);

  auto mul_res = env->builder.CreateMul(e1_, e2_);

  set_expr_tp(env, e1->get_expr_tp(env));
  return mul_res;
}

Value *divide_class::code(CgenEnvironment *env) {
  if (cgen_debug)
    std::cerr << "div" << std::endl;

  // TODO: add code here and replace `return nullptr`
  auto ok_label = env->new_ok_label();
  auto numerator = e1->code(env);
  auto denominator = e2->code(env);

  auto abort_true = env->get_abrt();              // true, 0
  auto ok_false = env->new_bb_at_fend(ok_label); // false, not 0

  auto cond_ = env->builder.CreateCmp(llvm::CmpInst::ICMP_EQ, ConstantInt::get(Type::getInt32Ty(env->context), 0), denominator);
  env->builder.CreateCondBr(cond_, abort_true, ok_false);

  env->builder.SetInsertPoint(ok_false);
  auto div_res = env->builder.CreateSDiv(numerator, denominator);

  set_expr_tp(env, e1->get_expr_tp(env));
  return div_res;
}

Value *neg_class::code(CgenEnvironment *env) {
  if (cgen_debug)
    std::cerr << "neg" << std::endl;

  // TODO: add code here and replace `return nullptr`
  auto e1_ = e1->code(env);

  auto neg_res = env->builder.CreateNeg(e1_);

  set_expr_tp(env, e1->get_expr_tp(env));
  return neg_res;
}

Value *lt_class::code(CgenEnvironment *env) {
  if (cgen_debug)
    std::cerr << "lt" << std::endl;

  // TODO: add code here and replace `return nullptr`
  auto e1_ = e1->code(env);
  auto e2_ = e2->code(env);

  auto lt_res = env->builder.CreateCmp(llvm::CmpInst::ICMP_SLT, e1_, e2_);

  set_expr_tp(env, Type::getInt1Ty(env->context));
  return lt_res;
}

Value *eq_class::code(CgenEnvironment *env) {
  if (cgen_debug)
    std::cerr << "eq" << std::endl;

  // TODO: add code here and replace `return nullptr`
  auto e1_ = e1->code(env);
  auto e2_ = e2->code(env);

  auto eq_res = env->builder.CreateCmp(llvm::CmpInst::ICMP_EQ, e1_, e2_);

  set_expr_tp(env, Type::getInt1Ty(env->context));
  return eq_res;
}

Value *leq_class::code(CgenEnvironment *env) {
  if (cgen_debug)
    std::cerr << "leq" << std::endl;

  // TODO: add code here and replace `return nullptr`
  auto e1_ = e1->code(env);
  auto e2_ = e2->code(env);

  auto leq_res = env->builder.CreateCmp(llvm::CmpInst::ICMP_SLE, e1_, e2_);

  set_expr_tp(env, Type::getInt1Ty(env->context));
  return leq_res;
}

Value *comp_class::code(CgenEnvironment *env) {
  if (cgen_debug)
    std::cerr << "complement" << std::endl;

  // TODO: add code here and replace `return nullptr`

  auto e1_ = e1->code(env);
  auto comp_res = env->builder.CreateXor(e1_, ConstantInt::get(Type::getInt1Ty(env->context), true));

  set_expr_tp(env, e1->get_expr_tp(env));
  return comp_res;
}

Value *int_const_class::code(CgenEnvironment *env) {
  if (cgen_debug)
    std::cerr << "Integer Constant" << std::endl;

  // TODO: add code here and replace `return nullptr`
  std::string int_val = token->get_string();
  const char *string_to_char = int_val.c_str();
  int real_val = std::atoi(string_to_char);
  int val_constraints = std::min(std::max(std::numeric_limits<int>::min(), real_val), std::numeric_limits<int>::max());

  auto int_ret = ConstantInt::get(Type::getInt32Ty(env->context), val_constraints);
  set_expr_tp(env, Type::getInt32Ty(env->context));
  return int_ret;
}

Value *bool_const_class::code(CgenEnvironment *env) {
  if (cgen_debug)
    std::cerr << "Boolean Constant" << std::endl;

  set_expr_tp(env, Type::getInt1Ty(env->context));

  if (val) {
    return ConstantInt::get(Type::getInt1Ty(env->context), true);
  } 
  
  return ConstantInt::get(Type::getInt1Ty(env->context), false);
}

Value *object_class::code(CgenEnvironment *env) {
  if (cgen_debug)
    std::cerr << "Object" << std::endl;

  // TODO: add code here and replace `return nullptr`
  auto [object_type, object_addr_val] = env->find_in_scopes(name);

  auto object_res = env->builder.CreateLoad(object_type, object_addr_val);
  set_expr_tp(env, object_type);

  return object_res;
}

Value *no_expr_class::code(CgenEnvironment *env) {
  if (cgen_debug)
    std::cerr << "No_expr" << std::endl;

  // TODO: add code here and replace `return nullptr`
  return nullptr;
}

//*****************************************************************
// The next few functions are for node types not supported in Phase 1
// but these functions must be defined because they are declared as
// methods via the Expression_SHARED_EXTRAS hack.
//*****************************************************************

Value *static_dispatch_class::code(CgenEnvironment *env) {
  if (cgen_debug)
    std::cerr << "static dispatch" << std::endl;
#ifndef MP3
  assert(0 && "Unsupported case for phase 1");
#else
  // TODO: add code here and replace `return nullptr`
  return nullptr;
#endif
}

Value *string_const_class::code(CgenEnvironment *env) {
  if (cgen_debug)
    std::cerr << "string_const" << std::endl;
#ifndef MP3
  assert(0 && "Unsupported case for phase 1");
#else
  // TODO: add code here and replace `return nullptr`
  return nullptr;
#endif
}

Value *dispatch_class::code(CgenEnvironment *env) {
  if (cgen_debug)
    std::cerr << "dispatch" << std::endl;
#ifndef MP3
  assert(0 && "Unsupported case for phase 1");
#else
  // TODO: add code here and replace `return nullptr`
  return nullptr;
#endif
}

// Handle a Cool case expression (selecting based on the type of an object)
Value *typcase_class::code(CgenEnvironment *env) {
  if (cgen_debug)
    std::cerr << "typecase::code()" << std::endl;
#ifndef MP3
  assert(0 && "Unsupported case for phase 1");
#else
  // TODO: add code here and replace `return nullptr`
  return nullptr;
#endif
}

Value *new__class::code(CgenEnvironment *env) {
  if (cgen_debug)
    std::cerr << "newClass" << std::endl;
#ifndef MP3
  assert(0 && "Unsupported case for phase 1");
#else
  // TODO: add code here and replace `return nullptr`
  return nullptr;
#endif
}

Value *isvoid_class::code(CgenEnvironment *env) {
  if (cgen_debug)
    std::cerr << "isvoid" << std::endl;
#ifndef MP3
  assert(0 && "Unsupported case for phase 1");
#else
  // TODO: add code here and replace `return nullptr`
  return nullptr;
#endif
}

// Create the LLVM Function corresponding to this method.
void method_class::layout_feature(CgenNode *cls) {
#ifndef MP3
  assert(0 && "Unsupported case for phase 1");
#else
  // TODO: add code here
#endif
}

// Handle one branch of a Cool case expression.
// If the source tag is >= the branch tag
// and <= (max child of the branch class) tag,
// then the branch is a superclass of the source.
// See the MP3 handout for more information about our use of class tags.
Value *branch_class::code(Value *expr_val, Value *tag, Type *join_type,
                          CgenEnvironment *env) {
#ifndef MP3
  assert(0 && "Unsupported case for phase 1");
#else
  // TODO: add code here and replace `return nullptr`
  return nullptr;
#endif
}

// Assign this attribute a slot in the class structure
void attr_class::layout_feature(CgenNode *cls) {
#ifndef MP3
  assert(0 && "Unsupported case for phase 1");
#else
  // TODO: add code here
#endif
}

Value *attr_class::code(CgenEnvironment *env) {
#ifndef MP3
  assert(0 && "Unsupported case for phase 1");
#else
  // TODO: add code here and replace `return nullptr`
  return nullptr;
#endif
}

#ifdef MP3
// Retrieve the class tag from an object record.
// src is the object we need the tag from.
// src_class is the CgenNode for the *static* class of the expression.
// You need to look up and return the class tag for it's dynamic value
Value *get_class_tag(Value *src, CgenNode *src_cls, CgenEnvironment *env) {
  // ADD CODE HERE (MP3 ONLY)
  return 0;
}
#endif