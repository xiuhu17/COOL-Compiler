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
#define PARSE_ERR NULL

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
%type <expression> let_no_expr_helper



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
        : class ';'           /* single class */
                { $$ = single_Classes($1); }
        | error              /* support the situation that error could be appear at the beginning of the class_list, {erro, normal, normal ...} */
                {  yyclearin;   }
        | class_list class ';' /* several classes */
                { $$ = append_Classes($1,single_Classes($2)); }
        | class_list error ';'
                {  yyclearin;   }
        ;

/* error will be popped to higher level, that is, class_list */
/* If no parent is specified, the class inherits from the Object class. */
class  : CLASS TYPEID '{' feature_list_star '}' 
                { $$ = class_($2,idtable.add_string("Object"), $4, stringtable.add_string(curr_filename)); }
        | CLASS TYPEID INHERITS TYPEID '{' feature_list_star '}' 
                { $$ = class_($2,$4,$6,stringtable.add_string(curr_filename)); }
        | error '{' feature_list_star '}' 
                {  yyclearin;  }
        ;
        

/* Feature list may be empty, but no empty features in list. */
feature_list_star      :  /* empty */
                                {  $$ = nil_Features(); }
                        | feature_list_star feature_single ';'
                                {  $$ = append_Features($1, single_Features($2)); }
                        | feature_list_star error ';'
                                {  yyclearin;  }
                ;          
feature_single          : OBJECTID '(' ')' ':' TYPEID '{' expression_single '}' 
                                {  $$ = method($1, nil_Formals(), $5, $7);  }
                        | OBJECTID '(' formal_single formal_list_star ')' ':' TYPEID '{' expression_single '}'
                                {  $$ = method($1, append_Formals(single_Formals($3), $4), $7, $9);  }
                        | OBJECTID ':' TYPEID 
                                {  $$ = attr($1, $3, no_expr());  }
                        | OBJECTID ':' TYPEID ASSIGN expression_single 
                                {  $$ = attr($1, $3, $5);  }      
                ;


formal_list_star        : /* empty */
                                {  $$ = nil_Formals();  }
                        | formal_list_star ',' formal_single
                                {  $$ = append_Formals($1, single_Formals($3));  }
                ;
formal_single           : OBJECTID ':' TYPEID 
                                {  $$ = formal($1, $3);  }
                ;


case_list_pos           : case_single ';'
                                {  $$ = single_Cases($1);  }
                        | case_list_pos case_single ';'
                                {  $$ = append_Cases($1, single_Cases($2));  }
                ;
case_single             : OBJECTID ':' TYPEID DARROW expression_single 
                                {  $$ = branch($1, $3, $5);  }
                ;


/* every time there is a nonterminal-reduce match, it will indicate the line number, 
   that is the reason we want to the no-ini/'empty' to be in a seperate nonterminal expand, if that, 
   when there is a no-ini/'empty', it will also force a reduce once it match no-ini/'empty',  
   rather than scan the entire let_expand or let_begin, then the line number is correct */
let_no_expr_helper      : /* empty */ 
                                {  $$ = no_expr();  }
                        | ASSIGN expression_single 
                                {  $$ = $2;  }
                ;
/* purpose of prec_let_expand is to eliminate the shift/reduce conflict, it will prefer choosing the ontinueing scan
   expression_single, in order to make a larger expression_single through + - * /, etc. */ 
let_expand              : IN expression_single %prec prec_let_expand
                                {  $$ = $2;  }
                        | ',' OBJECTID ':' TYPEID let_no_expr_helper let_expand  
                                {  $$ = let($2, $4, $5,  $6);  }
                        | ',' error let_expand
                                {   }
                        
                ;
let_begin               : LET OBJECTID ':' TYPEID let_no_expr_helper  let_expand 
                                {  $$ = let($2, $4, $5, $6);  }
                        | LET error let_expand
                                {  }   
                ; 
                   
for_second              : ';' expression_single ';' expression_single ')' '{' expression_single '}' 
                                {  $$ = loop($2, block(append_Expressions(single_Expressions($7), single_Expressions($4))));  }
                ;
