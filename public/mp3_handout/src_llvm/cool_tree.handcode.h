//
// The following include files must come first.

#ifndef COOL_TREE_HANDCODE_H
#define COOL_TREE_HANDCODE_H

#include "stringtab.h"
#include "symtab.h"
#include "tree.h"
#include "utils.h"
#include <iostream>
#include <llvm/IR/Function.h>
#include <llvm/IR/Value.h>
#include <string>

class CgenEnvironment;
class CgenNode;

class Program_class;
typedef Program_class *Program;
class Class__class;
typedef Class__class *Class_;
class Feature_class;
typedef Feature_class *Feature;
class Formal_class;
typedef Formal_class *Formal;
class Expression_class;
typedef Expression_class *Expression;
class Case_class;
typedef Case_class *Case;

typedef list_node<Class_> Classes_class;
typedef Classes_class *Classes;
typedef list_node<Feature> Features_class;
typedef Features_class *Features;
typedef list_node<Formal> Formals_class;
typedef Formals_class *Formals;
typedef list_node<Expression> Expressions_class;
typedef Expressions_class *Expressions;
typedef list_node<Case> Cases_class;
typedef Cases_class *Cases;

// Abstract classes:

#define Program_EXTRAS                                                         \
  virtual void dump_with_types(std::ostream &, int) = 0;                       \
  virtual void cgen(const std::optional<std::string> &) = 0;

#define Class__EXTRAS virtual void dump_with_types(std::ostream &, int) = 0;

#define Feature_EXTRAS                                                         \
  virtual void dump_with_types(std::ostream &, int) = 0;                       \
  virtual void layout_feature(CgenNode *cls) = 0;                              \
  virtual llvm::Value *code(CgenEnvironment *) = 0;                            \
  virtual Symbol get_name() = 0;

#define Expression_EXTRAS                                                      \
  virtual void dump_with_types(std::ostream &, int) = 0;                       \
  virtual llvm::Value *code(CgenEnvironment *) = 0;                            \
  Symbol type;                                                                 \
  Symbol get_type() { return type; }                                           \
  Expression set_type(Symbol s) {                                              \
    type = s;                                                                  \
    return this;                                                               \
  }                                                                            \
  virtual int no_code() { return 0; } /* ## */                                 \
  void dump_type(std::ostream &, int);                                         \
  virtual llvm::Type *get_expr_tp(CgenEnvironment *) = 0;                      \
  virtual void set_expr_tp(CgenEnvironment *, llvm::Type*) = 0;               \
  llvm::Type *expr_tp;                                                         \
  Expression_class() { type = (Symbol)NULL; }

#define program_EXTRAS                                                         \
  void dump_with_types(std::ostream &, int);                                   \
  void cgen(const std::optional<std::string> &);

#define class__EXTRAS                                                          \
  Symbol get_name() { return name; }                                           \
  Symbol get_parent() { return parent; }                                       \
  Symbol get_filename() { return filename; }                                   \
  void dump_with_types(std::ostream &, int);

#define Feature_SHARED_EXTRAS                                                  \
  void dump_with_types(std::ostream &, int);                                   \
  void layout_feature(CgenNode *cls);                                          \
  Symbol get_name() { return name; }

#define method_EXTRAS                                                          \
  virtual Symbol get_return_type() { return return_type; }                     \
  llvm::Function *code(CgenEnvironment *) override;

#define attr_EXTRAS                                                            \
  llvm::Value *code(CgenEnvironment *) override;                               \
  Symbol get_type_decl() { return type_decl; }

#define Formal_EXTRAS                                                          \
  virtual Symbol get_type_decl() = 0; /* ## */                                 \
  virtual Symbol get_name() = 0;      /* ## */                                 \
  virtual void dump_with_types(std::ostream &, int) = 0;

#define formal_EXTRAS                                                          \
  Symbol get_type_decl() { return type_decl; } /* ## */                        \
  Symbol get_name() { return name; }           /* ## */                        \
  void dump_with_types(std::ostream &, int);

#define Case_EXTRAS                                                            \
  virtual Symbol get_type_decl() = 0;                                          \
  virtual llvm::Value *code(llvm::Value *, llvm::Value *, llvm::Type *,        \
                            CgenEnvironment *) = 0;                            \
  virtual void dump_with_types(std::ostream &, int) = 0;

#define branch_EXTRAS                                                          \
  Symbol get_type_decl() { return type_decl; }                                 \
  Expression get_expr() { return expr; }                                       \
  llvm::Value *alloca_op;                                                      \
  llvm::Value *code(llvm::Value *expr_val, llvm::Value *tag,                   \
                    llvm::Type *join_type, CgenEnvironment *env);              \
  void dump_with_types(std::ostream &, int);

#define Expression_SHARED_EXTRAS                                               \
  llvm::Value *code(CgenEnvironment *);                                        \
  void dump_with_types(std::ostream &, int);                                   \
  llvm::Type *get_expr_tp(CgenEnvironment *env) override {return expr_tp;}     \
  void set_expr_tp(CgenEnvironment *env, llvm::Type* tp_) override {expr_tp = tp_;}           

#define no_expr_EXTRAS        /* ## */                                         \
  int no_code() { return 1; } /* ## */

#define cond_EXTRAS                                                            \
  llvm::Type  *if_type;                                                \
  llvm::Value *if_addr_val;
#define let_EXTRAS                                                             \
  llvm::Type  *identifier_type;                                                         \
  llvm::Value *identifier_addr_val;
// in mp2, assume if_type = expression_type
#endif /* COOL_TREE_HANDCODE_H */
