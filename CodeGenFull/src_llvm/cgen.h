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
  std::unordered_map<std::string, CgenNode*> Name_to_Node;  // StructType to Node
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
  CgenNode* get_parentnd() {
    return parentnd;
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
  // void code_init_function(CgenEnvironment *env);
  void code_init_function();
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

  
  // obj{vtable_pointer(not included in obj_tp); attr, ...}
  std::vector<std::pair<CgenNode*, attr_class*>> obj_tp; // only for after vtable_pointer
  std::unordered_map<std::string, int> clattr_to_offset; // cl attr name ---> offset in obj{vtable_pointer(not included in obj_tp); attr, ...}
  
  // vtable{tag(not included in vtable_tp); size(not included in vtable_tp); name(not included in vtable_tp); new_function(not included in vtable_tp); method, ...}
  std::vector<std::pair<CgenNode*, method_class*>> vtable_tp; // only for after XXX_new; only overwrite or create new function change the type, it remains same until someone overwrite or create new function
  std::unordered_map<std::string, int> clmethod_to_offset; // cl method name ---> offset in vtable{tag(not included in vtable_tp); size(not included in vtable_tp); name(not included in vtable_tp); new_function(not included in vtable_tp); method, ...} 

  // use as cl_method_name ---> index_of_vtable_tp vector
  std::unordered_map<std::string, int> clmethod_to_llmethod_idx; // only for after XXX_new; only for those who overload clmethod or create new function do not need to bit cast
  std::unordered_map<llvm::Function*, method_class*> Function_Body_Map; // if it is new function, the value == NULL
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
      : FUNC_PTR(0), SELF_ADDR(0), MALLOC_ADDR(0), branch_operand(0), branch_operand_tp(0), next_label(0), cur_class(cur_class), var_table(), var_tp_table(),
        class_table(*cur_class->get_classtable()), context(class_table.context),
        builder(class_table.builder), the_module(class_table.the_module), Type_Lookup(class_table.Type_Lookup), Vtable_Type_Lookup(class_table.Vtable_Type_Lookup), Vtable_Proto_Lookup(class_table.Vtable_Proto_Lookup),
        strEntry_to_GlobalStr(class_table.strEntry_to_GlobalStr), llmethod_to_Funtion_Ptr(class_table.llmethod_to_Funtion_Ptr), Name_to_Node(class_table.Name_to_Node) {
    block_count = 0;
    tmp_count = 0;
    ok_count = 0;
    loop_count = 0;
    true_count = 0;
    false_count = 0;
    end_count = 0;
    var_table.enterscope();
    var_tp_table.enterscope();
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
  std::string new_label(const std::string &prefix, bool increment) {
    std::string suffix = std::to_string(block_count);
    block_count += increment;
    return prefix + suffix;
  }

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

  // CgenEnv corropsoning function pointer
  llvm::Function* FUNC_PTR;
  // SELF_ADDR is **B which could store *B; load **B to get *B; *B could be used in [Get_Attr_Addr, Get_Func_Addr] function
  // it is just a text, help for generating ll code(getelementptr); same as other instruction, for example, add, alloca, ...
  // for current CgenEnv/method, for specific ll function body; for example, define i32 @F.test16(%F* %self) {...}
  // ----------------------------------------------------------------------------------------
  // let33(x : Int, y : B*): Int] ----> [i32 @Main.let33(%Main* %self, i32 %x, %B* %y)
  // [%tmp.102 = alloca %Main*]
  // [store %Main* %self, %Main** %tmp.102] || SELF_ADDR is %tmp.102
  // -----------------------------------------------------------------------------------------
  llvm::Value* SELF_ADDR; 
  llvm::Value* MALLOC_ADDR;
  llvm::Value* branch_operand;
  llvm::Type* branch_operand_tp;
  llvm::BasicBlock* next_label;
private:
  CgenNode *cur_class;

  // mapping from variable names to memory locations
  // need to map to <StructType, bool> bool indicates whether box/unbox
  cool::SymbolTable<llvm::Value> var_table;
  cool::SymbolTable<llvm::Type> var_tp_table;
  
  int block_count, tmp_count, ok_count; 
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
  std::unordered_map<int, llvm::GlobalVariable*> &strEntry_to_GlobalStr; 
  std::unordered_map<std::string, llvm::Function*> &llmethod_to_Funtion_Ptr;
  std::unordered_map<std::string, CgenNode*> &Name_to_Node;
};

#ifdef MP3
// TODO: implement these functions (MP3), and add more functions as necessary

// Utitlity function
// Generate any code necessary to convert from given Value* to
// dest_type, assuming it has already been checked to be compatible
llvm::Value *conform(llvm::Value *src, llvm::Type *dest_type,
                     CgenEnvironment *env);



// g : Int <- new Int;
// %tmp.33 = getelementptr %D, %D* %tmp.9, i32 0, i32 7
// %tmp.34 = call %Int* @Int_new(  )
// %tmp.36 = getelementptr %Int, %Int* %tmp.34, i32 0, i32 1  || ptr is %tmp.34 || ptr_type is "%Int"
// %tmp.35 = load i32, i32* %tmp.36 || ret is %tmp.35
// store i32 %tmp.35, i32* %tmp.33
// ---------------------------------------------------------------------------
// %tmp.44 = getelementptr %D, %D* %tmp.9, i32 0, i32 10
// %tmp.45 = call %Bool* @Bool_new(  )
// %tmp.47 = getelementptr %Bool, %Bool* %tmp.45, i32 0, i32 1
// %tmp.46 = load i1, i1* %tmp.47
// store i1 %tmp.46, i1* %tmp.44
// ---------------------------------------------------------------------------
auto UNBOX(CgenEnvironment *env, llvm::Type* ptr_type, llvm::Value* ptr) {
  assert(ptr_type->isStructTy());
  llvm::StructType* ptr_struct_type = llvm::cast<llvm::StructType>(ptr_type);
  if (ptr_struct_type->getName() == "Int") {
    // %tmp.36 = getelementptr %Int, %Int* %tmp.34, i32 0, i32 1 
    auto get_addr = env->builder.CreateGEP(ptr_struct_type, ptr, {llvm::ConstantInt::get(llvm::Type::getInt32Ty(env->context), 0), llvm::ConstantInt::get(llvm::Type::getInt32Ty(env->context), 1)});
    // %tmp.35 = load i32, i32* %tmp.36
    auto get_val = env->builder.CreateLoad(llvm::Type::getInt32Ty(env->context), get_addr);
    return get_val;
  } else if (ptr_struct_type->getName() == "Bool") {
    auto get_addr = env->builder.CreateGEP(ptr_struct_type, ptr, {llvm::ConstantInt::get(llvm::Type::getInt32Ty(env->context), 0), llvm::ConstantInt::get(llvm::Type::getInt32Ty(env->context), 1)});
    auto get_val = env->builder.CreateLoad(llvm::Type::getInt1Ty(env->context), get_addr);
    return get_val;
  } 
    
  assert(false);
}
// box i32 ---> Int 
//	%tmp.3 = load i32, i32* %tmp.2      
//	%tmp.5 = call %Int* @Int_new(  )    || ret is %tmp.5
//	call void(%Int*, i32 ) @Int_init( %Int* %tmp.5, i32 %tmp.3 ) || prim is %tmp.3 || ret is %tmp.5
//  %tmp.6 = getelementptr %Int, %Int* %tmp.5, i32 0, i32 0
//	%tmp.7 = load %_Int_vtable*, %_Int_vtable** %tmp.6
llvm::CallInst* BOX(CgenEnvironment *env, llvm::Value *prim) {
  if (prim->getType()->isIntegerTy(32)) { // i32
    //	%tmp.5 = call %Int* @Int_new(  )
    auto int_new_type = env->llmethod_to_Funtion_Ptr["Int_new"];
    auto int_new_callee = env->the_module.getOrInsertFunction("Int_new", int_new_type->getFunctionType());
    auto int_new_allocated = env->builder.CreateCall(int_new_callee, {});

    //	call void(%Int*, i32 ) @Int_init( %Int* %tmp.5, i32 %tmp.3 )
    auto int_init_type = env->llmethod_to_Funtion_Ptr["Int_init"];
    auto int_init_callee = env->the_module.getOrInsertFunction("Int_init", int_init_type->getFunctionType());
    env->builder.CreateCall(int_init_callee, {int_new_allocated, prim});

    return int_new_allocated;
  } else if (prim->getType()->isIntegerTy(1)) { // i1
    auto bool_new_type = env->llmethod_to_Funtion_Ptr["Bool_new"];
    auto bool_new_callee = env->the_module.getOrInsertFunction("Bool_new", bool_new_type->getFunctionType());
    auto bool_new_allocated = env->builder.CreateCall(bool_new_callee, {});

    auto bool_init_type = env->llmethod_to_Funtion_Ptr["Bool_init"];
    auto bool_init_callee = env->the_module.getOrInsertFunction("Bool_init", bool_init_type->getFunctionType());
    env->builder.CreateCall(bool_init_callee, {bool_new_allocated, prim});

    return bool_new_allocated;
  } 
    
  assert(false);
  return NULL;
}

// class D inherits C{} || class Int inherits Object{}
// ------------------------------------------------------------
// d : C <- new D; || decl_tp is "%C" || expr_tp is "%D"
// %tmp.24 = getelementptr %D, %D* %tmp.9, i32 0, i32 4 
// %tmp.25 = call %D* @D_new(  )        || expr_val is %tmp.25 
// %tmp.26 = bitcast %D* %tmp.25 to %C* || ret_val is %tmp.26
// store %C* %tmp.26, %C** %tmp.24
// ------------------------------------------------------------
// e : Object <- 1;   || decl_tp is "%Object" || expr_tp is "i32"
// %tmp.27 = getelementptr %D, %D* %tmp.9, i32 0, i32 5
// %tmp.29 = call %Int* @Int_new(  )  
// call void(%Int*, i32 ) @Int_init( %Int* %tmp.29, i32 1 )  || expr_val is i32 1
// %tmp.30 = bitcast %Int* %tmp.29 to %Object* || ret_val is %tmp.30
// store %Object* %tmp.30, %Object** %tmp.27
// ------------------------------------------------------------
// g : Int <- new Int; || decl_tp is "i32" || expr_tp is "%Int"
// %tmp.31 = getelementptr %D, %D* %tmp.9, i32 0, i32 6
// %tmp.32 = call %Int* @Int_new(  )  || expr_val is %tmp.32
// %tmp.34 = getelementptr %Int, %Int* %tmp.32, i32 0, i32 1
// %tmp.33 = load i32, i32* %tmp.34 || ret_val is %tmp.33
// store i32 %tmp.33, i32* %tmp.31
// ------------------------------------------------------------
// f : Object <- new Int; || decl_tp is "%Object" || expr_tp is "%Int"
// %tmp.35 = getelementptr %D, %D* %tmp.9, i32 0, i32 7
// %tmp.36 = call %Int* @Int_new(  )  || expr_val is %tmp.36
// %tmp.37 = bitcast %Int* %tmp.36 to %Object* || ret_val is %tmp.37
// store %Object* %tmp.37, %Object** %tmp.35
// ------------------------------------------------------------
// x : Int <- 2; || decl_tp is "i32" || expr_tp is "i32"
// %tmp.38 = getelementptr %D, %D* %tmp.9, i32 0, i32 8
// store i32 2, i32* %tmp.38 || expr_val is i32 2 || ret_val is i32 2
// ------------------------------------------------------------
// decl_tp could also be dest_tp
llvm::Value* Conform(CgenEnvironment* env, llvm::Type* decl_tp, llvm::Type* expr_tp, llvm::Value* expr_val) {
  if (decl_tp->isStructTy() && expr_tp->isStructTy()) { // only need bitcast
    llvm::StructType* decl_tp_struct = llvm::cast<llvm::StructType>(decl_tp);
    auto ret_val = env->builder.CreateBitCast(expr_val, llvm::PointerType::get(decl_tp_struct, 0));
    return ret_val;
  } else if ((!decl_tp->isStructTy()) && expr_tp->isStructTy()) { // need to unbox
    llvm::StructType* expr_tp_struct = llvm::cast<llvm::StructType>(expr_tp);
    if (decl_tp->isIntegerTy(32)) {
      auto ret_val = UNBOX(env, expr_tp_struct, expr_val);
      return ret_val;
    } else if (decl_tp->isIntegerTy(1)) {
      auto ret_val = UNBOX(env, expr_tp_struct, expr_val);
      return ret_val;
    } else {
      assert(false);
    }
  } else if (decl_tp->isStructTy() && (!expr_tp->isStructTy())) { // need to box
    llvm::StructType* decl_tp_struct = llvm::cast<llvm::StructType>(decl_tp);
    if (expr_tp->isIntegerTy(32)) {
      auto ret_before_cast = BOX(env, expr_val);
      auto ret_val = env->builder.CreateBitCast(ret_before_cast, llvm::PointerType::get(decl_tp_struct, 0));
      return ret_val;
    } else if (expr_tp->isIntegerTy(1)) {
      auto ret_before_cast = BOX(env, expr_val);
      auto ret_val = env->builder.CreateBitCast(ret_before_cast, llvm::PointerType::get(decl_tp_struct, 0));
      return ret_val;
    } else {
      assert(false);
    }
  } else if ((!decl_tp->isStructTy()) && (!expr_tp->isStructTy())) { // no need
    return expr_val;
  } else { 
    assert(false);
  }
}

// curr_cls is always current class, because only current class can access the attribute
// class Main { x : Int; y : B; };  || curr_cls is "Main"
// [%tmp.95 = alloca %Main*] [store %Main* %self, %Main** %tmp.95] [%tmp.96 = load %Main*, %Main** %tmp.95] || CgenEnvironment::SELF_ADDR acts as %tmp.95
// [%tmp.97 = getelementptr %Main, %Main* %tmp.96, i32 0, i32 4], [%tmp.98 = load %B*, %B** %tmp.97] || ptr acts as %tmp.96 || ret acts as %tmp.97
// [%tmp.100 = getelementptr %Main, %Main* %tmp.99, i32 0, i32 5] [%tmp.101 = load i32, i32* %tmp.100] || ptr acts as %tmp.99 || ret acts as %tmp.100
// ----------------------------------------------------------------
// [%tmp.98 = load %B*, %B** %tmp.97] || Other may need to check whether %tmp.98 is NULL or not
auto Get_Attr_Addr(CgenEnvironment* env, CgenNode* curr_cls, llvm::Value* ptr, std::string attr_name) {
  // [%tmp.97 = getelementptr %Main, %Main* %tmp.96, i32 0, i32 4]
  auto current_class_name = curr_cls->get_type_name();
  auto current_class_type = curr_cls->get_classtable()->Type_Lookup[current_class_name];
  auto attr_offset = (*curr_cls->get_current_clattr_to_offset())[attr_name];

  return env->builder.CreateGEP(current_class_type, ptr, {llvm::ConstantInt::get(llvm::Type::getInt32Ty(env->context), 0), llvm::ConstantInt::get(llvm::Type::getInt32Ty(env->context), attr_offset)});
} 
// class C {a : B; b : Int}  || curr_cls is C
// for a : B, return "%B"    
// for b : Int, return "i32"
// SELF_TYPE base on the used class
auto Get_Attr_Type(CgenEnvironment* env, CgenNode* curr_cls, std::string attr_name) {
  auto current_class_name = curr_cls->get_type_name();
  auto attr_offset = (*curr_cls->get_current_clattr_to_offset())[attr_name] - 1; assert(attr_offset >= 0);

  auto type_str = (*curr_cls->get_current_obj_tp())[attr_offset].second->get_type_decl()->get_string();
  llvm::Type* res;
  if (type_str == "Int") {
    res = llvm::Type::getInt32Ty(env->context);
  } else if (type_str == "Bool") {
    res = llvm::Type::getInt1Ty(env->context);
  } else if (type_str == "SELF_TYPE") {
    res = curr_cls->get_classtable()->Type_Lookup[current_class_name];
  } else {
    res = curr_cls->get_classtable()->Type_Lookup[type_str];
  }
  
  assert(res);
  return res;
}

// class B { test2(): SELF_TYPE{} }  || class C inherits B{} || class F inherits ... {p : C}
// class F { test15() : Int { { test2(); 0; } }; };  ------------> "%F"
// class F { test15() : Int { { p.test2(); 0; } }; };  ------------> "%C"
// for a : B, return "%B" 
// for b : Int, return "i32"
// SELF_TYPE: base on curr_cls
auto Get_Decl_Type(CgenEnvironment* env, CgenNode* curr_cls, std::string type_name) {
  llvm::Type* res;
  if (type_name == "Int") {
    res = llvm::Type::getInt32Ty(env->context);
  } else if (type_name == "Bool") {
    res = llvm::Type::getInt1Ty(env->context);
  } else if (type_name == "SELF_TYPE") {
    res = curr_cls->get_classtable()->Type_Lookup[curr_cls->get_type_name()];
  } else {
    res = curr_cls->get_classtable()->Type_Lookup[type_name];
  }
  return res;
}

// class B { test2(): SELF_TYPE{} }  || class C inherits B{} || class F inherits ... {p : C}
// ---------------------------------------------------------------------------------------------------------------------
// class F { test15() : Int { { test2(); 0; } }; };  ------------> "%F*"
// %tmp.49 = getelementptr %F, %F* %tmp.47, i32 0, i32 0  || ptr is %tmp.47 || func_class is "%F"
// %tmp.50 = load %_F_vtable*, %_F_vtable** %tmp.49
// %tmp.51 = getelementptr %_F_vtable, %_F_vtable* %tmp.50, i32 0, i32 9 || ret_val is %tmp.51
// %tmp.52 = load %F* (%F*) *, %F* (%F*) ** %tmp.51
// %tmp.53 = call %F*(%F* ) %tmp.52( %F* %tmp.47 )
// ---------------------------------------------------------------------------------------------------------------------
// class F { test15() : Int { { p.test2(); 0; } }; };  ------------> "%C*"
// %tmp.59 = getelementptr %C, %C* %tmp.57, i32 0, i32 0  || ptr is %tmp.57 || func_class is "%C"
// %tmp.60 = load %_C_vtable*, %_C_vtable** %tmp.59
// %tmp.61 = getelementptr %_C_vtable, %_C_vtable* %tmp.60, i32 0, i32 9 || ret_val is %tmp.61
// %tmp.62 = load %C* (%C*) *, %C* (%C*) ** %tmp.61
// %tmp.63 = call %C*(%C* ) %tmp.62( %C* %tmp.57 )
auto Get_Func_Addr(CgenEnvironment* env, CgenNode* func_class, llvm::Value* ptr, std::string clfunc_name) {
  // [%tmp.49 = getelementptr %F, %F* %tmp.47, i32 0, i32 0] || ptr acts as %tmp.47 || func_class acts as %F
  auto class_for_func = env->Type_Lookup[func_class->get_type_name()];
  auto vtable_prototype_ptr = env->builder.CreateGEP(class_for_func, ptr, {llvm::ConstantInt::get(llvm::Type::getInt32Ty(env->context), 0), llvm::ConstantInt::get(llvm::Type::getInt32Ty(env->context), 0)});
  
  // %tmp.50 = load %_F_vtable*, %_F_vtable** %tmp.49 
  auto vtable_type = env->Vtable_Type_Lookup[func_class->get_vtable_type_name()];
  auto vtable_ptr = env->builder.CreateLoad(llvm::PointerType::get(vtable_type, 0), vtable_prototype_ptr);
  
  // %tmp.51 = getelementptr %_F_vtable, %_F_vtable* %tmp.50, i32 0, i32 9 
  auto func_offset = (*func_class->get_current_clmethod_to_offset())[clfunc_name];
  auto func_ptr = env->builder.CreateGEP(vtable_type, vtable_ptr, {llvm::ConstantInt::get(llvm::Type::getInt32Ty(env->context), 0), llvm::ConstantInt::get(llvm::Type::getInt32Ty(env->context), func_offset)});

  return func_ptr;
}
// class B { test2(): SELF_TYPE{} }  || class C inherits B{} || class F inherits ... {p : C}
// ---------------------------------------------------------------------------------------------------------------------
// class F { test15() : Int { { test2(); 0; } }; };  ------------> "%F*"
// %tmp.49 = getelementptr %F, %F* %tmp.47, i32 0, i32 0  || func_class is "%F"
// class F { test15() : Int { { p.test2(); 0; } }; };  ------------> "%C*"
// %tmp.59 = getelementptr %C, %C* %tmp.57, i32 0, i32 0  || func_class is "%C"
// ret_val is function pointer
auto Get_Func_Ptr(CgenEnvironment* env, CgenNode* func_class, std::string clfunc_name) {
  auto func_offset = (*func_class->get_current_clmethod_to_offset())[clfunc_name] - 4; assert(func_offset >= 0);

  auto [defined_class, defined_method] = (*func_class->get_current_vtable_tp())[func_offset];
  auto get_func_ll_name = defined_class->get_function_name(defined_method->get_name()->get_string());
  auto function_ptr = env->llmethod_to_Funtion_Ptr[get_func_ll_name];

  assert(function_ptr);
  return function_ptr;
}
// two Conform, one inside the define function body, one after call function
// <i32/i1/%Main/%B, %Int/%Bool/%Main/%B, i32/i1/%Main/%B, ... || i32/i1/%Main/%B>
// ret_, self_, para_, ...
auto Get_Func_Decl_Type(CgenEnvironment* env, CgenNode* func_class, std::string clfunc_name) {
  auto func_offset = (*func_class->get_current_clmethod_to_offset())[clfunc_name] - 4; assert(func_offset >= 0);

  auto [_, defined_method] = (*func_class->get_current_vtable_tp())[func_offset];

  std::vector<llvm::Type*> type_;
  auto ret_ = Get_Decl_Type(env, func_class, defined_method->get_return_type()->get_string());
  type_.push_back(ret_);
  auto self_ = env->Type_Lookup[func_class->get_type_name()];
  type_.push_back(self_);
  
  auto formals = (*defined_method->get_formals()); 
  for (int i = formals->first(); formals->more(i); i = formals->next(i)) {
    auto formal_iter = formals->nth(i);
    type_.push_back(Get_Decl_Type(env, func_class, formal_iter->get_type_decl()->get_string()));
  }

  return type_;
}

// class B { test2(): SELF_TYPE{} }  || class C inherits B{} || class F inherits ... {p : C}
// ---------------------------------------------------------------------------------------------------------------------
// class F { test15() : Int { { p@B.test2(); 0; } }; };  ------------> "%B*"
// %tmp.69 = getelementptr %_B_vtable, %_B_vtable* @_B_vtable_prototype, i32 0, i32 9 || func_class is "%B"
// %tmp.70 = load %B* (%B*) *, %B* (%B*) ** %tmp.69 || ret_val is %tmp.69
// %tmp.71 = bitcast %C* %tmp.67 to %B*
// %tmp.72 = call %B*(%B* ) %tmp.70( %B* %tmp.71 )
// %tmp.73 = bitcast %B* %tmp.72 to %C*
auto Get_Func_Addr_Static(CgenEnvironment* env, CgenNode* func_class, std::string clfunc_name) {
  // %tmp.69 = getelementptr %_B_vtable, %_B_vtable* @_B_vtable_prototype, i32 0, i32 9
  auto vtable_type = env->Vtable_Type_Lookup[func_class->get_vtable_type_name()];
  auto vtable_proto = env->Vtable_Proto_Lookup[func_class->get_vtable_name()];
  auto func_offset = (*func_class->get_current_clmethod_to_offset())[clfunc_name];
  auto ret_val = env->builder.CreateGEP(vtable_type, vtable_proto, {llvm::ConstantInt::get(llvm::Type::getInt32Ty(env->context), 0), llvm::ConstantInt::get(llvm::Type::getInt32Ty(env->context), func_offset)});
  return ret_val;
}
// two Conform, one inside the define function body, one after call function
// <i32/i1/%Main/%B, %Int/%Bool/%Main/%B, i32/i1/%Main/%B, ... || i32/i1/%Main/%B>
// ret_, self_, para_, ...
auto Get_Func_Ret_Type_Static(CgenEnvironment* env, CgenNode* func_class, std::string clfunc_name) {
  auto func_offset = (*func_class->get_current_clmethod_to_offset())[clfunc_name] - 4; assert(func_offset >= 0);

  auto [_, defined_method] = (*func_class->get_current_vtable_tp())[func_offset];

  auto ret_ = Get_Decl_Type(env, func_class, defined_method->get_return_type()->get_string());

  return ret_;
}

auto LCA(CgenEnvironment* env, llvm::Type* a, llvm::Type* b) {
  llvm::StructType* a_struct = llvm::cast<llvm::StructType>(a);
  llvm::StructType* b_struct = llvm::cast<llvm::StructType>(b);
  CgenNode* A = env->Name_to_Node[a_struct->getName().str()];
  CgenNode* B = env->Name_to_Node[b_struct->getName().str()];
  std::unordered_map<CgenNode*, bool> storeA;

  CgenNode* curr = A;
  CgenNode* grab = NULL;
  while (curr) {
    storeA[curr] = true;
    if (curr->get_type_name() == "Object") {
      break;
    }
    curr = curr->get_parentnd();
  }

  curr = B;
  while (curr) {
    if (storeA.find(curr) != storeA.end()) {
      grab = curr;
      break;
    }
    curr = curr->get_parentnd();
  }

  assert(grab);
  return grab;
}

// new Int, new Int ---> i32 new Int, i32 ---> i32 i32, i32 ---> i32
// new Bool, new Bool ---> i1 new Bool, i1 ---> i1 i1, i1 ---> i1
// %Object, %Int, %B, ....
auto Find_Parent(CgenEnvironment* env, llvm::Type* a, llvm::Type* b) {
  llvm::Type* res;
  if (a->isStructTy() && b->isStructTy()) {
    llvm::StructType* a_struct = llvm::cast<llvm::StructType>(a);
    llvm::StructType* b_struct = llvm::cast<llvm::StructType>(b);
    if (a_struct->getName() == "Int" && b_struct->getName() == "Int") { // new Int, new Int ---> i32
      res = llvm::Type::getInt32Ty(env->context);
    } else if (a_struct->getName() == "Bool" && b_struct->getName() == "Bool") { // new Bool, new Bool ---> i1
      res = llvm::Type::getInt1Ty(env->context);
    } else {
      auto node = LCA(env, a_struct, b_struct);
      res = env->Type_Lookup[node->get_type_name()];
    }
  } else if ((!a->isStructTy()) && (!b->isStructTy())) {
    if (a->isIntegerTy(32) && b->isIntegerTy(32)) { // i32, i32 ---> i32
      res = llvm::Type::getInt32Ty(env->context);
    } else if (a->isIntegerTy(1) && b->isIntegerTy(1)) { // i1, i1 ---> i1
      res = llvm::Type::getInt1Ty(env->context);
    } else { // i32, i1 ---> %Object
      res = env->class_table.Type_Lookup["Object"];
    }
  } else if ((!a->isStructTy()) && b->isStructTy()) {
    llvm::StructType* b_struct = llvm::cast<llvm::StructType>(b);
    if (a->isIntegerTy(32) && b_struct->getName() == "Int") { // i32, Int ---> i32
      res = llvm::Type::getInt32Ty(env->context);
    } else if (a->isIntegerTy(1) && b_struct->getName() == "Bool") { // i1, Bool ---> i1
      res = llvm::Type::getInt1Ty(env->context);
    } else {
      res = env->class_table.Type_Lookup["Object"];
    }
  } else if (a->isStructTy() && (!b->isStructTy())) {
    llvm::StructType* a_struct = llvm::cast<llvm::StructType>(a);
    if (a_struct->getName() == "Int" && b->isIntegerTy(32)) { // Int, i32 ---> i32
      res = llvm::Type::getInt32Ty(env->context);
    } else if (a_struct->getName() == "Bool" && b->isIntegerTy(1)) { // Bool, i1 ---> i1
      res = llvm::Type::getInt1Ty(env->context);
    } else {
      res = env->class_table.Type_Lookup["Object"];
    }
  } else {
    assert(false);
  }
  return res;
}

// current env, class curr_cls {}, .....
// let33(x : Int, y : B*): Int ----> i32 @Main.let33(%Main* %self, i32 %x, %B* %y)
// [%tmp.102 = alloca %Main*]
// [%tmp.103 = alloca i32]
// [%tmp.104 = alloca %B*]
// [store %Main* %self, %Main** %tmp.102] || SELF_ADDR is %tmp.102
// [store i32 %x, i32* %tmp.103] || bind x ----> %tmp.103 || bind x ----> "i32"
// [store %B* %y, %B** %tmp.104] || bind y ----> %tmp.104 || bind y ----> "%B"
auto Create_Param(CgenEnvironment* env, CgenNode* curr_cls, llvm::Function* func_ptr, method_class* method_ptr) {
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
      env->add_binding(formals->nth(i-1)->get_name(), alloca_addr);
      auto type_str = formals->nth(i-1)->get_type_decl()->get_string();
      if (type_str == "Int") {
        env->var_tp_add_binding(formals->nth(i-1)->get_name(), llvm::Type::getInt32Ty(env->context));
      } else if (type_str == "Bool") {
        env->var_tp_add_binding(formals->nth(i-1)->get_name(), llvm::Type::getInt1Ty(env->context));
      } else if (type_str == "SELF_TYPE") {
        env->var_tp_add_binding(formals->nth(i-1)->get_name(), env->Type_Lookup[curr_cls->get_type_name()]);
      } else {
        env->var_tp_add_binding(formals->nth(i-1)->get_name(), env->Type_Lookup[type_str]);
      }
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
