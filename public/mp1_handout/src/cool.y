/*
 *  cool.y
 *              Parser definition for the COOL language.
 *
 */
%{
#include <iostream>
#include "cool-tree.h"
#include "stringtab.h"
#include "utilities.h"

/* Add your own C declarations here */


/************************************************************************/
/*                DONT CHANGE ANYTHING IN THIS SECTION                  */

extern int yylex();           /* the entry point to the lexer  */
extern int curr_lineno;
extern char *curr_filename;
Program ast_root;            /* the result of the parse  */
int omerrs = 0;              /* number of errors in lexing and parsing */

/*
   The parser will always call the yyerror function when it encounters a parse
   error. The given yyerror implementation (see below) justs prints out the
   location in the file where the error was found. You should not change the
   error message of yyerror, since it will be used for grading puproses.
*/
void yyerror(const char *s);

/*
   The VERBOSE_ERRORS flag can be used in order to provide more detailed error
   messages. You can use the flag like this:

     if (VERBOSE_ERRORS)
       fprintf(stderr, "semicolon missing from end of declaration of class\n");

   By default the flag is set to 0. If you want to set it to 1 and see your
   verbose error messages, invoke your parser with the -v flag.

   You should try to provide accurate and detailed error messages. A small part
   of your grade will be for good quality error messages.
*/
extern int VERBOSE_ERRORS;

%}

/* A union of all the types that can be the result of parsing actions. */
%union {
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
  char *error_msg;
}

/* 
   Declare the terminals; a few have types for associated lexemes.
   The token ERROR is never used in the parser; thus, it is a parse
   error when the lexer returns it.

   The integer following token declaration is the numeric constant used
   to represent that token internally.  Typically, Bison generates these
   on its own, but we give explicit numbers to prevent version parity
   problems (bison 1.25 and earlier start at 258, later versions -- at
   257)
*/
%token CLASS 258 ELSE 259 FI 260 IF 261 IN 262 
%token INHERITS 263 LET 264 LOOP 265 POOL 266 THEN 267 WHILE 268
%token CASE 269 ESAC 270 OF 271 DARROW 272 NEW 273 ISVOID 274
%token <symbol>  STR_CONST 275 INT_CONST 276 
%token <boolean> BOOL_CONST 277
%token <symbol>  TYPEID 278 OBJECTID 279 
%token ASSIGN 280 NOT 281 LE 282 FOR 283 ERROR 284

/*  DON'T CHANGE ANYTHING ABOVE THIS LINE, OR YOUR PARSER WONT WORK       */
/**************************************************************************/

/* Complete the nonterminal list below, giving a type for the semantic
  value of each non terminal. (See section 3.6 in the bison 
  documentation for details). */

/* Declare types for the grammar's non-terminals. */
%type <program> program
%type <classes> class_list
%type <class_> class

%type <features> feature_list_star
%type <feature> feature_single

%type <formals> formal_list_star
%type <formal> formal_single

%type <cases> case_list_pos
%type <case_> case_single

%type <expressions> expression_list_star
%type <expressions> expression_list_pos
%type <expression> expression_single 

%type <expression> let_begin 
%type <expression> let_expand
%type <expression> for_begin
%type <expression> for_second  
%type <expression> for_expand



/* You will want to change the following line. */
/* %type <features> dummy_feature_list */

/* Precedence declarations go here. */

%nonassoc prec_let_expand

%right ASSIGN
%left NOT
%nonassoc LE '<' '='
%left '+' '-'
%left '*' '/'
%left ISVOID
%left '~'
%left '@'
%left '.'

%%
/* 
   Save the root of the abstract syntax tree in a global variable.
*/
program : class_list { ast_root = program($1); }
        ;

class_list
        : class            /* single class */
                { $$ = single_Classes($1); }
        | class_list class /* several classes */
                { $$ = append_Classes($1,single_Classes($2)); }
        ;

/* If no parent is specified, the class inherits from the Object class. */
class  : CLASS TYPEID '{' feature_list_star '}' ';'
                { $$ = class_($2,idtable.add_string("Object"), $4, stringtable.add_string(curr_filename)); }
        | CLASS TYPEID INHERITS TYPEID '{' feature_list_star '}' ';'
                { $$ = class_($2,$4,$6,stringtable.add_string(curr_filename)); }
        ; 

