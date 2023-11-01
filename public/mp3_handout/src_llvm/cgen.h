/*
 This is the MP2 skeleton cgen header. As given, it contains only basic
 functionality. You will need to add members to each of the classes
 to get them to perform their desired functions. Document your important
 design decisions below. We should be able to read your documentation and
 get a general overview of how your compiler generates code. For instance,
 how does your compiler generate structures for classes, how is inheritance
 modeled, how do you handle dynamic binding, etc.
*/

// ------------------ INSERT DESIGN DOCUMENTATION HERE --------------------- //

// ----------------------------- END DESIGN DOCS --------------------------- //

#include "cool_tree.h"
#include "stringtab.h"
#include "symtab.h"
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/raw_ostream.h>

class CgenNode;

// CgenClassTable represents the top level of a Cool program, which is
// basically a list of classes. The class table is used to look up classes
// (CgenNodes) by name, and it also handles global code generation tasks.
// The CgenClassTable constructor is where you'll find the entry point for
// code generation for an entire Cool program.
class CgenClassTable : public cool::SymbolTable<CgenNode> {
public:
  // CgenClassTable constructor begins and ends the code generation process
  CgenClassTable(Classes);

private:
  // The following creates an inheritance graph from a list of classes.
  // The graph is implemented as a tree of `CgenNode', and class names
  // are placed in the base class symbol table.
  void install_basic_classes();
  void install_classes(Classes cs);
  void install_class(CgenNode *nd);
  void install_special_class(CgenNode *nd);
  void build_inheritance_tree();
  void set_relations(CgenNode *nd);
  // Create declarations for C runtime functions we need to generate code
  void setup_external_functions();
  void setup_classes(CgenNode *c, int depth);


  // TODO: implement the following functions.
  // Setup each class in the table and prepare for code generation phase
  void setup();
  // Code generation functions. You need to write these functions.
  void code_module();
#ifdef MP3
  void code_classes(CgenNode *c);
#endif
  void code_constants();
  void code_main();

  /* Util functions */
#ifndef MP3
  CgenNode *getMainmain(CgenNode *c);
#endif
  CgenNode *root(); // Get the root of the class Tree, i.e. Object
public:
  int get_num_classes() const { return current_tag; }

private:
  // Class lists and current class tag
  std::vector<CgenNode *> nds, special_nds;

  int current_tag;

public:
  // LLVM Util
  llvm::Function *create_llvm_function(const std::string &funcName,
                                       llvm::Type *retType,
                                       llvm::ArrayRef<llvm::Type *> argTypes,
                                       bool isVarArgs);

  // CgenClassTable owns the current LLVM module and everything attached.
  // One program, one class table, one module.
  llvm::LLVMContext context;
  llvm::IRBuilder<> builder;
  llvm::Module the_module;
  std::unordered_map<std::string, llvm::StructType*> Type_Lookup; // My_Type ---> %My_Type
  std::unordered_map<std::string, llvm::StructType*> Vtable_Type_Lookup; // My_Type_vtable ---> %_My_Type_vtable
  std::unordered_map<std::string, llvm::GlobalVariable*> Vtable_Proto_Lookup; // My_Type_vtable_prototype ---> @_My_Type_vtable_prototype
  std::unordered_map<int, llvm::GlobalVariable*> strEntry_to_GlobalStr; // string entry's index ---> @String.index
  std::unordered_map<std::string, llvm::Function*> llmethod_to_Funtion_Ptr; // My_Type_test1 ---> function pointer
};

// Each CgenNode corresponds to a Cool class. As such, it is responsible for
// performing code generation on the class level. This includes laying out
// the class attributes, creating the necessary Types for the class and
// generating code for each of its methods.
class CgenNode : public class__class {
public:
  enum Basicness { Basic, NotBasic };
  CgenNode(Class_ c, Basicness bstatus, CgenClassTable *class_table)
      : class__class((const class__class &)*c), parentnd(0), children(0),  
        basic_status(bstatus), class_table(class_table), tag(-1), obj_tp(0), vtable_tp(0), clmethod_to_llmethod_idx(0), clattr_to_offset(0), clmethod_to_offset(0), Function_Body_Map(0) {}

