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
  YYSYMBOL_let_no_expr_helper = 57,        /* let_no_expr_helper  */
  YYSYMBOL_let_expand = 58,                /* let_expand  */
  YYSYMBOL_let_begin = 59,                 /* let_begin  */
  YYSYMBOL_for_second = 60,                /* for_second  */
  YYSYMBOL_for_expand = 61,                /* for_expand  */
  YYSYMBOL_for_begin = 62,                 /* for_begin  */
  YYSYMBOL_expression_list_star = 63,      /* expression_list_star  */
  YYSYMBOL_expression_list_pos = 64,       /* expression_list_pos  */
  YYSYMBOL_expression_single = 65          /* expression_single  */
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
#define YYLAST   447

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  62
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  176

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
       0,   141,   141,   145,   147,   152,   154,   160,   161,   164,
     166,   168,   170,   176,   177,   180,   185,   187,   190,   195,
     196,   199,   201,   204,   209,   212,   214,   216,   219,   221,
     228,   229,   232,   234,   238,   240,   242,   244,   246,   248,
     250,   252,   254,   256,   258,   260,   262,   264,   266,   268,
     270,   272,   274,   276,   278,   280,   282,   284,   286,   288,
     290,   292,   294
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
  "case_single", "let_no_expr_helper", "let_expand", "let_begin",
  "for_second", "for_expand", "for_begin", "expression_list_star",
  "expression_list_pos", "expression_single", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-144)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       5,    21,    16,     5,  -144,    -7,  -144,  -144,    27,  -144,
      13,    34,  -144,   -28,   -23,   -18,    35,    -2,    37,  -144,
    -144,    28,    40,    56,  -144,    48,  -144,    51,    79,   -21,
     194,  -144,    44,    62,    84,   194,    88,   194,   194,    90,
     194,  -144,  -144,  -144,    29,   194,    85,   194,   194,   194,
    -144,  -144,   398,   194,   108,  -144,   252,    87,   223,   266,
    -144,    39,   194,    43,   398,   115,    39,   161,   320,   292,
     194,   194,   194,   194,   194,   194,   194,   121,   122,   359,
     105,   194,   131,   194,   128,   398,  -144,   398,   111,  -144,
     333,  -144,  -144,   408,   408,   408,    91,    91,    39,    39,
     119,   116,  -144,   194,   213,   135,   242,   117,    -4,   123,
       1,   138,  -144,   139,    97,   372,   194,   194,    -3,  -144,
     141,  -144,   126,  -144,  -144,   194,   -16,   133,  -144,   398,
    -144,    61,   398,   194,   147,  -144,   160,  -144,   398,   194,
     194,   154,  -144,  -144,   129,    45,  -144,   398,   143,   194,
     276,   346,   145,  -144,   398,  -144,   163,   398,  -144,   194,
     168,    76,   135,   306,     9,  -144,    -3,   144,   194,  -144,
    -144,   194,   276,   385,  -144,  -144
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
       0,     0,     9,     0,     0,    19,     0,     0,     0,     0,
       0,     0,    33,     0,     0,     0,     0,     0,     0,    42,
       0,    46,     0,    16,    40,     0,     0,     0,    35,    30,
      10,     0,    20,     0,     0,    23,     0,    17,    31,     0,
       0,     0,    25,    28,     0,     0,    41,    21,     0,     0,
       0,     0,     0,    37,    30,    36,     0,    18,    29,     0,
       0,     0,    19,     0,     0,    38,     0,     0,     0,    26,
      22,     0,     0,     0,    27,    24
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -144,  -144,  -144,   189,   181,  -144,  -144,   162,  -144,    86,
      33,    31,  -144,  -144,  -143,  -144,  -123,  -144,   -35
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     3,     4,    11,    15,    29,    24,   108,   109,
     118,   135,    50,   142,   143,    51,   110,    67,    52
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      56,     8,    58,    59,   133,    61,   145,   158,     1,   139,
      64,   121,    66,    68,    69,    17,     6,    18,    79,    19,
     107,   169,    22,    33,    20,    34,   140,    85,    87,   174,
     141,   161,    90,     9,   168,    93,    94,    95,    96,    97,
      98,    99,    23,   134,     5,   124,   104,   125,   106,    35,
      10,   140,    36,    12,    62,   141,    37,    38,    13,    13,
      25,    39,    40,    41,    42,    43,   146,    44,   115,    45,
      26,    46,    63,    30,    31,    14,    21,    77,    78,   129,
      47,   131,   132,    48,    53,    27,    49,    86,    70,   155,
     138,   125,    71,    72,    73,    74,    75,    76,   147,    77,
      78,    28,    32,    35,   150,   151,    36,    54,    22,   154,
      37,    38,    57,    60,   157,    39,    40,    41,    42,    43,
     165,    44,   125,    45,   163,    46,    75,    76,    65,    77,
      78,    80,    82,   172,    47,    35,   173,    48,    36,    88,
      49,   128,    37,    38,   100,   103,   101,    39,    40,    41,
      42,    43,   107,    44,   105,    45,   111,    46,   113,   114,
     117,   126,   120,   127,   136,   123,    47,    35,   137,    48,
      36,   148,    49,   153,    37,    38,   144,   149,   152,    39,
      40,    41,    42,    43,   171,    44,   162,    45,   156,    46,
     160,   164,     7,    16,   122,   166,    55,   170,    47,     0,
      35,    48,    89,    36,    49,     0,     0,    37,    38,     0,
       0,     0,    39,    40,    41,    42,    43,   116,    44,     0,
      45,     0,    46,     0,     0,     0,     0,     0,     0,     0,
       0,    47,     0,    83,    48,     0,     0,    49,     0,     0,
      70,     0,     0,     0,    71,    72,    73,    74,    75,    76,
      70,    77,    78,   119,    71,    72,    73,    74,    75,    76,
       0,    77,    78,     0,    81,     0,     0,     0,     0,    70,
       0,     0,     0,    71,    72,    73,    74,    75,    76,    70,
      77,    78,    84,    71,    72,    73,    74,    75,    76,     0,
      77,    78,     0,    70,     0,     0,     0,    71,    72,    73,
      74,    75,    76,    70,    77,    78,     0,    71,    72,    73,
      74,    75,    76,     0,    77,    78,     0,     0,   140,    70,
       0,     0,   141,    71,    72,    73,    74,    75,    76,     0,
      77,    78,     0,    70,     0,     0,    92,    71,    72,    73,
      74,    75,    76,     0,    77,    78,     0,    70,     0,     0,
     167,    71,    72,    73,    74,    75,    76,     0,    77,    78,
      70,     0,    91,     0,    71,    72,    73,    74,    75,    76,
       0,    77,    78,    70,     0,   112,     0,    71,    72,    73,
      74,    75,    76,     0,    77,    78,    70,     0,   159,     0,
      71,    72,    73,    74,    75,    76,     0,    77,    78,    70,
     102,     0,     0,    71,    72,    73,    74,    75,    76,     0,
      77,    78,    70,   130,     0,     0,    71,    72,    73,    74,
      75,    76,     0,    77,    78,    70,   175,     0,     0,    71,
      72,    73,    74,    75,    76,    -1,    77,    78,     0,    -1,
      -1,    73,    74,    75,    76,     0,    77,    78
};

