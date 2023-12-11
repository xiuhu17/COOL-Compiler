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
    Type_Lookup[nd->get_type_name()] = llvm::StructType::create(context, nd->get_type_name());
    Name_to_Node[nd->get_type_name()] = nd;
    Vtable_Type_Lookup[nd->get_vtable_type_name()] = llvm::StructType::create(context, nd->get_vtable_type_name());
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
  // std::cerr << nd->get_name()->get_string() << " parent is " << parent->get_string() << "\n";
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
       *i1 = Type::getInt1Ty(this->context),
       *void_ = Type::getVoidTy(this->context);
  // setup function: external int strcmp(sbyte*, sbyte*)
  auto a = create_llvm_function("strcmp", i32, {i8_ptr, i8_ptr}, false);
  llmethod_to_Funtion_Ptr["strcmp"] = a;
  // setup function: external int printf(sbyte*, ...)
  auto b = create_llvm_function("printf", i32, {i8_ptr}, true);
  llmethod_to_Funtion_Ptr["printf"] = b;
  // setup function: external void abort(void)
  auto c = create_llvm_function("abort", void_, {}, false);
  llmethod_to_Funtion_Ptr["abort"] = c;
  // setup function: external i8* malloc(i32)
  auto d = create_llvm_function("malloc", i8_ptr, {i32}, false);
  llmethod_to_Funtion_Ptr["malloc"] = d;

#ifdef MP3
  // TODO: add code here
  auto e = create_llvm_function("Int_init", void_, {llvm::PointerType::get(Type_Lookup["Int"], 0), i32}, false);
  llmethod_to_Funtion_Ptr["Int_init"] = e;

  auto f = create_llvm_function("Bool_init", void_, {llvm::PointerType::get(Type_Lookup["Bool"], 0), i1}, false);
  llmethod_to_Funtion_Ptr["Bool_init"] = f;
    
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
  c->code_init_function();
  c->code_class();
  for (auto child : c->get_children()) {
    code_classes(child);
  }
}
#endif

// Create global definitions for constant Cool objects
void CgenClassTable::code_constants() {
#ifdef MP3
  // TODO: add code here
  std::ostream *empty_;
  stringtable.code_string_table(*empty_, this);
#endif
}

// Create LLVM entry point. This function will initiate our Cool program
// by generating the code to execute (new Main).main()
// define i32 @main() {
// entry:
// %main.obj = call %Main*() @Main_new( )
// %main.retval = call i32(%Main*) @Main.main( %Main* %main.obj )
// ret i32 0
// }
void CgenClassTable::code_main(){
#ifdef MP3
// MP3

llvm::Type* i32 = Type::getInt32Ty(this->context);
auto main_func = create_llvm_function("main", i32, {}, false);
auto main_entry_block = llvm::BasicBlock::Create(context, "entry", main_func);
builder.SetInsertPoint(main_entry_block);
auto Main_new = llmethod_to_Funtion_Ptr["Main_new"];
auto Main_new_Callee = the_module.getOrInsertFunction("Main_new", Main_new->getFunctionType());
auto main_obj = builder.CreateCall(Main_new_Callee);
auto Main_main = llmethod_to_Funtion_Ptr["Main_main"];
auto Main_main_Callee = the_module.getOrInsertFunction("Main_main", Main_main->getFunctionType());
auto main_retval = builder.CreateCall(Main_main_Callee, main_obj);
builder.CreateRet(ConstantInt::get(i32, 0));

#else
  Type *i32 = Type::getInt32Ty(this->context),
       *i8_ptr = Type::getInt8PtrTy(this->context);
  
  llvm::StringRef Main_main_str = "Main.main() returned %d\x0A\x00";
  auto Main_main_val = this->builder.CreateGlobalString(Main_main_str, "main.printout.str", 0, &the_module);

  // Define a function main that has no parameters and returns an i32
  auto main_func = create_llvm_function("main", i32, {}, false);

  // Define an entry basic block
  auto main_entry_block = llvm::BasicBlock::Create(context, "entry", main_func); // function tie with block
  builder.SetInsertPoint(main_entry_block);  // irbuilder tie with block
  
  // Call Main_main(). This returns int for phase 1, Object for phase 2
  auto Main_main_tp = FunctionType::get(i32, {}, false);
  auto Main_main_callee = the_module.getOrInsertFunction("Main.main", Main_main_tp);
  auto Main_main_ret = builder.CreateCall(Main_main_callee);

  auto Main_main_str_ptr_tp = ArrayType::get(Type::getInt8Ty(this->context), 25);
  auto ele_ptr = this->builder.CreateConstGEP2_32(Main_main_str_ptr_tp, Main_main_val, 0, 0);
  
  auto printf_tp = FunctionType::get(i32, {i8_ptr}, true);
  auto printf_callee = the_module.getOrInsertFunction("printf", llmethod_to_Funtion_Ptr["printf"]->getFunctionType());
  builder.CreateCall(printf_callee, {ele_ptr, Main_main_ret});

  builder.CreateRet(ConstantInt::get(Type::getInt32Ty(this->context), 0));
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
  Constant* cons_str = ConstantDataArray::getString(ct->context, str);
  // @str.x = internal constant [14 x i8] c"<basic class>\00"
  auto global_str = new GlobalVariable(ct->the_module, cons_str->getType(), true, GlobalValue::InternalLinkage, cons_str, "str." + std::to_string(index));
  // @String.x = {}
  auto constant_global_str_obj = ConstantStruct::get(ct->Type_Lookup["String"], {ct->Vtable_Proto_Lookup["_String_vtable_prototype"], global_str});
  auto global_str_obj = new GlobalVariable(ct->the_module, ct->Type_Lookup["String"], true, GlobalValue::ExternalLinkage, constant_global_str_obj, "String." + std::to_string(index));
  // setup mapping
  ct->strEntry_to_GlobalStr[index] = global_str_obj;
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
  auto parent_obj_tp = get_parent_obj_tp();
  auto parent_vtable_tp = get_parent_vtable_tp();
  auto parent_clmethod_to_llmethod_idx = get_parent_clmethod_to_llmethod_idx();

  if (parent_obj_tp) {
    obj_tp = *parent_obj_tp;
  }
  if (parent_vtable_tp) {
    vtable_tp = *parent_vtable_tp;
  }
  if (parent_clmethod_to_llmethod_idx) {
    clmethod_to_llmethod_idx = *parent_clmethod_to_llmethod_idx;
  }

  // for overwrite function, newly created function and attr
  for(int i = features->first(); features->more(i); i = features->next(i)) {
    auto feature_iter = features->nth(i);
    feature_iter->layout_feature(this);
  }
  
  // create str
  llvm::Constant* str = ConstantDataArray::getString(class_table->context, get_type_name());
  llvm::GlobalVariable* global_str = new llvm::GlobalVariable(class_table->the_module, str->getType(), true, GlobalVariable::InternalLinkage, str, "str." + get_type_name());

  // setup for object type
  auto curr_type_struct = class_table->Type_Lookup[get_type_name()];
  auto curr_vtable_tp_ptr = llvm::PointerType::get(class_table->Vtable_Type_Lookup[get_vtable_type_name()], 0);
  std::vector<llvm::Type*> type_struct_setup = {curr_vtable_tp_ptr};
  int k = 1;
  for (auto& iter: obj_tp) {
    auto defined_class = iter.first;
    auto defined_attr = iter.second;
    auto defined_attr_tp = defined_attr->get_type_decl()->get_string();
    if (defined_attr_tp == "Int" || defined_attr_tp == "int") {
      type_struct_setup.push_back(Type::getInt32Ty(class_table->context));
    } else if (defined_attr_tp == "Bool" || defined_attr_tp == "bool") {
      type_struct_setup.push_back(Type::getInt1Ty(class_table->context));
    } else if (defined_attr_tp == "sbyte*") {
      type_struct_setup.push_back(llvm::PointerType::get(Type::getInt8Ty(class_table->context), 0));
    } else if (defined_attr_tp == "SELF_TYPE") {
      type_struct_setup.push_back(llvm::PointerType::get(class_table->Type_Lookup[get_type_name()], 0)); // current type ////////////////////////////////
    } else {
      type_struct_setup.push_back(llvm::PointerType::get(class_table->Type_Lookup[defined_attr_tp], 0));///////////////////////////////////
    }
    // setup the mapping
    clattr_to_offset[defined_attr->get_name()->get_string()] = k;
    k += 1;
  }
  curr_type_struct->setBody(type_struct_setup);

  // setup for vtable type
  auto curr_vtable_type_struct = class_table->Vtable_Type_Lookup[get_vtable_type_name()];
  // setup the first three: i32 tag, i32 size, i8* name
  std::vector<llvm::Type*> vtable_type_struct_setup = {Type::getInt32Ty(class_table->context), 
                                                        Type::getInt32Ty(class_table->context), 
                                                        llvm::PointerType::get(Type::getInt8Ty(class_table->context), 0)};
  // create xxx_new function
  auto function_new_created = create_llvm_function(get_init_function_name(), 
                                                    llvm::PointerType::get(class_table->Type_Lookup[get_type_name()], 0), 
                                                    {}, 
                                                    false);//////////////////
  // need to implement, insert into hash
  Function_Body_Map[function_new_created] = NULL;
  class_table->llmethod_to_Funtion_Ptr[get_init_function_name()] = function_new_created;
  // xxx_new function pointer
  vtable_type_struct_setup.push_back(llvm::PointerType::get(function_new_created->getFunctionType(), 0));/////////////////
  // start the normal
  k = 4;
  for (auto& iter: vtable_tp) {
    auto defined_class = iter.first;
    auto defined_method = iter.second;
    // define the current vtable_tp, so we need to use this as class, representing the current type
    auto func_tp = functp_helper(this, defined_method);
    vtable_type_struct_setup.push_back(llvm::PointerType::get(func_tp, 0));/////////////////////////
    // setup mapping
    clmethod_to_offset[defined_method->get_name()->get_string()] = k;
    k += 1;
  }
  curr_vtable_type_struct->setBody(vtable_type_struct_setup);

  // instantiate vtable
  std::vector<llvm::Constant*> vtable_proto_vec;
  // class tag
  vtable_proto_vec.push_back(ConstantInt::get(Type::getInt32Ty(class_table->context), tag));
  // object size
  auto get_elementptr_size = ConstantExpr::getGetElementPtr(class_table->Type_Lookup[get_type_name()],  // %My_Type
                                                              ConstantPointerNull::get(llvm::PointerType::get(class_table->Type_Lookup[get_type_name()],0)), // %My_Type* NULL
                                                              {ConstantInt::get(Type::getInt32Ty(class_table->context), 1)}); // i32 1 
  auto ptr_to_int_size = ConstantExpr::getPtrToInt(get_elementptr_size, Type::getInt32Ty(class_table->context));
  vtable_proto_vec.push_back(ptr_to_int_size);
  // get Struct name
  llvm::ArrayRef<llvm::Constant *> get_elementptr_name_ind = {ConstantInt::get(Type::getInt32Ty(class_table->context), 0), ConstantInt::get(Type::getInt32Ty(class_table->context), 0)};
  auto get_elementptr_name = ConstantExpr::getGetElementPtr(str->getType(), // % [??? x i8]
                                                            global_str, // @str.???
                                                            get_elementptr_name_ind); // i32 0 i32 0
  vtable_proto_vec.push_back(get_elementptr_name);
  // insert new function pointer
  vtable_proto_vec.push_back(function_new_created);
  // iterate through vtable_tp
  for (auto& iter: vtable_tp) {
    auto defined_class = iter.first;
    auto defined_method = iter.second;
    auto get_ll_func_name = defined_class->get_function_name(defined_method->get_name()->get_string());
    auto get_ll_func_ptr = class_table->llmethod_to_Funtion_Ptr[get_ll_func_name];
    auto current_type = functp_helper(this, defined_method);
    auto func_after_cast = ConstantExpr::getBitCast(get_ll_func_ptr, llvm::PointerType::get(current_type, 0));
    vtable_proto_vec.push_back(func_after_cast);
  }

  auto vtable_prototype_constant = ConstantStruct::get(curr_vtable_type_struct, vtable_proto_vec);
  auto vtable_prototype = new GlobalVariable(class_table->the_module, curr_vtable_type_struct, true, GlobalValue::ExternalLinkage, vtable_prototype_constant, get_vtable_name());

  class_table->Vtable_Proto_Lookup[get_vtable_name()] = vtable_prototype;
}

