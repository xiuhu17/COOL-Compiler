/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         cool_yyparse
#define yylex           cool_yylex
#define yyerror         cool_yyerror
#define yydebug         cool_yydebug
#define yynerrs         cool_yynerrs
#define yylval          cool_yylval
#define yychar          cool_yychar

/* First part of user prologue.  */
#line 6 "cool.y"

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


#line 121 "cool.y.cc"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "cool.y.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_CLASS = 3,                      /* CLASS  */
  YYSYMBOL_ELSE = 4,                       /* ELSE  */
  YYSYMBOL_FI = 5,                         /* FI  */
  YYSYMBOL_IF = 6,                         /* IF  */
  YYSYMBOL_IN = 7,                         /* IN  */
  YYSYMBOL_INHERITS = 8,                   /* INHERITS  */
  YYSYMBOL_LET = 9,                        /* LET  */
  YYSYMBOL_LOOP = 10,                      /* LOOP  */
  YYSYMBOL_POOL = 11,                      /* POOL  */
  YYSYMBOL_THEN = 12,                      /* THEN  */
  YYSYMBOL_WHILE = 13,                     /* WHILE  */
  YYSYMBOL_CASE = 14,                      /* CASE  */
  YYSYMBOL_ESAC = 15,                      /* ESAC  */
  YYSYMBOL_OF = 16,                        /* OF  */
  YYSYMBOL_DARROW = 17,                    /* DARROW  */
  YYSYMBOL_NEW = 18,                       /* NEW  */
  YYSYMBOL_ISVOID = 19,                    /* ISVOID  */
  YYSYMBOL_STR_CONST = 20,                 /* STR_CONST  */
  YYSYMBOL_INT_CONST = 21,                 /* INT_CONST  */
  YYSYMBOL_BOOL_CONST = 22,                /* BOOL_CONST  */
  YYSYMBOL_TYPEID = 23,                    /* TYPEID  */
  YYSYMBOL_OBJECTID = 24,                  /* OBJECTID  */
  YYSYMBOL_ASSIGN = 25,                    /* ASSIGN  */
  YYSYMBOL_NOT = 26,                       /* NOT  */
  YYSYMBOL_LE = 27,                        /* LE  */
  YYSYMBOL_FOR = 28,                       /* FOR  */
  YYSYMBOL_ERROR = 29,                     /* ERROR  */
  YYSYMBOL_prec_let_expand = 30,           /* prec_let_expand  */
  YYSYMBOL_31_ = 31,                       /* '<'  */
  YYSYMBOL_32_ = 32,                       /* '='  */
  YYSYMBOL_33_ = 33,                       /* '+'  */
  YYSYMBOL_34_ = 34,                       /* '-'  */
  YYSYMBOL_35_ = 35,                       /* '*'  */
  YYSYMBOL_36_ = 36,                       /* '/'  */
  YYSYMBOL_37_ = 37,                       /* '~'  */
  YYSYMBOL_38_ = 38,                       /* '@'  */
  YYSYMBOL_39_ = 39,                       /* '.'  */
  YYSYMBOL_40_ = 40,                       /* '{'  */
  YYSYMBOL_41_ = 41,                       /* '}'  */
  YYSYMBOL_42_ = 42,                       /* ';'  */
  YYSYMBOL_43_ = 43,                       /* '('  */
  YYSYMBOL_44_ = 44,                       /* ')'  */
  YYSYMBOL_45_ = 45,                       /* ':'  */
  YYSYMBOL_46_ = 46,                       /* ','  */
  YYSYMBOL_YYACCEPT = 47,                  /* $accept  */
  YYSYMBOL_program = 48,                   /* program  */
  YYSYMBOL_class_list = 49,                /* class_list  */
  YYSYMBOL_class = 50,                     /* class  */
  YYSYMBOL_feature_list_star = 51,         /* feature_list_star  */
  YYSYMBOL_feature_single = 52,            /* feature_single  */
  YYSYMBOL_formal_list_star = 53,          /* formal_list_star  */
  YYSYMBOL_formal_single = 54,             /* formal_single  */
  YYSYMBOL_case_list_pos = 55,             /* case_list_pos  */
  YYSYMBOL_case_single = 56,               /* case_single  */
  YYSYMBOL_let_expand = 57,                /* let_expand  */
  YYSYMBOL_let_begin = 58,                 /* let_begin  */
  YYSYMBOL_for_second = 59,                /* for_second  */
  YYSYMBOL_for_expand = 60,                /* for_expand  */
  YYSYMBOL_for_begin = 61,                 /* for_begin  */
  YYSYMBOL_expression_list_star = 62,      /* expression_list_star  */
  YYSYMBOL_expression_list_pos = 63,       /* expression_list_pos  */
  YYSYMBOL_expression_single = 64          /* expression_single  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   486

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  18
/* YYNRULES -- Number of rules.  */
#define YYNRULES  62
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  178

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   286


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      43,    44,    35,    33,    46,    34,    39,    36,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    45,    42,
      31,    32,     2,     2,    38,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    40,     2,    41,    37,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,     2,    30
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   140,   140,   144,   146,   151,   153,   159,   160,   163,
     165,   167,   169,   175,   176,   179,   184,   186,   189,   194,
     196,   198,   201,   203,   208,   211,   213,   215,   218,   220,
     227,   228,   231,   233,   237,   239,   241,   243,   245,   247,
     249,   251,   253,   255,   257,   259,   261,   263,   265,   267,
     269,   271,   273,   275,   277,   279,   281,   283,   285,   287,
     289,   291,   293
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "CLASS", "ELSE", "FI",
  "IF", "IN", "INHERITS", "LET", "LOOP", "POOL", "THEN", "WHILE", "CASE",
  "ESAC", "OF", "DARROW", "NEW", "ISVOID", "STR_CONST", "INT_CONST",
  "BOOL_CONST", "TYPEID", "OBJECTID", "ASSIGN", "NOT", "LE", "FOR",
  "ERROR", "prec_let_expand", "'<'", "'='", "'+'", "'-'", "'*'", "'/'",
  "'~'", "'@'", "'.'", "'{'", "'}'", "';'", "'('", "')'", "':'", "','",
  "$accept", "program", "class_list", "class", "feature_list_star",
  "feature_single", "formal_list_star", "formal_single", "case_list_pos",
  "case_single", "let_expand", "let_begin", "for_second", "for_expand",
  "for_begin", "expression_list_star", "expression_list_pos",
  "expression_single", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-135)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       6,    -2,    44,     6,  -135,    21,  -135,  -135,    32,  -135,
      19,   -17,  -135,    17,    24,    42,    34,   -13,    57,  -135,
    -135,    46,    54,    76,  -135,    84,  -135,    99,   100,    41,
     252,  -135,    86,    79,   103,   252,   106,   252,   252,   108,
     252,  -135,  -135,  -135,   -10,   252,    90,   252,   252,   252,
    -135,  -135,   437,   252,   111,  -135,   295,    94,   267,   305,
    -135,    64,   252,   123,   437,   116,    64,   219,   359,   331,
     252,   252,   252,   252,   252,   252,   252,   125,   122,   398,
     110,   252,   129,   252,   130,   437,  -135,   437,   112,  -135,
     372,  -135,  -135,   447,   447,   447,   -19,   -19,    64,    64,
     114,   113,  -135,   252,    38,    -3,   277,   117,    89,   128,
      70,   132,  -135,   134,   155,   411,   252,   252,   252,   135,
    -135,  -135,   142,  -135,   136,  -135,  -135,   252,    65,   137,
    -135,   437,  -135,    62,   437,    18,   126,   165,  -135,   437,
     252,   252,   148,  -135,  -135,   187,    73,  -135,  -135,   161,
     252,   315,   385,   140,  -135,   437,  -135,     1,   437,  -135,
     252,   163,    74,   252,  -135,   345,    66,  -135,    18,   147,
     252,  -135,  -135,   252,   315,   424,  -135,  -135
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     2,     3,     0,     1,     4,     0,     7,
       0,     0,     7,     0,     0,     0,     0,     0,     0,     5,
       8,     0,     0,     0,    13,    11,     6,     0,     0,     0,
       0,    15,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    61,    60,    62,    59,     0,     0,     0,     0,     0,
      44,    45,    12,     0,     0,    14,     0,     0,     0,     0,
      47,    48,     0,     0,    57,     0,    53,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    34,    39,    30,     0,    43,
       0,    32,    58,    55,    54,    56,    49,    50,    51,    52,
       0,     0,     9,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    33,     0,     0,     0,     0,     0,     0,     0,
      22,    42,     0,    46,     0,    16,    40,     0,     0,     0,
      35,    30,    10,     0,    19,     0,     0,     0,    17,    31,
       0,     0,     0,    25,    28,     0,     0,    41,    23,     0,
       0,     0,     0,     0,    37,    30,    36,     0,    18,    29,
       0,     0,     0,     0,    20,     0,     0,    38,     0,     0,
       0,    26,    21,     0,     0,     0,    27,    24
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -135,  -135,  -135,   185,   177,  -135,  -135,   156,  -135,    83,
    -134,  -135,  -135,   -88,  -135,  -125,  -135,   -35
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     3,     4,    11,    15,    29,    24,   108,   109,
     120,    50,   143,   144,    51,   110,    67,    52
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      56,   148,    58,    59,   117,    61,   146,    13,   117,     1,
      64,    22,    66,    68,    69,    62,    75,    76,    79,    77,
      78,     5,   118,   164,    14,   117,   163,    85,    87,     8,
     162,    23,    90,    63,   172,    93,    94,    95,    96,    97,
      98,    99,   116,   119,     6,    70,   104,   119,   106,    71,
      72,    73,    74,    75,    76,    10,    77,    78,    13,    12,
      17,     9,    18,   159,   119,    70,    19,   147,   115,    71,
      72,    73,    74,    75,    76,    21,    77,    78,   171,   131,
      25,   133,   134,   135,    20,    33,   176,    34,    26,    70,
     140,   170,   139,    71,    72,    73,    74,    75,    76,    27,
      77,    78,    77,    78,   123,   151,   152,   141,   141,    30,
     155,   142,   142,   107,   126,   158,   127,   156,   167,   127,
     127,    28,    31,    32,    54,   165,    53,    22,   168,    35,
      57,    60,    36,    65,    80,   174,    37,    38,   175,    82,
      88,    39,    40,    41,    42,    43,   101,    44,   100,    45,
     103,    46,   105,   113,   107,   128,   114,   111,   129,   136,
      47,    35,   122,    48,    36,   137,    49,    86,    37,    38,
     125,   149,   153,    39,    40,    41,    42,    43,   138,    44,
     145,    45,   150,    46,   157,   161,   166,   173,     7,    16,
      55,   124,    47,    35,     0,    48,    36,     0,    49,   130,
      37,    38,     0,     0,     0,    39,    40,    41,    42,    43,
       0,    44,     0,    45,     0,    46,     0,     0,     0,     0,
       0,     0,     0,     0,    47,    35,     0,    48,    36,     0,
      49,   154,    37,    38,     0,     0,     0,    39,    40,    41,
      42,    43,     0,    44,     0,    45,     0,    46,     0,     0,
       0,     0,     0,     0,     0,     0,    47,     0,    35,    48,
      89,    36,    49,     0,     0,    37,    38,     0,     0,     0,
      39,    40,    41,    42,    43,     0,    44,    83,    45,     0,
      46,     0,     0,     0,     0,     0,     0,     0,   121,    47,
       0,     0,    48,     0,    70,    49,     0,     0,    71,    72,
      73,    74,    75,    76,    70,    77,    78,    81,    71,    72,
      73,    74,    75,    76,     0,    77,    78,     0,     0,     0,
       0,    84,    70,     0,     0,     0,    71,    72,    73,    74,
      75,    76,    70,    77,    78,     0,    71,    72,    73,    74,
      75,    76,    70,    77,    78,     0,    71,    72,    73,    74,
      75,    76,     0,    77,    78,     0,     0,   141,    70,     0,
       0,   142,    71,    72,    73,    74,    75,    76,     0,    77,
      78,     0,    70,     0,     0,    92,    71,    72,    73,    74,
      75,    76,     0,    77,    78,     0,    70,     0,     0,   169,
      71,    72,    73,    74,    75,    76,     0,    77,    78,    70,
       0,    91,     0,    71,    72,    73,    74,    75,    76,     0,
      77,    78,    70,     0,   112,     0,    71,    72,    73,    74,
      75,    76,     0,    77,    78,    70,     0,   160,     0,    71,
      72,    73,    74,    75,    76,     0,    77,    78,    70,   102,
       0,     0,    71,    72,    73,    74,    75,    76,     0,    77,
      78,    70,   132,     0,     0,    71,    72,    73,    74,    75,
      76,     0,    77,    78,    70,   177,     0,     0,    71,    72,
      73,    74,    75,    76,    -1,    77,    78,     0,    -1,    -1,
      73,    74,    75,    76,     0,    77,    78
};

