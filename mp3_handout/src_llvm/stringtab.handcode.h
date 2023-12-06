// This file defines extra methods for classes in stringtab.h
// that are specific to code generation.
#ifndef STRINGTAB_HANDCODE_H
#define STRINGTAB_HANDCODE_H

#include <iostream>
class CgenClassTable;

// Extra methods added to classes in stringtab.h
#define StringEntry_EXTRAS                                                     \
  void code_def(std::ostream &str, CgenClassTable *classTable);                \
  void code_ref(std::ostream &str, CgenClassTable *classTable);                \

#define IntEntry_EXTRAS                                                        \
  void code_ref(std::ostream &str, CgenClassTable *classTable);

#define StrTable_EXTRAS                                                        \
  void code_string_table(std::ostream &, CgenClassTable *classTable);

#endif /* STRINGTAB_HANDCODE_H */
