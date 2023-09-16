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
  YYSYMBOL_40_ = 40,                       /* ';'  */
  YYSYMBOL_41_ = 41,                       /* '{'  */
  YYSYMBOL_42_ = 42,                       /* '}'  */
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
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   479

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  72
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  195

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
       2,     2,     2,     2,     2,     2,     2,     2,    45,    40,
      31,    32,     2,     2,    38,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    41,     2,    42,    37,     2,     2,     2,
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
       0,   141,   141,   145,   147,   149,   151,   157,   159,   161,
     168,   169,   171,   174,   176,   178,   180,   186,   187,   190,
     195,   197,   200,   210,   211,   213,   218,   220,   222,   226,
     228,   233,   236,   238,   240,   243,   245,   252,   253,   257,
     259,   261,   263,   267,   269,   271,   273,   275,   277,   279,
     281,   283,   285,   287,   289,   291,   293,   295,   297,   299,
     301,   303,   305,   307,   309,   311,   313,   315,   317,   319,
     321,   323,   325
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
  "'~'", "'@'", "'.'", "';'", "'{'", "'}'", "'('", "')'", "':'", "','",
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

#define YYPACT_NINF (-120)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-24)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      32,   -25,     4,  -120,    19,   128,    29,  -120,    16,  -120,
     118,    42,  -120,     8,    52,  -120,  -120,  -120,    45,    35,
    -120,    72,    75,    20,  -120,   -18,    97,  -120,  -120,  -120,
      88,   100,  -120,   115,    21,   133,   139,    55,   228,  -120,
    -120,   123,   120,   143,   228,     7,   228,   228,   140,   228,
    -120,  -120,  -120,    71,   228,   126,   228,    89,   228,  -120,
    -120,   430,   228,   151,  -120,   293,    10,   132,   268,   307,
    -120,   122,   228,   129,   430,   154,   122,    64,    46,   400,
     333,   228,   228,   228,   228,   228,   228,   228,   156,   161,
     361,   146,   228,   228,    53,  -120,   166,   228,   167,   430,
    -120,   430,   147,  -120,  -120,   153,  -120,   410,  -120,  -120,
     440,   440,   440,    86,    86,   122,   122,   155,   152,  -120,
     228,   241,   430,    10,   157,     0,   283,   165,    -4,   158,
      90,   173,  -120,  -120,   176,   162,   374,   228,  -120,   174,
    -120,   228,    10,  -120,   184,  -120,   171,  -120,  -120,   228,
     -10,   169,  -120,   430,  -120,   254,     0,   430,  -120,   201,
    -120,   430,   228,   228,   196,  -120,  -120,   195,    95,  -120,
      10,   228,   317,   420,   177,  -120,   430,  -120,  -120,   430,
    -120,   228,   202,   108,   347,    54,  -120,   183,   228,  -120,
     228,   317,   387,  -120,  -120
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     4,     0,     0,     0,    10,     0,     1,
       0,     0,     3,     0,     0,    10,     6,     5,     0,     0,
       9,     0,     0,     0,    12,     0,     0,    11,    10,     7,
       0,     0,    17,    15,     0,     0,     0,     0,     0,     8,
      19,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      70,    69,    71,    68,     0,     0,     0,     0,     0,    53,
      54,    16,     0,     0,    18,     0,     0,     0,     0,     0,
      56,    57,     0,     0,    66,     0,    62,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    30,     0,     0,     0,    43,
      48,    37,     0,    42,    72,     0,    52,     0,    39,    67,
      64,    63,    65,    58,    59,    60,    61,     0,     0,    13,
       0,     0,    26,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    41,    40,     0,     0,     0,     0,    28,     0,
      25,     0,     0,    51,     0,    55,     0,    20,    49,     0,
       0,     0,    44,    37,    14,     0,     0,    24,    29,     0,
      21,    38,     0,     0,     0,    32,    35,     0,     0,    50,
       0,     0,     0,     0,     0,    46,    37,    45,    27,    22,
      36,     0,     0,     0,     0,     0,    47,     0,     0,    33,
       0,     0,     0,    34,    31
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -120,  -120,  -120,   221,    56,  -120,  -120,   185,  -120,    99,
      73,  -119,  -120,  -120,   -99,  -120,   -95,  -120,   -44
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     4,     5,     6,    13,    21,    37,    32,   128,   129,
     142,    95,    59,   165,   166,    60,   130,    78,    61
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      65,   140,    68,    69,   138,    71,    30,   -23,    66,    18,
      74,   145,    76,    79,    80,   162,     7,    93,    90,     9,
     127,    18,    18,   158,    14,   141,    31,     8,    99,   101,
     163,    67,    19,     1,   107,     2,   164,   110,   111,   112,
     113,   114,   115,   116,    19,    19,   -23,   105,   121,   122,
      20,   178,    44,   126,   123,    45,    94,    15,   168,    46,
      47,     3,    29,    39,    48,    49,    50,    51,    52,    12,
      53,    23,    54,   180,    55,    22,   136,   124,    25,   188,
      26,   183,    17,    56,    34,    24,   189,    57,   106,    58,
      77,   153,   193,   155,   163,    44,    72,   157,    45,    42,
     164,    43,    46,    47,   103,   161,   104,    48,    49,    50,
      51,    52,    27,    53,    73,    54,    28,    55,   172,   173,
      33,    86,    87,   176,    88,    89,    56,   179,    -2,    10,
      57,     2,    58,    35,   148,    44,   149,   184,    45,   177,
      38,   149,    46,    47,   191,    36,   192,    48,    49,    50,
      51,    52,   186,    53,   149,    54,    40,    55,    16,     7,
      88,    89,    41,    70,    62,    63,    56,    30,    44,    75,
      57,    45,    58,   100,    91,    46,    47,    96,   102,   117,
      48,    49,    50,    51,    52,   118,    53,   120,    54,   125,
      55,   127,   131,   132,   134,   135,   150,   156,   147,    56,
     151,    44,   139,    57,    45,    58,   152,   159,    46,    47,
     144,   160,   167,    48,    49,    50,    51,    52,   171,    53,
     174,    54,   182,    55,   190,   185,    11,   146,    64,   170,
       0,     0,    56,     0,    44,     0,    57,    45,    58,   175,
       0,    46,    47,     0,     0,   137,    48,    49,    50,    51,
      52,     0,    53,     0,    54,     0,    55,     0,     0,   169,
       0,     0,     0,     0,     0,    56,     0,     0,    81,    57,
       0,    58,    82,    83,    84,    85,    86,    87,    97,    88,
      89,    81,     0,     0,     0,    82,    83,    84,    85,    86,
      87,     0,    88,    89,   143,    81,     0,     0,     0,    82,
      83,    84,    85,    86,    87,    92,    88,    89,     0,     0,
      81,     0,     0,     0,    82,    83,    84,    85,    86,    87,
      81,    88,    89,    98,    82,    83,    84,    85,    86,    87,
       0,    88,    89,     0,    81,     0,     0,     0,    82,    83,
      84,    85,    86,    87,    81,    88,    89,     0,    82,    83,
      84,    85,    86,    87,     0,    88,    89,   163,     0,     0,
      81,     0,     0,   164,    82,    83,    84,    85,    86,    87,
       0,    88,    89,     0,    81,     0,     0,   109,    82,    83,
      84,    85,    86,    87,     0,    88,    89,     0,    81,     0,
       0,   187,    82,    83,    84,    85,    86,    87,     0,    88,
      89,    81,     0,   119,     0,    82,    83,    84,    85,    86,
      87,     0,    88,    89,    81,     0,   154,     0,    82,    83,
      84,    85,    86,    87,     0,    88,    89,    81,     0,   194,
       0,    82,    83,    84,    85,    86,    87,    81,    88,    89,
     108,    82,    83,    84,    85,    86,    87,    81,    88,    89,
     133,    82,    83,    84,    85,    86,    87,    81,    88,    89,
     181,    82,    83,    84,    85,    86,    87,   -24,    88,    89,
       0,   -24,   -24,    84,    85,    86,    87,     0,    88,    89
};