static const yytype_int16 yycheck[] =
{
      35,   135,    37,    38,     7,    40,   131,    24,     7,     3,
      45,    24,    47,    48,    49,    25,    35,    36,    53,    38,
      39,    23,    25,   157,    41,     7,    25,    62,    63,     8,
     155,    44,    67,    43,   168,    70,    71,    72,    73,    74,
      75,    76,     4,    46,     0,    27,    81,    46,    83,    31,
      32,    33,    34,    35,    36,    23,    38,    39,    24,    40,
      43,    40,    45,   151,    46,    27,    42,     5,   103,    31,
      32,    33,    34,    35,    36,    41,    38,    39,   166,   114,
      23,   116,   117,   118,    42,    44,   174,    46,    42,    27,
      25,    25,   127,    31,    32,    33,    34,    35,    36,    45,
      38,    39,    38,    39,    15,   140,   141,    42,    42,    25,
     145,    46,    46,    24,    44,   150,    46,    44,    44,    46,
      46,    45,    23,    23,    45,   160,    40,    24,   163,     6,
      24,    23,     9,    43,    23,   170,    13,    14,   173,    45,
      24,    18,    19,    20,    21,    22,    24,    24,    23,    26,
      40,    28,    23,    39,    24,    23,    43,    45,    24,    24,
      37,     6,    45,    40,     9,    23,    43,    44,    13,    14,
      42,    45,    24,    18,    19,    20,    21,    22,    42,    24,
      43,    26,    17,    28,    23,    45,    23,    40,     3,    12,
      34,   108,    37,     6,    -1,    40,     9,    -1,    43,    44,
      13,    14,    -1,    -1,    -1,    18,    19,    20,    21,    22,
      -1,    24,    -1,    26,    -1,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    37,     6,    -1,    40,     9,    -1,
      43,    44,    13,    14,    -1,    -1,    -1,    18,    19,    20,
      21,    22,    -1,    24,    -1,    26,    -1,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    37,    -1,     6,    40,
      41,     9,    43,    -1,    -1,    13,    14,    -1,    -1,    -1,
      18,    19,    20,    21,    22,    -1,    24,    10,    26,    -1,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    11,    37,
      -1,    -1,    40,    -1,    27,    43,    -1,    -1,    31,    32,
      33,    34,    35,    36,    27,    38,    39,    12,    31,    32,
      33,    34,    35,    36,    -1,    38,    39,    -1,    -1,    -1,
      -1,    16,    27,    -1,    -1,    -1,    31,    32,    33,    34,
      35,    36,    27,    38,    39,    -1,    31,    32,    33,    34,
      35,    36,    27,    38,    39,    -1,    31,    32,    33,    34,
      35,    36,    -1,    38,    39,    -1,    -1,    42,    27,    -1,
      -1,    46,    31,    32,    33,    34,    35,    36,    -1,    38,
      39,    -1,    27,    -1,    -1,    44,    31,    32,    33,    34,
      35,    36,    -1,    38,    39,    -1,    27,    -1,    -1,    44,
      31,    32,    33,    34,    35,    36,    -1,    38,    39,    27,
      -1,    42,    -1,    31,    32,    33,    34,    35,    36,    -1,
      38,    39,    27,    -1,    42,    -1,    31,    32,    33,    34,
      35,    36,    -1,    38,    39,    27,    -1,    42,    -1,    31,
      32,    33,    34,    35,    36,    -1,    38,    39,    27,    41,
      -1,    -1,    31,    32,    33,    34,    35,    36,    -1,    38,
      39,    27,    41,    -1,    -1,    31,    32,    33,    34,    35,
      36,    -1,    38,    39,    27,    41,    -1,    -1,    31,    32,
      33,    34,    35,    36,    27,    38,    39,    -1,    31,    32,
      33,    34,    35,    36,    -1,    38,    39
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    48,    49,    50,    23,     0,    50,     8,    40,
      23,    51,    40,    24,    41,    52,    51,    43,    45,    42,
      42,    41,    24,    44,    54,    23,    42,    45,    45,    53,
      25,    23,    23,    44,    46,     6,     9,    13,    14,    18,
      19,    20,    21,    22,    24,    26,    28,    37,    40,    43,
      58,    61,    64,    40,    45,    54,    64,    24,    64,    64,
      23,    64,    25,    43,    64,    43,    64,    63,    64,    64,
      27,    31,    32,    33,    34,    35,    36,    38,    39,    64,
      23,    12,    45,    10,    16,    64,    44,    64,    24,    41,
      64,    42,    44,    64,    64,    64,    64,    64,    64,    64,
      23,    24,    41,    40,    64,    23,    64,    24,    55,    56,
      62,    45,    42,    39,    43,    64,     4,     7,    25,    46,
      57,    11,    45,    15,    56,    42,    44,    46,    23,    24,
      44,    64,    41,    64,    64,    64,    24,    23,    42,    64,
      25,    42,    46,    59,    60,    43,    62,     5,    57,    45,
      17,    64,    64,    24,    44,    64,    44,    23,    64,    60,
      42,    45,    62,    25,    57,    64,    23,    44,    64,    44,
      25,    60,    57,    40,    64,    64,    60,    41
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    47,    48,    49,    49,    50,    50,    51,    51,    52,
      52,    52,    52,    53,    53,    54,    55,    55,    56,    57,
      57,    57,    58,    58,    59,    60,    60,    60,    61,    61,
      62,    62,    63,    63,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     6,     8,     0,     3,     8,
      10,     3,     5,     0,     3,     3,     2,     3,     5,     2,
       5,     7,     5,     7,     8,     1,     5,     7,     6,     8,
       0,     3,     2,     3,     3,     5,     7,     7,     9,     3,
       5,     7,     5,     3,     1,     1,     5,     2,     2,     3,
       3,     3,     3,     2,     3,     3,     3,     2,     3,     1,
       1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: class_list  */
#line 140 "cool.y"
                     { ast_root = program((yyvsp[0].classes)); }
#line 1337 "cool.y.cc"
    break;

  case 3: /* class_list: class  */
#line 145 "cool.y"
                { (yyval.classes) = single_Classes((yyvsp[0].class_)); }
#line 1343 "cool.y.cc"
    break;

  case 4: /* class_list: class_list class  */
#line 147 "cool.y"
                { (yyval.classes) = append_Classes((yyvsp[-1].classes),single_Classes((yyvsp[0].class_))); }
#line 1349 "cool.y.cc"
    break;

  case 5: /* class: CLASS TYPEID '{' feature_list_star '}' ';'  */
#line 152 "cool.y"
                { (yyval.class_) = class_((yyvsp[-4].symbol),idtable.add_string("Object"), (yyvsp[-2].features), stringtable.add_string(curr_filename)); }
#line 1355 "cool.y.cc"
    break;

  case 6: /* class: CLASS TYPEID INHERITS TYPEID '{' feature_list_star '}' ';'  */
#line 154 "cool.y"
                { (yyval.class_) = class_((yyvsp[-6].symbol),(yyvsp[-4].symbol),(yyvsp[-2].features),stringtable.add_string(curr_filename)); }
#line 1361 "cool.y.cc"
    break;

  case 7: /* feature_list_star: %empty  */
#line 159 "cool.y"
                                {  (yyval.features) = nil_Features(); }
#line 1367 "cool.y.cc"
    break;

  case 8: /* feature_list_star: feature_list_star feature_single ';'  */
#line 161 "cool.y"
                                {  (yyval.features) = append_Features((yyvsp[-2].features), single_Features((yyvsp[-1].feature))); }
#line 1373 "cool.y.cc"
    break;

  case 9: /* feature_single: OBJECTID '(' ')' ':' TYPEID '{' expression_single '}'  */
#line 164 "cool.y"
                                {  (yyval.feature) = method((yyvsp[-7].symbol), nil_Formals(), (yyvsp[-3].symbol), (yyvsp[-1].expression));  }
#line 1379 "cool.y.cc"
    break;

  case 10: /* feature_single: OBJECTID '(' formal_single formal_list_star ')' ':' TYPEID '{' expression_single '}'  */
#line 166 "cool.y"
                                {  (yyval.feature) = method((yyvsp[-9].symbol), append_Formals(single_Formals((yyvsp[-7].formal)), (yyvsp[-6].formals)), (yyvsp[-3].symbol), (yyvsp[-1].expression));  }
#line 1385 "cool.y.cc"
    break;

  case 11: /* feature_single: OBJECTID ':' TYPEID  */
#line 168 "cool.y"
                                {  (yyval.feature) = attr((yyvsp[-2].symbol), (yyvsp[0].symbol), no_expr());  }
#line 1391 "cool.y.cc"
    break;

  case 12: /* feature_single: OBJECTID ':' TYPEID ASSIGN expression_single  */
#line 170 "cool.y"
                                {  (yyval.feature) = attr((yyvsp[-4].symbol), (yyvsp[-2].symbol), (yyvsp[0].expression));  }
#line 1397 "cool.y.cc"
    break;

  case 13: /* formal_list_star: %empty  */
#line 175 "cool.y"
                                {  (yyval.formals) = nil_Formals();  }
#line 1403 "cool.y.cc"
    break;

  case 14: /* formal_list_star: formal_list_star ',' formal_single  */
#line 177 "cool.y"
                                {  (yyval.formals) = append_Formals((yyvsp[-2].formals), single_Formals((yyvsp[0].formal)));  }
#line 1409 "cool.y.cc"
    break;

  case 15: /* formal_single: OBJECTID ':' TYPEID  */
#line 180 "cool.y"
                                {  (yyval.formal) = formal((yyvsp[-2].symbol), (yyvsp[0].symbol));  }
#line 1415 "cool.y.cc"
    break;

  case 16: /* case_list_pos: case_single ';'  */
#line 185 "cool.y"
                                {  (yyval.cases) = single_Cases((yyvsp[-1].case_));  }
#line 1421 "cool.y.cc"
    break;

  case 17: /* case_list_pos: case_list_pos case_single ';'  */
#line 187 "cool.y"
                                {  (yyval.cases) = append_Cases((yyvsp[-2].cases), single_Cases((yyvsp[-1].case_)));  }
#line 1427 "cool.y.cc"
    break;

  case 18: /* case_single: OBJECTID ':' TYPEID DARROW expression_single  */
#line 190 "cool.y"
                                {  (yyval.case_) = branch((yyvsp[-4].symbol), (yyvsp[-2].symbol), (yyvsp[0].expression));  }
#line 1433 "cool.y.cc"
    break;

  case 19: /* let_expand: IN expression_single  */
#line 195 "cool.y"
                                {  (yyval.expression) = (yyvsp[0].expression);  }
#line 1439 "cool.y.cc"
    break;

  case 20: /* let_expand: ',' OBJECTID ':' TYPEID let_expand  */
#line 197 "cool.y"
                                {  (yyval.expression) = let((yyvsp[-3].symbol), (yyvsp[-1].symbol), no_expr(), (yyvsp[0].expression));  }
#line 1445 "cool.y.cc"
    break;

  case 21: /* let_expand: ',' OBJECTID ':' TYPEID ASSIGN expression_single let_expand  */
#line 199 "cool.y"
                                {  (yyval.expression) = let((yyvsp[-5].symbol), (yyvsp[-3].symbol), (yyvsp[-1].expression), (yyvsp[0].expression));  }
#line 1451 "cool.y.cc"
    break;

  case 22: /* let_begin: LET OBJECTID ':' TYPEID let_expand  */
#line 202 "cool.y"
                                {  (yyval.expression) = let((yyvsp[-3].symbol), (yyvsp[-1].symbol), no_expr(), (yyvsp[0].expression));  }
#line 1457 "cool.y.cc"
    break;

  case 23: /* let_begin: LET OBJECTID ':' TYPEID ASSIGN expression_single let_expand  */
#line 204 "cool.y"
                                {  (yyval.expression) = let((yyvsp[-5].symbol), (yyvsp[-3].symbol), (yyvsp[-1].expression), (yyvsp[0].expression));  }
#line 1463 "cool.y.cc"
    break;

  case 24: /* for_second: ';' expression_single ';' expression_single ')' '{' expression_single '}'  */
#line 209 "cool.y"
                                {  (yyval.expression) = loop((yyvsp[-6].expression), block(append_Expressions(single_Expressions((yyvsp[-1].expression)), single_Expressions((yyvsp[-4].expression)))));  }
#line 1469 "cool.y.cc"
    break;

  case 25: /* for_expand: for_second  */
#line 212 "cool.y"
                                {  (yyval.expression) = (yyvsp[0].expression);  }
#line 1475 "cool.y.cc"
    break;

  case 26: /* for_expand: ',' OBJECTID ':' TYPEID for_expand  */
#line 214 "cool.y"
                                {  (yyval.expression) = let((yyvsp[-3].symbol), (yyvsp[-1].symbol), no_expr(), (yyvsp[0].expression));  }
#line 1481 "cool.y.cc"
    break;

  case 27: /* for_expand: ',' OBJECTID ':' TYPEID ASSIGN expression_single for_expand  */
#line 216 "cool.y"
                                {  (yyval.expression) = let((yyvsp[-5].symbol), (yyvsp[-3].symbol), (yyvsp[-1].expression), (yyvsp[0].expression));  }
#line 1487 "cool.y.cc"
    break;

  case 28: /* for_begin: FOR '(' OBJECTID ':' TYPEID for_expand  */
#line 219 "cool.y"
                                {  (yyval.expression) = let((yyvsp[-3].symbol), (yyvsp[-1].symbol), no_expr(), (yyvsp[0].expression));  }
#line 1493 "cool.y.cc"
    break;

  case 29: /* for_begin: FOR '(' OBJECTID ':' TYPEID ASSIGN expression_single for_expand  */
#line 221 "cool.y"
                                {  (yyval.expression) = let((yyvsp[-5].symbol), (yyvsp[-3].symbol), (yyvsp[-1].expression), (yyvsp[0].expression));  }
#line 1499 "cool.y.cc"
    break;

  case 30: /* expression_list_star: %empty  */
#line 227 "cool.y"
                                {  (yyval.expressions) = nil_Expressions();  }
#line 1505 "cool.y.cc"
    break;

  case 31: /* expression_list_star: expression_list_star ',' expression_single  */
#line 229 "cool.y"
                                {  (yyval.expressions) = append_Expressions((yyvsp[-2].expressions), single_Expressions((yyvsp[0].expression)));  }
#line 1511 "cool.y.cc"
    break;

  case 32: /* expression_list_pos: expression_single ';'  */
#line 232 "cool.y"
                                {  (yyval.expressions) = single_Expressions((yyvsp[-1].expression));  }
#line 1517 "cool.y.cc"
    break;

  case 33: /* expression_list_pos: expression_list_pos expression_single ';'  */
#line 234 "cool.y"
                                {  (yyval.expressions) = append_Expressions((yyvsp[-2].expressions), single_Expressions((yyvsp[-1].expression)));  }
#line 1523 "cool.y.cc"
    break;

  case 34: /* expression_single: OBJECTID ASSIGN expression_single  */
#line 238 "cool.y"
                                {  (yyval.expression) = assign((yyvsp[-2].symbol), (yyvsp[0].expression));  }
#line 1529 "cool.y.cc"
    break;

  case 35: /* expression_single: expression_single '.' OBJECTID '(' ')'  */
#line 240 "cool.y"
                                {  (yyval.expression) = dispatch((yyvsp[-4].expression), (yyvsp[-2].symbol), nil_Expressions());  }
#line 1535 "cool.y.cc"
    break;

  case 36: /* expression_single: expression_single '.' OBJECTID '(' expression_single expression_list_star ')'  */
#line 242 "cool.y"
                                {  (yyval.expression) = dispatch((yyvsp[-6].expression), (yyvsp[-4].symbol), append_Expressions(single_Expressions((yyvsp[-2].expression)), (yyvsp[-1].expressions)));  }
#line 1541 "cool.y.cc"
    break;

  case 37: /* expression_single: expression_single '@' TYPEID '.' OBJECTID '(' ')'  */
#line 244 "cool.y"
                                {  (yyval.expression) = static_dispatch((yyvsp[-6].expression), (yyvsp[-4].symbol), (yyvsp[-2].symbol), nil_Expressions());  }
#line 1547 "cool.y.cc"
    break;

  case 38: /* expression_single: expression_single '@' TYPEID '.' OBJECTID '(' expression_single expression_list_star ')'  */
#line 246 "cool.y"
                                {  (yyval.expression) = static_dispatch((yyvsp[-8].expression), (yyvsp[-6].symbol), (yyvsp[-4].symbol), append_Expressions(single_Expressions((yyvsp[-2].expression)), (yyvsp[-1].expressions)));  }
#line 1553 "cool.y.cc"
    break;

  case 39: /* expression_single: OBJECTID '(' ')'  */
#line 248 "cool.y"
                                {  (yyval.expression) = dispatch(object(idtable.add_string("self")), (yyvsp[-2].symbol), nil_Expressions());  }
#line 1559 "cool.y.cc"
    break;

  case 40: /* expression_single: OBJECTID '(' expression_single expression_list_star ')'  */
#line 250 "cool.y"
                                {  (yyval.expression) = dispatch(object(idtable.add_string("self")), (yyvsp[-4].symbol), append_Expressions(single_Expressions((yyvsp[-2].expression)), (yyvsp[-1].expressions)));  }
#line 1565 "cool.y.cc"
    break;

  case 41: /* expression_single: IF expression_single THEN expression_single ELSE expression_single FI  */
#line 252 "cool.y"
                                {  (yyval.expression) = cond((yyvsp[-5].expression), (yyvsp[-3].expression), (yyvsp[-1].expression));  }
#line 1571 "cool.y.cc"
    break;

  case 42: /* expression_single: WHILE expression_single LOOP expression_single POOL  */
#line 254 "cool.y"
                                {  (yyval.expression) = loop((yyvsp[-3].expression), (yyvsp[-1].expression));  }
#line 1577 "cool.y.cc"
    break;

  case 43: /* expression_single: '{' expression_list_pos '}'  */
#line 256 "cool.y"
                                {  (yyval.expression) = block((yyvsp[-1].expressions));  }
#line 1583 "cool.y.cc"
    break;

  case 44: /* expression_single: let_begin  */
#line 258 "cool.y"
                                {  (yyval.expression) = (yyvsp[0].expression); }
#line 1589 "cool.y.cc"
    break;

  case 45: /* expression_single: for_begin  */
#line 260 "cool.y"
                                {  (yyval.expression) = (yyvsp[0].expression); }
#line 1595 "cool.y.cc"
    break;

  case 46: /* expression_single: CASE expression_single OF case_list_pos ESAC  */
#line 262 "cool.y"
                                {  (yyval.expression) = typcase((yyvsp[-3].expression), (yyvsp[-1].cases));  }
#line 1601 "cool.y.cc"
    break;

  case 47: /* expression_single: NEW TYPEID  */
#line 264 "cool.y"
                                {  (yyval.expression) = new_((yyvsp[0].symbol));  }
#line 1607 "cool.y.cc"
    break;

  case 48: /* expression_single: ISVOID expression_single  */
#line 266 "cool.y"
                                {  (yyval.expression) = isvoid((yyvsp[0].expression));  }
#line 1613 "cool.y.cc"
    break;

  case 49: /* expression_single: expression_single '+' expression_single  */
#line 268 "cool.y"
                                {  (yyval.expression) = plus((yyvsp[-2].expression), (yyvsp[0].expression));  }
#line 1619 "cool.y.cc"
    break;

  case 50: /* expression_single: expression_single '-' expression_single  */
#line 270 "cool.y"
                                {  (yyval.expression) = sub((yyvsp[-2].expression), (yyvsp[0].expression));  }
#line 1625 "cool.y.cc"
    break;

  case 51: /* expression_single: expression_single '*' expression_single  */
#line 272 "cool.y"
                                {  (yyval.expression) = mul((yyvsp[-2].expression), (yyvsp[0].expression));  }
#line 1631 "cool.y.cc"
    break;

  case 52: /* expression_single: expression_single '/' expression_single  */
#line 274 "cool.y"
                                {  (yyval.expression) = divide((yyvsp[-2].expression), (yyvsp[0].expression));  }
#line 1637 "cool.y.cc"
    break;

  case 53: /* expression_single: '~' expression_single  */
#line 276 "cool.y"
                                {  (yyval.expression) = neg((yyvsp[0].expression));  }
#line 1643 "cool.y.cc"
    break;

  case 54: /* expression_single: expression_single '<' expression_single  */
#line 278 "cool.y"
                                {  (yyval.expression) = lt((yyvsp[-2].expression), (yyvsp[0].expression));  }
#line 1649 "cool.y.cc"
    break;

  case 55: /* expression_single: expression_single LE expression_single  */
#line 280 "cool.y"
                                {  (yyval.expression) = leq((yyvsp[-2].expression), (yyvsp[0].expression));  }
#line 1655 "cool.y.cc"
    break;

  case 56: /* expression_single: expression_single '=' expression_single  */
#line 282 "cool.y"
                                {  (yyval.expression) = eq((yyvsp[-2].expression), (yyvsp[0].expression));  }
#line 1661 "cool.y.cc"
    break;

  case 57: /* expression_single: NOT expression_single  */
#line 284 "cool.y"
                                {  (yyval.expression) = comp((yyvsp[0].expression));  }
#line 1667 "cool.y.cc"
    break;

  case 58: /* expression_single: '(' expression_single ')'  */
#line 286 "cool.y"
                                {  (yyval.expression) = (yyvsp[-1].expression);  }
#line 1673 "cool.y.cc"
    break;

  case 59: /* expression_single: OBJECTID  */
#line 288 "cool.y"
                                {  (yyval.expression) = object((yyvsp[0].symbol));  }
#line 1679 "cool.y.cc"
    break;

  case 60: /* expression_single: INT_CONST  */
#line 290 "cool.y"
                                {  (yyval.expression) = int_const((yyvsp[0].symbol));  }
#line 1685 "cool.y.cc"
    break;

  case 61: /* expression_single: STR_CONST  */
#line 292 "cool.y"
                                {  (yyval.expression) = string_const((yyvsp[0].symbol));  }
#line 1691 "cool.y.cc"
    break;

  case 62: /* expression_single: BOOL_CONST  */
#line 294 "cool.y"
                                {  (yyval.expression) = bool_const((yyvsp[0].boolean));  }
#line 1697 "cool.y.cc"
    break;


#line 1701 "cool.y.cc"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 298 "cool.y"


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