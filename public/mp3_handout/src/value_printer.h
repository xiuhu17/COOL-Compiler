/* ValuePrinter
 * Contains methods to print the instructions in the format that LLVM supports.
 * You are only given the instructions that you'll need to use in creating the
 * code generator in MP2.1. For a full list of LLVM instructions, visit
 * http://llvm.org/docs/LangRef.html
 */

#ifndef __VALUE_PRINTER_H
#define __VALUE_PRINTER_H

#include "operand.h"
#include <assert.h>
#include <vector>

using label = std::string;
/* Values acceptable by the icmp instruction */
typedef enum { EQ, NE, LT, LE, GT, GE } icmp_val;

class ValuePrinter {
private:
  void bin_inst(std::ostream &o, std::string inst_name, operand op1,
                operand op2, operand result);
  operand bin_inst(std::string inst_name, operand op1, operand op2);
  // if an ostream is explicitly supplied, check it is compatible with
  // constructor arguments.
  void check_ostream(std::ostream &supplied) {
    assert(!stream || (stream == &supplied));
  }
  // if called without an explicitly supplied ostream,
  // check that one was provided in the constructor.
  void check_ostream() { assert(stream); }
  std::ostream *stream;

public:
  /* default constructor. */
  ValuePrinter() : stream(NULL) {}
  /* constructor taking ostream.
     If any methods taking and explicit ostream are called, the supplied ostream
     must match. */
  ValuePrinter(std::ostream &o) : stream(&o) {}

  /* Global constant initialization */
  void init_constant(std::ostream &o, std::string name, const_value op);
  void init_constant(std::string name, const_value op);
  /* External constant declaration */
  void init_ext_constant(std::ostream &o, std::string name, op_type type);
  void init_ext_constant(std::string name, op_type type);

  /* Function definitions and declarations */
  void declare(std::ostream &o, op_type ret_type, std::string name,
               std::vector<op_type> args);
  void declare(op_type ret_type, std::string name, std::vector<op_type> args);
  void define(std::ostream &o, op_type ret_type, std::string name,
              std::vector<operand> args);
  void define(op_type ret_type, std::string name, std::vector<operand> args);
  void end_define(std::ostream &o) {
    check_ostream(o);
    o << "}\n\n";
  }
  void end_define() { *stream << "}\n\n"; }

  /* Type definition */
  void type_define(std::ostream &o, std::string class_name,
                   std::vector<op_type> attributes);
  void type_define(std::string class_name, std::vector<op_type> attributes);

  void type_alias_define(std::ostream &o, std::string alias_name, op_type type);
  void type_alias_define(std::string alias_name, op_type type);

  /* Structure constant definition */
  void init_struct_constant(std::ostream &o, operand constant,
                            std::vector<op_type> field_types,
                            std::vector<const_value> init_values);
  void init_struct_constant(operand constant, std::vector<op_type> field_types,
                            std::vector<const_value> init_values);

  /* Print a label */
  void begin_block(std::string label);

  /* Instruction Output methods are duplicated, once with the old signature
     taking an ostream and the result, and a new signature which does not take
     an ostream, and usually produces the result operand itself. */
  /* Binary operations */
  void add(std::ostream &o, operand op1, operand op2, operand result);
  void sub(std::ostream &o, operand op1, operand op2, operand result);
  void mul(std::ostream &o, operand op1, operand op2, operand result);
  void div(std::ostream &o, operand op1, operand op2, operand result);
  void xor_in(std::ostream &o, operand op1, operand op2, operand result);

  operand add(operand op1, operand op2);
  operand sub(operand op1, operand op2);
  operand mul(operand op1, operand op2);
  operand div(operand op1, operand op2);
  operand xor_in(operand op1, operand op2);

  /* Memory access instructions */
  void malloc_mem(std::ostream &o, int size, operand result);
  void malloc_mem(std::ostream &o, operand size, operand result);
  void alloca_mem(std::ostream &o, op_type type, operand op2);
  void load(std::ostream &o, op_type type, operand op, operand op2);
  void store(std::ostream &o, operand op, operand op2);
  void getelementptr(std::ostream &o, op_type type, operand op1, operand op2,
                     operand result);
  void getelementptr(std::ostream &o, op_type type, operand op1, operand op2,
                     operand op3, operand result);
  void getelementptr(std::ostream &o, op_type type, operand op1, operand op2,
                     operand op3, operand op4, operand result);
  void getelementptr(std::ostream &o, op_type type, operand op1, operand op2,
                     operand op3, operand op4, operand op5, operand result);
  void getelementptr(std::ostream &o, op_type type, std::vector<operand> op,
                     operand result);

  operand malloc_mem(int size);
  operand malloc_mem(operand size);
  operand alloca_mem(op_type type);
  operand load(op_type type, operand op);

  /* store does not produce a result */
  void store(operand op, operand op2);

  /* getelementptr continues to requre an argument for the result type,
     becuase it is difficult to compute. */
  operand getelementptr(op_type type, operand op1, operand op2,
                        op_type result_type);
  operand getelementptr(op_type type, operand op1, operand op2, operand op3,
                        op_type result_type);
  operand getelementptr(op_type type, operand op1, operand op2, operand op3,
                        operand op4, op_type result_type);
  operand getelementptr(op_type type, operand op1, operand op2, operand op3,
                        operand op4, operand op5, op_type result_type);
  operand getelementptr(op_type type, std::vector<operand> op,
                        op_type result_type);

  /* Terminator instructions */
  void branch_cond(std::ostream &o, operand op, label label_true,
                   label label_false);
  void branch_uncond(std::ostream &o, std::string label);
  void ret(std::ostream &o, operand op);
  void unreachable(std::ostream &o) {
    check_ostream(o);
    o << "\tunreachable\n";
  }

  void branch_cond(operand op, label label_true, label label_false);
  void branch_uncond(std::string label);
  void ret(operand op);
  void unreachable() { unreachable(*stream); }

  /* Other operations */
  void select(std::ostream &o, operand op1, operand op2, operand op3,
              operand result);
  void icmp(std::ostream &o, icmp_val v, operand op1, operand op2,
            operand result);
  void call(std::ostream &o, std::vector<op_type> arg_types,
            std::string fn_name, bool is_global, std::vector<operand> args,
            operand result);
  void bitcast(std::ostream &o, operand op, op_type new_type, operand result);
  void ptrtoint(std::ostream &o, operand op, op_type new_type, operand result);

  operand select(operand op1, operand op2, operand op3);
  operand icmp(icmp_val v, operand op1, operand op2);
  operand call(std::vector<op_type> arg_types, op_type result_type,
               std::string fn_name, bool is_global, std::vector<operand> args);
  operand bitcast(operand op, op_type new_type);
  operand ptrtoint(operand op, op_type new_type);

  operand call_variadic(std::vector<op_type> arg_types, op_type result_type,
                        std::string fn_name, bool is_global,
                        std::vector<operand> args);
};

#endif
