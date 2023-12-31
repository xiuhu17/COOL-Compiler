/*
 *  The scanner definition for COOL.
 */

/*
 *  Stuff enclosed in %{ %} in the first section is copied verbatim to the
 *  output, so headers and global definitions are placed here to be visible
 * to the code in the file.  Don't remove anything that was here initially
 */
%{
#include <cool-parse.h>
#include <stringtab.h>
#include <utilities.h>
#define MAX_STR_LEN 1024



/* define YY_INPUT so we read from the FILE fin:
 * This change makes it possible to use this scanner in
 * the Cool compiler.
 */
extern FILE *fin; /* we read from this file */
#undef YY_INPUT
#define YY_INPUT(buf, result, max_size)                                        \
  if ((result = fread((char *)buf, sizeof(char), max_size, fin)) < 0)          \
    YY_FATAL_ERROR("read() in flex scanner failed");

extern int curr_lineno;
char string_buf[MAX_STR_LEN + 1];
int string_buf_idx = 0;
int open_comment_cnt = 0;
int str_escaped_helper(char input, char match);
%}


%option noyywrap
%x single_string
%x single_string_null
%x single_string_long
%x triple_string
%x triple_string_null
%x triple_string_long
%x comment
%x dash_comment

digit                       [0-9]
CLASS_                      [cC][lL][aA][sS][sS]                
ELSE_                       [eE][lL][sS][eE]                    
FI_                         [fF][iI]                            
IF_                         [iI][fF]                            
IN_                         [iI][nN]                            
INHERITS_                   [iI][nN][hH][eE][rR][iI][tT][sS]    
ISVOID_                     [iI][sS][vV][oO][iI][dD]            
LET_                        [lL][eE][tT]                        
LOOP_                       [lL][oO][oO][pP]                    
POOL_                       [pP][oO][oO][lL]                    
THEN_                       [tT][hH][eE][nN]                    
WHILE_                      [wW][hH][iI][lL][eE]                
CASE_                       [cC][aA][sS][eE]                    
ESAC_                       [eE][sS][aA][cC]                    
NEW_                        [nN][eE][wW]                        
OF_                         [oO][fF]                            
NOT_                        [nN][oO][tT]                        
FOR_                        [fF][oO][rR]
OPERATOR_                   [+/-*=<.~,;:()@{}]

DEC_INT_                    [0-9]+
DEC_INT_ERROR_              [0-9]+[a-zA-Z_][0-9a-zA-Z_]*
HEX_INT_                    [0][x][0-9abcdef]+
HEX_INT_ERROR_              [0][x][0-9abcdef]+[g-zA-Z_][0-9a-zA-Z_]*


