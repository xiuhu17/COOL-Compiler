//
// See copyright.h for copyright notice and limitation of liability
// and disclaimer of warranty provisions.
//
#include "copyright.h"

//////////////////////////////////////////////////////////////////////////////
//
//  lextest.cc
//
//  Reads input from file argument.
//
//  Option -l prints summary of flex actions.
//
//////////////////////////////////////////////////////////////////////////////

#include "cool-parse.h" // bison-generated file; defines tokens
#include "utilities.h"
#include <iostream>
#include <stdio.h>  // needed on Linux system
#include <unistd.h> // for getopt

//
//  The lexer keeps this global variable up to date with the line number
//  of the current line read from the input.
//
int curr_lineno = 1;
const char *curr_filename = "<stdin>"; // this name is arbitrary
FILE *fin; // This is the file pointer from which the lexer reads its input.

//
//  cool_yylex() is the function produced by flex. It returns the next
//  token each time it is called.
//
extern int cool_yylex();
YYSTYPE cool_yylval; // Not compiled with parser, so must define this.

extern int optind; // used for option processing (man 3 getopt for more info)

//
//  Option -l sets yy_flex_debug.
//
extern int yy_flex_debug; // Flex debugging; see flex documentation.

void handle_flags(int argc, char *argv[]);

//
//  The full Cool compiler contains several debugging flags, all of which
//  are handled and set by the routine handle_flags.  Here we declare
//  cool_yydebug, which is not used by the lexer but is needed to link
//  with handle_flags.
//
int cool_yydebug;

// defined in utilities.cc
extern void dump_cool_token(std::ostream &out, int lineno, int token,
                            YYSTYPE yylval);

int main(int argc, char **argv) {
  int token;

  handle_flags(argc, argv);

  while (optind < argc) {
    fin = fopen(argv[optind], "r");
    if (fin == NULL) {
      std::cerr << "Could not open input file " << argv[optind] << std::endl;
      exit(1);
    }

    // sm: the 'coolc' compiler's file-handling loop resets
    // this counter, so let's make the stand-alone lexer
    // do the same thing
    curr_lineno = 1;

    //
    // Scan and print all tokens.
    //
    std::cout << "#name \"" << argv[optind] << "\"" << std::endl;
    while ((token = cool_yylex()) != 0) {
      dump_cool_token(std::cout, curr_lineno, token, cool_yylval);
    }
    fclose(fin);
    optind++;
  }
  exit(0);
}
