/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         parserparse
#define yylex           parserlex
#define yyerror         parsererror
#define yydebug         parserdebug
#define yynerrs         parsernerrs

#define yylval          parserlval
#define yychar          parserchar
#define yylloc          parserlloc

/* Copy the first part of user declarations.  */
#line 30 "src/parser.y" /* yacc.c:339  */


#include <sys/types.h>
#include <sys/stat.h>
#ifndef _MSC_VER
#include <unistd.h>
#endif

#include "typedefs.h"
#include "module.h"
#include "expression.h"
#include "value.h"
#include "function.h"
#include "printutils.h"
#include "memory.h"
#include <sstream>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

#include "boosty.h"

#define YYMAXDEPTH 20000

int parser_error_pos = -1;

int parserlex(void);
void yyerror(char const *s);

int lexerget_lineno(void);
fs::path sourcefile(void);
int lexerlex_destroy(void);
int lexerlex(void);

std::stack<LocalScope *> scope_stack;
FileModule *rootmodule;

extern void lexerdestroy();
extern FILE *lexerin;
extern const char *parser_input_buffer;
const char *parser_input_buffer;
fs::path parser_sourcefile;
extern std::vector<fs::path> filename_stack;

#line 120 "parser.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.tab.h".  */
#ifndef YY_PARSER_PARSER_TAB_H_INCLUDED
# define YY_PARSER_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int parserdebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TOK_ERROR = 258,
    TOK_MODULE = 259,
    TOK_FUNCTION = 260,
    TOK_IF = 261,
    TOK_ELSE = 262,
    TOK_FOR = 263,
    TOK_LET = 264,
    TOK_EACH = 265,
    TOK_ID = 266,
    TOK_STRING = 267,
    TOK_USE = 268,
    TOK_NUMBER = 269,
    TOK_TRUE = 270,
    TOK_FALSE = 271,
    TOK_UNDEF = 272,
    LE = 273,
    GE = 274,
    EQ = 275,
    NE = 276,
    AND = 277,
    OR = 278,
    LET = 279
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 75 "src/parser.y" /* yacc.c:355  */

  char *text;
  double number;
  class Value *value;
  class Expression *expr;
  class ModuleInstantiation *inst;
  class IfElseModuleInstantiation *ifelse;
  Assignment *arg;
  AssignmentList *args;

#line 196 "parser.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE parserlval;
extern YYLTYPE parserlloc;
int parserparse (void);

#endif /* !YY_PARSER_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 225 "parser.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  35
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   650

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  96
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  198

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   279

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    29,     2,    44,     2,    34,     2,     2,
      41,    42,    32,    30,    45,    31,    37,    33,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    26,    38,
      27,    43,    28,    25,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    35,     2,    36,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    39,     2,    40,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   144,   144,   146,   145,   151,   155,   156,   157,   161,
     163,   162,   176,   175,   185,   187,   191,   209,   214,   219,
     224,   230,   229,   239,   246,   251,   250,   263,   262,   276,
     278,   279,   283,   284,   285,   293,   294,   295,   296,   300,
     314,   318,   322,   326,   331,   336,   341,   345,   350,   354,
     358,   362,   366,   370,   374,   378,   382,   386,   390,   394,
     398,   402,   406,   410,   414,   418,   422,   426,   430,   434,
     438,   442,   453,   458,   462,   475,   481,   485,   493,   494,
     501,   502,   506,   507,   511,   515,   519,   528,   531,   537,
     546,   551,   560,   563,   569,   578,   582
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOK_ERROR", "TOK_MODULE",
  "TOK_FUNCTION", "TOK_IF", "TOK_ELSE", "TOK_FOR", "TOK_LET", "TOK_EACH",
  "TOK_ID", "TOK_STRING", "TOK_USE", "TOK_NUMBER", "TOK_TRUE", "TOK_FALSE",
  "TOK_UNDEF", "LE", "GE", "EQ", "NE", "AND", "OR", "LET", "'?'", "':'",
  "'<'", "'>'", "'!'", "'+'", "'-'", "'*'", "'/'", "'%'", "'['", "']'",
  "'.'", "';'", "'{'", "'}'", "'('", "')'", "'='", "'#'", "','", "$accept",
  "input", "$@1", "statement", "$@2", "$@3", "inner_input", "assignment",
  "module_instantiation", "@4", "ifelse_statement", "$@5", "if_statement",
  "@6", "child_statements", "child_statement", "module_id",
  "single_module_instantiation", "expr", "list_comprehension_elements",
  "list_comprehension_elements_p", "list_comprehension_elements_or_expr",
  "optional_commas", "vector_expr", "arguments_decl", "argument_decl",
  "arguments_call", "argument_call", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,    63,    58,    60,    62,    33,
      43,    45,    42,    47,    37,    91,    93,    46,    59,   123,
     125,    40,    41,    61,    35,    44
};
# endif