  // Relationships with other nodes in the tree
  void set_parent(CgenNode *p) {
    assert(this->parentnd == nullptr && p != nullptr);
    p->children.push_back(this);
    this->parentnd = p;
  }
  int basic() { return basic_status == Basic; }
  std::vector<CgenNode *> &get_children() { return children; }
  void set_max_child(int mc) { max_child = mc; }
  int get_max_child() const { return max_child; }

  // Accessors for other provided fields
  int get_tag() const { return tag; }
  CgenClassTable *get_classtable() { return class_table; }

  // access current obj_tp and vtable_tp layout
  auto get_current_obj_tp(){
    return &obj_tp;
  }
  auto get_current_vtable_tp(){
    return &vtable_tp;
  }
  // access current map
  auto get_current_clmethod_to_llmethod_idx() {
    return &clmethod_to_llmethod_idx;
  }

  auto get_current_Function_Body_Map() {
    return &Function_Body_Map;
  }

  auto get_current_clattr_to_offset() {
    return &clattr_to_offset;
  }

  auto get_current_clmethod_to_offset() {
    return &clmethod_to_offset;
  }

  // access parent obj_tp and vtable_tp layout
  std::vector<std::pair<CgenNode *, attr_class *>>* get_parent_obj_tp(){
    if (parentnd == NULL) {
      return NULL;
    }
    return parentnd->get_current_obj_tp();
  }
  std::vector<std::pair<CgenNode *, method_class *>>* get_parent_vtable_tp(){
    if (parentnd == NULL) {
      return NULL;
    }
    return parentnd->get_current_vtable_tp();
  }

  std::unordered_map<std::string, int>* get_parent_clmethod_to_llmethod_idx() {
    if (parentnd == NULL) {
      return NULL;
    }
    return parentnd->get_current_clmethod_to_llmethod_idx();
  }

#ifdef MP3
  std::string get_type_name() { return name->get_string(); }
  std::string get_vtable_type_name() {
    return "_" + get_type_name() + "_vtable";
  }
  std::string get_vtable_name() {
    return "_" + get_type_name() + "_vtable_prototype";
  }
  std::string get_init_function_name() { return get_type_name() + "_new"; }
  std::string get_function_name(std::string name_) {return get_type_name() + "_" + name_;}
#endif

  // TODO: Complete the implementations of following functions
  // and add more as necessary

  // Class setup. You need to write the body of this function.
  void setup(int tag, int depth);
#ifdef MP3
  // Layout the methods and attributes for code generation
  void layout_features();
  // Class codegen. You need to write the body of this function.
  void code_class();
  // Codegen for the init function of every class
  void code_init_function(CgenEnvironment *env);
#endif
  void codeGenMainmain();

  llvm::Function *create_llvm_function(const std::string &funcName,
                                       llvm::Type *retType,
                                       llvm::ArrayRef<llvm::Type *> argTypes,
                                       bool isVarArgs) {
    return class_table->create_llvm_function(funcName, retType, argTypes,
                                            isVarArgs);
  }

private:
  CgenNode *parentnd;               // Parent of class
  std::vector<CgenNode *> children; // Children of class
  Basicness basic_status;           // `Basic' or 'NotBasic'
  CgenClassTable *class_table;
  // Class tag. Should be unique for each class in the tree
  int tag, max_child;
  std::ostream *ct_stream;

  // TODO: Add more functions / fields here as necessary
  // all these three are only for inheritance purpose
  std::vector<std::pair<CgenNode*, attr_class*>> obj_tp; // only for after vtable_pointer;
  std::vector<std::pair<CgenNode*, method_class*>> vtable_tp; // only for after XXX_new; only overwrite or create new function change the type, it remains same until someone overwrite or create new function
  // use as cl_method_name ---> index_of_vtable_tp vector
  std::unordered_map<std::string, int> clmethod_to_llmethod_idx; // only for after XXX_new; only for those who overload clmethod or create new function do not need to bit cast
  
  // TODO:
  std::unordered_map<std::string, int> clattr_to_offset; // cl attr name ---> offset in obj{}
  std::unordered_map<std::string, int> clmethod_to_offset; // cl method name ---> offset in vtable{} 