for_expand              : for_second 
                                {  $$ = $1;  }
                        | ',' OBJECTID ':' TYPEID for_expand 
                                {  $$ = let($2, $4, no_expr(), $5);  }
                        | ',' OBJECTID ':' TYPEID ASSIGN expression_single for_expand
                                {  $$ = let($2, $4, $6, $7);  }
                ;
for_begin               : FOR '(' OBJECTID ':' TYPEID for_expand  
                                {  $$ = let($3, $5, no_expr(), $6);  }         
                        | FOR '(' OBJECTID ':' TYPEID ASSIGN expression_single for_expand
                                {  $$ = let($3, $5, $7, $8);  }
                ;



expression_list_star    : /* empty */
                                {  $$ = nil_Expressions();  }
                        | expression_list_star ',' expression_single
                                {  $$ = append_Expressions($1, single_Expressions($3));  }
                ;
/* error will be popped to the higher level, that is, expression_single */
expression_list_pos     : expression_single ';'
                                {  $$ = single_Expressions($1);  }
                        | expression_list_pos expression_single ';'
                                {  $$ = append_Expressions($1, single_Expressions($2));  }
                        | expression_list_pos error ';'
                                {  yyclearin;  }
                        | error ';'                 /* support the situation that error could be appear at the beginning of the block, {erro, normal, normal ...} */
                                {  yyclearin;  }
                ;

expression_single       : OBJECTID ASSIGN expression_single
                                {  $$ = assign($1, $3);  }
                        | expression_single '.' OBJECTID '('  ')'
                                {  $$ = dispatch($1, $3, nil_Expressions());  }
                        | expression_single '.' OBJECTID '(' expression_single  expression_list_star ')'
                                {  $$ = dispatch($1, $3, append_Expressions(single_Expressions($5), $6));  }
                        | expression_single '@' TYPEID '.' OBJECTID '('  ')'
                                {  $$ = static_dispatch($1, $3, $5, nil_Expressions());  }
                        | expression_single '@' TYPEID '.' OBJECTID '(' expression_single  expression_list_star ')'
                                {  $$ = static_dispatch($1, $3, $5, append_Expressions(single_Expressions($7), $8));  }
                        | OBJECTID '(' ')'
                                {  $$ = dispatch(object(idtable.add_string("self")), $1, nil_Expressions());  }
                        | OBJECTID '(' expression_single  expression_list_star ')'
                                {  $$ = dispatch(object(idtable.add_string("self")), $1, append_Expressions(single_Expressions($3), $4));  }                       
                        | IF expression_single THEN expression_single ELSE expression_single FI 
                                {  $$ = cond($2, $4, $6);  }
                        | WHILE expression_single LOOP expression_single POOL
                                {  $$ = loop($2, $4);  }
                        | '{' expression_list_pos '}' 
                                {  $$ = block($2);  }
                        | let_begin
                                {  $$ = $1; }
                        | for_begin
                                {  $$ = $1; }
                        | CASE expression_single OF case_list_pos ESAC 
                                {  $$ = typcase($2, $4);  }
                        | NEW TYPEID
                                {  $$ = new_($2);  }
                        | ISVOID expression_single
                                {  $$ = isvoid($2);  }
                        | expression_single '+' expression_single 
                                {  $$ = plus($1, $3);  }
                        | expression_single '-' expression_single
                                {  $$ = sub($1, $3);  }
                        | expression_single '*' expression_single
                                {  $$ = mul($1, $3);  }
                        | expression_single '/' expression_single
                                {  $$ = divide($1, $3);  }
                        | '~' expression_single 
                                {  $$ = neg($2);  }
                        | expression_single '<' expression_single 
                                {  $$ = lt($1, $3);  }
                        | expression_single LE expression_single 
                                {  $$ = leq($1, $3);  }
                        | expression_single '=' expression_single 
                                {  $$ = eq($1, $3);  }
                        | NOT expression_single 
                                {  $$ = comp($2);  }
                        | '(' expression_single ')'
                                {  $$ = $2;  }
                        | OBJECTID
                                {  $$ = object($1);  }
                        | INT_CONST
                                {  $$ = int_const($1);  }
                        | STR_CONST
                                {  $$ = string_const($1);  }
                        | BOOL_CONST
                                {  $$ = bool_const($1);  }
                        | '{' error '}'
                                {  yyclearin;  }
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