#define YYPACT_NINF -69

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-69)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     164,    -8,    20,   -28,   -69,   -69,   -69,     5,   -69,     6,
       6,     6,   -69,   175,     6,    37,   164,   -69,   -69,   -69,
      72,    17,   -69,    41,    42,   286,   286,   164,   -69,   -69,
     -69,   -69,   175,    49,   -69,   -69,   -69,   -69,   314,   240,
      79,    79,    52,    55,   -69,   -69,   -69,   -69,   -69,   286,
     286,   286,   212,   286,   338,   413,   -69,   -69,   -69,   240,
       8,   555,   -23,   -69,   -69,   -69,   -69,   -69,    56,    47,
     -69,    47,   314,   314,     9,     9,     9,    57,    60,    61,
     104,    63,   475,   -69,    70,    64,   363,   286,   286,   286,
     286,   286,   286,   286,   286,   286,   286,   286,   286,   286,
     286,   286,   100,   -69,   -69,   -69,   286,   -69,    63,   226,
     286,    63,    75,    81,   -22,   -12,   286,   314,   314,   277,
     555,   -69,   -69,   -69,   -69,   286,   -69,    63,    88,   -69,
     613,   613,   157,   157,   595,   575,   495,   613,   613,     9,
       9,    51,    51,    51,   515,   -69,   240,   555,   314,   -69,
     -69,   -69,   555,    79,   -69,    82,   286,   -69,   388,    -6,
      14,    85,   455,   104,   -69,   286,   -69,   -69,   -69,   -69,
     175,   286,   555,   104,   286,   104,   104,   -69,   286,   -69,
     -69,   555,   -69,   555,   122,   434,   -69,   -69,   535,    92,
     104,   314,   -69,   -69,   -69,    35,   104,   -69
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     0,    36,    37,    38,    35,     3,     0,
       0,     0,     6,    14,     0,     0,     2,     9,     8,    23,
      24,     0,    21,     0,     0,     0,     0,     2,    35,    17,
      20,    19,    14,     0,    18,     1,     5,    25,    92,     0,
      87,    87,     0,    43,    45,    46,    40,    41,    42,     0,
       0,     0,    83,     0,     0,     0,     4,    15,     7,     0,
      43,    95,     0,    93,    32,    29,    34,    22,    90,    83,
      88,    83,    92,    92,    67,    65,    66,     0,     0,     0,
       0,    83,    84,    85,     0,    83,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    27,    16,    26,     0,    39,    83,     0,
       0,    83,     0,     0,     0,     0,     0,    92,    92,     0,
      81,    78,    80,    73,    82,     0,    50,    83,     0,    68,
      58,    61,    59,    60,    63,    64,     0,    57,    62,    55,
      56,    52,    53,    54,     0,    44,     0,    96,     0,    33,
      31,    30,    91,    82,    10,     0,     0,    71,     0,     0,
       0,     0,     0,    82,    51,     0,    70,    28,    94,    89,
       0,     0,    47,     0,     0,     0,     0,    79,     0,    48,
      86,    69,    11,    12,    76,     0,    74,    72,     0,     0,
       0,    92,    49,    13,    77,     0,     0,    75
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -69,     2,   -69,   -11,   -69,   -69,   105,    23,    -5,   -69,
     -69,   -69,   -69,   -69,   -69,   -49,   -69,   -69,   -25,   -41,
     -40,   -68,   -24,   -69,   101,   -10,   -65,    -4
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    15,    27,    16,   170,   189,    33,    17,    18,    39,
      19,    59,    20,   146,   109,    67,    21,    22,    61,   121,
     122,   123,    84,    85,    69,    70,    62,    63
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      54,    55,    32,    23,    29,    30,    31,   114,   115,    34,
     105,    83,     3,    25,     4,     5,     6,    28,    36,   107,
     156,    32,   108,   108,    74,    75,    76,    82,    86,    56,
     157,    24,   174,   108,    66,     9,   175,    35,    10,   108,
      11,    98,    99,   100,   101,   112,   102,   113,    26,    73,
      14,   106,   159,   160,    66,   120,   176,   124,    38,   108,
     151,   128,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   196,   161,    37,
     108,   147,    40,    41,   148,   152,   101,   153,   102,    58,
      68,   158,   111,    72,    86,   180,    73,   167,   116,   110,
     162,   117,   118,   163,    66,   184,   126,   186,    81,   127,
      77,   145,    78,    79,    80,    43,    44,   154,    45,    46,
      47,    48,   194,   155,   164,   171,   195,   177,   197,   190,
     193,   172,   150,    49,    50,    51,   187,    57,   120,    52,
     181,    66,    71,   169,   168,   119,   183,     0,   120,   185,
     120,   172,     0,   188,     0,     0,     0,     0,     0,   182,
       0,     0,     0,     0,     0,   120,     0,     0,     1,     2,
       3,   120,     4,     5,     6,     7,     0,     8,     0,     1,
       2,     3,     0,     4,     5,     6,     7,    96,    97,    98,
      99,   100,   101,     9,   102,     0,    10,     0,    11,     0,
       0,     0,    12,    13,     9,     0,     0,    10,    14,    11,
       0,     0,     0,    12,    13,     0,     0,     0,    77,    14,
      78,    79,    80,    43,    44,     0,    45,    46,    47,    48,
       0,     0,     3,     0,     4,     5,     6,     7,     0,     0,
       0,    49,    50,    51,     0,     0,     3,    52,     4,     5,
       6,    28,     0,    53,     0,     9,     0,    81,    10,     0,
      11,     0,     0,     0,    64,    65,   149,     0,     0,     9,
      14,     0,    10,     0,    11,     0,     0,     0,    64,    65,
       0,     0,     0,    77,    14,    78,    79,    80,    43,    44,
       0,    45,    46,    47,    48,    42,     0,    43,    44,     0,
      45,    46,    47,    48,     0,     0,    49,    50,    51,     0,
       0,     0,    52,     0,     0,    49,    50,    51,    53,     0,
       0,    52,     0,    42,     0,    60,    44,    53,    45,    46,
      47,    48,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    49,    50,    51,     0,     0,     0,    52,
       0,     0,     0,     0,     0,    53,    87,    88,    89,    90,
      91,    92,     0,    93,     0,    94,    95,     0,    96,    97,
      98,    99,   100,   101,     0,   102,     0,     0,     0,     0,
     103,    87,    88,    89,    90,    91,    92,     0,    93,     0,
      94,    95,     0,    96,    97,    98,    99,   100,   101,     0,
     102,     0,     0,     0,     0,   129,    87,    88,    89,    90,
      91,    92,     0,    93,     0,    94,    95,     0,    96,    97,
      98,    99,   100,   101,     0,   102,     0,     0,     0,     0,
     173,    87,    88,    89,    90,    91,    92,     0,    93,     0,
      94,    95,     0,    96,    97,    98,    99,   100,   101,     0,
     102,   104,    87,    88,    89,    90,    91,    92,     0,    93,
       0,    94,    95,     0,    96,    97,    98,    99,   100,   101,
       0,   102,   191,    87,    88,    89,    90,    91,    92,     0,
      93,   178,    94,    95,     0,    96,    97,    98,    99,   100,
     101,   179,   102,    87,    88,    89,    90,    91,    92,     0,
      93,   125,    94,    95,     0,    96,    97,    98,    99,   100,
     101,     0,   102,    87,    88,    89,    90,    91,    92,     0,
      93,   165,    94,    95,     0,    96,    97,    98,    99,   100,
     101,     0,   102,    87,    88,    89,    90,    91,    92,     0,
      93,     0,    94,    95,     0,    96,    97,    98,    99,   100,
     101,   166,   102,    87,    88,    89,    90,    91,    92,     0,
      93,     0,    94,    95,     0,    96,    97,    98,    99,   100,
     101,   192,   102,    87,    88,    89,    90,    91,    92,     0,
      93,     0,    94,    95,     0,    96,    97,    98,    99,   100,
     101,     0,   102,    87,    88,    89,    90,    91,     0,     0,
       0,     0,    94,    95,     0,    96,    97,    98,    99,   100,
     101,     0,   102,    87,    88,    89,    90,     0,     0,     0,
       0,     0,    94,    95,     0,    96,    97,    98,    99,   100,
     101,     0,   102,    89,    90,     0,     0,     0,     0,     0,
       0,     0,     0,    96,    97,    98,    99,   100,   101,     0,
     102
};