  std::unordered_map<llvm::Function*, method_class*> Function_Body_Map; // if it is new function, the value == NULL
  // llvm::LLVMContext context_store;
  // llvm::IRBuilder<> builder_store;
  // llvm::Module the_module_store;
};

// CgenEnvironment provides the environment for code generation of a method.
// Its main task is to provide a mapping from Cool names to LLVM Values.
// This mapping needs to be maintained as scopes are entered and exited, new
// variables are declared, and so on. CgenEnvironment is also a good place
// to put non-local information you will need during code generation. Two
// examples are the current CgenNode and the current Function.
class CgenEnvironment {
public:
  // Class CgenEnvironment should be constructed by a class prior to code
  // generation for each method. You may need to add parameters to this
  // constructor.
  CgenEnvironment(CgenNode *cur_class)
      : FUNC_PTR(0), SELF_ADDR(0), var_table(), var_tp_table(), var_addr_mp3(), var_type_mp3(), cur_class(cur_class),
        class_table(*cur_class->get_classtable()), context(class_table.context),
        builder(class_table.builder), the_module(class_table.the_module), Type_Lookup(class_table.Type_Lookup), Vtable_Type_Lookup(class_table.Vtable_Type_Lookup), Vtable_Proto_Lookup(class_table.Vtable_Proto_Lookup){
    tmp_count = 0;
    ok_count = 0;
    loop_count = 0;
    true_count = 0;
    false_count = 0;
    end_count = 0;
    var_table.enterscope();
    var_tp_table.enterscope();
    var_addr_mp3.enterscope();
    var_type_mp3.enterscope();
    // TODO: add code here
  }

  CgenNode *get_class() { return cur_class; }
  void set_class(CgenNode *c) { cur_class = c; }

  // Must return the CgenNode for a class given the symbol of its name
  CgenNode *type_to_class(Symbol t);


  std::pair<llvm::Type *, llvm::Value *> find_in_scopes(Symbol name) { return {var_tp_table.find_in_scopes(name), var_table.find_in_scopes(name)}; }

  void add_binding(Symbol name, llvm::Value *val_ptr) { var_table.insert(name, val_ptr); }
  void open_scope() { var_table.enterscope(); }
  void close_scope() { var_table.exitscope(); }

  void var_tp_add_binding(Symbol name, llvm::Type *tp_ptr) { var_tp_table.insert(name, tp_ptr);}
  void var_tp_open_scope() { var_tp_table.enterscope(); }
  void var_tp_close_scope() { var_tp_table.exitscope(); }


llvm::Value* find_var_addr_mp3(Symbol name) { return var_addr_mp3.find_in_scopes(name); }
void add_var_addr_mp3(Symbol name, llvm::Value* addr) { var_addr_mp3.insert(name, addr); }
void open_var_addr_mp3() { var_addr_mp3.enterscope(); }
void close_var_addr_mp3() { var_addr_mp3.exitscope(); }

llvm::StructType* find_var_type_mp3(Symbol name) { return var_type_mp3.find_in_scopes(name); }
void add_var_type_mp3(Symbol name, llvm::StructType* tp) { var_type_mp3.insert(name, tp); }
void open_var_type_mp3() {var_type_mp3.enterscope(); }
void close_var_type_mp3() {var_type_mp3.exitscope(); }


  // LLVM Utils:
  // Create a new llvm function in the current module
  llvm::Function *create_llvm_function(const std::string &funcName,
                                       llvm::Type *retType,
                                       llvm::ArrayRef<llvm::Type *> argTypes,
                                       bool isVarArgs) {
    return class_table.create_llvm_function(funcName, retType, argTypes,
                                            isVarArgs);
  }


  // Insert a new BasicBlock at the end of the current function (the function
  // that builder is in)
  llvm::BasicBlock *new_bb_at_fend(const std::string &name) {
    return llvm::BasicBlock::Create(context, name,
                                    builder.GetInsertBlock()->getParent());
  }
  // Insert an alloca instruction in the head BasicBlock of the current
  // function, such that this alloca is available in all BasicBlocks of the
  // function.
  llvm::AllocaInst *insert_alloca_at_head(llvm::Type *ty);
  // Get or insert a BasicBlock with the name "abort" which calls the ::abort
  // function. This block will be inserted at the end of the given function,
  // without moving the builder.
  llvm::BasicBlock *get_or_insert_abort_block(llvm::Function *f);

