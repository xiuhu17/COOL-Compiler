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
/*
 *  Add Your own definitions here
 */

#define MAX_STR_LEN 1024
%}

%option noyywrap
%x single_string
%x triple_string
%x open_comment
%x dash_comment


/*
 * Define names for regular expressions here.
 */

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

  char string_buf[MAX_STR_LEN + 1]
  int string_buf_idx = 0;
  int comment_open_cnt = 0;


  [cC][lL][aA][sS][sS]                {return CLASS;}
  [eE][lL][sS][eE]                    {return ELSE;}
  [fF][iI]                            {return FI;}
  [iI][fF]                            {return IF;}
  [iI][nN]                            {return IN;}
  [iI][nN][hH][eE][rR][iI][tT][sS]    {return INHERITS;}
  [iI][sS][vV][oO][iI][dD]            {return ISVOID;}
  [lL][eE][tT]                        {return LET;}
  [lL][oO][oO][pP]                    {return LOOP;}
  [pP][oO][oO][lL]                    {return POOL;}
  [tT][hH][eE][nN]                    {return THEN;}
  [wW][hH][iI][lL][eE]                {return WHILE;}
  [cC][aA][sS][eE]                    {return CASE;}
  [eE][sS][aA][cC]                    {return ESAC;}
  [nN][eE][wW]                        {return NEW;}
  [oO][fF]                            {return OF;}
  [nN][oO][tT]                        {return NOT;}
  [fF][oO][rR]                        {return FOR;}
  <-                                  {return ASSIGN;}
  =>                                  {return DARROW;}


  false                               {cool_yylval.boolean = false; return BOOL_CONST;}
  true                                {cool_yylval.boolean = true; return BOOL_CONST;}


  [+/-*=<.~,;:()@{}]                  {return *yytext;}


  [0-9]+                              {Symbol symb = inttable.add_string(yytext); cool_yylval.symbol = symb; return INT_CONST;}
  0x[0-9]+                            {string store_hex = yytext; string store_dec = hex2dec(store_hex); Symbol symb = inttable.add_int(std::stoi(store_dec)); cool_yylval.symbol = symb; return INT_CONST;}
  [A-Z][a-zA-Z0-9_]*                  {Symbol symb = idtable.add_string(yytext); cool_yylval.symbol = symb; return TYPEID;}
  SELF | SELF_TYPE                    {Symbol symb = idtable.add_string(yytext); cool_yylval.symbol = symb; return TYPEID;}
  [a-z][a-zA-Z0-9_]*                  {Symbol symb = idtable.add_string(yytext); cool_yylval.symbol = symb; return OBJECTID;}


  [ \f\r\t\v]+                        {}
  [\n]                                {curr_lineno ++;}  


  "                                   {memset(string_buf, 0, 1024 + 1); string_buf_idx = 0; BEGIN(single_string);}
  <single_string>\"                   {string_buf[string_buf_idx] = '\0'; Symbol symb = stringtable.add_string(string_buf); cool_yylval.symbol = symb; BEGIN(INITIAL); return STR_CONST;}
  <single_string>[\\][btnf"]          {
                                        if (string_buf_idx < 1024 - 1) {
                                          string_buf[string_buf_idx] = '\\'; 
                                          string_buf[string_buf_idx + 1] = *(yytext  + 1);
                                          string_buf_idx += 2;
                                        } else {
                                          char *errom = "String constant too long";
                                          cool_yylval.error_msg = errom; 
                                          BEGIN(INITIAL);
                                          return ERROR;
                                        }
                                      }
  <single_string>[\\][.]              {
                                        if (string_buf_idx < 1024) {
                                          string_buf[string_buf_idx] = *(yytext);
                                          string_buf_idx += 1;
                                        } else {
                                          char *errom = "String constant too long";
                                          cool_yylval.error_msg = errom; 
                                          BEGIN(INITIAL);
                                          return ERROR;
                                        }
                                      }
  <single_string>[^\\\n\"]+           {
                                        char *iter = yytext;
                                        while (iter && *iter) {
                                          if (string_buf_idx < 1024) {
                                            string_buf[string_buf_idx] = *iter;
                                            iter ++;
                                            string_buf_idx ++;
                                          } else {
                                            char *errom = "String constant too long";
                                            cool_yylval.error_msg = errom; 
                                            BEGIN(INITIAL);
                                            return ERROR;
                                          }
                                        }
                                        if ((char next = input()) == '\0') {
                                          char *errom = "String contains null character.";
                                          cool_yylval.error_msg = errom; 
                                          BEGIN(INITIAL);
                                          return ERROR;
                                        }
                                      } 
  <single_string><<EOF>>              {char *errom = "Unterminated string constant"; cool_yylval.error_msg = errom; BEGIN(INITIAL); return ERROR;}
  <single_string>\n                   {char *errom = "Unterminated string constant"; cool_yylval.error_msg = errom; BEGIN(INITIAL); return ERROR;}



  """                                 {string_buf_ptr = string_buf; BEGIN(triple_string);}    



  <<EOF>>                             {BEGIN(INITIAL); return EOF;}

%%