static const yytype_int16 yycheck[] =
{
      25,    26,    13,    11,     9,    10,    11,    72,    73,    14,
      59,    52,     6,    41,     8,     9,    10,    11,    16,    42,
      42,    32,    45,    45,    49,    50,    51,    52,    53,    27,
      42,    11,    38,    45,    39,    29,    42,     0,    32,    45,
      34,    32,    33,    34,    35,    69,    37,    71,    43,    41,
      44,    43,   117,   118,    59,    80,    42,    81,    41,    45,
     109,    85,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,    42,   119,     7,
      45,   106,    41,    41,   108,   110,    35,   111,    37,    40,
      11,   116,    45,    41,   119,   163,    41,   146,    41,    43,
     125,    41,    41,   127,   109,   173,    36,   175,    45,    45,
       6,    11,     8,     9,    10,    11,    12,    42,    14,    15,
      16,    17,   190,    42,    36,    43,   191,    42,   196,     7,
      38,   156,   109,    29,    30,    31,   176,    32,   163,    35,
     165,   146,    41,   153,   148,    41,   171,    -1,   173,   174,
     175,   176,    -1,   178,    -1,    -1,    -1,    -1,    -1,   170,
      -1,    -1,    -1,    -1,    -1,   190,    -1,    -1,     4,     5,
       6,   196,     8,     9,    10,    11,    -1,    13,    -1,     4,
       5,     6,    -1,     8,     9,    10,    11,    30,    31,    32,
      33,    34,    35,    29,    37,    -1,    32,    -1,    34,    -1,
      -1,    -1,    38,    39,    29,    -1,    -1,    32,    44,    34,
      -1,    -1,    -1,    38,    39,    -1,    -1,    -1,     6,    44,
       8,     9,    10,    11,    12,    -1,    14,    15,    16,    17,
      -1,    -1,     6,    -1,     8,     9,    10,    11,    -1,    -1,
      -1,    29,    30,    31,    -1,    -1,     6,    35,     8,     9,
      10,    11,    -1,    41,    -1,    29,    -1,    45,    32,    -1,
      34,    -1,    -1,    -1,    38,    39,    40,    -1,    -1,    29,
      44,    -1,    32,    -1,    34,    -1,    -1,    -1,    38,    39,
      -1,    -1,    -1,     6,    44,     8,     9,    10,    11,    12,
      -1,    14,    15,    16,    17,     9,    -1,    11,    12,    -1,
      14,    15,    16,    17,    -1,    -1,    29,    30,    31,    -1,
      -1,    -1,    35,    -1,    -1,    29,    30,    31,    41,    -1,
      -1,    35,    -1,     9,    -1,    11,    12,    41,    14,    15,
      16,    17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    29,    30,    31,    -1,    -1,    -1,    35,
      -1,    -1,    -1,    -1,    -1,    41,    18,    19,    20,    21,
      22,    23,    -1,    25,    -1,    27,    28,    -1,    30,    31,
      32,    33,    34,    35,    -1,    37,    -1,    -1,    -1,    -1,
      42,    18,    19,    20,    21,    22,    23,    -1,    25,    -1,
      27,    28,    -1,    30,    31,    32,    33,    34,    35,    -1,
      37,    -1,    -1,    -1,    -1,    42,    18,    19,    20,    21,
      22,    23,    -1,    25,    -1,    27,    28,    -1,    30,    31,
      32,    33,    34,    35,    -1,    37,    -1,    -1,    -1,    -1,
      42,    18,    19,    20,    21,    22,    23,    -1,    25,    -1,
      27,    28,    -1,    30,    31,    32,    33,    34,    35,    -1,
      37,    38,    18,    19,    20,    21,    22,    23,    -1,    25,
      -1,    27,    28,    -1,    30,    31,    32,    33,    34,    35,
      -1,    37,    38,    18,    19,    20,    21,    22,    23,    -1,
      25,    26,    27,    28,    -1,    30,    31,    32,    33,    34,
      35,    36,    37,    18,    19,    20,    21,    22,    23,    -1,
      25,    26,    27,    28,    -1,    30,    31,    32,    33,    34,
      35,    -1,    37,    18,    19,    20,    21,    22,    23,    -1,
      25,    26,    27,    28,    -1,    30,    31,    32,    33,    34,
      35,    -1,    37,    18,    19,    20,    21,    22,    23,    -1,
      25,    -1,    27,    28,    -1,    30,    31,    32,    33,    34,
      35,    36,    37,    18,    19,    20,    21,    22,    23,    -1,
      25,    -1,    27,    28,    -1,    30,    31,    32,    33,    34,
      35,    36,    37,    18,    19,    20,    21,    22,    23,    -1,
      25,    -1,    27,    28,    -1,    30,    31,    32,    33,    34,
      35,    -1,    37,    18,    19,    20,    21,    22,    -1,    -1,
      -1,    -1,    27,    28,    -1,    30,    31,    32,    33,    34,
      35,    -1,    37,    18,    19,    20,    21,    -1,    -1,    -1,
      -1,    -1,    27,    28,    -1,    30,    31,    32,    33,    34,
      35,    -1,    37,    20,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    -1,
      37
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,     6,     8,     9,    10,    11,    13,    29,
      32,    34,    38,    39,    44,    47,    49,    53,    54,    56,
      58,    62,    63,    11,    11,    41,    43,    48,    11,    54,
      54,    54,    49,    52,    54,     0,    47,     7,    41,    55,
      41,    41,     9,    11,    12,    14,    15,    16,    17,    29,
      30,    31,    35,    41,    64,    64,    47,    52,    40,    57,
      11,    64,    72,    73,    38,    39,    54,    61,    11,    70,
      71,    70,    41,    41,    64,    64,    64,     6,     8,     9,
      10,    45,    64,    65,    68,    69,    64,    18,    19,    20,
      21,    22,    23,    25,    27,    28,    30,    31,    32,    33,
      34,    35,    37,    42,    38,    61,    43,    42,    45,    60,
      43,    45,    68,    68,    72,    72,    41,    41,    41,    41,
      64,    65,    66,    67,    68,    26,    36,    45,    68,    42,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    11,    59,    64,    68,    40,
      53,    61,    64,    68,    42,    42,    42,    42,    64,    72,
      72,    65,    64,    68,    36,    26,    36,    61,    73,    71,
      50,    43,    64,    42,    38,    42,    42,    42,    26,    36,
      67,    64,    49,    64,    67,    64,    67,    66,    64,    51,
       7,    38,    36,    38,    67,    72,    42,    67
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    46,    47,    48,    47,    47,    49,    49,    49,    49,
      50,    49,    51,    49,    52,    52,    53,    54,    54,    54,
      54,    55,    54,    54,    56,    57,    56,    59,    58,    60,
      60,    60,    61,    61,    61,    62,    62,    62,    62,    63,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    65,    65,    65,    65,    65,    65,    66,    66,
      67,    67,    68,    68,    69,    69,    69,    70,    70,    70,
      71,    71,    72,    72,    72,    73,    73
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     0,     3,     2,     1,     3,     1,     1,
       0,     8,     0,    10,     0,     2,     4,     2,     2,     2,
       2,     0,     3,     1,     1,     0,     4,     0,     6,     0,
       2,     2,     1,     3,     1,     1,     1,     1,     1,     4,
       1,     1,     1,     1,     3,     1,     1,     5,     5,     7,
       3,     4,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     2,     3,     5,
       4,     4,     5,     2,     5,     9,     5,     7,     1,     3,
       1,     1,     2,     0,     1,     1,     4,     0,     1,     4,
       1,     3,     0,     1,     4,     1,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
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
| yyreduce -- Do a reduction.  |
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

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
#line 146 "src/parser.y" /* yacc.c:1646  */
    {
              rootmodule->registerUse(std::string((yyvsp[0].text)));
              free((yyvsp[0].text));
            }
#line 1623 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 158 "src/parser.y" /* yacc.c:1646  */
    {
                if ((yyvsp[0].inst)) scope_stack.top()->addChild((yyvsp[0].inst));
            }
#line 1631 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 163 "src/parser.y" /* yacc.c:1646  */
    {
                Module *newmodule = new Module();
                newmodule->definition_arguments = *(yyvsp[-2].args);
                scope_stack.top()->modules[(yyvsp[-4].text)] = newmodule;
                scope_stack.push(&newmodule->scope);
                free((yyvsp[-4].text));
                delete (yyvsp[-2].args);
            }
#line 1644 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 172 "src/parser.y" /* yacc.c:1646  */
    {
                scope_stack.pop();
            }
#line 1652 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 176 "src/parser.y" /* yacc.c:1646  */
    {
                Function *func = Function::create((yyvsp[-6].text), *(yyvsp[-4].args), (yyvsp[0].expr));
                scope_stack.top()->functions[(yyvsp[-6].text)] = func;
                free((yyvsp[-6].text));
                delete (yyvsp[-4].args);
            }
#line 1663 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 192 "src/parser.y" /* yacc.c:1646  */
    {
                bool found = false;
                for (auto& iter : scope_stack.top()->assignments) {
                    if (iter.first == (yyvsp[-3].text)) {
                        iter.second = shared_ptr<Expression>((yyvsp[-1].expr));
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    scope_stack.top()->assignments.push_back(Assignment((yyvsp[-3].text), shared_ptr<Expression>((yyvsp[-1].expr))));
                }
                free((yyvsp[-3].text));
            }
#line 1682 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 210 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.inst) = (yyvsp[0].inst);
                if ((yyval.inst)) (yyval.inst)->tag_root = true;
            }
#line 1691 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 215 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.inst) = (yyvsp[0].inst);
                if ((yyval.inst)) (yyval.inst)->tag_highlight = true;
            }