  // TODO: Add more functions as necessary.

  std::string new_name() { return "tmp." + std::to_string(tmp_count++); }
  std::string new_ok_label() { return "ok." + std::to_string(ok_count++); }
  std::string new_loop_label() { return "loop." + std::to_string(loop_count++); }
  std::string new_true_label() { return "true." + std::to_string(true_count++); }
  std::string new_false_label() { return "false." + std::to_string(false_count++); }
  std::string new_end_label() { return "end." + std::to_string(end_count++); } 

  llvm::BasicBlock *get_abrt() {
    return abrt;
  }
  void set_abrt(llvm::BasicBlock *abrt_) {
    abrt = abrt_;
  }
  llvm::Function* FUNC_PTR;
  llvm::Value* SELF_ADDR; // SELF_ADDR is **B which could store *B; load **B to get *B; *B could be used in [Get_Attr_Addr, Get_Func_Addr] function
private:
  // mapping from variable names to memory locations
  // need to map to <StructType, bool> bool indicates whether box/unbox
  // TODO: 
  cool::SymbolTable<llvm::Value> var_table;
  cool::SymbolTable<llvm::Type> var_tp_table;

  cool::SymbolTable<llvm::Value> var_addr_mp3;
  cool::SymbolTable<llvm::StructType> var_type_mp3;

  CgenNode *cur_class;
  int tmp_count, ok_count; 
  int loop_count, true_count, false_count, end_count;
  llvm::BasicBlock *abrt;

public:
  CgenClassTable &class_table;
  // These are references to the current LLVM context and module,
  // and they point to the ones in CgenClassTable.
  llvm::LLVMContext &context;
  llvm::IRBuilder<> &builder;
  llvm::Module &the_module;
  std::unordered_map<std::string, llvm::StructType*> &Type_Lookup;
  std::unordered_map<std::string, llvm::StructType*> &Vtable_Type_Lookup;
  std::unordered_map<std::string, llvm::GlobalVariable*> &Vtable_Proto_Lookup;
};

#ifdef MP3
// TODO: implement these functions (MP3), and add more functions as necessary

// Utitlity function
// Generate any code necessary to convert from given Value* to
// dest_type, assuming it has already been checked to be compatible
llvm::Value *conform(llvm::Value *src, llvm::Type *dest_type,
                     CgenEnvironment *env);


// box i32 ---> Int 
llvm::CallInst* BOX(CgenClassTable* clstb, llvm::Value *prim, CgenEnvironment *env) {
  if (prim->getType()->isIntegerTy(32)) { // i32
    auto int_new_type = clstb->llmethod_to_Funtion_Ptr["Int_new"];
    auto int_new_callee = clstb->the_module.getOrInsertFunction("Int_new", int_new_type->getType());
    auto int_new_allocated = clstb->builder.CreateCall(int_new_callee, {});

    auto int_init_type = clstb->llmethod_to_Funtion_Ptr["Int_init"];
    auto int_init_callee = clstb->the_module.getOrInsertFunction("Int_init", int_init_type->getType());
    clstb->builder.CreateCall(int_init_callee, {int_new_allocated, prim});

    return int_new_allocated;
  } else if (prim->getType()->isIntegerTy(1)) { // i1
    auto bool_new_type = clstb->llmethod_to_Funtion_Ptr["Bool_new"];
    auto bool_new_callee = clstb->the_module.getOrInsertFunction("Bool_new", bool_new_type->getType());
    auto bool_new_allocated = clstb->builder.CreateCall(bool_new_callee, {});

    auto bool_init_type = clstb->llmethod_to_Funtion_Ptr["Bool_init"];
    auto bool_init_callee = clstb->the_module.getOrInsertFunction("Bool_init", bool_init_type->getType());
    clstb->builder.CreateCall(bool_init_callee, {bool_new_allocated, prim});

    return bool_new_allocated;
  } 
    
  assert(false);
  return NULL;
}