static const yytype_int16 yycheck[] =
{
      35,     8,    37,    38,     7,    40,   129,   150,     3,    25,
      45,    15,    47,    48,    49,    43,     0,    45,    53,    42,
      24,   164,    24,    44,    42,    46,    42,    62,    63,   172,
      46,   154,    67,    40,    25,    70,    71,    72,    73,    74,
      75,    76,    44,    46,    23,    44,    81,    46,    83,     6,
      23,    42,     9,    40,    25,    46,    13,    14,    24,    24,
      23,    18,    19,    20,    21,    22,     5,    24,   103,    26,
      42,    28,    43,    25,    23,    41,    41,    38,    39,   114,
      37,   116,   117,    40,    40,    45,    43,    44,    27,    44,
     125,    46,    31,    32,    33,    34,    35,    36,   133,    38,
      39,    45,    23,     6,   139,   140,     9,    45,    24,   144,
      13,    14,    24,    23,   149,    18,    19,    20,    21,    22,
      44,    24,    46,    26,   159,    28,    35,    36,    43,    38,
      39,    23,    45,   168,    37,     6,   171,    40,     9,    24,
      43,    44,    13,    14,    23,    40,    24,    18,    19,    20,
      21,    22,    24,    24,    23,    26,    45,    28,    39,    43,
      25,    23,    45,    24,    23,    42,    37,     6,    42,    40,
       9,    24,    43,    44,    13,    14,    43,    17,    24,    18,
      19,    20,    21,    22,    40,    24,    23,    26,    45,    28,
      45,    23,     3,    12,   108,   162,    34,   166,    37,    -1,
       6,    40,    41,     9,    43,    -1,    -1,    13,    14,    -1,
      -1,    -1,    18,    19,    20,    21,    22,     4,    24,    -1,
      26,    -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    37,    -1,    10,    40,    -1,    -1,    43,    -1,    -1,
      27,    -1,    -1,    -1,    31,    32,    33,    34,    35,    36,
      27,    38,    39,    11,    31,    32,    33,    34,    35,    36,
      -1,    38,    39,    -1,    12,    -1,    -1,    -1,    -1,    27,
      -1,    -1,    -1,    31,    32,    33,    34,    35,    36,    27,
      38,    39,    16,    31,    32,    33,    34,    35,    36,    -1,
      38,    39,    -1,    27,    -1,    -1,    -1,    31,    32,    33,
      34,    35,    36,    27,    38,    39,    -1,    31,    32,    33,
      34,    35,    36,    -1,    38,    39,    -1,    -1,    42,    27,
      -1,    -1,    46,    31,    32,    33,    34,    35,    36,    -1,
      38,    39,    -1,    27,    -1,    -1,    44,    31,    32,    33,
      34,    35,    36,    -1,    38,    39,    -1,    27,    -1,    -1,
      44,    31,    32,    33,    34,    35,    36,    -1,    38,    39,
      27,    -1,    42,    -1,    31,    32,    33,    34,    35,    36,
      -1,    38,    39,    27,    -1,    42,    -1,    31,    32,    33,
      34,    35,    36,    -1,    38,    39,    27,    -1,    42,    -1,
      31,    32,    33,    34,    35,    36,    -1,    38,    39,    27,
      41,    -1,    -1,    31,    32,    33,    34,    35,    36,    -1,
      38,    39,    27,    41,    -1,    -1,    31,    32,    33,    34,
      35,    36,    -1,    38,    39,    27,    41,    -1,    -1,    31,
      32,    33,    34,    35,    36,    27,    38,    39,    -1,    31,
      32,    33,    34,    35,    36,    -1,    38,    39
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
      59,    62,    65,    40,    45,    54,    65,    24,    65,    65,
      23,    65,    25,    43,    65,    43,    65,    64,    65,    65,
      27,    31,    32,    33,    34,    35,    36,    38,    39,    65,
      23,    12,    45,    10,    16,    65,    44,    65,    24,    41,
      65,    42,    44,    65,    65,    65,    65,    65,    65,    65,
      23,    24,    41,    40,    65,    23,    65,    24,    55,    56,
      63,    45,    42,    39,    43,    65,     4,    25,    57,    11,
      45,    15,    56,    42,    44,    46,    23,    24,    44,    65,
      41,    65,    65,     7,    46,    58,    23,    42,    65,    25,
      42,    46,    60,    61,    43,    63,     5,    65,    24,    17,
      65,    65,    24,    44,    65,    44,    45,    65,    61,    42,
      45,    63,    23,    65,    23,    44,    57,    44,    25,    61,
      58,    40,    65,    65,    61,    41
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    47,    48,    49,    49,    50,    50,    51,    51,    52,
      52,    52,    52,    53,    53,    54,    55,    55,    56,    57,
      57,    58,    58,    59,    60,    61,    61,    61,    62,    62,
      63,    63,    64,    64,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     6,     8,     0,     3,     8,
      10,     3,     5,     0,     3,     3,     2,     3,     5,     0,
       2,     2,     6,     6,     8,     1,     5,     7,     6,     8,
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
#line 141 "cool.y"
                     { ast_root = program((yyvsp[0].classes)); }
#line 1330 "cool.y.cc"
    break;

  case 3: /* class_list: class  */
#line 146 "cool.y"
                { (yyval.classes) = single_Classes((yyvsp[0].class_)); }
#line 1336 "cool.y.cc"
    break;

  case 4: /* class_list: class_list class  */
#line 148 "cool.y"
                { (yyval.classes) = append_Classes((yyvsp[-1].classes),single_Classes((yyvsp[0].class_))); }
#line 1342 "cool.y.cc"
    break;

  case 5: /* class: CLASS TYPEID '{' feature_list_star '}' ';'  */
#line 153 "cool.y"
                { (yyval.class_) = class_((yyvsp[-4].symbol),idtable.add_string("Object"), (yyvsp[-2].features), stringtable.add_string(curr_filename)); }
#line 1348 "cool.y.cc"
    break;

  case 6: /* class: CLASS TYPEID INHERITS TYPEID '{' feature_list_star '}' ';'  */
#line 155 "cool.y"
                { (yyval.class_) = class_((yyvsp[-6].symbol),(yyvsp[-4].symbol),(yyvsp[-2].features),stringtable.add_string(curr_filename)); }
#line 1354 "cool.y.cc"
    break;

  case 7: /* feature_list_star: %empty  */
#line 160 "cool.y"
                                {  (yyval.features) = nil_Features(); }
#line 1360 "cool.y.cc"
    break;

  case 8: /* feature_list_star: feature_list_star feature_single ';'  */
#line 162 "cool.y"
                                {  (yyval.features) = append_Features((yyvsp[-2].features), single_Features((yyvsp[-1].feature))); }
#line 1366 "cool.y.cc"
    break;

  case 9: /* feature_single: OBJECTID '(' ')' ':' TYPEID '{' expression_single '}'  */
#line 165 "cool.y"
                                {  (yyval.feature) = method((yyvsp[-7].symbol), nil_Formals(), (yyvsp[-3].symbol), (yyvsp[-1].expression));  }
#line 1372 "cool.y.cc"
    break;

  case 10: /* feature_single: OBJECTID '(' formal_single formal_list_star ')' ':' TYPEID '{' expression_single '}'  */
#line 167 "cool.y"
                                {  (yyval.feature) = method((yyvsp[-9].symbol), append_Formals(single_Formals((yyvsp[-7].formal)), (yyvsp[-6].formals)), (yyvsp[-3].symbol), (yyvsp[-1].expression));  }
#line 1378 "cool.y.cc"
    break;

  case 11: /* feature_single: OBJECTID ':' TYPEID  */
#line 169 "cool.y"
                                {  (yyval.feature) = attr((yyvsp[-2].symbol), (yyvsp[0].symbol), no_expr());  }
#line 1384 "cool.y.cc"
    break;

  case 12: /* feature_single: OBJECTID ':' TYPEID ASSIGN expression_single  */
#line 171 "cool.y"
                                {  (yyval.feature) = attr((yyvsp[-4].symbol), (yyvsp[-2].symbol), (yyvsp[0].expression));  }
#line 1390 "cool.y.cc"
    break;

  case 13: /* formal_list_star: %empty  */
#line 176 "cool.y"
                                {  (yyval.formals) = nil_Formals();  }
#line 1396 "cool.y.cc"
    break;

  case 14: /* formal_list_star: formal_list_star ',' formal_single  */
#line 178 "cool.y"
                                {  (yyval.formals) = append_Formals((yyvsp[-2].formals), single_Formals((yyvsp[0].formal)));  }
#line 1402 "cool.y.cc"
    break;

  case 15: /* formal_single: OBJECTID ':' TYPEID  */
#line 181 "cool.y"
                                {  (yyval.formal) = formal((yyvsp[-2].symbol), (yyvsp[0].symbol));  }
#line 1408 "cool.y.cc"
    break;

  case 16: /* case_list_pos: case_single ';'  */
#line 186 "cool.y"
                                {  (yyval.cases) = single_Cases((yyvsp[-1].case_));  }
#line 1414 "cool.y.cc"
    break;

  case 17: /* case_list_pos: case_list_pos case_single ';'  */
#line 188 "cool.y"
                                {  (yyval.cases) = append_Cases((yyvsp[-2].cases), single_Cases((yyvsp[-1].case_)));  }
#line 1420 "cool.y.cc"
    break;

  case 18: /* case_single: OBJECTID ':' TYPEID DARROW expression_single  */
#line 191 "cool.y"
                                {  (yyval.case_) = branch((yyvsp[-4].symbol), (yyvsp[-2].symbol), (yyvsp[0].expression));  }
#line 1426 "cool.y.cc"
    break;

  case 19: /* let_no_expr_helper: %empty  */
#line 195 "cool.y"
                                {  (yyval.expression) = no_expr();  }
#line 1432 "cool.y.cc"
    break;

  case 20: /* let_no_expr_helper: ASSIGN expression_single  */
#line 197 "cool.y"
                                {  (yyval.expression) = (yyvsp[0].expression);  }
#line 1438 "cool.y.cc"
    break;

  case 21: /* let_expand: IN expression_single  */
#line 200 "cool.y"
                                {  (yyval.expression) = (yyvsp[0].expression);  }
#line 1444 "cool.y.cc"
    break;

  case 22: /* let_expand: ',' OBJECTID ':' TYPEID let_no_expr_helper let_expand  */
#line 202 "cool.y"
                                {  (yyval.expression) = let((yyvsp[-4].symbol), (yyvsp[-2].symbol), (yyvsp[-1].expression),  (yyvsp[0].expression));  }
#line 1450 "cool.y.cc"
    break;

  case 23: /* let_begin: LET OBJECTID ':' TYPEID let_no_expr_helper let_expand  */
#line 205 "cool.y"
                                {  (yyval.expression) = let((yyvsp[-4].symbol), (yyvsp[-2].symbol), (yyvsp[-1].expression), (yyvsp[0].expression));  }
#line 1456 "cool.y.cc"
    break;

  case 24: /* for_second: ';' expression_single ';' expression_single ')' '{' expression_single '}'  */
#line 210 "cool.y"
                                {  (yyval.expression) = loop((yyvsp[-6].expression), block(append_Expressions(single_Expressions((yyvsp[-1].expression)), single_Expressions((yyvsp[-4].expression)))));  }
#line 1462 "cool.y.cc"
    break;

  case 25: /* for_expand: for_second  */
#line 213 "cool.y"
                                {  (yyval.expression) = (yyvsp[0].expression);  }
#line 1468 "cool.y.cc"
    break;

  case 26: /* for_expand: ',' OBJECTID ':' TYPEID for_expand  */
#line 215 "cool.y"
                                {  (yyval.expression) = let((yyvsp[-3].symbol), (yyvsp[-1].symbol), no_expr(), (yyvsp[0].expression));  }
#line 1474 "cool.y.cc"
    break;

  case 27: /* for_expand: ',' OBJECTID ':' TYPEID ASSIGN expression_single for_expand  */
#line 217 "cool.y"
                                {  (yyval.expression) = let((yyvsp[-5].symbol), (yyvsp[-3].symbol), (yyvsp[-1].expression), (yyvsp[0].expression));  }
#line 1480 "cool.y.cc"
    break;

  case 28: /* for_begin: FOR '(' OBJECTID ':' TYPEID for_expand  */
#line 220 "cool.y"
                                {  (yyval.expression) = let((yyvsp[-3].symbol), (yyvsp[-1].symbol), no_expr(), (yyvsp[0].expression));  }
#line 1486 "cool.y.cc"
    break;

  case 29: /* for_begin: FOR '(' OBJECTID ':' TYPEID ASSIGN expression_single for_expand  */
#line 222 "cool.y"
                                {  (yyval.expression) = let((yyvsp[-5].symbol), (yyvsp[-3].symbol), (yyvsp[-1].expression), (yyvsp[0].expression));  }
#line 1492 "cool.y.cc"
    break;

  case 30: /* expression_list_star: %empty  */
#line 228 "cool.y"
                                {  (yyval.expressions) = nil_Expressions();  }
#line 1498 "cool.y.cc"
    break;

  case 31: /* expression_list_star: expression_list_star ',' expression_single  */
#line 230 "cool.y"
                                {  (yyval.expressions) = append_Expressions((yyvsp[-2].expressions), single_Expressions((yyvsp[0].expression)));  }
#line 1504 "cool.y.cc"
    break;

  case 32: /* expression_list_pos: expression_single ';'  */
#line 233 "cool.y"
                                {  (yyval.expressions) = single_Expressions((yyvsp[-1].expression));  }
#line 1510 "cool.y.cc"
    break;

  case 33: /* expression_list_pos: expression_list_pos expression_single ';'  */
#line 235 "cool.y"
                                {  (yyval.expressions) = append_Expressions((yyvsp[-2].expressions), single_Expressions((yyvsp[-1].expression)));  }
#line 1516 "cool.y.cc"
    break;

  case 34: /* expression_single: OBJECTID ASSIGN expression_single  */
#line 239 "cool.y"
                                {  (yyval.expression) = assign((yyvsp[-2].symbol), (yyvsp[0].expression));  }
#line 1522 "cool.y.cc"
    break;

  case 35: /* expression_single: expression_single '.' OBJECTID '(' ')'  */
#line 241 "cool.y"
                                {  (yyval.expression) = dispatch((yyvsp[-4].expression), (yyvsp[-2].symbol), nil_Expressions());  }
#line 1528 "cool.y.cc"
    break;

  case 36: /* expression_single: expression_single '.' OBJECTID '(' expression_single expression_list_star ')'  */
#line 243 "cool.y"
                                {  (yyval.expression) = dispatch((yyvsp[-6].expression), (yyvsp[-4].symbol), append_Expressions(single_Expressions((yyvsp[-2].expression)), (yyvsp[-1].expressions)));  }
#line 1534 "cool.y.cc"
    break;

  case 37: /* expression_single: expression_single '@' TYPEID '.' OBJECTID '(' ')'  */
#line 245 "cool.y"
                                {  (yyval.expression) = static_dispatch((yyvsp[-6].expression), (yyvsp[-4].symbol), (yyvsp[-2].symbol), nil_Expressions());  }
#line 1540 "cool.y.cc"
    break;

  case 38: /* expression_single: expression_single '@' TYPEID '.' OBJECTID '(' expression_single expression_list_star ')'  */
#line 247 "cool.y"
                                {  (yyval.expression) = static_dispatch((yyvsp[-8].expression), (yyvsp[-6].symbol), (yyvsp[-4].symbol), append_Expressions(single_Expressions((yyvsp[-2].expression)), (yyvsp[-1].expressions)));  }
#line 1546 "cool.y.cc"
    break;

  case 39: /* expression_single: OBJECTID '(' ')'  */
#line 249 "cool.y"
                                {  (yyval.expression) = dispatch(object(idtable.add_string("self")), (yyvsp[-2].symbol), nil_Expressions());  }
#line 1552 "cool.y.cc"
    break;

  case 40: /* expression_single: OBJECTID '(' expression_single expression_list_star ')'  */
#line 251 "cool.y"
                                {  (yyval.expression) = dispatch(object(idtable.add_string("self")), (yyvsp[-4].symbol), append_Expressions(single_Expressions((yyvsp[-2].expression)), (yyvsp[-1].expressions)));  }
#line 1558 "cool.y.cc"
    break;

  case 41: /* expression_single: IF expression_single THEN expression_single ELSE expression_single FI  */
#line 253 "cool.y"
                                {  (yyval.expression) = cond((yyvsp[-5].expression), (yyvsp[-3].expression), (yyvsp[-1].expression));  }
#line 1564 "cool.y.cc"
    break;

  case 42: /* expression_single: WHILE expression_single LOOP expression_single POOL  */
#line 255 "cool.y"
                                {  (yyval.expression) = loop((yyvsp[-3].expression), (yyvsp[-1].expression));  }
#line 1570 "cool.y.cc"
    break;

  case 43: /* expression_single: '{' expression_list_pos '}'  */
#line 257 "cool.y"
                                {  (yyval.expression) = block((yyvsp[-1].expressions));  }
#line 1576 "cool.y.cc"
    break;

  case 44: /* expression_single: let_begin  */
#line 259 "cool.y"
                                {  (yyval.expression) = (yyvsp[0].expression); }
#line 1582 "cool.y.cc"
    break;

  case 45: /* expression_single: for_begin  */
#line 261 "cool.y"
                                {  (yyval.expression) = (yyvsp[0].expression); }
#line 1588 "cool.y.cc"
    break;

  case 46: /* expression_single: CASE expression_single OF case_list_pos ESAC  */
#line 263 "cool.y"
                                {  (yyval.expression) = typcase((yyvsp[-3].expression), (yyvsp[-1].cases));  }
#line 1594 "cool.y.cc"
    break;

  case 47: /* expression_single: NEW TYPEID  */
#line 265 "cool.y"
                                {  (yyval.expression) = new_((yyvsp[0].symbol));  }
#line 1600 "cool.y.cc"
    break;

  case 48: /* expression_single: ISVOID expression_single  */
#line 267 "cool.y"
                                {  (yyval.expression) = isvoid((yyvsp[0].expression));  }
#line 1606 "cool.y.cc"
    break;

  case 49: /* expression_single: expression_single '+' expression_single  */
#line 269 "cool.y"
                                {  (yyval.expression) = plus((yyvsp[-2].expression), (yyvsp[0].expression));  }
#line 1612 "cool.y.cc"
    break;

  case 50: /* expression_single: expression_single '-' expression_single  */
#line 271 "cool.y"
                                {  (yyval.expression) = sub((yyvsp[-2].expression), (yyvsp[0].expression));  }
#line 1618 "cool.y.cc"
    break;

  case 51: /* expression_single: expression_single '*' expression_single  */
#line 273 "cool.y"
                                {  (yyval.expression) = mul((yyvsp[-2].expression), (yyvsp[0].expression));  }
#line 1624 "cool.y.cc"
    break;

  case 52: /* expression_single: expression_single '/' expression_single  */
#line 275 "cool.y"
                                {  (yyval.expression) = divide((yyvsp[-2].expression), (yyvsp[0].expression));  }
#line 1630 "cool.y.cc"
    break;

  case 53: /* expression_single: '~' expression_single  */
#line 277 "cool.y"
                                {  (yyval.expression) = neg((yyvsp[0].expression));  }
#line 1636 "cool.y.cc"
    break;

  case 54: /* expression_single: expression_single '<' expression_single  */
#line 279 "cool.y"
                                {  (yyval.expression) = lt((yyvsp[-2].expression), (yyvsp[0].expression));  }
#line 1642 "cool.y.cc"
    break;

  case 55: /* expression_single: expression_single LE expression_single  */
#line 281 "cool.y"
                                {  (yyval.expression) = leq((yyvsp[-2].expression), (yyvsp[0].expression));  }
#line 1648 "cool.y.cc"
    break;

  case 56: /* expression_single: expression_single '=' expression_single  */
#line 283 "cool.y"
                                {  (yyval.expression) = eq((yyvsp[-2].expression), (yyvsp[0].expression));  }
#line 1654 "cool.y.cc"
    break;

  case 57: /* expression_single: NOT expression_single  */
#line 285 "cool.y"
                                {  (yyval.expression) = comp((yyvsp[0].expression));  }
#line 1660 "cool.y.cc"
    break;

  case 58: /* expression_single: '(' expression_single ')'  */
#line 287 "cool.y"
                                {  (yyval.expression) = (yyvsp[-1].expression);  }
#line 1666 "cool.y.cc"
    break;

  case 59: /* expression_single: OBJECTID  */
#line 289 "cool.y"
                                {  (yyval.expression) = object((yyvsp[0].symbol));  }
#line 1672 "cool.y.cc"
    break;

  case 60: /* expression_single: INT_CONST  */
#line 291 "cool.y"
                                {  (yyval.expression) = int_const((yyvsp[0].symbol));  }
#line 1678 "cool.y.cc"
    break;

  case 61: /* expression_single: STR_CONST  */
#line 293 "cool.y"
                                {  (yyval.expression) = string_const((yyvsp[0].symbol));  }
#line 1684 "cool.y.cc"
    break;

  case 62: /* expression_single: BOOL_CONST  */
#line 295 "cool.y"
                                {  (yyval.expression) = bool_const((yyvsp[0].boolean));  }
#line 1690 "cool.y.cc"
    break;


#line 1694 "cool.y.cc"

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

#line 299 "cool.y"


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