void CgenNode::code_init_function() {
  // TODO: add code here
  if (basic()) {
    return;
  }

  CgenEnvironment env(this);

  // basic settup
  auto new_func_pointer = env.llmethod_to_Funtion_Ptr[get_init_function_name()];
  env.FUNC_PTR = new_func_pointer;
  auto func_entry_block = llvm::BasicBlock::Create(env.context, "entry", new_func_pointer);
  env.builder.SetInsertPoint(func_entry_block);
  auto func_abort_block = env.get_or_insert_abort_block(new_func_pointer);
  env.set_abrt(func_abort_block);
  
  // setup entry block
  auto ok_label = env.new_ok_label();
  auto ok_false = env.new_bb_at_fend(ok_label);
  // %tmp.107 = alloca %Main*
  auto curr_type = env.Type_Lookup[get_type_name()];
  auto allocated_curr_class_ptr = env.insert_alloca_at_head(llvm::PointerType::get(curr_type, 0)); 
  // %tmp.108 = getelementptr %_Main_vtable, %_Main_vtable* @_Main_vtable_prototype, i32 0, i32 1
  auto vtable_type = env.Vtable_Type_Lookup[get_vtable_type_name()];
  auto vtable_proto = env.Vtable_Proto_Lookup[get_vtable_name()]; 
  auto grab_size_ptr = env.builder.CreateGEP(vtable_type, vtable_proto, {llvm::ConstantInt::get(llvm::Type::getInt32Ty(env.context), 0), llvm::ConstantInt::get(llvm::Type::getInt32Ty(env.context), 1)}); 
  // %tmp.109 = load i32, i32* %tmp.108
  auto grab_size = env.builder.CreateLoad(llvm::Type::getInt32Ty(env.context), grab_size_ptr); 
  // %tmp.110 = call i8*(i32 ) @malloc( i32 %tmp.109 )
  auto malloc_func_callee = env.the_module.getOrInsertFunction("malloc", env.llmethod_to_Funtion_Ptr["malloc"]->getFunctionType());
  auto malloc_alloc = env.builder.CreateCall(malloc_func_callee, {grab_size}); 
  // %tmp.111 = bitcast i8* %tmp.110 to %Main*
  auto after_cast = env.builder.CreateBitCast(malloc_alloc, llvm::PointerType::get(curr_type, 0)); 
  env.MALLOC_ADDR = after_cast;
  // %malloc.null = icmp eq %Main* %tmp.111, null
  auto cond_check = env.builder.CreateCmp(llvm::CmpInst::ICMP_EQ, after_cast, llvm::ConstantPointerNull::get(llvm::PointerType::get(curr_type, 0))); 
  // br i1 %malloc.null, label %abort, label %okay
  env.builder.CreateCondBr(cond_check, func_abort_block, ok_false);

  // ok block
  env.builder.SetInsertPoint(ok_false);
  // first for vtable_proto
  // %tmp.112 = getelementptr %Main, %Main* %tmp.111, i32 0, i32 0
  auto prepare_to_sotre_proto = env.builder.CreateGEP(curr_type, after_cast, {llvm::ConstantInt::get(llvm::Type::getInt32Ty(env.context), 0), llvm::ConstantInt::get(llvm::Type::getInt32Ty(env.context), 0)});
  // store %_Main_vtable* @_Main_vtable_prototype, %_Main_vtable** %tmp.112
  env.builder.CreateStore(vtable_proto, prepare_to_sotre_proto);
	// store %Main* %tmp.111, %Main** %tmp.107
  env.builder.CreateStore(after_cast, allocated_curr_class_ptr);
  //-------------------
  env.SELF_ADDR = allocated_curr_class_ptr; // %Main **
  //-------------------

  // loop from the list, include the inheritance
  // after the vtable_pointer
  for (auto& [defined_class, defined_attr]: obj_tp) {
    auto attr_ptr = Get_Attr_Addr(&env, this, after_cast, defined_attr->get_name()->get_string());
    auto attr_tp = Get_Attr_Type(&env, this, defined_attr->get_name()->get_string());
    if (attr_tp->isStructTy()) {
      llvm::StructType* struct_type = llvm::cast<StructType>(attr_tp);
      env.builder.CreateStore(llvm::ConstantPointerNull::get((llvm::PointerType::get(struct_type, 0))), attr_ptr);
    } else {
      if (attr_tp->isIntegerTy(32)) {
        env.builder.CreateStore(llvm::ConstantInt::get(llvm::Type::getInt32Ty(env.context), 0), attr_ptr);
      } else if (attr_tp->isIntegerTy(1)) {
        env.builder.CreateStore(llvm::ConstantInt::get(llvm::Type::getInt1Ty(env.context), false), attr_ptr);
      } else {
        assert(false);
      }
    }
  }

  // loop over the true expr
  for (auto& [defined_class, defined_attr]: obj_tp) {
    defined_attr->code(&env);
  }
  
  // return malloc allocated stuff
  env.builder.CreateRet(after_cast);
}