// for a : B, return **B || store *B -> ** B
// for a : Int, return *i32 || store i32 -> * i32
// current env, class curr_cls {}, .....
// curr_cls is always current class, because only current class can access the attribute
// [%tmp.96 = load %Main*, %Main** %tmp.95] || CgenEnvironment::SELF_ADDR acts as %tmp.95
// [%tmp.97 = getelementptr %Main, %Main* %tmp.96, i32 0, i32 4], [%tmp.98 = load %B*, %B** %tmp.97] || ptr acts as %tmp.96 || ret acts as %tmp.97
// [%tmp.100 = getelementptr %Main, %Main* %tmp.99, i32 0, i32 5] [%tmp.101 = load i32, i32* %tmp.100] || ptr acts as %tmp.99 || ret acts as %tmp.100
auto Get_Attr_Addr(CgenEnvironment* env, CgenNode* curr_cls, llvm::Value* ptr, std::string attr_name) {
  auto current_class_name = curr_cls->get_type_name();
  auto current_class_type = curr_cls->get_classtable()->Type_Lookup[current_class_name];
  auto attr_offset = (*curr_cls->get_current_clattr_to_offset())[attr_name];

  return env->builder.CreateGEP(current_class_type, ptr, {llvm::ConstantInt::get(llvm::Type::getInt32Ty(env->context), 0), llvm::ConstantInt::get(llvm::Type::getInt32Ty(env->context), attr_offset)});
} 

// if indeed use attribute rather than local, para, then we need to get the type
// %A, %B, %IO, %Int, SELF_TYPE = ..., ...
// for a : B, return %"B" 
// for a : Int, return %"Int" 
auto Get_Attr_Type(CgenNode* curr_cls, llvm::Value* ptr, std::string attr_name) {
  auto current_class_name = curr_cls->get_type_name();
  auto attr_offset = (*curr_cls->get_current_clattr_to_offset())[attr_name];

  auto type_str = (*curr_cls->get_current_obj_tp())[attr_offset].second->get_type_decl()->get_string();
  auto struct_type = curr_cls->get_classtable()->Type_Lookup[type_str];
  if (type_str == "SELF_TYPE") {
    struct_type = curr_cls->get_classtable()->Type_Lookup[current_class_name];
  }

  return struct_type;
}

// return i32 (%F*,i1,i32) ** 
// [%tmp.49 = getelementptr %F, %F* %tmp.47, i32 0, i32 0] || ptr act as %tmp.47
auto Get_Func_Addr(CgenEnvironment* env, CgenNode* func_class, llvm::Value* ptr, std::string func_name) {
  // [%tmp.49 = getelementptr %F, %F* %tmp.47, i32 0, i32 0] || ptr acts as %tmp.47 || class_name acts as %F
  auto class_for_func = env->Type_Lookup[func_class->get_type_name()];
  auto vtable_prototype_ptr = env->builder.CreateGEP(class_for_func, ptr, {llvm::ConstantInt::get(llvm::Type::getInt32Ty(env->context), 0), llvm::ConstantInt::get(llvm::Type::getInt32Ty(env->context), 0)});
  
  // %tmp.50 = load %_F_vtable*, %_F_vtable** %tmp.49 
  auto vtable_type = env->Vtable_Type_Lookup[func_class->get_vtable_type_name()];
  auto vtable_ptr = env->builder.CreateLoad(llvm::PointerType::get(vtable_type, 0), vtable_prototype_ptr);
  
  // %tmp.51 = getelementptr %_F_vtable, %_F_vtable* %tmp.50, i32 0, i32 9 
  auto offset = (*func_class->get_current_clmethod_to_offset())[func_name];
  auto func_ptr = env->builder.CreateGEP(vtable_type, vtable_ptr, {llvm::ConstantInt::get(llvm::Type::getInt32Ty(env->context), 0), llvm::ConstantInt::get(llvm::Type::getInt32Ty(env->context), offset)});

  return func_ptr;
}

