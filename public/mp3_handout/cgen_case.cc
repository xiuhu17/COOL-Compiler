operand typcase_class::code(CgenEnvironment *env) {
  if (cgen_debug)
    std::cerr << "typecase::code()" << endl;
#ifndef MP3
  assert(0 && "Unsupported case for phase 1");
#else
  ValuePrinter vp(*env->cur_stream);
  CgenClassTable *ct = env->get_class()->get_classtable();

  string header_label = env->new_label("case.hdr.", false);
  string exit_label = env->new_label("case.exit.", false);

  // Generate code for expression to select on, and get its static type
  operand code_val = expr->code(env);
  operand expr_val = code_val;
  string code_val_t = code_val.get_typename();
  op_type join_type = env->type_to_class(type)->get_type_name();
  CgenNode *cls = env->type_to_class(expr->get_type());

  // Check for case on void, which gives a runtime error
  if (code_val.get_type().get_id() != INT32 &&
      code_val.get_type().get_id() != INT1) {
    op_type bool_type(INT1), empty_type;
    null_value null_op(code_val.get_type());
    operand icmp_result(bool_type, env->new_name());
    vp.icmp(*env->cur_stream, EQ, code_val, null_op, icmp_result);
    string ok_label = env->new_ok_label();
    vp.branch_cond(icmp_result, "abort", ok_label);
    vp.begin_block(ok_label);
  }

  operand tag = get_class_tag(expr_val, cls, env);
  vp.branch_uncond(header_label);
  string prev_label = header_label;
  vp.begin_block(header_label);

  env->branch_operand = alloca_op;

  std::vector<operand> values;
  env->next_label = exit_label;

  // Generate code for the branches
  for (int i = ct->get_num_classes() - 1; i >= 0; --i) {
    for (auto case_branch : cases) {
      if (i == ct->find_in_scopes(case_branch->get_type_decl())->get_tag()) {
        string prefix = string("case.") + itos(i) + ".";
        string case_label = env->new_label(prefix, false);
        vp.branch_uncond(case_label);
        vp.begin_block(case_label);
        operand val = case_branch->code(expr_val, tag, join_type, env);
        values.push_back(val);
      }
    }
  }

  // Abort if there was not a branch covering the actual type
  vp.branch_uncond("abort");

  // Done with case expression: get final result
  env->new_label("", true);
  vp.begin_block(exit_label);
  operand final_result(alloca_type, env->new_name());
  alloca_op.set_type(alloca_op.get_type().get_ptr_type());
  vp.load(*env->cur_stream, alloca_op.get_type().get_deref_type(),
          alloca_op, final_result);
  alloca_op.set_type(alloca_op.get_type().get_deref_type());

  if (cgen_debug)
    cerr << "Done typcase::code()" << endl;
  return final_result;
#endif
}

