//
// See copyright.h for copyright notice and limitation of liability
// and disclaimer of warranty provisions.
//
#include "copyright.h"

#ifndef _SYMTAB_H_
#define _SYMTAB_H_

#include <optional>
#include <unordered_map>
#include <vector>

// added to prevent clash with llvm::SymbolTable
namespace cool {

// SymbolTable<V> describes a symbol table mapping symbols of
//    type `K` to data of type `V`. It is implemented as a
//    vector of vectors of `SymtabEntry<K, V>`.
//
//    `enterscope` makes the table point to a new scope whose parent
//       is the scope it pointed to previously.
//
//    `exitscope` makes the table point to the parent scope of the
//        current scope.  Note that the old child scope is not
//        deallocated.  One may save the state of a symbol table
//        at a given point by copying it with `operator =`
//
//    `insert(k, v)` adds a symbol table entry to the current scope of
//        the symbol table mapping symbol `k` to data `v`.
//
//    `find_in_scopes(k)` looks for the symbol `k` in all scopes starting at the
//    top scope,
//        returning the data item associated with the entry, or nullptr if
//        not found.
//
//    `find(s)` looks for the symbol `k` in the current scope only.
//
//    `dump()` prints the symbols in the symbol table.
//

template <class V> class SymbolTable {
private:
  using TableEntry = std::pair<Symbol, V *>;
  using Scope = std::unordered_map<Symbol, V *>;

  std::vector<Scope> scopes;

public:
  SymbolTable() = default;

  void enterscope() { this->scopes.emplace_back(); }

  void exitscope() {
    // It is an error to exit a scope that doesn't exist.
    if (this->scopes.empty()) {
      throw std::runtime_error(
          "exitscope: Can't remove scope from an empty symbol table.");
    }
    this->scopes.pop_back();
  }

  void insert(const Symbol &k, V *v) {
    // There must be at least one scope to add a symbol.
    if (this->scopes.empty()) {
      throw std::runtime_error("insert: Can't add a symbol without a scope.");
    }
    if (v == nullptr) {
      throw std::runtime_error("insert: Can't add a nullptr value.");
    }
    this->scopes.back().emplace(k, v);
  }

  V *find(const Symbol &k) const {
    if (this->scopes.empty()) {
      throw std::runtime_error("probe: No scope in symbol table.");
    }
    auto it = this->scopes.back().find(k);
    if (it == this->scopes.back().end()) {
      return nullptr;
    }
    return it->second;
  }

  V *find_in_scopes(const Symbol &k) const {
    for (auto it = this->scopes.rbegin(); it != this->scopes.rend(); ++it) {
      auto entry = it->find(k);
      if (entry != it->end()) {
        return entry->second;
      }
    }
    return nullptr;
  }

  void dump(std::ostream &s) const {
    s << "SymbolTable(\n";
    for (auto &scope : this->scopes) {
      s << "  Scope(\n";
      for (auto &[k, v] : scope) {
        s << "    " << k->get_string() << " -> " << v << "\n";
      }
      s << "  )\n";
    }
    s << ")\n";
  }
};

template <typename V>
std::ostream &operator<<(std::ostream &s, const SymbolTable<V> &symtab) {
  symtab.dump(s);
  return s;
}

} // namespace cool

#endif
