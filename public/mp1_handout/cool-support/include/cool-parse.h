//
// See copyright.h for copyright notice and limitation of liability
// and disclaimer of warranty provisions.
//
#include "copyright.h"

#ifndef _COOL_PARSE_H
#define _COOL_PARSE_H

#include "cool-tree.h"
#include "cool.h"
#include <ostream>

#ifndef BISON_COOL_TAB_H
#define BISON_COOL_TAB_H

#define MAX_STR_CONST 1025
#define YY_NO_UNPUT
#define yylval cool_yylval
#define yylex cool_yylex

#ifndef YYSTYPE
typedef union {
  Boolean boolean;
  Symbol symbol;
  Program program;
  Class_ class_;
  Classes classes;
  Feature feature;
  Features features;
  Formal formal;
  Formals formals;
  Case case_;
  Cases cases;
  Expression expression;
  Expressions expressions;
  const char *error_msg;
} yystype;
#define YYSTYPE yystype
#define YYSTYPE_IS_TRIVIAL 1
#endif
#define CLASS 258
#define ELSE 259
#define FI 260
#define IF 261
#define IN 262
#define INHERITS 263
#define LET 264
#define LOOP 265
#define POOL 266
#define THEN 267
#define WHILE 268
#define CASE 269
#define ESAC 270
#define OF 271
#define DARROW 272
#define NEW 273
#define ISVOID 274
#define STR_CONST 275
#define INT_CONST 276
#define BOOL_CONST 277
#define TYPEID 278
#define OBJECTID 279
#define ASSIGN 280
#define NOT 281
#define LE 282
#define FOR 283
#define ERROR 284

extern YYSTYPE cool_yylval;

#endif /* not BISON_COOL_TAB_H */
#endif
