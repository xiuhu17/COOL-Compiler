//
// The following include files must come first.

#ifndef COOL_TREE_HANDCODE_H
#define COOL_TREE_HANDCODE_H

#include "operand.h"
#include "stringtab.h"
#include "symtab.h"
#include "tree.h"
#include "utils.h"
#include <iostream>
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

#define Class__EXTRAS                                                          \
  virtual void dump_with_types(std::ostream &, int) = 0;                       \
  virtual Symbol get_name() = 0;                                               \
  virtual Symbol get_parent() = 0;                                             \
  virtual Symbol get_filename() = 0;

#define Feature_EXTRAS                                                         \
  virtual void dump_with_types(std::ostream &, int) = 0;                       \
  virtual void layout_feature(CgenNode *cls) = 0;                              \
  virtual void make_alloca(CgenEnvironment *env) = 0;                          \
  virtual Expression get_expression() = 0;                                     \
  virtual void code(CgenEnvironment *env) = 0;

#define Expression_EXTRAS                                                      \
  virtual void dump_with_types(std::ostream &, int) = 0;                       \
  virtual void make_alloca(CgenEnvironment *) = 0;                             \
  virtual operand code(CgenEnvironment *) = 0;                                 \
  virtual op_type get_expr_type(CgenEnvironment *) = 0;                        \
  virtual void    set_expr_type(CgenEnvironment *, op_type) = 0;               \
  op_type op_expr_tp;                                                          \
  Symbol type;                                                                 \
  Symbol get_type() { return type; }                                           \
  Expression set_type(Symbol s) {                                              \
    type = s;                                                                  \
    return this;                                                               \
  }                                                                            \
  virtual int no_code() { return 0; } /* ## */                                 \
  void dump_type(std::ostream &, int);                                         \
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
  virtual void make_alloca(CgenEnvironment *env);                              \
  void code(CgenEnvironment *env);

#define method_EXTRAS                                                          \
  Expression get_expression() override { return expr; }                        \
  virtual Symbol get_return_type() { return return_type; }

#define attr_EXTRAS                                                            \
  Expression get_expression() override { return init; }                        

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
  virtual void make_alloca(CgenEnvironment *) = 0;                             \
  virtual operand code(operand, operand, const op_type,                        \
                       CgenEnvironment *) = 0;                                 \
  virtual void dump_with_types(std::ostream &, int) = 0;

#define branch_EXTRAS                                                          \
  Symbol get_type_decl() { return type_decl; }                                 \
  Expression get_expr() { return expr; }                                       \
  void make_alloca(CgenEnvironment *);                                         \
  op_type alloca_type;                                                         \
  operand alloca_op;                                                           \
  operand code(operand expr_val, operand tag, const op_type join_type,         \
               CgenEnvironment *env);                                          \
  void dump_with_types(std::ostream &, int);

#define Expression_SHARED_EXTRAS                                                      \
  void make_alloca(CgenEnvironment *);                                                \
  operand code(CgenEnvironment *);                                                    \
  void dump_with_types(std::ostream &, int);                                          \
  op_type get_expr_type(CgenEnvironment *env) override {return op_expr_tp;}           \
  void set_expr_type(CgenEnvironment *env, op_type tp) override {op_expr_tp = tp;}   

#define no_expr_EXTRAS        /* ## */                                         \
  int no_code() { return 1; } /* ## */

#define cond_EXTRAS                                                            \
  op_type result_type;                                                         \
  operand res_ptr;
#define let_EXTRAS                                                             \
  op_type id_type;                                                             \
  operand id_op;
#define typcase_EXTRAS                                                         \
  op_type alloca_type;                                                         \
  operand alloca_op;                                                


  // store
// Expression_EXTRAS:   [op_expr_tp] is the "op_type of entire Expression-subclass"
// cond_EXTRAS:         [result_type] is the "op_type" of "newly allocated stack-allocation memory" for entire {if .. then ... else ... fi}
//                      [res_ptr] is the "register/operand which store the addr" of "newly allocated stack-allocation memory" for entire {if .. then ... else ... fi}
// let_EXTRAS:          [id_type] is the "op_type" of "newly allocated stack-allocation memory" for {identifier}
//                      [id_op] is the "register/operand which store the addr" of "newly allocated stack-allocation memory" for {identifier}

// make_alloca: 1A: use alloca || set_up_part
//              1B: "register/operand which store the addr" of "newly allocated stack-allocation memory" and "op_type" of "newly allocated stack-allocation memory" into cond_EXTRAS or let_EXTRAS; 
//              1C: "op_type" of "op_type of entire Expression-subclass" into Expression_EXTRAS
// code:        2A: return "operand/register" represents "entire Expression-subclass(operation/result)"; (we do not know the specific value of each register/operand, we will know it until run-time, but we can use "register/operand" represent "entire Expression-subclass(operation/result)", called "register/operand representation") 
//              2B: emit corrosponding IR code || set_up_part

// we need to control scope, since same variable/identifier name may have different type or address(different address will store different value)

// make_alloca: 1: recursivly invoke {invoke make_alloca to all its Expression-subclass-member} ||  recursivly invoke "1A_recur 1B_recur 1C_recur"
//              2: use the {get "1B_recur 1C_recur" <- all its Expression-subclass-member}; use them for alloca
//              3: use value from 1B_recur and 1C_recur; allocate on-stack memory : 1A; store the newly allocated address and store newly_allocated op_type : 1B
//              4: set the {type -> the entire Expression-subclass} : 1C
//              5: bind [identifier] to [op_type] in [current var_tp_table scope] inside {let_class} || variable ===> type
//              6: find [identifier] to [op_type] in [current var_tp_table scope] inside {object_class} || variable ===> type
//              7: when asking type for variable, we need to control scope of [identifier] to [op_type]

// code:        1: recursivly invoke {invoke code to all its Expression-subclass member} || 2A_recur 2B_recur
//              2: use the {get "2A_recur" <- all its Expression-subclass-member}; use them("register/operand representation") for later IR code-generation 
//              3: use the value from 2A_recur; do IR Code-Generation ; use "register/operand" represent "entire Expression-subclass(operation/result)" which is "register/operand representation"; return it : 2A
//              4: do store-IR Code-Generation using "register/operand which store the addr" of "newly allocated stack-allocation memory", cond_EXTRAS-res_ptr or let_EXTRAS-id_op in {cond_Class} {let_Class} {assign_Class}; since we could only get "register/operand representation" until code-stage || addr ~~~ value
//              5: bind [identifier] to [id_op] in the [current var_table scope] inside {let_class} || variable ===> addr 
//              6: find [identifier] to [id_op] in the [current var_table scope] inside {assign_class} & {object_class} || variable ===> addr
//              7: do load-IR Code-Generation using "register/operand which store the addr" of "newly allocated stack-allocation memory", cond_EXTRAS-res_ptr or let_EXTRAS-id_op in {cond_Class} {object_Class}
//              7: enter/exit scope to realize control scope in the code-stage || control-scope, control "variable ===> addr" in different scope

// type, addr are all stored inside let_Extras

#endif /* COOL_TREE_HANDCODE_H */