#line 1700 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 220 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.inst) = (yyvsp[0].inst);
                if ((yyval.inst)) (yyval.inst)->tag_background = true;
            }
#line 1709 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 225 "src/parser.y" /* yacc.c:1646  */
    {
                delete (yyvsp[0].inst);
                (yyval.inst) = NULL;
            }
#line 1718 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 230 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.inst) = (yyvsp[0].inst);
                scope_stack.push(&(yyvsp[0].inst)->scope);
            }
#line 1727 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 235 "src/parser.y" /* yacc.c:1646  */
    {
                scope_stack.pop();
                (yyval.inst) = (yyvsp[-1].inst);
            }
#line 1736 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 240 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.inst) = (yyvsp[0].ifelse);
            }
#line 1744 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 247 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.ifelse) = (yyvsp[0].ifelse);
            }
#line 1752 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 251 "src/parser.y" /* yacc.c:1646  */
    {
                scope_stack.push(&(yyvsp[-1].ifelse)->else_scope);
            }
#line 1760 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 255 "src/parser.y" /* yacc.c:1646  */
    {
                scope_stack.pop();
                (yyval.ifelse) = (yyvsp[-3].ifelse);
            }
#line 1769 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 263 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.ifelse) = new IfElseModuleInstantiation();
                (yyval.ifelse)->arguments.push_back(Assignment("", shared_ptr<Expression>((yyvsp[-1].expr))));
                (yyval.ifelse)->setPath(boosty::stringy(parser_sourcefile.parent_path()));
                scope_stack.push(&(yyval.ifelse)->scope);
            }
