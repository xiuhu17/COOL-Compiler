//
// See copyright.h for copyright notice and limitation of liability
// and disclaimer of warranty provisions.
//
#include "copyright.h"

#ifndef _COOL_H_
#define _COOL_H_

#include "utilities.h"
#include <ostream>

/* a type renaming */
typedef int Boolean;
class Entry;
typedef Entry *Symbol;

inline Boolean copy_Boolean(Boolean b) { return b; }
inline void assert_Boolean(Boolean) {}
inline void dump_Boolean(std::ostream &stream, int padding, Boolean b) {
  stream << pad(padding) << (int)b << "\n";
}

Symbol copy_Symbol(Symbol);
void assert_Symbol(Symbol);
void dump_Symbol(std::ostream &, int, Symbol);

#endif