// current env, class curr_cls {}, .....
// [let33(x : Int, y : B*): Int] ----> [i32 @Main.let33(%Main* %self, i32 %x, %B* %y)]
// for x : i32, alloca(i32), bind to *i32 || need to store i32 -> *i32
// for y : B*, alloca(B*), bind to **B || need to store *B -> **B
auto Create_Param(CgenEnvironment* env, llvm::Function* func_ptr, method_class* method_ptr) {
  auto formals = *(method_ptr->get_formals());

  int i = 0;
  for (auto& arg: func_ptr->args()) {
    if (i == 0) {
      arg.setName("self");
    } else {
      arg.setName(formals->nth(i-1)->get_name()->get_string());
    }
    i += 1;
  }

  auto func_entry_block = llvm::BasicBlock::Create(env->context, "entry", func_ptr);
  env->builder.SetInsertPoint(func_entry_block);
  auto func_abort_block = env->get_or_insert_abort_block(func_ptr);
  env->set_abrt(func_abort_block);
  
  i = 0;
  for (auto& arg: func_ptr->args()) {
    auto alloca_addr = env->insert_alloca_at_head(arg.getType()); 
    env->builder.CreateStore(&arg, alloca_addr);
    if (i == 0) {
      env->SELF_ADDR = alloca_addr;
    } else {
      env->add_var_addr_mp3(formals->nth(i-1)->get_name(), alloca_addr);
      env->add_var_type_mp3(formals->nth(i-1)->get_name(), env->Type_Lookup[formals->nth(i-1)->get_type_decl()->get_string()]);
    }
    i += 1;
  }
}

llvm::FunctionType* functp_helper(CgenNode* cls, method_class* md) {
  llvm::Type* curr_ll_func_ret_tp;
  auto curr_ll_func_ret_tp_str = md->get_return_type()->get_string();
  if (curr_ll_func_ret_tp_str == "Int") {
    curr_ll_func_ret_tp = llvm::Type::getInt32Ty(cls->get_classtable()->context);
  } else if (curr_ll_func_ret_tp_str == "Bool") {
    curr_ll_func_ret_tp = llvm::Type::getInt1Ty(cls->get_classtable()->context);
  } else if (curr_ll_func_ret_tp_str == "SELF_TYPE") {
    auto get_type = cls->get_classtable()->Type_Lookup[cls->get_type_name()];
    curr_ll_func_ret_tp = llvm::PointerType::get(get_type, 0);///////////////////////
  } else {
    auto get_type = cls->get_classtable()->Type_Lookup[curr_ll_func_ret_tp_str];
    curr_ll_func_ret_tp = llvm::PointerType::get(get_type, 0);/////////////////////////
  }

  // par type with unboxing
  std::vector<llvm::Type*> curr_ll_func_par_tp_vec;
  // begin with SLEF_TYPE
  auto get_type = cls->get_classtable()->Type_Lookup[cls->get_type_name()]; 
  curr_ll_func_par_tp_vec.push_back(llvm::PointerType::get(get_type, 0));////////////////////////////////////
  // then other par
  auto formals = *(md->get_formals());
  for(int i = formals->first(); formals->more(i); i = formals->next(i)) {
    auto formal_iter = formals->nth(i);
    llvm::Type* curr_ll_func_par_tp;
    auto curr_ll_func_par_tp_str = formal_iter->get_type_decl()->get_string();
    if (curr_ll_func_par_tp_str == "Int") {
      curr_ll_func_par_tp = llvm::Type::getInt32Ty(cls->get_classtable()->context);
    } else if (curr_ll_func_par_tp_str == "Bool") {
      curr_ll_func_par_tp = llvm::Type::getInt1Ty(cls->get_classtable()->context);
    } else if (curr_ll_func_par_tp_str == "SELF_TYPE") {
      auto get_type = cls->get_classtable()->Type_Lookup[cls->get_type_name()];
      curr_ll_func_par_tp = llvm::PointerType::get(get_type, 0); //////////////////////////
    } else {
      auto get_type = cls->get_classtable()->Type_Lookup[curr_ll_func_par_tp_str];
      curr_ll_func_par_tp = llvm::PointerType::get(get_type, 0);////////////////////////////
    }
    curr_ll_func_par_tp_vec.push_back(curr_ll_func_par_tp);
  } 

  llvm::FunctionType* create_func_tp = llvm::FunctionType::get(curr_ll_func_ret_tp, curr_ll_func_par_tp_vec, false);
  return create_func_tp;
}
#endif