#line 1780 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 270 "src/parser.y" /* yacc.c:1646  */
    {
                scope_stack.pop();
                (yyval.ifelse) = (yyvsp[-1].ifelse);
            }
#line 1789 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 286 "src/parser.y" /* yacc.c:1646  */
    {
                if ((yyvsp[0].inst)) scope_stack.top()->addChild((yyvsp[0].inst));
            }
#line 1797 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 293 "src/parser.y" /* yacc.c:1646  */
    { (yyval.text) = (yyvsp[0].text); }
#line 1803 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 294 "src/parser.y" /* yacc.c:1646  */
    { (yyval.text) = strdup("for"); }
#line 1809 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 295 "src/parser.y" /* yacc.c:1646  */
    { (yyval.text) = strdup("let"); }
#line 1815 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 296 "src/parser.y" /* yacc.c:1646  */
    { (yyval.text) = strdup("each"); }
#line 1821 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 301 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.inst) = new ModuleInstantiation((yyvsp[-3].text));
                (yyval.inst)->arguments = *(yyvsp[-1].args);
                (yyval.inst)->setPath(boosty::stringy(parser_sourcefile.parent_path()));
                if (filename_stack.empty())
                  (yyval.inst)->setLocation((yyloc).first_line, (yyloc).first_column,
                                  (yyloc).last_line, (yyloc).last_column);
                free((yyvsp[-3].text));
                delete (yyvsp[-1].args);
            }
