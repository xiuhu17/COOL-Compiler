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
#include "value_printer.h"
#include <map>

class CgenNode;

// CgenClassTable represents the top level of a Cool program, which is
// basically a list of classes. The class table is used to look up classes
// (CgenNodes) by name, and it also handles global code generation tasks.
// The CgenClassTable constructor is where you'll find the entry point for
// code generation for an entire Cool program.
class CgenClassTable : public cool::SymbolTable<CgenNode> {
public:
  // CgenClassTable constructor begins and ends the code generation process
  CgenClassTable(Classes, std::ostream &str);

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
  // The ostream where we are emitting code
  std::ostream *ct_stream;
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
        basic_status(bstatus), class_table(class_table), tag(-1),
        ct_stream(class_table->ct_stream) {}

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
  CgenEnvironment(std::ostream &stream, CgenNode *cur_class)
      : var_table(), cur_class(cur_class), block_count(0), tmp_count(0),
        ok_count(0), cur_stream(&stream) {
    var_table.enterscope();
    // TODO: add code here
  }

  // fresh name generation functions
  std::string new_name() { return "tmp." + std::to_string(tmp_count++); }
  std::string new_ok_label() { return "ok." + std::to_string(ok_count++); }
  std::string new_label(const std::string &prefix, bool increment) {
    std::string suffix = std::to_string(block_count);
    block_count += increment;
    return prefix + suffix;
  }

  CgenNode *get_class() { return cur_class; }
  void set_class(CgenNode *c) { cur_class = c; }

  // Must return the CgenNode for a class given the symbol of its name
  CgenNode *type_to_class(Symbol t);

  operand *find_in_scopes(Symbol name) {
    return var_table.find_in_scopes(name);
  }
  void add_binding(Symbol name, operand *op) { var_table.insert(name, op); }
  void open_scope() { var_table.enterscope(); }
  void close_scope() { var_table.exitscope(); }

  // TODO: Add more functions as necessary.

private:
  cool::SymbolTable<operand>
      var_table; // mapping from variable names to memory locations
  CgenNode *cur_class;
  int block_count, tmp_count, ok_count; // Keep counters for unique name
                                        // generation in the current method

public:
  std::ostream *cur_stream;
};

#ifdef MP3
// TODO: implement these functions (MP3), and add more functions as necessary

// Utitlity function
// Generate any code necessary to convert from given operand to
// dest_type, assuming it has already been checked to be compatible
operand conform(operand src, op_type dest_type, CgenEnvironment *env);
#endif
