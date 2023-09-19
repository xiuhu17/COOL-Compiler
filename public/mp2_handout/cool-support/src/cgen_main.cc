
//
// See copyright.h for copyright notice and limitation of liability
// and disclaimer of warranty provisions.
//
#include "copyright.h"

#include "cool_tree.h"
#include <fstream>
#include <iostream>
#include <optional>
#include <unistd.h>

extern Program ast_root;      // root of the abstract syntax tree
FILE *ast_file = stdin;       // we read the AST from standard input
extern int ast_yyparse(void); // entry point to the AST parser

std::string out_filename;    // file name for generated code
int cgen_debug, curr_lineno; // for code gen
extern char *optarg; // used for option processing (man 3 getopt for more info)

void handle_flags(int argc, char *argv[]) {
  int c;
  int unknownopt = 0;

  // no debugging or optimization by default
  cgen_debug = 0;

  while ((c = getopt(argc, argv, "do:")) != -1) {
    switch (c) {
#ifdef DEBUG
    case 'd':
      cgen_debug = 1;
      break;
#else
    case 'd':
      std::cerr << "No debugging available\n";
      break;
#endif
    case 'o': // set the name of the output file
      out_filename = optarg;
      break;
    case '?':
      unknownopt = 1;
      break;
    case ':':
      unknownopt = 1;
      break;
    }
  }

  if (unknownopt) {
    std::cerr << "usage: " << argv[0] <<
#ifdef DEBUG
        " [-d -o outname]\n";
#else
        " [-o outname]\n";
#endif
    exit(1);
  }
}

int main(int argc, char *argv[]) {
  handle_flags(argc, argv);
  if (optind < argc) {
    ast_file = fopen(argv[optind], "r");
    if (!ast_file) {
      std::cerr << "Cannot open input file " << argv[optind] << std::endl;
      exit(1);
    }
  }

  // Don't touch the output file until we know that earlier phases of the
  // compiler have succeeded.
  ast_yyparse();

  if (!out_filename.empty()) {
    ast_root->cgen(out_filename);
  } else {
    ast_root->cgen(std::nullopt);
  }
}