#line 1836 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 315 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.expr) = new ExpressionConst(ValuePtr(true));
            }
#line 1844 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 319 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.expr) = new ExpressionConst(ValuePtr(false));
            }
#line 1852 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 323 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.expr) = new ExpressionConst(ValuePtr::undefined);
            }
#line 1860 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 327 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.expr) = new ExpressionLookup((yyvsp[0].text));
                free((yyvsp[0].text));
            }
#line 1869 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 332 "src/parser.y" /* yacc.c:1646  */
    {
              (yyval.expr) = new ExpressionMember((yyvsp[-2].expr), (yyvsp[0].text));
                free((yyvsp[0].text));
            }
#line 1878 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 337 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.expr) = new ExpressionConst(ValuePtr(std::string((yyvsp[0].text))));
                free((yyvsp[0].text));
            }
#line 1887 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 342 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.expr) = new ExpressionConst(ValuePtr((yyvsp[0].number)));
            }
#line 1895 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 346 "src/parser.y" /* yacc.c:1646  */
    {
              (yyval.expr) = new ExpressionLet(*(yyvsp[-2].args), (yyvsp[0].expr));
                delete (yyvsp[-2].args);
            }
#line 1904 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 351 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.expr) = new ExpressionRange((yyvsp[-3].expr), (yyvsp[-1].expr));
            }
