#include "utils.h"
#include <iomanip>
#include <ostream>
#include <unordered_map>

std::string pad(int n) {
  if (n <= 0) {
    return "";
  }
  return std::string(std::min(n, 80), ' ');
}

void print_escaped_string(std::ostream &str, const std::string &s) {
  for (char c : s) {
    switch (c) {
    case '\\':
      str << "\\\\";
      break;
    case '\"':
      str << "\\\"";
      break;
    case '\n':
      str << "\\n";
      break;
    case '\t':
      str << "\\t";
      break;
    case '\b':
      str << "\\b";
      break;
    case '\f':
      str << "\\f";
      break;

    default:
      if (isprint(c))
        str << c;
      else
        //
        // Unprintable characters are printed using octal equivalents.
        // To get the sign of the octal number correct, the character
        // must be cast to an unsigned char before coverting it to an
        // integer.
        //
        str << '\\' << std::oct << std::setfill('0') << std::setw(3)
            << (int)((unsigned char)(c)) << std::dec << std::setfill(' ');
      break;
    }
  }
}

void dump_Boolean(std::ostream &stream, int padding, bool b) {
  stream << pad(padding) << (int)b << "\n";
}
void dump_Symbol(std::ostream &s, int n, Symbol sym) {
  s << pad(n) << sym->get_string() << std::endl;
}
