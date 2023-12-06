// -*-Mode: C++;-*-
//
// See copyright.h for copyright notice and limitation of liability
// and disclaimer of warranty provisions.
//
#include "copyright.h"
#include <ostream>

#ifndef _UTILITIES_H_
#define _UTILITIES_H_

const char *cool_token_to_string(int tok);
void print_cool_token(int tok);
void fatal_error(char *);
void print_escaped_string(std::ostream &str, const char *s);
const char *pad(int);
std::string hex2dec(const std::string &hex);

#endif