// Handle one branch of a Cool case expression.
// If the source tag is >= the branch tag
// and <= (max child of the branch class) tag,
// then the branch is a superclass of the source.
// See the MP3 handout for more information about our use of class tags.
operand branch_class::code(operand expr_val, operand tag, op_type join_type,
                           CgenEnvironment *env) {
#ifndef MP3
  assert(0 && "Unsupported case for phase 1");
#else
  operand empty;
  ValuePrinter vp(*env->cur_stream);
  if (cgen_debug)
    cerr << "In branch_class::code()" << endl;

  CgenNode *cls = env->get_class()->get_classtable()->find_in_scopes(type_decl);
  int my_tag = cls->get_tag();
  int max_child = cls->get_max_child();

  // Generate unique labels for branching into >= branch tag and <= max child
  string sg_label =
      env->new_label(string("src_gte_br") + "." + itos(my_tag) + ".", false);
  string sl_label =
      env->new_label(string("src_lte_mc") + "." + itos(my_tag) + ".", false);
  string exit_label =
      env->new_label(string("br_exit") + "." + itos(my_tag) + ".", false);

  int_value my_tag_val(my_tag);
  op_type old_tag_t(tag.get_type()), i32_t(INT32);
  tag.set_type(i32_t);

  // Compare the source tag to the class tag
  operand icmp_result = vp.icmp(LT, tag, my_tag_val);
  vp.branch_cond(icmp_result, exit_label, sg_label);
  vp.begin_block(sg_label);
  int_value max_child_val(max_child);

  // Compare the source tag to max child
  operand icmp2_result = vp.icmp(GT, tag, max_child_val);
  vp.branch_cond(icmp2_result, exit_label, sl_label);
  vp.begin_block(sl_label);
  tag.set_type(old_tag_t);

  // Handle casts of *arbitrary* types to Int or Bool.  We need to:
  // (a) cast expr_val to boxed type (struct Int* or struct Bool*)
  // (b) unwrap value field from the boxed type
  // At run-time, if source object is not Int or Bool, this will never
  // be invoked (assuming no bugs in the type checker).
  if (cls->get_type_name() == "Int") {
    expr_val = conform(expr_val, op_type(cls->get_type_name(), 1), env);
  } else if (cls->get_type_name() == "Bool") {
    expr_val = conform(expr_val, op_type(cls->get_type_name(), 1), env);
  }

  // If the case expression is of the right type, make a new local
  // variable for the type-casted version of it, which can be used
  // within the expression to evaluate on this branch.
  operand conf_result = conform(expr_val, alloca_type, env);
  vp.store(conf_result, alloca_op);
  env->add_local(name, alloca_op);

  // Generate code for the expression to evaluate on this branch
  operand val = conform(expr->code(env), join_type.get_ptr_type(), env);
  operand conformed = conform(val, env->branch_operand.get_type(), env);
  env->branch_operand.set_type(env->branch_operand.get_type().get_ptr_type());
  // Store result of the expression evaluated
  vp.store(conformed, env->branch_operand);
  env->branch_operand.set_type(env->branch_operand.get_type().get_deref_type());
  env->close_scope();
  // Branch to case statement exit label
  vp.branch_uncond(env->next_label);
  vp.begin_block(exit_label);
  if (cgen_debug)
    cerr << "Done branch_class::code()" << endl;
  return conformed;
#endif
}

void typcase_class::make_alloca(CgenEnvironment *env) {
  if (cgen_debug)
    std::cerr << "typecase::make_alloca()" << endl;
#ifndef MP3
  assert(0 && "Unsupported case for phase 1");
#else
  ValuePrinter vp(*env->cur_stream);
  expr->make_alloca(env);

  // Get result type of case expression
  branch_class *b = (branch_class *)cases->nth(cases->first());
  string case_result_type = b->get_expr()->get_type()->get_string();
  if (case_result_type == "SELF_TYPE")
    case_result_type = env->get_class()->get_type_name();

  // Allocate space for result of case expression
  alloca_type = op_type(case_result_type, 1);
  alloca_op = operand(alloca_type, env->new_name());
  vp.alloca_mem(*env->cur_stream, alloca_type, alloca_op);

  for (auto case_branch : cases) {
    case_branch->make_alloca(env);
  }
#endif
}

void branch_class::make_alloca(CgenEnvironment *env) {
#ifndef MP3
  assert(0 && "Unsupported case for phase 1");
#else
  ValuePrinter vp(*env->cur_stream);
  if (cgen_debug)
    cerr << "In branch_class::make_alloca()" << endl;

  CgenNode *cls = env->get_class()->get_classtable()->find_in_scopes(type_decl);
  alloca_type = op_type(cls->get_type_name(), 1);
  
  if (cls->get_type_name() == "Int") {
    alloca_type = op_type(INT32);
  } else if (cls->get_type_name() == "Bool") {
    alloca_type = op_type(INT1);
  }

  alloca_op = vp.alloca_mem(alloca_type);

  expr->make_alloca(env);
  
  if (cgen_debug)
    cerr << "Done branch_class::make_alloca()" << endl;
#endif
}

void CgenEnvironment::add_local(Symbol name, operand &vb) {
    this->open_scope();
    this->add_binding(name, vb);
}
