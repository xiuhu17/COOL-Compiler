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
        basic_status(bstatus), class_table(class_table), tag(-1) {}

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

#ifdef MP3
  std::string get_type_name() { return name->get_string(); }
  std::string get_vtable_type_name() {
    return "_" + get_type_name() + "_vtable";
  }
  std::string get_vtable_name() {
    return "_" + get_type_name() + "_vtable_prototype";
  }
  std::string get_init_function_name() { return get_type_name() + "_new"; }
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

private:
  CgenNode *parentnd;               // Parent of class
  std::vector<CgenNode *> children; // Children of class
  Basicness basic_status;           // `Basic' or 'NotBasic'
  CgenClassTable *class_table;
  // Class tag. Should be unique for each class in the tree
  int tag, max_child;
  std::ostream *ct_stream;

  // TODO: Add more functions / fields here as necessary.
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
      : var_table(), vat_tp_table(), cur_class(cur_class),
        class_table(*cur_class->get_classtable()), context(class_table.context), 
        builder(class_table.builder), the_module(class_table.the_module) {
    tmp_count = 0;
    ok_count = 0;
    loop_count = 0;
    true_count = 0;
    false_count = 0;
    end_count = 0;
    var_table.enterscope();
    vat_tp_table.enterscope();

    // TODO: add code here
  }

  CgenNode *get_class() { return cur_class; }
  void set_class(CgenNode *c) { cur_class = c; }

  // Must return the CgenNode for a class given the symbol of its name
  CgenNode *type_to_class(Symbol t);

  std::pair<llvm::Type *, llvm::Value *> find_in_scopes(Symbol name);

  void add_binding(Symbol name, llvm::Value *val_ptr) {
    var_table.insert(name, val_ptr);
  }
  void open_scope() { var_table.enterscope(); }
  void close_scope() { var_table.exitscope(); }

  void vat_tp_add_binding(Symbol name, llvm::Type *tp_ptr) {
    vat_tp_table.insert(name, tp_ptr);
  }
  void var_tp_open_scope() { vat_tp_table.enterscope(); }
  void vat_tp_close_scope() { vat_tp_table.exitscope(); }

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

private:
  // mapping from variable names to memory locations
  cool::SymbolTable<llvm::Value> var_table;
  cool::SymbolTable<llvm::Type> vat_tp_table;
  CgenNode *cur_class;
  int tmp_count, ok_count; 
  int loop_count, true_count, false_count, end_count;

public:
  CgenClassTable &class_table;
  // These are references to the current LLVM context and module,
  // and they point to the ones in CgenClassTable.
  llvm::LLVMContext &context;
  llvm::IRBuilder<> &builder;
  llvm::Module &the_module;
};

#ifdef MP3
// TODO: implement these functions (MP3), and add more functions as necessary

// Utitlity function
// Generate any code necessary to convert from given Value* to
// dest_type, assuming it has already been checked to be compatible
llvm::Value *conform(llvm::Value *src, llvm::Type *dest_type,
                     CgenEnvironment *env);
#endif