#ifdef MP3
// Retrieve the class tag from an object record.
// src is the object we need the tag from.
// src_class is the CgenNode for the *static* class of the expression.
// You need to look up and return the class tag for it's dynamic value
Value *get_class_tag(Value *src, CgenNode *src_cls, CgenEnvironment *env) {
  // ADD CODE HERE (MP3 ONLY)
  auto static_obj_tp = env->Type_Lookup[src_cls->get_type_name()];
  auto static_vtable_tp = env->Vtable_Type_Lookup[src_cls->get_vtable_type_name()];

  auto gep = env->builder.CreateGEP(static_obj_tp, src, {llvm::ConstantInt::get(llvm::Type::getInt32Ty(env->context), 0), llvm::ConstantInt::get(llvm::Type::getInt32Ty(env->context), 0)});
  auto vtable_ptr = env->builder.CreateLoad(llvm::PointerType::get(static_vtable_tp, 0), gep);
  auto tag_ptr = env->builder.CreateGEP(static_vtable_tp, vtable_ptr, {llvm::ConstantInt::get(llvm::Type::getInt32Ty(env->context), 0), llvm::ConstantInt::get(llvm::Type::getInt32Ty(env->context), 0)});
  auto tag = env->builder.CreateLoad(llvm::Type::getInt32Ty(env->context), tag_ptr);

  return tag;
}
#endif


