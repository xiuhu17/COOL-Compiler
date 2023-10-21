// -*-Mode: C++;-*-
//
// See copyright.h for copyright notice and limitation of liability
// and disclaimer of warranty provisions.
//
#include "copyright.h"

#ifndef _STRINGTAB_H_
#define _STRINGTAB_H_

#include "stringtab.handcode.h"
#include <cassert>
#include <ostream>
#include <string>
#include <unordered_map>

class Entry {
protected:
  std::string str;
  int index;

public:
  Entry() = default;
  Entry(std::string s, int i) : str(std::move(s)), index(i) {}

  const std::string &get_string() const { return str; }
  int get_index() const { return index; }
};

using Symbol = Entry *;

inline std::ostream &operator<<(std::ostream &s, const Entry &sym) {
  return s << "{" << sym.get_string() << ", " << sym.get_index() << "}\n";
}

//
// There are three kinds of string table entries:
//   a true string, an string representation of an identifier, and
//   a string representation of an integer.
//
// Having separate tables is convenient for code generation. Different
// data definitions are generated for string constants (StringEntry) and
// integer  constants (IntEntry). Identifiers (IdEntry) don't produce
// static data definitions.
//
// code_def and code_ref are used by the code to produce definitions and
// references (respectively) to constants.
//
class StringEntry : public Entry {
public:
  StringEntry() = default;
  StringEntry(std::string s, int i) : Entry(std::move(s), i) {}

#ifdef StringEntry_EXTRAS
  StringEntry_EXTRAS
#endif
};

class IdEntry : public Entry {
public:
  IdEntry() = default;
  IdEntry(std::string s, int i) : Entry(std::move(s), i) {}
};

class IntEntry : public Entry {
public:
  IntEntry() = default;
  IntEntry(std::string s, int i) : Entry(std::move(s), i) {}
#ifdef IntEntry_EXTRAS
  IntEntry_EXTRAS
#endif
};

//////////////////////////////////////////////////////////////////////////
//
//  String Tables
//
//////////////////////////////////////////////////////////////////////////

template <typename Entry> class StringTable {
protected:
  std::unordered_map<std::string, Entry> _table;

public:
  Symbol add_string(const std::string &s) {
    if (_table.find(s) == _table.end()) {
      _table[s] = Entry(s, _table.size());
    }
    // unordered_map pointer is stable, so we are safe here.
    return &_table.find(s)->second;
  }

  Symbol lookup_string(const std::string &s) {
    auto found = _table.find(s);
    return found == _table.end() ? nullptr : &found->second;
  }
};

class IdTable : public StringTable<IdEntry> {};

class StrTable : public StringTable<StringEntry> {
public:
#ifdef StrTable_EXTRAS
  StrTable_EXTRAS
#endif
};

class IntTable : public StringTable<IntEntry> {
public:
#ifdef IntTable_EXTRAS
  IntTable_EXTRAS
#endif
};

extern IdTable idtable;
extern IntTable inttable;
extern StrTable stringtable;
#endif