#line 1912 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 355 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.expr) = new ExpressionRange((yyvsp[-5].expr), (yyvsp[-3].expr), (yyvsp[-1].expr));
            }
#line 1920 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 359 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.expr) = new ExpressionConst(ValuePtr(Value::VectorType()));
            }
#line 1928 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 363 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.expr) = (yyvsp[-2].expr);
            }
#line 1936 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 367 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.expr) = new ExpressionMultiply((yyvsp[-2].expr), (yyvsp[0].expr));
            }
#line 1944 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 371 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.expr) = new ExpressionDivision((yyvsp[-2].expr), (yyvsp[0].expr));
            }
#line 1952 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 375 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.expr) = new ExpressionModulo((yyvsp[-2].expr), (yyvsp[0].expr));
            }
#line 1960 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 379 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.expr) = new ExpressionPlus((yyvsp[-2].expr), (yyvsp[0].expr));
            }
#line 1968 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 383 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.expr) = new ExpressionMinus((yyvsp[-2].expr), (yyvsp[0].expr));
            }
#line 1976 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 387 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.expr) = new ExpressionLess((yyvsp[-2].expr), (yyvsp[0].expr));
            }
#line 1984 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 391 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.expr) = new ExpressionLessOrEqual((yyvsp[-2].expr), (yyvsp[0].expr));
            }
#line 1992 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 395 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.expr) = new ExpressionEqual((yyvsp[-2].expr), (yyvsp[0].expr));
            }
#line 2000 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 399 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.expr) = new ExpressionNotEqual((yyvsp[-2].expr), (yyvsp[0].expr));
            }
#line 2008 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 403 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.expr) = new ExpressionGreaterOrEqual((yyvsp[-2].expr), (yyvsp[0].expr));
            }
#line 2016 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 407 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.expr) = new ExpressionGreater((yyvsp[-2].expr), (yyvsp[0].expr));
            }
#line 2024 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 411 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.expr) = new ExpressionLogicalAnd((yyvsp[-2].expr), (yyvsp[0].expr));
            }
#line 2032 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 415 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.expr) = new ExpressionLogicalOr((yyvsp[-2].expr), (yyvsp[0].expr));
            }
#line 2040 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 419 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.expr) = (yyvsp[0].expr);
            }
#line 2048 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 423 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.expr) = new ExpressionInvert((yyvsp[0].expr));
            }
#line 2056 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 427 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.expr) = new ExpressionNot((yyvsp[0].expr));
            }
#line 2064 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 431 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.expr) = (yyvsp[-1].expr);
            }
#line 2072 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 435 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.expr) = new ExpressionTernary((yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].expr));
            }
#line 2080 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 439 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.expr) = new ExpressionArrayLookup((yyvsp[-3].expr), (yyvsp[-1].expr));
            }
#line 2088 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 443 "src/parser.y" /* yacc.c:1646  */
    {
              (yyval.expr) = new ExpressionFunctionCall((yyvsp[-3].text), *(yyvsp[-1].args));
                free((yyvsp[-3].text));
                delete (yyvsp[-1].args);
            }
#line 2098 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 454 "src/parser.y" /* yacc.c:1646  */
    {
              (yyval.expr) = new ExpressionLcLet(*(yyvsp[-2].args), (yyvsp[0].expr));
                delete (yyvsp[-2].args);
            }