/* Feature list may be empty, but no empty features in list. */
feature_list_star      :  /* empty */
                                {  $$ = nil_Features(); }
                        | feature_list_star feature_single ';'
                                {}
                ;          
feature_single          : OBJECTID '(' ')' ':' TYPEID '{' expression_single '}' 
                                {}
                        | OBJECTID '(' formal_single formal_list_star ')' ':' TYPEID '{' expression_single '}'
                                {}
                        | OBJECTID ':' TYPEID 
                                {}
                        | OBJECTID ':' TYPEID ASSIGN expression_single 
                                {}
                ;


formal_list_star        : /* empty */
                                {}
                        | formal_list_star ',' formal_single
                                {}
                ;
formal_single           : OBJECTID ':' TYPEID 
                                {}
                ;


case_list_pos           : case_single ';'
                                {}
                        | case_list_pos case_single ';'
                                {}
                ;
case_single             : OBJECTID ':' TYPEID DARROW expression_single 
                                {}
                ;


let_expand              : IN expression_single  %prec prec_let_expand
                                {}
                        | ',' OBJECTID ':' TYPEID let_expand  
                                {}
                        | ',' OBJECTID ':' TYPEID ASSIGN expression_single let_expand  
                                {} 
                ;
let_begin               : LET OBJECTID ':' TYPEID let_expand 
                                {}
                        | LET OBJECTID ':' TYPEID ASSIGN expression_single let_expand  
                                {}
                ;
                

for_second              : ';' expression_single ';' expression_single ')' '{' expression_single '}' 
                                {}
                ;
for_expand              : for_second 
                                {}
                        | ',' OBJECTID ':' TYPEID for_expand 
                                {}
                        | ',' OBJECTID ':' TYPEID ASSIGN expression_single for_expand
                                {}
                ;
for_begin               : FOR '(' OBJECTID ':' TYPEID for_expand  
                                {}         
                        | FOR '(' OBJECTID ':' TYPEID ASSIGN expression_single for_expand
                                {}
                ;



expression_list_star    : /* empty */
                                {}
                        | expression_list_star ',' expression_single
                                {}
                ;
expression_list_pos     : expression_single ';'
                                {}
                        | expression_list_pos expression_single ';'
                                {}
                ;

expression_single       : OBJECTID ASSIGN expression_single
                                {}
                        | expression_single '.' OBJECTID '('  ')'
                                {}
                        | expression_single '.' OBJECTID '(' expression_single  expression_list_star ')'
                                {}
                        | expression_single '@' TYPEID '.' OBJECTID '('  ')'
                                {}
                        | expression_single '@' TYPEID '.' OBJECTID '(' expression_single  expression_list_star ')'
                                {}
                        | OBJECTID '(' ')'
                                {}
                        | OBJECTID '(' expression_single  expression_list_star ')'
                                {}
                        | IF expression_single THEN expression_single ELSE expression_single FI 
                                {}
                        | WHILE expression_single LOOP expression_single POOL
                                {}
                        | '{' expression_list_pos '}' 
                                {}
                        | let_begin
                                {}
                        | for_begin
                                {}
                        | CASE expression_single OF case_list_pos ESAC 
                                {}
                        | NEW TYPEID
                                {}
                        | ISVOID expression_single
                                {}
                        | expression_single '+' expression_single 
                                {}
                        | expression_single '-' expression_single
                                {}
                        | expression_single '*' expression_single
                                {}
                        | expression_single '/' expression_single
                                {}
                        | '~' expression_single 
                                {}
                        | expression_single '<' expression_single 
                                {}
                        | expression_single LE expression_single 
                                {}
                        | expression_single '=' expression_single 
                                {}
                        | NOT expression_single 
                                {}
                        | '(' expression_single ')'
                                {}
                        | OBJECTID
                                {}
                        | INT_CONST
                                {}
                        | STR_CONST
                                {}
                        | BOOL_CONST
                                {}
                ;

/* end of grammar */
%%

/* This function is called automatically when Bison detects a parse error. */
void yyerror(const char *s) {
  std::cerr << "\"" << curr_filename << "\", line " << curr_lineno << ": " << s
            << " at or near ";
  print_cool_token(yychar);
  std::cerr << std::endl;
  omerrs++;

  if (omerrs > 20) {
    if (VERBOSE_ERRORS) {
      std::cerr << "More than 20 errors\n";
    }
    exit(1);
  }
}
