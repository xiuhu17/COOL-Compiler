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
  std::unordered_map<std::string, llvm::Type*> Type_Lookup;
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
        basic_status(bstatus), class_table(class_table), tag(-1), obj_tp(0), vtable_tp(0), clmethod_to_llmethod(0), clattr_to_offset(0), clmethod_to_offset(0), Function_Body_Map(0) {}

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
  // access current real function name in cl to the offsetin vtable
  auto get_current_clmethod_to_offset() {
    return &clmethod_to_offset;
  }
  // access current real attr name in cl to the offsetin obj
  auto get_current_clattr_to_offset() {
    return &clattr_to_offset;
  }
  // access current map
  auto get_current_clmethod_to_llmethod() {
    return &clmethod_to_llmethod;
  }

  auto get_current_Function_Body_Map() {
    return &Function_Body_Map;
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
  // access parent real function name in cl to the offsetin vtable
  std::unordered_map<Symbol, int>* get_parent_clmethod_to_offset(){
    if (parentnd == NULL) {
      return NULL;
    }
    return parentnd->get_current_clmethod_to_offset();
  }
  // access parent real attr name in cl to the offsetin obj
  std::unordered_map<Symbol, int>* get_parent_clattr_to_offset(){
    if (parentnd == NULL) {
      return NULL;
    }
    return parentnd->get_current_clattr_to_offset();
  }

  std::unordered_map<std::string, int>* get_parent_clmethod_to_llmethod() {
    if (parentnd == NULL) {
      return NULL;
    }
    return parentnd->get_current_clmethod_to_llmethod();
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
  std::vector<std::pair<CgenNode*, attr_class*>> obj_tp;
  std::vector<std::pair<CgenNode*, method_class*>> vtable_tp; // only for function after XXX_new; only overwrite or create new function change the type, it remains same until someone overwrite or create new function
  std::unordered_map<std::string, int> clmethod_to_llmethod; // only for function after XXX_new; only for those who overload clmethod or create new function do not need to bit cast
  
  // TODO:
  std::unordered_map<Symbol, int> clattr_to_offset;
  std::unordered_map<Symbol, int> clmethod_to_offset; // true name for cl file

  std::unordered_map<llvm::Function*, method_class*> Function_Body_Map;
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
      : var_table(), var_tp_table(), cur_class(cur_class),
        class_table(*cur_class->get_classtable()), context(class_table.context),
        builder(class_table.builder), the_module(class_table.the_module), Type_Lookup(class_table.Type_Lookup) {
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

  std::pair<llvm::Type *, llvm::Value *> find_in_scopes(Symbol name) {
    return {var_tp_table.find_in_scopes(name), var_table.find_in_scopes(name)};
  }

  void add_binding(Symbol name, llvm::Value *val_ptr) {
    var_table.insert(name, val_ptr);
  }
  void open_scope() { var_table.enterscope(); }
  void close_scope() { var_table.exitscope(); }

  void var_tp_add_binding(Symbol name, llvm::Type *tp_ptr) {
    var_tp_table.insert(name, tp_ptr);
  }
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
private:
  // mapping from variable names to memory locations
  cool::SymbolTable<llvm::Value> var_table;
  cool::SymbolTable<llvm::Type> var_tp_table;
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
  std::unordered_map<std::string, llvm::Type*> &Type_Lookup;
};

#ifdef MP3
// TODO: implement these functions (MP3), and add more functions as necessary

// Utitlity function
// Generate any code necessary to convert from given Value* to
// dest_type, assuming it has already been checked to be compatible
llvm::Value *conform(llvm::Value *src, llvm::Type *dest_type,
                     CgenEnvironment *env);
#endif