#line 2107 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 459 "src/parser.y" /* yacc.c:1646  */
    {
              (yyval.expr) = new ExpressionLcEach((yyvsp[0].expr));
            }
#line 2115 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 463 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.expr) = (yyvsp[0].expr);

                /* transform for(i=...,j=...) -> for(i=...) for(j=...) */
                for (int i = (yyvsp[-2].args)->size()-1; i >= 0; i--) {
                  AssignmentList arglist;
                  arglist.push_back((*(yyvsp[-2].args))[i]);
                  Expression *e = new ExpressionLcFor(arglist, (yyval.expr));
                    (yyval.expr) = e;
                }
                delete (yyvsp[-2].args);
            }
#line 2132 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 476 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.expr) = new ExpressionLcForC(*(yyvsp[-6].args), *(yyvsp[-2].args), (yyvsp[-4].expr), (yyvsp[0].expr));
                delete (yyvsp[-6].args);
                delete (yyvsp[-2].args);
            }
#line 2142 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 482 "src/parser.y" /* yacc.c:1646  */
    {
              (yyval.expr) = new ExpressionLcIf((yyvsp[-2].expr), (yyvsp[0].expr), 0);
            }
#line 2150 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 486 "src/parser.y" /* yacc.c:1646  */
    {
              (yyval.expr) = new ExpressionLcIf((yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].expr));
            }
#line 2158 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 495 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.expr) = (yyvsp[-1].expr);
            }
#line 2166 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 512 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.expr) = new ExpressionVector((yyvsp[0].expr));
            }
#line 2174 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 516 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.expr) = new ExpressionVector((yyvsp[0].expr));
            }
#line 2182 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 520 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.expr) = (yyvsp[-3].expr);
                (yyval.expr)->children.push_back((yyvsp[0].expr));
            }
#line 2191 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 528 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.args) = new AssignmentList();
            }
#line 2199 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 532 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.args) = new AssignmentList();
                (yyval.args)->push_back(*(yyvsp[0].arg));
                delete (yyvsp[0].arg);
            }
#line 2209 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 538 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.args) = (yyvsp[-3].args);
                (yyval.args)->push_back(*(yyvsp[0].arg));
                delete (yyvsp[0].arg);
            }
#line 2219 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 547 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.arg) = new Assignment((yyvsp[0].text));
                free((yyvsp[0].text));
            }
#line 2228 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 552 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.arg) = new Assignment((yyvsp[-2].text), shared_ptr<Expression>((yyvsp[0].expr)));
                free((yyvsp[-2].text));
            }
#line 2237 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 560 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.args) = new AssignmentList();
            }
#line 2245 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 564 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.args) = new AssignmentList();
                (yyval.args)->push_back(*(yyvsp[0].arg));
                delete (yyvsp[0].arg);
            }
#line 2255 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 570 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.args) = (yyvsp[-3].args);
                (yyval.args)->push_back(*(yyvsp[0].arg));
                delete (yyvsp[0].arg);
            }
#line 2265 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 579 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.arg) = new Assignment("", shared_ptr<Expression>((yyvsp[0].expr)));
            }
#line 2273 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 583 "src/parser.y" /* yacc.c:1646  */
    {
                (yyval.arg) = new Assignment((yyvsp[-2].text), shared_ptr<Expression>((yyvsp[0].expr)));
                free((yyvsp[-2].text));
            }
#line 2282 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 2286 "parser.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

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
                      yytoken, &yylval, &yylloc);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 589 "src/parser.y" /* yacc.c:1906  */


int parserlex(void)
{
  return lexerlex();
}

void yyerror (char const *s)
{
    // FIXME: We leak memory on parser errors...
    PRINTB("ERROR: Parser error in file %s, line %d: %s\n",
        sourcefile() % lexerget_lineno() % s);
}

FileModule *parse(const char *text, const fs::path &filename, int debug)
{
  lexerin = NULL;
  parser_error_pos = -1;
  parser_input_buffer = text;
  parser_sourcefile = boosty::absolute(filename);

  rootmodule = new FileModule();
  rootmodule->setModulePath(boosty::stringy(filename.parent_path()));
  scope_stack.push(&rootmodule->scope);
  //        PRINTB_NOCACHE("New module: %s %p", "root" % rootmodule);

  parserdebug = debug;
  int parserretval = parserparse();
  lexerdestroy();
  lexerlex_destroy();

  if (parserretval != 0) return NULL;

  parser_error_pos = -1;
  scope_stack.pop();
  return rootmodule;
}