// Class codegen. This should performed after every class has been setup.
// Generate code for each method of the class.
void CgenNode::code_class() {
  // No code generation for basic classes. The runtime will handle that.
  if (basic()) {
    return;
  }
  // TODO: add code here
  std::cerr << "-------------------" << get_type_name() << '\n';
  for (auto& [FunctionPointer_, method_]: Function_Body_Map) {
    if (method_ == NULL) continue;
    CgenEnvironment env(this);
    env.FUNC_PTR = FunctionPointer_;
    Create_Param(&env, this, FunctionPointer_, method_);
    method_->code(&env);
  }
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

// define a method body
Function *method_class::code(CgenEnvironment *env) {
  if (cgen_debug) {
    std::cerr << "method" << std::endl;
  }
  std::cerr << "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb \n";

  auto ret_expr_val = expr->code(env);
  auto ret_expr_tp = expr->get_expr_tp(env);
  auto ret_decl_tp = Get_Decl_Type(env, env->get_class(), return_type->get_string());
  auto ret_conform = Conform(env, ret_decl_tp, ret_expr_tp, ret_expr_val);
  env->builder.CreateRet(ret_conform);
  return env->FUNC_PTR;
}

// Codegen for expressions. Note that each expression has a value.

#ifdef MP3
// TODO: implement these functions (MP3), and add more functions as necessary

// Utitlity function
// Generate any code necessary to convert from given Value* to
// dest_type, assuming it has already been checked to be compatible

// conform - If necessary, emit a bitcast or boxing/unboxing operations
// to convert an object to a new type. This can assume the object
// is known to be (dynamically) compatible with the target type.
// It should only be called when this condition holds.
// (It's needed by the supplied code for typecase)
llvm::Value *conform(llvm::Value *src, llvm::Type *dest_type, CgenEnvironment *env) {
  auto type = src->getType();
  if (type->isIntegerTy(32)) {
    type = llvm::Type::getInt32Ty(env->context);
  } else if (type->isIntegerTy(1)) {
    type = llvm::Type::getInt1Ty(env->context);
  } else if (type->isStructTy()) {
    llvm::StructType* type_struct = llvm::cast<StructType>(type);
    type = env->Type_Lookup[type_struct->getName().str()];
  } else {
    if (type->isPointerTy()) {
      std::cerr << "src: POINTER ISSUE---------------------- \n";
    } else if (dest_type->isPointerTy()) {
      std::cerr << "dest_type: POINTER ISSUE---------------------- \n";
    }
    assert(false);
  }
  return Conform(env, dest_type, type, src);
}
#endif

Value *assign_class::code(CgenEnvironment *env) {
  if (cgen_debug)
    std::cerr << "assign" << std::endl;

  // TODO: add code here and replace `return nullptr`

  // find in symtable
  auto expr_val = expr->code(env);
  auto expr_tp = expr->get_expr_tp(env);

  // find in attribute
  auto [decl_tp, id_addr_val] = env->find_in_scopes(name);
  if (decl_tp  == nullptr || id_addr_val == nullptr) {
    auto curr_class_type = env->class_table.Type_Lookup[env->get_class()->get_type_name()];
    auto self_ptr = env->builder.CreateLoad(llvm::PointerType::get(curr_class_type, 0), env->SELF_ADDR);
    id_addr_val = Get_Attr_Addr(env, env->get_class(), self_ptr, name->get_string());
    decl_tp = Get_Attr_Type(env, env->get_class(), name->get_string());
  }

  // conform
  auto conform_val = Conform(env, decl_tp, expr_tp, expr_val);

  // store value 
  env->builder.CreateStore(conform_val, id_addr_val);

  // settup expression_extra
  set_expr_tp(env, expr_tp);

  return expr_val;
}

Value *cond_class::code(CgenEnvironment *env) {
  if (cgen_debug)
    std::cerr << "cond" << std::endl;

  // TODO: add code here and replace `return nullptr`
  llvm::Type  *if_type;                                                
  llvm::Value *if_addr_val;

  auto true_label = env->new_true_label();
  auto false_label = env->new_false_label();
  auto end_label = env->new_end_label();

  auto true_block = env->new_bb_at_fend(true_label);
  auto false_block = env->new_bb_at_fend(false_label);
  auto end_block = env->new_bb_at_fend(end_label);

  auto pred_val = pred->code(env);
  auto pred_tp = pred->get_expr_tp(env);
  auto pred_val_bool = Conform(env, llvm::Type::getInt1Ty(env->context), pred_tp, pred_val);

  env->builder.CreateCondBr(pred_val_bool, true_block, false_block);

  // then branch
  env->builder.SetInsertPoint(true_block);
  auto then_val = then_exp->code(env);
  auto then_tp = then_exp->get_expr_tp(env);
  auto remain_true_block = env->builder.GetInsertBlock();
  
  // else branch
  env->builder.SetInsertPoint(false_block);
  auto else_val = else_exp->code(env);
  auto else_tp = else_exp->get_expr_tp(env);
  auto remain_false_block = env->builder.GetInsertBlock();

  // if_type and if_addr_val
  if_type = Find_Parent(env, then_tp, else_tp);
  if (if_type->isIntegerTy(32)) {
    if_addr_val = env->insert_alloca_at_head(llvm::Type::getInt32Ty(env->context));
  } else if (if_type->isIntegerTy(1)) {
    if_addr_val = env->insert_alloca_at_head(llvm::Type::getInt1Ty(env->context));
  } else if (if_type->isStructTy()) {
    if_addr_val = env->insert_alloca_at_head(llvm::PointerType::get(if_type, 0));
  } else {
    assert(false);
  }

  // then branch
  env->builder.SetInsertPoint(remain_true_block);
  auto after_conform_then = Conform(env, if_type, then_tp, then_val);
  env->builder.CreateStore(after_conform_then, if_addr_val);
  env->builder.CreateBr(end_block);

  // else branch
  env->builder.SetInsertPoint(remain_false_block);
  auto after_conform_else = Conform(env, if_type, else_tp, else_val);
  env->builder.CreateStore(after_conform_else, if_addr_val);
  env->builder.CreateBr(end_block);

  // end block
  env->builder.SetInsertPoint(end_block);
  llvm::LoadInst *cond_res;
  if (if_type->isIntegerTy(32)) {
    cond_res = env->builder.CreateLoad(llvm::Type::getInt32Ty(env->context), if_addr_val);
  } else if (if_type->isIntegerTy(1)) {
    cond_res = env->builder.CreateLoad(llvm::Type::getInt1Ty(env->context), if_addr_val);
  } else if (if_type->isStructTy()) {
    cond_res = env->builder.CreateLoad(llvm::PointerType::get(if_type, 0), if_addr_val);
  } else {
    assert(false);
  }

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
  auto pred_val = pred->code(env);
  auto pred_tp = pred->get_expr_tp(env);
  auto pred_val_conform = Conform(env, llvm::Type::getInt1Ty(env->context), pred_tp, pred_val);

  env->builder.CreateCondBr(pred_val_conform, true_block, false_block);

  // if true, then body
  env->builder.SetInsertPoint(true_block);
  body->code(env);
  env->builder.CreateBr(loop_block);

  // if false, then ...
  env->builder.SetInsertPoint(false_block);

  // set expr_extra
  set_expr_tp(env, env->Type_Lookup["Object"]);
  auto loop_res = llvm::ConstantPointerNull::get(llvm::PointerType::get(env->Type_Lookup["Object"], 0));

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

  // go init first 
  auto init_expr_val = init->code(env);
  auto init_expr_tp = init->get_expr_tp(env);

  // 
  llvm::Type* identifier_type = Get_Decl_Type(env, env->get_class(), type_decl->get_string());               
  llvm::Value* identifier_addr_val;

  if (init_expr_val == nullptr || init_expr_tp == nullptr) {
      if (identifier_type->isIntegerTy(32)) {
        identifier_addr_val = env->insert_alloca_at_head(llvm::Type::getInt32Ty(env->context));
        env->builder.CreateStore(llvm::ConstantInt::get(llvm::Type::getInt32Ty(env->context), 0), identifier_addr_val);
      } else if (identifier_type->isIntegerTy(1)) {
        identifier_addr_val = env->insert_alloca_at_head(llvm::Type::getInt1Ty(env->context));
        env->builder.CreateStore(llvm::ConstantInt::get(llvm::Type::getInt1Ty(env->context), false), identifier_addr_val);
      } else {
        identifier_addr_val = env->insert_alloca_at_head(llvm::PointerType::get(identifier_type, 0));
        env->builder.CreateStore(llvm::ConstantPointerNull::get(llvm::PointerType::get(identifier_type, 0)), identifier_addr_val);
      }
  } else {
     if (identifier_type->isIntegerTy(32)) {
        identifier_addr_val = env->insert_alloca_at_head(llvm::Type::getInt32Ty(env->context));
        auto after_conform = Conform(env, identifier_type, init_expr_tp, init_expr_val);
        env->builder.CreateStore(after_conform, identifier_addr_val);
      } else if (identifier_type->isIntegerTy(1)) {
        identifier_addr_val = env->insert_alloca_at_head(llvm::Type::getInt1Ty(env->context));
        auto after_conform = Conform(env, identifier_type, init_expr_tp, init_expr_val);
        env->builder.CreateStore(after_conform, identifier_addr_val);
      } else {
        identifier_addr_val = env->insert_alloca_at_head(llvm::PointerType::get(identifier_type, 0));
        auto after_conform = Conform(env, identifier_type, init_expr_tp, init_expr_val);
        env->builder.CreateStore(after_conform, identifier_addr_val);
      }
  }

  env->var_tp_open_scope();
  env->open_scope();

  env->var_tp_add_binding(identifier, identifier_type);
  env->add_binding(identifier, identifier_addr_val);

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

  auto left_val = e1->code(env);
  auto left_tp = e1->get_expr_tp(env);
  auto right_val = e2->code(env);
  auto right_tp = e2->get_expr_tp(env);

  auto left_val_conform = Conform(env, llvm::Type::getInt32Ty(env->context), left_tp, left_val);
  auto right_val_conform = Conform(env, llvm::Type::getInt32Ty(env->context), right_tp, right_val);

  auto add_res = env->builder.CreateAdd(left_val_conform, right_val_conform);

  set_expr_tp(env, llvm::Type::getInt32Ty(env->context));
  return add_res;
}

Value *sub_class::code(CgenEnvironment *env) {
  if (cgen_debug)
    std::cerr << "sub" << std::endl;

  // TODO: add code here and replace `return nullptr`
  auto left_val = e1->code(env);
  auto left_tp = e1->get_expr_tp(env);
  auto right_val = e2->code(env);
  auto right_tp = e2->get_expr_tp(env);

  auto left_val_conform = Conform(env, llvm::Type::getInt32Ty(env->context), left_tp, left_val);
  auto right_val_conform = Conform(env, llvm::Type::getInt32Ty(env->context), right_tp, right_val);

  auto sub_res = env->builder.CreateSub(left_val_conform, right_val_conform);

  set_expr_tp(env, llvm::Type::getInt32Ty(env->context));
  return sub_res;
}

Value *mul_class::code(CgenEnvironment *env) {
  if (cgen_debug)
    std::cerr << "mul" << std::endl;

  // TODO: add code here and replace `return nullptr`
  auto left_val = e1->code(env);
  auto left_tp = e1->get_expr_tp(env);
  auto right_val = e2->code(env);
  auto right_tp = e2->get_expr_tp(env);

  auto left_val_conform = Conform(env, llvm::Type::getInt32Ty(env->context), left_tp, left_val);
  auto right_val_conform = Conform(env, llvm::Type::getInt32Ty(env->context), right_tp, right_val);

  auto mul_res = env->builder.CreateMul(left_val_conform, right_val_conform);

  set_expr_tp(env, llvm::Type::getInt32Ty(env->context));
  return mul_res;
}

Value *divide_class::code(CgenEnvironment *env) {
  if (cgen_debug)
    std::cerr << "div" << std::endl;

  // TODO: add code here and replace `return nullptr`
  auto ok_label = env->new_ok_label();
  auto numerator_val = e1->code(env);
  auto numerator_tp = e1->get_expr_tp(env);
  auto denominator_val = e2->code(env);
  auto denominator_tp = e2->get_expr_tp(env);

  auto numerator_conform = Conform(env, llvm::Type::getInt32Ty(env->context), numerator_tp, numerator_val);
  auto denominator_conform = Conform(env, llvm::Type::getInt32Ty(env->context), denominator_tp, denominator_val);

  auto abort_true = env->get_abrt();              // true, 0
  auto ok_false = env->new_bb_at_fend(ok_label); // false, not 0

  auto cond_ = env->builder.CreateCmp(llvm::CmpInst::ICMP_EQ, ConstantInt::get(Type::getInt32Ty(env->context), 0), denominator_conform);
  env->builder.CreateCondBr(cond_, abort_true, ok_false);

  env->builder.SetInsertPoint(ok_false);
  auto div_res = env->builder.CreateSDiv(numerator_conform, denominator_conform);

  set_expr_tp(env, llvm::Type::getInt32Ty(env->context));
  return div_res;
}

Value *neg_class::code(CgenEnvironment *env) {
  if (cgen_debug)
    std::cerr << "neg" << std::endl;

  // TODO: add code here and replace `return nullptr`
  auto left_val = e1->code(env);
  auto left_type = e1->get_expr_tp(env);

  auto left_val_conform = Conform(env, llvm::Type::getInt32Ty(env->context), left_type, left_val);
  auto neg_res = env->builder.CreateNeg(left_val_conform);

  set_expr_tp(env, llvm::Type::getInt32Ty(env->context));
  return neg_res;
}

Value *lt_class::code(CgenEnvironment *env) {
  if (cgen_debug)
    std::cerr << "lt" << std::endl;

  // TODO: add code here and replace `return nullptr`
  auto left_val = e1->code(env);
  auto left_tp = e1->get_expr_tp(env);
  auto right_val = e2->code(env);
  auto right_tp = e2->get_expr_tp(env);

  auto left_val_conform = Conform(env, llvm::Type::getInt32Ty(env->context), left_tp, left_val);
  auto right_val_conform = Conform(env, llvm::Type::getInt32Ty(env->context), right_tp, right_val);

  auto lt_res = env->builder.CreateCmp(llvm::CmpInst::ICMP_SLT, left_val_conform, right_val_conform);

  set_expr_tp(env, Type::getInt1Ty(env->context));
  return lt_res;
}

Value *leq_class::code(CgenEnvironment *env) {
  if (cgen_debug)
    std::cerr << "leq" << std::endl;

  // TODO: add code here and replace `return nullptr`
  auto left_val = e1->code(env);
  auto left_tp = e1->get_expr_tp(env);
  auto right_val = e2->code(env);
  auto right_tp = e2->get_expr_tp(env);

  auto left_val_conform = Conform(env, llvm::Type::getInt32Ty(env->context), left_tp, left_val);
  auto right_val_conform = Conform(env, llvm::Type::getInt32Ty(env->context), right_tp, right_val);

  auto leq_res = env->builder.CreateCmp(llvm::CmpInst::ICMP_SLE, left_val_conform, right_val_conform);

  set_expr_tp(env, Type::getInt1Ty(env->context));
  return leq_res;
}

Value *eq_class::code(CgenEnvironment *env) {
  if (cgen_debug)
    std::cerr << "eq" << std::endl;

  // TODO: add code here and replace `return nullptr`
  auto left_val = e1->code(env);
  auto left_tp = e1->get_expr_tp(env);
  auto right_val = e2->code(env);
  auto right_tp = e2->get_expr_tp(env);
  llvm::Value* eq_res;

  if ((!left_tp->isStructTy()) && (!right_tp->isStructTy())) {
    eq_res = env->builder.CreateCmp(llvm::CmpInst::ICMP_EQ, left_val, right_val);
  } else {
    if (left_tp->isIntegerTy(32)) {
      left_val = BOX(env, left_val);
    } else if (left_tp->isIntegerTy(1)) {
      left_val = BOX(env, left_val);
    }
    if (right_tp->isIntegerTy(32)) {
      right_val = BOX(env, right_val);
    } else if (right_tp->isIntegerTy(1)) {
      right_val = BOX(env, right_val);
    }
    eq_res = env->builder.CreateCmp(llvm::CmpInst::ICMP_EQ, left_val, right_val);
  }
  
  assert(eq_res);
  set_expr_tp(env, Type::getInt1Ty(env->context));
  return eq_res;
}

Value *comp_class::code(CgenEnvironment *env) {
  if (cgen_debug)
    std::cerr << "complement" << std::endl;

  // TODO: add code here and replace `return nullptr`
  auto left_val = e1->code(env);
  auto left_type = e1->get_expr_tp(env);

  auto left_val_conform = Conform(env, llvm::Type::getInt1Ty(env->context), left_type, left_val);
  auto comp_res = env->builder.CreateXor(left_val_conform, ConstantInt::get(Type::getInt1Ty(env->context), true));

  set_expr_tp(env, Type::getInt1Ty(env->context));
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

  // "self"
  if (name->get_string() == "self") {
    auto cls_tp = env->class_table.Type_Lookup[env->get_class()->get_type_name()];
    auto self_val = env->builder.CreateLoad(llvm::PointerType::get(cls_tp, 0), env->SELF_ADDR);
    set_expr_tp(env, cls_tp);
    assert(self_val);

    return self_val;
  }
	
  // find in symbol table
  auto [object_type, object_addr_val] = env->find_in_scopes(name);

  // find in attribute
  if (object_type == nullptr || object_addr_val == nullptr) {
    auto curr_class_type = env->class_table.Type_Lookup[env->get_class()->get_type_name()];
    auto self_ptr = env->builder.CreateLoad(llvm::PointerType::get(curr_class_type, 0), env->SELF_ADDR);
    object_addr_val = Get_Attr_Addr(env, env->get_class(), self_ptr, name->get_string());
    object_type = Get_Attr_Type(env, env->get_class(), name->get_string());
  }

  llvm::LoadInst *obj_val;
  if (object_type->isIntegerTy(32)) {
    obj_val = env->builder.CreateLoad(llvm::Type::getInt32Ty(env->context), object_addr_val); // i32* -> i32
  } else if (object_type->isIntegerTy(1)) {
    obj_val = env->builder.CreateLoad(llvm::Type::getInt1Ty(env->context), object_addr_val); // i1* -> i1
  } else if (object_type->isStructTy()) {
    obj_val = env->builder.CreateLoad(llvm::PointerType::get(object_type, 0), object_addr_val); // %B** -> %B*
  } else {
    assert(false);
  }

  set_expr_tp(env, object_type);
  return obj_val;
}

Value *no_expr_class::code(CgenEnvironment *env) {
  if (cgen_debug)
    std::cerr << "No_expr" << std::endl;

  // TODO: add code here and replace `return nullptr`
  set_expr_tp(env, nullptr);
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

  auto expr_val = expr->code(env);
  auto expr_tp = expr->get_expr_tp(env);

  auto ok_label = env->new_ok_label();
  auto abort_true = env->get_abrt();              // true, 0
  auto ok_false = env->new_bb_at_fend(ok_label); // false, not 0

  auto cond_ = env->builder.CreateCmp(llvm::CmpInst::ICMP_EQ, llvm::ConstantPointerNull::get(llvm::PointerType::get(expr_tp, 0)), expr_val);
  env->builder.CreateCondBr(cond_, abort_true, ok_false);

  env->builder.SetInsertPoint(ok_false);

  auto func_class = env->Name_to_Node[type_name->get_string()];
  auto clfunc_name = name->get_string();

  auto func_addr = Get_Func_Addr_Static(env, func_class, clfunc_name);
  auto func_ptr = Get_Func_Ptr(env, func_class, clfunc_name);

  auto func_call = env->builder.CreateLoad(func_ptr->getType(), func_addr);
  auto func_tp_vec = Get_Func_Decl_Type(env, func_class, clfunc_name);

  std::vector<llvm::Value*> arg_conform_vec = {Conform(env, func_tp_vec[1], expr_tp, expr_val)};
  for (int i = actual->first(); actual->more(i); i = actual->next(i)) {
    auto arg = actual->nth(i);
    auto arg_val = arg->code(env);
    auto arg_tp = arg->get_expr_tp(env);
    auto arg_val_conform = Conform(env, func_tp_vec[i + 2], arg_tp, arg_val);
    arg_conform_vec.push_back(arg_val_conform);
  }
  auto ret_val = env->builder.CreateCall(func_ptr->getFunctionType(), func_call, arg_conform_vec);

  CgenNode* orig_class;
  if (expr_tp->isIntegerTy(32)) {
    orig_class = env->Name_to_Node["Int"];
  } else if (expr_tp->isIntegerTy(1)) {
    orig_class = env->Name_to_Node["Bool"];
  } else if (expr_tp->isStructTy()) {
    llvm::StructType* expr_tp_struct = llvm::cast<llvm::StructType>(expr_tp);
    orig_class = env->Name_to_Node[expr_tp_struct->getName().str()];
  } else {
    assert(false);
  }
  
  auto orig_type = Get_Func_Ret_Type_Static(env, orig_class, clfunc_name);
  auto ret_val_conform = Conform(env, orig_type, func_tp_vec[0], ret_val);

  set_expr_tp(env, orig_type);
  return ret_val_conform;
#endif
}

Value *string_const_class::code(CgenEnvironment *env) {
  if (cgen_debug)
    std::cerr << "string_const" << std::endl;
#ifndef MP3
  assert(0 && "Unsupported case for phase 1");
#else
  // TODO: add code here and replace `return nullptr`
  auto idx = token->get_index();
  auto global_str = env->strEntry_to_GlobalStr[idx];

  set_expr_tp(env, env->Type_Lookup["String"]);
  return global_str;
#endif
}

Value *dispatch_class::code(CgenEnvironment *env) {
  if (cgen_debug)
    std::cerr << "dispatch" << std::endl;
#ifndef MP3
  assert(0 && "Unsupported case for phase 1");
#else
  // TODO: add code here and replace `return nullptr`
  auto expr_val = expr->code(env);
  auto expr_tp = expr->get_expr_tp(env);

  // when happens func_call(arg, arg, ....) rather than object.func_call(arg, arg, ...)
  if (expr_val == nullptr || expr_tp == nullptr) { // use self
      auto self_tp_dispatch = env->Type_Lookup[env->get_class()->get_type_name()];
      auto self_val_dispatch = env->builder.CreateLoad(llvm::PointerType::get(self_tp_dispatch, 0), env->SELF_ADDR);

      auto func_class = env->Name_to_Node[env->get_class()->get_type_name()];
      auto clfunc_name = name->get_string();

      auto func_addr = Get_Func_Addr(env, func_class, self_val_dispatch, clfunc_name);
      auto func_ptr = Get_Func_Ptr(env, func_class, clfunc_name);

      auto func_call = env->builder.CreateLoad(func_ptr->getType(), func_addr);
      auto func_tp_vec = Get_Func_Decl_Type(env, func_class, clfunc_name); // ret, self, para

      std::vector<llvm::Value*> arg_conform_vec = {Conform(env, func_tp_vec[1], self_tp_dispatch, self_val_dispatch)};
      for (int i = actual->first(); actual->more(i); i = actual->next(i)) {
        auto arg = actual->nth(i);
        auto arg_val = arg->code(env);
        auto arg_tp = arg->get_expr_tp(env);
        auto arg_val_conform = Conform(env, func_tp_vec[i + 2], arg_tp, arg_val);
        arg_conform_vec.push_back(arg_val_conform);
      }

      auto ret_val = env->builder.CreateCall(func_ptr->getFunctionType(), func_call, arg_conform_vec);
      set_expr_tp(env, func_tp_vec[0]);
      return ret_val;
  } else {
    if (expr_tp->isIntegerTy(32)) {
      auto self_tp_dispatch = env->Type_Lookup["Int"];
      auto self_val_dispatch = BOX(env, expr_val);

      auto func_class = env->Name_to_Node["Int"];
      auto clfunc_name = name->get_string();
      auto func_addr = Get_Func_Addr(env, func_class, self_val_dispatch, clfunc_name);
      auto func_ptr = Get_Func_Ptr(env, func_class, clfunc_name);

      auto func_call = env->builder.CreateLoad(func_ptr->getType(), func_addr);
      auto func_tp_vec  = Get_Func_Decl_Type(env, func_class, clfunc_name); // ret, self, para

      std::vector<llvm::Value*> arg_conform_vec = {Conform(env, func_tp_vec[1], self_tp_dispatch, self_val_dispatch)};
      for (int i = actual->first(); actual->more(i); i = actual->next(i)) {
        auto arg = actual->nth(i);
        auto arg_val = arg->code(env);
        auto arg_tp = arg->get_expr_tp(env);
        auto arg_val_conform = Conform(env, func_tp_vec[i + 2], arg_tp, arg_val);
        arg_conform_vec.push_back(arg_val_conform);
      }

      auto ret_val = env->builder.CreateCall(func_ptr->getFunctionType(), func_call, arg_conform_vec);
      set_expr_tp(env, func_tp_vec[0]);
      return ret_val;
    } else if (expr_tp->isIntegerTy(1)) {
      auto self_tp_dispatch = env->Type_Lookup["Bool"];
      auto self_val_dispatch = BOX(env, expr_val);

      auto func_class = env->Name_to_Node["Bool"];
      auto clfunc_name = name->get_string();
      auto func_addr = Get_Func_Addr(env, func_class, self_val_dispatch, clfunc_name);
      auto func_ptr = Get_Func_Ptr(env, func_class, clfunc_name);

      auto func_call = env->builder.CreateLoad(func_ptr->getType(), func_addr);
      auto func_tp_vec  = Get_Func_Decl_Type(env, func_class, clfunc_name); // ret, self, para

      std::vector<llvm::Value*> arg_conform_vec = {Conform(env, func_tp_vec[1], self_tp_dispatch, self_val_dispatch)};
      for (int i = actual->first(); actual->more(i); i = actual->next(i)) {
        auto arg = actual->nth(i);
        auto arg_val = arg->code(env);
        auto arg_tp = arg->get_expr_tp(env);
        auto arg_val_conform = Conform(env, func_tp_vec[i + 2], arg_tp, arg_val);
        arg_conform_vec.push_back(arg_val_conform);
      }

      auto ret_val = env->builder.CreateCall(func_ptr->getFunctionType(), func_call, arg_conform_vec);
      set_expr_tp(env, func_tp_vec[0]);
      return ret_val;
    } else if (expr_tp->isStructTy()) {
      auto self_tp_dispatch = expr_tp;
      auto self_val_dispatch = expr_val;

      llvm::StructType* tp_cast = llvm::cast<llvm::StructType>(self_tp_dispatch);
      auto func_class = env->Name_to_Node[tp_cast->getName().str()];
      auto clfunc_name = name->get_string();
      auto func_addr = Get_Func_Addr(env, func_class, self_val_dispatch, clfunc_name);
      auto func_ptr = Get_Func_Ptr(env, func_class, clfunc_name);

      auto func_call = env->builder.CreateLoad(func_ptr->getType(), func_addr);
      auto func_tp_vec = Get_Func_Decl_Type(env, func_class, clfunc_name); // ret, self, para

      std::vector<llvm::Value*> arg_conform_vec = {Conform(env, func_tp_vec[1], self_tp_dispatch, self_val_dispatch)};
      for (int i = actual->first(); actual->more(i); i = actual->next(i)) {
        auto arg = actual->nth(i);
        auto arg_val = arg->code(env);
        auto arg_tp = arg->get_expr_tp(env);
        auto arg_val_conform = Conform(env, func_tp_vec[i + 2], arg_tp, arg_val);
        arg_conform_vec.push_back(arg_val_conform);
      }

      auto ret_val = env->builder.CreateCall(func_ptr->getFunctionType(), func_call, arg_conform_vec);
      set_expr_tp(env, func_tp_vec[0]);
      return ret_val;
    } else {
      assert(false);
    }
  }

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
  // // TODO: add code here and replace `return nullptr`
  llvm::Type* alloca_type;
  llvm::Value* alloca_op;

  auto code_val = expr->code(env);
  auto code_val_tp = expr->get_expr_tp(env);
  auto expr_val = code_val;
 
  branch_class *b = (branch_class *)cases->nth(cases->first());
  std::string case_result_type = b->get_expr()->get_type()->get_string();
  if (case_result_type == "SELF_TYPE")
    case_result_type = env->get_class()->get_type_name();
  alloca_type = env->Type_Lookup[case_result_type];
  alloca_op = env->insert_alloca_at_head(llvm::PointerType::get(alloca_type, 0));

  CgenClassTable *ct = env->get_class()->get_classtable();
  std::string header_label_ = env->new_label("case.hdr.", false);
  std::string exit_label_ = env->new_label("case.exit.", false);
  auto header_label = env->new_bb_at_fend(header_label_);
  auto exit_label = env->new_bb_at_fend(exit_label_);


  auto expr_type = expr->get_expr_tp(env);
  auto join_type = env->Type_Lookup[env->type_to_class(type)->get_type_name()];
  CgenNode *cls = env->type_to_class(expr->get_type());

  if (!code_val_tp->isStructTy()) {
    llvm::Value* null_op = llvm::ConstantPointerNull::get(llvm::PointerType::get(code_val_tp, 0));
    auto icmp_result = env->builder.CreateCmp(llvm::CmpInst::ICMP_EQ, code_val, null_op);
    auto abort_true = env->get_abrt();
    auto ok_label = env->new_ok_label();
    auto ok_false = env->new_bb_at_fend(ok_label); // false, not 0
    env->builder.CreateCondBr(icmp_result, abort_true, ok_false);
    env->builder.SetInsertPoint(ok_false);
  }
  auto tag = get_class_tag(expr_val, cls, env);
  env->builder.CreateBr(header_label);
  auto prev_label = header_label;
  env->builder.SetInsertPoint(header_label);
  env->branch_operand = alloca_op;
  env->branch_operand_tp = alloca_type;
  std::vector<llvm::Value*> values;
  std::vector<llvm::Type*> types;
  env->next_label = exit_label;


  for (int i = ct->get_num_classes() - 1; i >= 0; --i) {
    for (auto case_branch : cases) {
      if (i == ct->find_in_scopes(case_branch->get_type_decl())->get_tag()) {
        std::string prefix = std::string("case.") + std::to_string(i) + ".";
        std::string case_label_ = env->new_label(prefix, false);
        auto case_label = env->new_bb_at_fend(case_label_);
        env->builder.CreateBr(case_label);
        env->builder.SetInsertPoint(case_label);
        auto [val, tp_] = case_branch->code(expr->get_expr_tp(env), expr_val, tag, join_type, env);
        values.push_back(val);
        types.push_back(tp_);
      }
    }
  } 

  llvm::Type* set_;
  if (types.size() == 0) {
    set_ = env->Type_Lookup["Object"];
  } else if (types.size() == 1) {
    set_ = types[0];
  } else {
    set_ = Find_Parent(env, types[0], types[1]);
    for (size_t i = 2; i < types.size(); ++ i) {
      set_ = Find_Parent(env, set_, types[i]);
    }
  }
  set_expr_tp(env, set_);

  env->builder.CreateBr(env->get_abrt());

  env->new_label("", true);
  env->builder.SetInsertPoint(exit_label);

  auto final_result = env->builder.CreateLoad(llvm::PointerType::get(alloca_type, 0), alloca_op);
  return final_result;
#endif
}

Value *new__class::code(CgenEnvironment *env) {
  if (cgen_debug)
    std::cerr << "newClass" << std::endl;
#ifndef MP3
  assert(0 && "Unsupported case for phase 1");
#else
  // TODO: add code here and replace `return nullptr`
  llvm::CallInst* allocated;
  if (type_name->get_string() == "Int") {
    auto func_ptr = env->llmethod_to_Funtion_Ptr["Int_new"];
    auto callee = env->the_module.getOrInsertFunction("Int_new", func_ptr->getFunctionType());
    allocated = env->builder.CreateCall(callee, {});
    set_expr_tp(env, env->Type_Lookup["Int"]);
  } else if (type_name->get_string() == "Bool") {
    auto func_ptr = env->llmethod_to_Funtion_Ptr["Bool_new"];
    auto callee = env->the_module.getOrInsertFunction("Bool_new", func_ptr->getFunctionType());
    allocated = env->builder.CreateCall(callee, {});
    set_expr_tp(env, env->Type_Lookup["Bool"]);
  } else if (type_name->get_string() == "SELF_TYPE") {
    auto func_ptr = env->llmethod_to_Funtion_Ptr[env->get_class()->get_init_function_name()];
    auto callee = env->the_module.getOrInsertFunction(env->get_class()->get_init_function_name(), func_ptr->getFunctionType());
    allocated = env->builder.CreateCall(callee, {});
    set_expr_tp(env, env->Type_Lookup[env->get_class()->get_type_name()]);
  } else {
    auto cls = env->Name_to_Node[type_name->get_string()];
    auto func_ptr = env->llmethod_to_Funtion_Ptr[cls->get_init_function_name()];
    auto callee = env->the_module.getOrInsertFunction(cls->get_init_function_name(), func_ptr->getFunctionType());
    allocated = env->builder.CreateCall(callee, {});
    set_expr_tp(env, env->Type_Lookup[type_name->get_string()]);
  }
  return allocated;
#endif
}


Value *isvoid_class::code(CgenEnvironment *env) {
  if (cgen_debug)
    std::cerr << "isvoid" << std::endl;
#ifndef MP3
  assert(0 && "Unsupported case for phase 1");
#else
  // TODO: add code here and replace `return nullptr`
  set_expr_tp(env, Type::getInt1Ty(env->context));
  auto e1_expr = e1->code(env);
  auto e1_type = e1->get_expr_tp(env);

  if (e1_type->isStructTy()) {
    auto cond_ = env->builder.CreateCmp(llvm::CmpInst::ICMP_EQ, llvm::ConstantPointerNull::get(llvm::PointerType::get(e1_type, 0)), e1_expr);
    return cond_;
  } else {
    return ConstantInt::get(Type::getInt1Ty(env->context), false); // not void
  }

  return nullptr;
#endif
}

// Create the LLVM Function corresponding to this method.
void method_class::layout_feature(CgenNode *cls) {
#ifndef MP3
  assert(0 && "Unsupported case for phase 1");
#else
  // TODO: add code here
  // std::cerr << cls->get_name()->get_string() << ": " << name->get_string() << '\n';
  auto curr_cl_func_name = name->get_string();

  if (cls->get_current_clmethod_to_llmethod_idx()->find(curr_cl_func_name) != cls->get_current_clmethod_to_llmethod_idx()->end()) { // overload
    auto idx = (*cls->get_current_clmethod_to_llmethod_idx())[curr_cl_func_name];
    (*cls->get_current_vtable_tp())[idx] = {cls, this};
  } else { // newly insert function
    cls->get_current_vtable_tp()->push_back({cls, this});
    (*cls->get_current_clmethod_to_llmethod_idx())[curr_cl_func_name] = cls->get_current_vtable_tp()->size() - 1;
  }

  // get the ll function name
  auto curr_ll_func_name = cls->get_function_name(curr_cl_func_name);

  // ret type with unboxing
  llvm::Type* curr_ll_func_ret_tp;
  auto curr_ll_func_ret_tp_str = return_type->get_string();
  if (curr_ll_func_ret_tp_str == "Int") {
    curr_ll_func_ret_tp = Type::getInt32Ty(cls->get_classtable()->context);
  } else if (curr_ll_func_ret_tp_str == "Bool") {
    curr_ll_func_ret_tp = Type::getInt1Ty(cls->get_classtable()->context);
  } else if (curr_ll_func_ret_tp_str == "SELF_TYPE") {
    auto get_type = cls->get_classtable()->Type_Lookup[cls->get_type_name()];
    curr_ll_func_ret_tp = llvm::PointerType::get(get_type, 0);
  } else {
    auto get_type = cls->get_classtable()->Type_Lookup[curr_ll_func_ret_tp_str];
    curr_ll_func_ret_tp = llvm::PointerType::get(get_type, 0);
  }

  // par type with unboxing
  std::vector<llvm::Type*> curr_ll_func_par_tp_vec;
  // begin with SLEF_TYPE
  auto get_type = cls->get_classtable()->Type_Lookup[cls->get_type_name()]; 
  curr_ll_func_par_tp_vec.push_back(llvm::PointerType::get(get_type, 0));
  // then other par
  for(int i = formals->first(); formals->more(i); i = formals->next(i)) {
    auto formal_iter = formals->nth(i);
    llvm::Type* curr_ll_func_par_tp;
    auto curr_ll_func_par_tp_str = formal_iter->get_type_decl()->get_string();
    if (curr_ll_func_par_tp_str == "Int") {
      curr_ll_func_par_tp = Type::getInt32Ty(cls->get_classtable()->context);
    } else if (curr_ll_func_par_tp_str == "Bool") {
      curr_ll_func_par_tp = Type::getInt1Ty(cls->get_classtable()->context);
    } else if (curr_ll_func_par_tp_str == "SELF_TYPE") {
      auto get_type = cls->get_classtable()->Type_Lookup[cls->get_type_name()];
      curr_ll_func_par_tp = llvm::PointerType::get(get_type, 0);
    } else {
      auto get_type = cls->get_classtable()->Type_Lookup[curr_ll_func_par_tp_str];
      curr_ll_func_par_tp = llvm::PointerType::get(get_type, 0);
    }
    curr_ll_func_par_tp_vec.push_back(curr_ll_func_par_tp);
  } 

  assert(curr_ll_func_ret_tp);
  auto created_ll_func = cls->create_llvm_function(curr_ll_func_name, curr_ll_func_ret_tp, curr_ll_func_par_tp_vec, false);
  (*cls->get_current_Function_Body_Map())[created_ll_func] = this;
  cls->get_classtable()->llmethod_to_Funtion_Ptr[curr_ll_func_name] = created_ll_func;

#endif
}


// Handle one branch of a Cool case expression.
// If the source tag is >= the branch tag
// and <= (max child of the branch class) tag,
// then the branch is a superclass of the source.
// See the MP3 handout for more information about our use of class tags.
std::pair<llvm::Value*, llvm::Type*> branch_class::code(llvm::Type* expr_tp, Value *expr_val, Value *tag, Type *join_type,
                          CgenEnvironment *env) {
#ifndef MP3
  assert(0 && "Unsupported case for phase 1");
#else
  // TODO: add code here and replace `return nullptr`

  CgenNode *cls = env->get_class()->get_classtable()->find_in_scopes(type_decl);
  llvm::Type* alloca_type;
  llvm::Value* alloca_op;
  if (cls->get_type_name() == "Int") {
    alloca_type = llvm::Type::getInt32Ty(env->context);
    alloca_op = env->insert_alloca_at_head(llvm::Type::getInt32Ty(env->context));
  } else if (cls->get_type_name() == "Bool") {
    alloca_type = llvm::Type::getInt1Ty(env->context);
    alloca_op = env->insert_alloca_at_head(llvm::Type::getInt1Ty(env->context));
  } else {
    alloca_type = env->Type_Lookup[cls->get_type_name()];
    alloca_op = env->insert_alloca_at_head(llvm::PointerType::get(alloca_type, 0));
  }
  int my_tag = cls->get_tag();
  int max_child = cls->get_max_child();

  std::string sg_label_ =
      env->new_label(std::string("src_gte_br") + "." + std::to_string(my_tag) + ".", false);
  std::string sl_label_ =
      env->new_label(std::string("src_lte_mc") + "." + std::to_string(my_tag) + ".", false);
  std::string exit_label_ =
      env->new_label(std::string("br_exit") + "." + std::to_string(my_tag) + ".", false);
  auto sg_label = env->new_bb_at_fend(sg_label_);
  auto sl_label = env->new_bb_at_fend(sl_label_);
  auto exit_label = env->new_bb_at_fend(exit_label_);


  llvm::Value* my_tag_val = llvm::ConstantInt::get(llvm::Type::getInt32Ty(env->context), my_tag);
  auto icmp_result = env->builder.CreateCmp(llvm::CmpInst::ICMP_SLT, tag, my_tag_val);
  env->builder.CreateCondBr(icmp_result, exit_label, sg_label);
  env->builder.SetInsertPoint(sg_label);

  llvm::Value* max_child_val = llvm::ConstantInt::get(llvm::Type::getInt32Ty(env->context), max_child);
  auto icmp_result2 = env->builder.CreateCmp(llvm::CmpInst::ICMP_SGT, tag, max_child_val);
  env->builder.CreateCondBr(icmp_result2, exit_label, sl_label);
  env->builder.SetInsertPoint(sl_label);

  if (cls->get_type_name() == "Int") {
    expr_val = Conform(env, env->Type_Lookup["Int"], expr_tp, expr_val);
    expr_tp = env->Type_Lookup["Int"];
  } else if (cls->get_type_name() == "Bool") {
    expr_val = Conform(env, env->Type_Lookup["Bool"], expr_tp, expr_val);
    expr_tp = env->Type_Lookup["Bool"];
  }
  
  auto conf_result = Conform(env, alloca_type, expr_tp, expr_val);

  env->builder.CreateStore(conf_result, alloca_op);
  env->open_scope();
  env->var_tp_open_scope();
  env->add_binding(name, alloca_op);
  env->var_tp_add_binding(name, alloca_type); //////////////////////////////

  auto Val_ = expr->code(env);
  auto Tp_ = expr->get_expr_tp(env);
  auto val = Conform(env, join_type, Tp_, Val_);
  auto conformed = Conform(env, env->branch_operand_tp, join_type, val); 
  env->builder.CreateStore(conformed, env->branch_operand);


  env->close_scope();
  env->var_tp_close_scope();

  env->builder.CreateBr(env->next_label);
  env->builder.SetInsertPoint(exit_label);

  return {conformed, env->branch_operand_tp};
#endif
}

// Assign this attribute a slot in the class structure
void attr_class::layout_feature(CgenNode *cls) {
#ifndef MP3
  assert(0 && "Unsupported case for phase 1");
#else
  // TODO: add code here
  cls->get_current_obj_tp()->push_back({cls, this});
#endif
}

Value *attr_class::code(CgenEnvironment *env) {
#ifndef MP3
  assert(0 && "Unsupported case for phase 1");
#else
  // TODO: add code here and replace `return nullptr`
  auto expr_val = init->code(env);
  auto expr_type = init->get_expr_tp(env);

  if (expr_val == nullptr || expr_type == nullptr) {
      auto self_ptr = env->MALLOC_ADDR;
      auto attr_addr_val = Get_Attr_Addr(env, env->get_class(), self_ptr, name->get_string());
      auto attr_type = Get_Attr_Type(env, env->get_class(), name->get_string());
      if (attr_type->isIntegerTy(32)) {
        env->builder.CreateStore(llvm::ConstantInt::get(llvm::Type::getInt32Ty(env->context), 0), attr_addr_val);
      } else if (attr_type->isIntegerTy(1)) {
        env->builder.CreateStore(llvm::ConstantInt::get(llvm::Type::getInt1Ty(env->context), false), attr_addr_val);
      } else if (attr_type->isStructTy()) {
        env->builder.CreateStore(llvm::ConstantPointerNull::get(llvm::PointerType::get(attr_type, 0)), attr_addr_val);
      } else {
        assert(false);
      }
  } else {
      auto self_ptr = env->MALLOC_ADDR;
      auto attr_addr_val = Get_Attr_Addr(env, env->get_class(), self_ptr, name->get_string());
      auto attr_type = Get_Attr_Type(env, env->get_class(), name->get_string());

      auto expr_val_conform = Conform(env, attr_type, expr_type, expr_val);
      env->builder.CreateStore(expr_val_conform, attr_addr_val);
  }

  return expr_val;
#endif
}