TYPEID_                     [A-Z][a-zA-Z0-9_]*
OBJECTID_                   [a-z][a-zA-Z0-9_]* 
BLANK_                      [ \f\r\t\v]+
NEW_LINE_                   [\n]
NULL_                       [\0]
SINGLE_STR_ESCAPED_         [\\][btnf\"]
SINGLE_STR_N_ESCAPED_       [\\][^btnf\"]
SINGLE_STR_NORMAL_          [^\\\n\"\0]+  

TRIPLE_STR_ESCAPED_         [\\][btnf\"]
TRIPLE_STR_N_ESCAPED_       [\\][^btnf\"]
TRIPLE_STR_NORMAL_          [^\\\n\"\0]+ 

COMMENT_L_                  [(][*]
COMMENT_R_                  [*][)]
DASH_COMMENT_               [-][-]

%%

 /*
  * Define regular expressions for the tokens of COOL here. Make sure, you
  * handle correctly special cases, like:
  *   - Nested comments
  *   - String constants: They use C like systax and can contain escape
  *     sequences. Escape sequence \c is accepted for all characters c. Except
  *     for \n \t \b \f, the result is c.
  *   - Keywords: They are case-insensitive except for the values true and
  *     false, which must begin with a lower-case letter.
  *   - Multiple-character operators (like <-): The scanner should produce a
  *     single token for every such operator.
  *   - Line counting: You should keep the global variable curr_lineno updated
  *     with the correct line number
  */
   
{CLASS_}                          {return CLASS;}
{ELSE_}                           {return ELSE;}
{FI_}                             {return FI;}
{IF_}                             {return IF;}
{IN_}                             {return IN;}
{INHERITS_}                       {return INHERITS;}
{ISVOID_}                         {return ISVOID;}
{LET_}                            {return LET;}
{LOOP_}                           {return LOOP;}
{POOL_}                           {return POOL;}
{THEN_}                           {return THEN;}
{WHILE_}                          {return WHILE;}
{CASE_}                           {return CASE;}
{ESAC_}                           {return ESAC;}
{NEW_}                            {return NEW;}
{OF_}                             {return OF;}
{NOT_}                            {return NOT;}
{FOR_}                            {return FOR;}
"<-"                              {return ASSIGN;}
"=>"                              {return DARROW;}
"<="                              {return LE;}


"false"                           {cool_yylval.boolean = false; return BOOL_CONST;}
"true"                            {cool_yylval.boolean = true; return BOOL_CONST;}

"+"                               {return '+';}
"/"                               {return '/';}
"-"                               {return '-';}
"*"                               {return '*';}
"="                               {return '=';}
"<"                               {return '<';}
"."                               {return '.';}
"~"                               {return '~';}
","                               {return ',';}
";"                               {return ';';}
":"                               {return ':';}
"("                               {return '(';}
")"                               {return ')';}    
"@"                               {return '@';}
"{"                               {return '{';}
"}"                               {return '}';}
 

"SELF_TYPE"                       {Symbol symb = idtable.add_string(yytext); cool_yylval.symbol = symb; return TYPEID;}
"self"                            {Symbol symb = idtable.add_string(yytext); cool_yylval.symbol = symb; return OBJECTID;}

{DEC_INT_}                        {Symbol symb = inttable.add_string(yytext); cool_yylval.symbol = symb; return INT_CONST;}
{HEX_INT_}                        {std::string store_hex = yytext; std::string store_dec = hex2dec(store_hex); Symbol symb = inttable.add_int(std::stoi(store_dec)); cool_yylval.symbol = symb; return INT_CONST;}

{DEC_INT_ERROR_}                  {const char *errom = "Invalid integer constant"; cool_yylval.error_msg = errom; BEGIN(INITIAL); return ERROR;}
{HEX_INT_ERROR_}                  {const char *errom = "Invalid integer constant"; cool_yylval.error_msg = errom; BEGIN(INITIAL); return ERROR;}




{TYPEID_}                         {Symbol symb = idtable.add_string(yytext); cool_yylval.symbol = symb; return TYPEID;}
{OBJECTID_}                       {Symbol symb = idtable.add_string(yytext); cool_yylval.symbol = symb; return OBJECTID;}

{BLANK_}                          {}
{NEW_LINE_}                       {curr_lineno ++;}

\"                                    {memset(string_buf, 0, 1024 + 1); string_buf_idx = 0; BEGIN(single_string);}
<single_string>\"                     {string_buf[string_buf_idx] = '\0'; Symbol symb = stringtable.add_string(string_buf); cool_yylval.symbol = symb; BEGIN(INITIAL); return STR_CONST;}

<single_string>[\\]*\\b                    {int erron = str_escaped_helper('\b', 'b'); if (erron < 0) {BEGIN(single_string_long);}}
<single_string>[\\]*\\t                    {int erron = str_escaped_helper('\t', 't'); if (erron < 0) {BEGIN(single_string_long);}}
<single_string>[\\]*\\n                    {int erron = str_escaped_helper('\n', 'n'); if (erron < 0) {BEGIN(single_string_long);}}
<single_string>[\\]*\\f                    {int erron = str_escaped_helper('\f', 'f'); if (erron < 0) {BEGIN(single_string_long);}}
<single_string>\\["]                       {int erron = str_escaped_helper('\"', '\0'); if (erron < 0) {BEGIN(single_string_long);}}
<single_string>{SINGLE_STR_N_ESCAPED_}  { 
                                          if (string_buf_idx < 1024) {
                                            string_buf[string_buf_idx] = *(yytext + 1);
                                            string_buf_idx += 1;
                                          } else {
                                            BEGIN(single_string_long);
                                          }
                                        }
<single_string>{SINGLE_STR_NORMAL_}   { 
                                        char *iter = yytext;
                                        while (iter && *iter) {
                                          if (string_buf_idx < 1024) {
                                            string_buf[string_buf_idx] = *iter;
                                            iter ++;
                                            string_buf_idx ++;
                                          } else {
                                            BEGIN(single_string_long);
                                            break;
                                          }
                                        }
                                      } 
<single_string>{NEW_LINE_}            {curr_lineno ++; const char *errom = "Unterminated string constant"; cool_yylval.error_msg = errom; BEGIN(INITIAL); return ERROR;}
<single_string><<EOF>>                {const char *errom = "EOF in string constant"; cool_yylval.error_msg = errom; BEGIN(INITIAL); return ERROR;}
<single_string>{NULL_}                {BEGIN(single_string_null);}


<single_string_null>{NEW_LINE_}       {curr_lineno ++; const char *errom = "Unterminated string constant"; cool_yylval.error_msg = errom; BEGIN(INITIAL); return ERROR;}
<single_string_long>{NEW_LINE_}       {curr_lineno ++; const char *errom = "Unterminated string constant"; cool_yylval.error_msg = errom; BEGIN(INITIAL); return ERROR;}

<single_string_null><<EOF>>           {const char *errom = "EOF in string constant"; cool_yylval.error_msg = errom; BEGIN(INITIAL); return ERROR;}
<single_string_long><<EOF>>           {const char *errom = "EOF in string constant"; cool_yylval.error_msg = errom; BEGIN(INITIAL); return ERROR;}

<single_string_null>\"                {const char *errom = "String contains null character."; cool_yylval.error_msg = errom; BEGIN(INITIAL); return ERROR;}
<single_string_long>\"                {const char *errom = "String constant too long"; cool_yylval.error_msg = errom; BEGIN(INITIAL); return ERROR;}

<single_string_null>.
<single_string_long>.

\"\"\"                                    {memset(string_buf, 0, 1024 + 1); string_buf_idx = 0; BEGIN(triple_string);}
<triple_string>\"\"\"                     {string_buf[string_buf_idx] = '\0'; Symbol symb = stringtable.add_string(string_buf); cool_yylval.symbol = symb; BEGIN(INITIAL); return STR_CONST;}

<triple_string>[\\]*\\b                    {int erron = str_escaped_helper('\b', 'b'); if (erron < 0) {BEGIN(triple_string_long);}}
<triple_string>[\\]*\\t                    {int erron = str_escaped_helper('\t', 't'); if (erron < 0) {BEGIN(triple_string_long);}}
<triple_string>[\\]*\\n                    {int erron = str_escaped_helper('\n', 'n'); if (erron < 0) {BEGIN(triple_string_long);}}
<triple_string>[\\]*\\f                    {int erron = str_escaped_helper('\f', 'f'); if (erron < 0) {BEGIN(triple_string_long);}}
<triple_string>\\["]                       {int erron = str_escaped_helper('\"', '\0'); if (erron < 0) {BEGIN(triple_string_long);}}
<triple_string>{TRIPLE_STR_N_ESCAPED_}  {
                                          if (string_buf_idx < 1024) {
                                            string_buf[string_buf_idx] = *(yytext + 1);
                                            string_buf_idx += 1;
                                          } else {
                                            BEGIN(triple_string_long);
                                          }
                                        }

<triple_string>{TRIPLE_STR_NORMAL_}   { 
                                        char *iter = yytext;
                                        while (iter && *iter) {
                                          if (string_buf_idx < 1024) {
                                            string_buf[string_buf_idx] = *iter;
                                            iter ++;
                                            string_buf_idx ++;
                                          } else {
                                            BEGIN(triple_string_long);
                                            break;
                                          }
                                        }
                                      }
<triple_string>\"                     { if (string_buf_idx < 1024) {
                                            string_buf[string_buf_idx] = '\"';
                                            string_buf_idx += 1;
                                          } else {
                                            BEGIN(triple_string_long);
                                        }
                                      }                                  
<triple_string>{NEW_LINE_}            { 
                                        curr_lineno ++; 
                                        if (string_buf_idx < 1024) {
                                            string_buf[string_buf_idx] = '\n';
                                            string_buf_idx += 1;
                                          } else {
                                            BEGIN(triple_string_long);
                                        }
                                      }
<triple_string><<EOF>>                {const char *errom = "EOF in string constant"; cool_yylval.error_msg = errom; BEGIN(INITIAL); return ERROR;}
<triple_string>{NULL_}                {BEGIN(triple_string_null);}

<triple_string_null>{NEW_LINE_}       {curr_lineno ++;}
<triple_string_long>{NEW_LINE_}       {curr_lineno ++;}

<triple_string_null><<EOF>>           {const char *errom = "EOF in string constant"; cool_yylval.error_msg = errom; BEGIN(INITIAL); return ERROR;}
<triple_string_long><<EOF>>           {const char *errom = "EOF in string constant"; cool_yylval.error_msg = errom; BEGIN(INITIAL); return ERROR;}

<triple_string_null>\"\"\"            {const char *errom = "String contains null character."; cool_yylval.error_msg = errom; BEGIN(INITIAL); return ERROR;}
<triple_string_long>\"\"\"            {const char *errom = "String constant too long"; cool_yylval.error_msg = errom; BEGIN(INITIAL); return ERROR;}

<triple_string_null>.
<triple_string_long>.


{COMMENT_L_}                            {open_comment_cnt ++; BEGIN(comment);}
<comment>{COMMENT_L_}                   {open_comment_cnt ++;}
<comment>{COMMENT_R_}                   {open_comment_cnt --; if (open_comment_cnt == 0) {BEGIN(INITIAL);}}
<comment>\n                             {curr_lineno ++;}
<comment><<EOF>>                        {const char* errom = "EOF in comment"; cool_yylval.error_msg = errom; BEGIN(INITIAL); return ERROR;}
<comment>.                              {}
{COMMENT_R_}                            {const char* errom = "Unmatched *)"; cool_yylval.error_msg = errom; BEGIN(INITIAL); return ERROR;}

{DASH_COMMENT_}                         {BEGIN(dash_comment);}  
<dash_comment>\n                        {curr_lineno ++; BEGIN(INITIAL);}
<dash_comment><<EOF>>                   {return 0;}
<dash_comment>.                         {}


<<EOF>> {return 0;}
.       {const char *errom = yytext; cool_yylval.error_msg = errom; BEGIN(INITIAL); return ERROR;}
%%


int str_escaped_helper(char input, char match) {
  int extra = 0;
  if (match != '\0'){
    extra += (strlen(yytext) - 2) / 2;
  }
  if (string_buf_idx + extra < 1024) {
    for (int i = 0; i < extra; ++ i) {
      string_buf[string_buf_idx] = '\\';
      string_buf_idx ++;
    }
    string_buf[string_buf_idx] = input;
    string_buf_idx ++;
  } else {
    return -1;
  }
  return 0;
}