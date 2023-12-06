// -*-Mode: C++;-*-
//
// See copyright.h for copyright notice and limitation of liability
// and disclaimer of warranty provisions.
//
#include "copyright.h"

#ifndef _STRINGTAB_H_
#define _STRINGTAB_H_

#include "list.h" // list template
#include <cassert>
#include <cstring>
#include <iostream>

const size_t MAXSIZE = 1000000;

/////////////////////////////////////////////////////////////////////////
//
//  String Table Entries
//
/////////////////////////////////////////////////////////////////////////

class Entry {
protected:
  char *str; // the string
  int len;   // the length of the string (without trailing \0)
  int index; // a unique index for each string
public:
  Entry(const char *s, int l, int i);

  // is string argument equal to the str of this Entry?
  int equal_string(const char *s, int len) const;

  // is the integer argument equal to the index of this Entry?
  bool equal_index(int ind) const { return ind == index; }

  std::ostream &print(std::ostream &s) const;

  // Return the str and len components of the Entry.
  const char *get_string() const;
  int get_len() const;
};

std::ostream &operator<<(std::ostream &s, const Entry &sym);

typedef Entry *Symbol;
std::ostream &operator<<(std::ostream &s, Symbol sym);

//
// There are three kinds of string table entries:
//   a true string, an string representation of an identifier, and
//   a string representation of an integer.
//
// Having separate tables is convenient for code generation.  Different
// data definitions are generated for string constants (StringEntry) and
// integer  constants (IntEntry).  Identifiers (IdEntry) don't produce
// static data definitions.
//
// code_def and code_ref are used by the code to produce definitions and
// references (respectively) to constants.
//
class StringEntry : public Entry {
public:
  void code_def(std::ostream &str, int stringclasstag);
  void code_ref(std::ostream &str);
  StringEntry(const char *s, int l, int i);
};

class IdEntry : public Entry {
public:
  IdEntry(const char *s, int l, int i);
};

class IntEntry : public Entry {
public:
  void code_def(std::ostream &str, int intclasstag);
  void code_ref(std::ostream &str);
  IntEntry(const char *s, int l, int i);
};

typedef StringEntry *StringEntryP;
typedef IdEntry *IdEntryP;
typedef IntEntry *IntEntryP;

//////////////////////////////////////////////////////////////////////////
//
//  String Tables
//
//////////////////////////////////////////////////////////////////////////

template <class Elem> class StringTable {
protected:
  List<Elem> *tbl; // a string table is a list
  int index;       // the current index
public:
  StringTable() : tbl((List<Elem> *)NULL), index(0) {} // an empty table
  // The following methods each add a string to the string table.
  // Only one copy of each string is maintained.
  // Returns a pointer to the string table entry with the string.

  // add the prefix of s of length maxchars
  Elem *add_string(const char *s, int maxchars);

  // add the (null terminated) string s
  Elem *add_string(const char *s);

  // add the string representation of an integer
  Elem *add_int(int i);

  // An iterator.
  int first();     // first index
  int more(int i); // are there more indices?
  int next(int i); // next index

  Elem *lookup(int index);            // lookup an element using its index
  Elem *lookup_string(const char *s); // lookup an element using its string

  void print(); // print the entire table; for debugging
};

class IdTable : public StringTable<IdEntry> {};

class StrTable : public StringTable<StringEntry> {
public:
  void code_string_table(std::ostream &, int classtag);
};

class IntTable : public StringTable<IntEntry> {
public:
  void code_string_table(std::ostream &, int classtag);
};

//
// A string table is implemented a linked list of Entrys.  Each Entry
// in the list has a unique string.
//

template <class Elem> Elem *StringTable<Elem>::add_string(const char *s) {
  return add_string(s, MAXSIZE);
}

//
// Add a string requires two steps.  First, the list is searched; if the
// string is found, a pointer to the existing Entry for that string is
// returned.  If the string is not found, a new Entry is created and added
// to the list.
//
template <class Elem>
Elem *StringTable<Elem>::add_string(const char *s, int maxchars) {
  int len = std::min((int)strlen(s), maxchars);
  for (List<Elem> *l = tbl; l; l = l->tl())
    if (l->hd()->equal_string(s, len))
      return l->hd();

  Elem *e = new Elem(s, len, index++);
  tbl = new List<Elem>(e, tbl);
  return e;
}

//
// To look up a string, the list is scanned until a matching Entry is located.
// If no such entry is found, an assertion failure occurs.  Thus, this function
// is used only for strings that one expects to find in the table.
//
template <class Elem> Elem *StringTable<Elem>::lookup_string(const char *s) {
  int len = strlen(s);
  for (List<Elem> *l = tbl; l; l = l->tl())
    if (l->hd()->equal_string(s, len))
      return l->hd();
  assert(0);   // fail if string is not found
  return NULL; // to avoid compiler warning
}

//
// lookup is similar to lookup_string, but uses the index of the string
// as the key.
//
template <class Elem> Elem *StringTable<Elem>::lookup(int ind) {
  for (List<Elem> *l = tbl; l; l = l->tl())
    if (l->hd()->equal_index(ind))
      return l->hd();
  assert(0);   // fail if string is not found
  return NULL; // to avoid compiler warning
}

//
// add_int adds the string representation of an integer to the list.
//
template <class Elem> Elem *StringTable<Elem>::add_int(int i) {
  static char *buf = new char[20];
  snprintf(buf, 20, "%d", i);
  return add_string(buf);
}
template <class Elem> int StringTable<Elem>::first() { return 0; }

template <class Elem> int StringTable<Elem>::more(int i) { return i < index; }

template <class Elem> int StringTable<Elem>::next(int i) {
  assert(i < index);
  return i + 1;
}

template <class Elem> void StringTable<Elem>::print() {
  list_print(std::cerr, tbl);
}

extern IdTable idtable;
extern IntTable inttable;
extern StrTable stringtable;

#endif