static const yytype_int16 yycheck[] =
{
      44,     1,    46,    47,   123,    49,    24,     7,     1,     1,
      54,    15,    56,    57,    58,    25,    41,     7,    62,     0,
      24,     1,     1,   142,     8,    25,    44,    23,    72,    73,
      40,    24,    24,     1,    78,     3,    46,    81,    82,    83,
      84,    85,    86,    87,    24,    24,    46,     1,    92,    93,
      42,   170,     6,    97,     1,     9,    46,    41,   153,    13,
      14,    29,    42,    42,    18,    19,    20,    21,    22,    40,
      24,    15,    26,   172,    28,    23,   120,    24,    43,    25,
      45,   176,    40,    37,    28,    40,   185,    41,    42,    43,
       1,   135,   191,   137,    40,     6,    25,   141,     9,    44,
      46,    46,    13,    14,    40,   149,    42,    18,    19,    20,
      21,    22,    40,    24,    43,    26,    41,    28,   162,   163,
      23,    35,    36,   167,    38,    39,    37,   171,     0,     1,
      41,     3,    43,    45,    44,     6,    46,   181,     9,    44,
      25,    46,    13,    14,   188,    45,   190,    18,    19,    20,
      21,    22,    44,    24,    46,    26,    23,    28,    40,    41,
      38,    39,    23,    23,    41,    45,    37,    24,     6,    43,
      41,     9,    43,    44,    23,    13,    14,    45,    24,    23,
      18,    19,    20,    21,    22,    24,    24,    41,    26,    23,
      28,    24,    45,    40,    39,    43,    23,    23,    40,    37,
      24,     6,    45,    41,     9,    43,    44,    23,    13,    14,
      45,    40,    43,    18,    19,    20,    21,    22,    17,    24,
      24,    26,    45,    28,    41,    23,     5,   128,    43,   156,
      -1,    -1,    37,    -1,     6,    -1,    41,     9,    43,    44,
      -1,    13,    14,    -1,    -1,     4,    18,    19,    20,    21,
      22,    -1,    24,    -1,    26,    -1,    28,    -1,    -1,     5,
      -1,    -1,    -1,    -1,    -1,    37,    -1,    -1,    27,    41,
      -1,    43,    31,    32,    33,    34,    35,    36,    10,    38,
      39,    27,    -1,    -1,    -1,    31,    32,    33,    34,    35,
      36,    -1,    38,    39,    11,    27,    -1,    -1,    -1,    31,
      32,    33,    34,    35,    36,    12,    38,    39,    -1,    -1,
      27,    -1,    -1,    -1,    31,    32,    33,    34,    35,    36,
      27,    38,    39,    16,    31,    32,    33,    34,    35,    36,
      -1,    38,    39,    -1,    27,    -1,    -1,    -1,    31,    32,
      33,    34,    35,    36,    27,    38,    39,    -1,    31,    32,
      33,    34,    35,    36,    -1,    38,    39,    40,    -1,    -1,
      27,    -1,    -1,    46,    31,    32,    33,    34,    35,    36,
      -1,    38,    39,    -1,    27,    -1,    -1,    44,    31,    32,
      33,    34,    35,    36,    -1,    38,    39,    -1,    27,    -1,
      -1,    44,    31,    32,    33,    34,    35,    36,    -1,    38,
      39,    27,    -1,    42,    -1,    31,    32,    33,    34,    35,
      36,    -1,    38,    39,    27,    -1,    42,    -1,    31,    32,
      33,    34,    35,    36,    -1,    38,    39,    27,    -1,    42,
      -1,    31,    32,    33,    34,    35,    36,    27,    38,    39,
      40,    31,    32,    33,    34,    35,    36,    27,    38,    39,
      40,    31,    32,    33,    34,    35,    36,    27,    38,    39,
      40,    31,    32,    33,    34,    35,    36,    27,    38,    39,
      -1,    31,    32,    33,    34,    35,    36,    -1,    38,    39
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     3,    29,    48,    49,    50,    41,    23,     0,
       1,    50,    40,    51,     8,    41,    40,    40,     1,    24,
      42,    52,    23,    51,    40,    43,    45,    40,    41,    42,
      24,    44,    54,    23,    51,    45,    45,    53,    25,    42,
      23,    23,    44,    46,     6,     9,    13,    14,    18,    19,
      20,    21,    22,    24,    26,    28,    37,    41,    43,    59,
      62,    65,    41,    45,    54,    65,     1,    24,    65,    65,
      23,    65,    25,    43,    65,    43,    65,     1,    64,    65,
      65,    27,    31,    32,    33,    34,    35,    36,    38,    39,
      65,    23,    12,     7,    46,    58,    45,    10,    16,    65,
      44,    65,    24,    40,    42,     1,    42,    65,    40,    44,
      65,    65,    65,    65,    65,    65,    65,    23,    24,    42,
      41,    65,    65,     1,    24,    23,    65,    24,    55,    56,
      63,    45,    40,    40,    39,    43,    65,     4,    58,    45,
       1,    25,    57,    11,    45,    15,    56,    40,    44,    46,
      23,    24,    44,    65,    42,    65,    23,    65,    58,    23,
      40,    65,    25,    40,    46,    60,    61,    43,    63,     5,
      57,    17,    65,    65,    24,    44,    65,    44,    58,    65,
      61,    40,    45,    63,    65,    23,    44,    44,    25,    61,
      41,    65,    65,    61,    42
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    47,    48,    49,    49,    49,    49,    50,    50,    50,
      51,    51,    51,    52,    52,    52,    52,    53,    53,    54,
      55,    55,    56,    57,    57,    57,    58,    58,    58,    59,
      59,    60,    61,    61,    61,    62,    62,    63,    63,    64,
      64,    64,    64,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     3,     3,     5,     7,     4,
       0,     3,     3,     8,    10,     3,     5,     0,     3,     3,
       2,     3,     5,     0,     2,     1,     2,     6,     3,     6,
       3,     8,     1,     5,     7,     6,     8,     0,     3,     2,
       3,     3,     2,     3,     5,     7,     7,     9,     3,     5,
       7,     5,     3,     1,     1,     5,     2,     2,     3,     3,
       3,     3,     2,     3,     3,     3,     2,     3,     1,     1,
       1,     1,     3
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
#line 1345 "cool.y.cc"
    break;

  case 3: /* class_list: class ';'  */
#line 146 "cool.y"
                { (yyval.classes) = single_Classes((yyvsp[-1].class_)); }
#line 1351 "cool.y.cc"
    break;

  case 4: /* class_list: ERROR  */
#line 148 "cool.y"
                {  yyclearin;   }
#line 1357 "cool.y.cc"
    break;

  case 5: /* class_list: class_list class ';'  */
#line 150 "cool.y"
                { (yyval.classes) = append_Classes((yyvsp[-2].classes),single_Classes((yyvsp[-1].class_))); }
#line 1363 "cool.y.cc"
    break;

  case 6: /* class_list: class_list error ';'  */
#line 152 "cool.y"
                {  yyclearin;   }
#line 1369 "cool.y.cc"
    break;

  case 7: /* class: CLASS TYPEID '{' feature_list_star '}'  */
#line 158 "cool.y"
                { (yyval.class_) = class_((yyvsp[-3].symbol),idtable.add_string("Object"), (yyvsp[-1].features), stringtable.add_string(curr_filename)); }
#line 1375 "cool.y.cc"
    break;

  case 8: /* class: CLASS TYPEID INHERITS TYPEID '{' feature_list_star '}'  */
#line 160 "cool.y"
                { (yyval.class_) = class_((yyvsp[-5].symbol),(yyvsp[-3].symbol),(yyvsp[-1].features),stringtable.add_string(curr_filename)); }
#line 1381 "cool.y.cc"
    break;

  case 9: /* class: error '{' feature_list_star '}'  */
#line 162 "cool.y"
                {  yyclearin;  }
#line 1387 "cool.y.cc"
    break;

  case 10: /* feature_list_star: %empty  */
#line 168 "cool.y"
                                {  (yyval.features) = nil_Features(); }
#line 1393 "cool.y.cc"
    break;

  case 11: /* feature_list_star: feature_list_star feature_single ';'  */
#line 170 "cool.y"
                                {  (yyval.features) = append_Features((yyvsp[-2].features), single_Features((yyvsp[-1].feature))); }
#line 1399 "cool.y.cc"
    break;

  case 12: /* feature_list_star: feature_list_star error ';'  */
#line 172 "cool.y"
                                {  yyclearin;  }
#line 1405 "cool.y.cc"
    break;

  case 13: /* feature_single: OBJECTID '(' ')' ':' TYPEID '{' expression_single '}'  */
#line 175 "cool.y"
                                {  (yyval.feature) = method((yyvsp[-7].symbol), nil_Formals(), (yyvsp[-3].symbol), (yyvsp[-1].expression));  }
#line 1411 "cool.y.cc"
    break;

  case 14: /* feature_single: OBJECTID '(' formal_single formal_list_star ')' ':' TYPEID '{' expression_single '}'  */
#line 177 "cool.y"
                                {  (yyval.feature) = method((yyvsp[-9].symbol), append_Formals(single_Formals((yyvsp[-7].formal)), (yyvsp[-6].formals)), (yyvsp[-3].symbol), (yyvsp[-1].expression));  }
#line 1417 "cool.y.cc"
    break;

  case 15: /* feature_single: OBJECTID ':' TYPEID  */
#line 179 "cool.y"
                                {  (yyval.feature) = attr((yyvsp[-2].symbol), (yyvsp[0].symbol), no_expr());  }
#line 1423 "cool.y.cc"
    break;

  case 16: /* feature_single: OBJECTID ':' TYPEID ASSIGN expression_single  */
#line 181 "cool.y"
                                {  (yyval.feature) = attr((yyvsp[-4].symbol), (yyvsp[-2].symbol), (yyvsp[0].expression));  }
#line 1429 "cool.y.cc"
    break;

  case 17: /* formal_list_star: %empty  */
#line 186 "cool.y"
                                {  (yyval.formals) = nil_Formals();  }
#line 1435 "cool.y.cc"
    break;

  case 18: /* formal_list_star: formal_list_star ',' formal_single  */
#line 188 "cool.y"
                                {  (yyval.formals) = append_Formals((yyvsp[-2].formals), single_Formals((yyvsp[0].formal)));  }
#line 1441 "cool.y.cc"
    break;

  case 19: /* formal_single: OBJECTID ':' TYPEID  */
#line 191 "cool.y"
                                {  (yyval.formal) = formal((yyvsp[-2].symbol), (yyvsp[0].symbol));  }
#line 1447 "cool.y.cc"
    break;

  case 20: /* case_list_pos: case_single ';'  */
#line 196 "cool.y"
                                {  (yyval.cases) = single_Cases((yyvsp[-1].case_));  }
#line 1453 "cool.y.cc"
    break;

  case 21: /* case_list_pos: case_list_pos case_single ';'  */
#line 198 "cool.y"
                                {  (yyval.cases) = append_Cases((yyvsp[-2].cases), single_Cases((yyvsp[-1].case_)));  }
#line 1459 "cool.y.cc"
    break;

  case 22: /* case_single: OBJECTID ':' TYPEID DARROW expression_single  */
#line 201 "cool.y"
                                {  (yyval.case_) = branch((yyvsp[-4].symbol), (yyvsp[-2].symbol), (yyvsp[0].expression));  }
#line 1465 "cool.y.cc"
    break;

  case 23: /* let_no_expr_helper: %empty  */
#line 210 "cool.y"
                                {  (yyval.expression) = no_expr();  }
#line 1471 "cool.y.cc"
    break;

  case 24: /* let_no_expr_helper: ASSIGN expression_single  */
#line 212 "cool.y"
                                {  (yyval.expression) = (yyvsp[0].expression);  }
#line 1477 "cool.y.cc"
    break;

  case 25: /* let_no_expr_helper: error  */
#line 214 "cool.y"
                                {  yyclearin;  }
#line 1483 "cool.y.cc"
    break;

  case 26: /* let_expand: IN expression_single  */
#line 219 "cool.y"
                                {  (yyval.expression) = (yyvsp[0].expression);  }
#line 1489 "cool.y.cc"
    break;

  case 27: /* let_expand: ',' OBJECTID ':' TYPEID let_no_expr_helper let_expand  */
#line 221 "cool.y"
                                {  (yyval.expression) = let((yyvsp[-4].symbol), (yyvsp[-2].symbol), (yyvsp[-1].expression),  (yyvsp[0].expression));  }
#line 1495 "cool.y.cc"
    break;

  case 28: /* let_expand: ',' error let_expand  */
#line 223 "cool.y"
                                {  yyclearin;  }
#line 1501 "cool.y.cc"
    break;

  case 29: /* let_begin: LET OBJECTID ':' TYPEID let_no_expr_helper let_expand  */
#line 227 "cool.y"
                                {  (yyval.expression) = let((yyvsp[-4].symbol), (yyvsp[-2].symbol), (yyvsp[-1].expression), (yyvsp[0].expression));  }
#line 1507 "cool.y.cc"
    break;

  case 30: /* let_begin: LET error let_expand  */
#line 229 "cool.y"
                                {  yyclearin;  }
#line 1513 "cool.y.cc"
    break;

  case 31: /* for_second: ';' expression_single ';' expression_single ')' '{' expression_single '}'  */
#line 234 "cool.y"
                                {  (yyval.expression) = loop((yyvsp[-6].expression), block(append_Expressions(single_Expressions((yyvsp[-1].expression)), single_Expressions((yyvsp[-4].expression)))));  }
#line 1519 "cool.y.cc"
    break;

  case 32: /* for_expand: for_second  */
#line 237 "cool.y"
                                {  (yyval.expression) = (yyvsp[0].expression);  }
#line 1525 "cool.y.cc"
    break;

  case 33: /* for_expand: ',' OBJECTID ':' TYPEID for_expand  */
#line 239 "cool.y"
                                {  (yyval.expression) = let((yyvsp[-3].symbol), (yyvsp[-1].symbol), no_expr(), (yyvsp[0].expression));  }
#line 1531 "cool.y.cc"
    break;

  case 34: /* for_expand: ',' OBJECTID ':' TYPEID ASSIGN expression_single for_expand  */
#line 241 "cool.y"
                                {  (yyval.expression) = let((yyvsp[-5].symbol), (yyvsp[-3].symbol), (yyvsp[-1].expression), (yyvsp[0].expression));  }
#line 1537 "cool.y.cc"
    break;

  case 35: /* for_begin: FOR '(' OBJECTID ':' TYPEID for_expand  */
#line 244 "cool.y"
                                {  (yyval.expression) = let((yyvsp[-3].symbol), (yyvsp[-1].symbol), no_expr(), (yyvsp[0].expression));  }
#line 1543 "cool.y.cc"
    break;

  case 36: /* for_begin: FOR '(' OBJECTID ':' TYPEID ASSIGN expression_single for_expand  */
#line 246 "cool.y"
                                {  (yyval.expression) = let((yyvsp[-5].symbol), (yyvsp[-3].symbol), (yyvsp[-1].expression), (yyvsp[0].expression));  }
#line 1549 "cool.y.cc"
    break;

  case 37: /* expression_list_star: %empty  */
#line 252 "cool.y"
                                {  (yyval.expressions) = nil_Expressions();  }
#line 1555 "cool.y.cc"
    break;

  case 38: /* expression_list_star: expression_list_star ',' expression_single  */
#line 254 "cool.y"
                                {  (yyval.expressions) = append_Expressions((yyvsp[-2].expressions), single_Expressions((yyvsp[0].expression)));  }
#line 1561 "cool.y.cc"
    break;

  case 39: /* expression_list_pos: expression_single ';'  */
#line 258 "cool.y"
                                {  (yyval.expressions) = single_Expressions((yyvsp[-1].expression));  }
#line 1567 "cool.y.cc"
    break;

  case 40: /* expression_list_pos: expression_list_pos expression_single ';'  */
#line 260 "cool.y"
                                {  (yyval.expressions) = append_Expressions((yyvsp[-2].expressions), single_Expressions((yyvsp[-1].expression)));  }
#line 1573 "cool.y.cc"
    break;

  case 41: /* expression_list_pos: expression_list_pos error ';'  */
#line 262 "cool.y"
                                {  yyclearin;  }
#line 1579 "cool.y.cc"
    break;

  case 42: /* expression_list_pos: error ';'  */
#line 264 "cool.y"
                                {  yyclearin;  }
#line 1585 "cool.y.cc"
    break;

  case 43: /* expression_single: OBJECTID ASSIGN expression_single  */
#line 268 "cool.y"
                                {  (yyval.expression) = assign((yyvsp[-2].symbol), (yyvsp[0].expression));  }
#line 1591 "cool.y.cc"
    break;

  case 44: /* expression_single: expression_single '.' OBJECTID '(' ')'  */
#line 270 "cool.y"
                                {  (yyval.expression) = dispatch((yyvsp[-4].expression), (yyvsp[-2].symbol), nil_Expressions());  }
#line 1597 "cool.y.cc"
    break;

  case 45: /* expression_single: expression_single '.' OBJECTID '(' expression_single expression_list_star ')'  */
#line 272 "cool.y"
                                {  (yyval.expression) = dispatch((yyvsp[-6].expression), (yyvsp[-4].symbol), append_Expressions(single_Expressions((yyvsp[-2].expression)), (yyvsp[-1].expressions)));  }
#line 1603 "cool.y.cc"
    break;

  case 46: /* expression_single: expression_single '@' TYPEID '.' OBJECTID '(' ')'  */
#line 274 "cool.y"
                                {  (yyval.expression) = static_dispatch((yyvsp[-6].expression), (yyvsp[-4].symbol), (yyvsp[-2].symbol), nil_Expressions());  }
#line 1609 "cool.y.cc"
    break;

  case 47: /* expression_single: expression_single '@' TYPEID '.' OBJECTID '(' expression_single expression_list_star ')'  */
#line 276 "cool.y"
                                {  (yyval.expression) = static_dispatch((yyvsp[-8].expression), (yyvsp[-6].symbol), (yyvsp[-4].symbol), append_Expressions(single_Expressions((yyvsp[-2].expression)), (yyvsp[-1].expressions)));  }
#line 1615 "cool.y.cc"
    break;

  case 48: /* expression_single: OBJECTID '(' ')'  */
#line 278 "cool.y"
                                {  (yyval.expression) = dispatch(object(idtable.add_string("self")), (yyvsp[-2].symbol), nil_Expressions());  }
#line 1621 "cool.y.cc"
    break;

  case 49: /* expression_single: OBJECTID '(' expression_single expression_list_star ')'  */
#line 280 "cool.y"
                                {  (yyval.expression) = dispatch(object(idtable.add_string("self")), (yyvsp[-4].symbol), append_Expressions(single_Expressions((yyvsp[-2].expression)), (yyvsp[-1].expressions)));  }
#line 1627 "cool.y.cc"
    break;

  case 50: /* expression_single: IF expression_single THEN expression_single ELSE expression_single FI  */
#line 282 "cool.y"
                                {  (yyval.expression) = cond((yyvsp[-5].expression), (yyvsp[-3].expression), (yyvsp[-1].expression));  }
#line 1633 "cool.y.cc"
    break;

  case 51: /* expression_single: WHILE expression_single LOOP expression_single POOL  */
#line 284 "cool.y"
                                {  (yyval.expression) = loop((yyvsp[-3].expression), (yyvsp[-1].expression));  }
#line 1639 "cool.y.cc"
    break;

  case 52: /* expression_single: '{' expression_list_pos '}'  */
#line 286 "cool.y"
                                {  (yyval.expression) = block((yyvsp[-1].expressions));  }
#line 1645 "cool.y.cc"
    break;

  case 53: /* expression_single: let_begin  */
#line 288 "cool.y"
                                {  (yyval.expression) = (yyvsp[0].expression); }
#line 1651 "cool.y.cc"
    break;

  case 54: /* expression_single: for_begin  */
#line 290 "cool.y"
                                {  (yyval.expression) = (yyvsp[0].expression); }
#line 1657 "cool.y.cc"
    break;

  case 55: /* expression_single: CASE expression_single OF case_list_pos ESAC  */
#line 292 "cool.y"
                                {  (yyval.expression) = typcase((yyvsp[-3].expression), (yyvsp[-1].cases));  }
#line 1663 "cool.y.cc"
    break;

  case 56: /* expression_single: NEW TYPEID  */
#line 294 "cool.y"
                                {  (yyval.expression) = new_((yyvsp[0].symbol));  }
#line 1669 "cool.y.cc"
    break;

  case 57: /* expression_single: ISVOID expression_single  */
#line 296 "cool.y"
                                {  (yyval.expression) = isvoid((yyvsp[0].expression));  }
#line 1675 "cool.y.cc"
    break;

  case 58: /* expression_single: expression_single '+' expression_single  */
#line 298 "cool.y"
                                {  (yyval.expression) = plus((yyvsp[-2].expression), (yyvsp[0].expression));  }
#line 1681 "cool.y.cc"
    break;

  case 59: /* expression_single: expression_single '-' expression_single  */
#line 300 "cool.y"
                                {  (yyval.expression) = sub((yyvsp[-2].expression), (yyvsp[0].expression));  }
#line 1687 "cool.y.cc"
    break;

  case 60: /* expression_single: expression_single '*' expression_single  */
#line 302 "cool.y"
                                {  (yyval.expression) = mul((yyvsp[-2].expression), (yyvsp[0].expression));  }
#line 1693 "cool.y.cc"
    break;

  case 61: /* expression_single: expression_single '/' expression_single  */
#line 304 "cool.y"
                                {  (yyval.expression) = divide((yyvsp[-2].expression), (yyvsp[0].expression));  }
#line 1699 "cool.y.cc"
    break;

  case 62: /* expression_single: '~' expression_single  */
#line 306 "cool.y"
                                {  (yyval.expression) = neg((yyvsp[0].expression));  }
#line 1705 "cool.y.cc"
    break;

  case 63: /* expression_single: expression_single '<' expression_single  */
#line 308 "cool.y"
                                {  (yyval.expression) = lt((yyvsp[-2].expression), (yyvsp[0].expression));  }
#line 1711 "cool.y.cc"
    break;

  case 64: /* expression_single: expression_single LE expression_single  */
#line 310 "cool.y"
                                {  (yyval.expression) = leq((yyvsp[-2].expression), (yyvsp[0].expression));  }
#line 1717 "cool.y.cc"
    break;

  case 65: /* expression_single: expression_single '=' expression_single  */
#line 312 "cool.y"
                                {  (yyval.expression) = eq((yyvsp[-2].expression), (yyvsp[0].expression));  }
#line 1723 "cool.y.cc"
    break;

  case 66: /* expression_single: NOT expression_single  */
#line 314 "cool.y"
                                {  (yyval.expression) = comp((yyvsp[0].expression));  }
#line 1729 "cool.y.cc"
    break;

  case 67: /* expression_single: '(' expression_single ')'  */
#line 316 "cool.y"
                                {  (yyval.expression) = (yyvsp[-1].expression);  }
#line 1735 "cool.y.cc"
    break;

  case 68: /* expression_single: OBJECTID  */
#line 318 "cool.y"
                                {  (yyval.expression) = object((yyvsp[0].symbol));  }
#line 1741 "cool.y.cc"
    break;

  case 69: /* expression_single: INT_CONST  */
#line 320 "cool.y"
                                {  (yyval.expression) = int_const((yyvsp[0].symbol));  }
#line 1747 "cool.y.cc"
    break;

  case 70: /* expression_single: STR_CONST  */
#line 322 "cool.y"
                                {  (yyval.expression) = string_const((yyvsp[0].symbol));  }
#line 1753 "cool.y.cc"
    break;

  case 71: /* expression_single: BOOL_CONST  */
#line 324 "cool.y"
                                {  (yyval.expression) = bool_const((yyvsp[0].boolean));  }
#line 1759 "cool.y.cc"
    break;

  case 72: /* expression_single: '{' error '}'  */
#line 326 "cool.y"
                                {  yyclearin;  }
#line 1765 "cool.y.cc"
    break;


#line 1769 "cool.y.cc"

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

#line 330 "cool.y"


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
