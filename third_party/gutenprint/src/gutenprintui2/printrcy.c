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




/* First part of user prologue.  */
#line 21 "printrcy.y"


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <gutenprint/gutenprint-intl-internal.h>
#include <gutenprintui2/gutenprintui.h>
#include "gutenprintui-internal.h"
#include "printrc.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

extern int mylineno;

extern int yylex(void);
char *quotestrip(const char *i);
char *endstrip(const char *i);

extern char* yytext;

static int yyerror( const char *s )
{
  fprintf(stderr,"stdin:%d: %s before '%s'\n", mylineno, s, yytext);
  return 0;
}

static stpui_plist_t *current_printer = NULL;


#line 104 "printrcy.c"

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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_PRINTRCY_H_INCLUDED
# define YY_YY_PRINTRCY_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    tNUMBER = 258,                 /* tNUMBER  */
    tBOOLEAN = 259,                /* tBOOLEAN  */
    tSTRING = 260,                 /* tSTRING  */
    tWORD = 261,                   /* tWORD  */
    tGSWORD = 262,                 /* tGSWORD  */
    CURRENT_PRINTER = 263,         /* CURRENT_PRINTER  */
    SHOW_ALL_PAPER_SIZES = 264,    /* SHOW_ALL_PAPER_SIZES  */
    PRINTER = 265,                 /* PRINTER  */
    DESTINATION = 266,             /* DESTINATION  */
    SCALING = 267,                 /* SCALING  */
    ORIENTATION = 268,             /* ORIENTATION  */
    AUTOSIZE_ROLL_PAPER = 269,     /* AUTOSIZE_ROLL_PAPER  */
    UNIT = 270,                    /* UNIT  */
    DRIVER = 271,                  /* DRIVER  */
    LEFT = 272,                    /* LEFT  */
    TOP = 273,                     /* TOP  */
    CUSTOM_PAGE_WIDTH = 274,       /* CUSTOM_PAGE_WIDTH  */
    CUSTOM_PAGE_HEIGHT = 275,      /* CUSTOM_PAGE_HEIGHT  */
    OUTPUT_TYPE = 276,             /* OUTPUT_TYPE  */
    PRINTRC_HDR = 277,             /* PRINTRC_HDR  */
    PARAMETER = 278,               /* PARAMETER  */
    QUEUE_NAME = 279,              /* QUEUE_NAME  */
    OUTPUT_FILENAME = 280,         /* OUTPUT_FILENAME  */
    EXTRA_PRINTER_OPTIONS = 281,   /* EXTRA_PRINTER_OPTIONS  */
    CUSTOM_COMMAND = 282,          /* CUSTOM_COMMAND  */
    COMMAND_TYPE = 283,            /* COMMAND_TYPE  */
    GLOBAL_SETTINGS = 284,         /* GLOBAL_SETTINGS  */
    GLOBAL = 285,                  /* GLOBAL  */
    END_GLOBAL_SETTINGS = 286,     /* END_GLOBAL_SETTINGS  */
    pINT = 287,                    /* pINT  */
    pSTRING_LIST = 288,            /* pSTRING_LIST  */
    pFILE = 289,                   /* pFILE  */
    pDOUBLE = 290,                 /* pDOUBLE  */
    pDIMENSION = 291,              /* pDIMENSION  */
    pBOOLEAN = 292,                /* pBOOLEAN  */
    pCURVE = 293                   /* pCURVE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define tNUMBER 258
#define tBOOLEAN 259
#define tSTRING 260
#define tWORD 261
#define tGSWORD 262
#define CURRENT_PRINTER 263
#define SHOW_ALL_PAPER_SIZES 264
#define PRINTER 265
#define DESTINATION 266
#define SCALING 267
#define ORIENTATION 268
#define AUTOSIZE_ROLL_PAPER 269
#define UNIT 270
#define DRIVER 271
#define LEFT 272
#define TOP 273
#define CUSTOM_PAGE_WIDTH 274
#define CUSTOM_PAGE_HEIGHT 275
#define OUTPUT_TYPE 276
#define PRINTRC_HDR 277
#define PARAMETER 278
#define QUEUE_NAME 279
#define OUTPUT_FILENAME 280
#define EXTRA_PRINTER_OPTIONS 281
#define CUSTOM_COMMAND 282
#define COMMAND_TYPE 283
#define GLOBAL_SETTINGS 284
#define GLOBAL 285
#define END_GLOBAL_SETTINGS 286
#define pINT 287
#define pSTRING_LIST 288
#define pFILE 289
#define pDOUBLE 290
#define pDIMENSION 291
#define pBOOLEAN 292
#define pCURVE 293

/* Value type.  */


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PRINTRCY_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_tNUMBER = 3,                    /* tNUMBER  */
  YYSYMBOL_tBOOLEAN = 4,                   /* tBOOLEAN  */
  YYSYMBOL_tSTRING = 5,                    /* tSTRING  */
  YYSYMBOL_tWORD = 6,                      /* tWORD  */
  YYSYMBOL_tGSWORD = 7,                    /* tGSWORD  */
  YYSYMBOL_CURRENT_PRINTER = 8,            /* CURRENT_PRINTER  */
  YYSYMBOL_SHOW_ALL_PAPER_SIZES = 9,       /* SHOW_ALL_PAPER_SIZES  */
  YYSYMBOL_PRINTER = 10,                   /* PRINTER  */
  YYSYMBOL_DESTINATION = 11,               /* DESTINATION  */
  YYSYMBOL_SCALING = 12,                   /* SCALING  */
  YYSYMBOL_ORIENTATION = 13,               /* ORIENTATION  */
  YYSYMBOL_AUTOSIZE_ROLL_PAPER = 14,       /* AUTOSIZE_ROLL_PAPER  */
  YYSYMBOL_UNIT = 15,                      /* UNIT  */
  YYSYMBOL_DRIVER = 16,                    /* DRIVER  */
  YYSYMBOL_LEFT = 17,                      /* LEFT  */
  YYSYMBOL_TOP = 18,                       /* TOP  */
  YYSYMBOL_CUSTOM_PAGE_WIDTH = 19,         /* CUSTOM_PAGE_WIDTH  */
  YYSYMBOL_CUSTOM_PAGE_HEIGHT = 20,        /* CUSTOM_PAGE_HEIGHT  */
  YYSYMBOL_OUTPUT_TYPE = 21,               /* OUTPUT_TYPE  */
  YYSYMBOL_PRINTRC_HDR = 22,               /* PRINTRC_HDR  */
  YYSYMBOL_PARAMETER = 23,                 /* PARAMETER  */
  YYSYMBOL_QUEUE_NAME = 24,                /* QUEUE_NAME  */
  YYSYMBOL_OUTPUT_FILENAME = 25,           /* OUTPUT_FILENAME  */
  YYSYMBOL_EXTRA_PRINTER_OPTIONS = 26,     /* EXTRA_PRINTER_OPTIONS  */
  YYSYMBOL_CUSTOM_COMMAND = 27,            /* CUSTOM_COMMAND  */
  YYSYMBOL_COMMAND_TYPE = 28,              /* COMMAND_TYPE  */
  YYSYMBOL_GLOBAL_SETTINGS = 29,           /* GLOBAL_SETTINGS  */
  YYSYMBOL_GLOBAL = 30,                    /* GLOBAL  */
  YYSYMBOL_END_GLOBAL_SETTINGS = 31,       /* END_GLOBAL_SETTINGS  */
  YYSYMBOL_pINT = 32,                      /* pINT  */
  YYSYMBOL_pSTRING_LIST = 33,              /* pSTRING_LIST  */
  YYSYMBOL_pFILE = 34,                     /* pFILE  */
  YYSYMBOL_pDOUBLE = 35,                   /* pDOUBLE  */
  YYSYMBOL_pDIMENSION = 36,                /* pDIMENSION  */
  YYSYMBOL_pBOOLEAN = 37,                  /* pBOOLEAN  */
  YYSYMBOL_pCURVE = 38,                    /* pCURVE  */
  YYSYMBOL_YYACCEPT = 39,                  /* $accept  */
  YYSYMBOL_Printer = 40,                   /* Printer  */
  YYSYMBOL_Destination = 41,               /* Destination  */
  YYSYMBOL_Queue_Name = 42,                /* Queue_Name  */
  YYSYMBOL_Output_Filename = 43,           /* Output_Filename  */
  YYSYMBOL_Extra_Printer_Options = 44,     /* Extra_Printer_Options  */
  YYSYMBOL_Custom_Command = 45,            /* Custom_Command  */
  YYSYMBOL_Command_Type = 46,              /* Command_Type  */
  YYSYMBOL_Scaling = 47,                   /* Scaling  */
  YYSYMBOL_Orientation = 48,               /* Orientation  */
  YYSYMBOL_Autosize_Roll_Paper = 49,       /* Autosize_Roll_Paper  */
  YYSYMBOL_Unit = 50,                      /* Unit  */
  YYSYMBOL_Left = 51,                      /* Left  */
  YYSYMBOL_Top = 52,                       /* Top  */
  YYSYMBOL_Output_Type = 53,               /* Output_Type  */
  YYSYMBOL_Custom_Page_Width = 54,         /* Custom_Page_Width  */
  YYSYMBOL_Custom_Page_Height = 55,        /* Custom_Page_Height  */
  YYSYMBOL_Empty = 56,                     /* Empty  */
  YYSYMBOL_Int_Param = 57,                 /* Int_Param  */
  YYSYMBOL_String_List_Param = 58,         /* String_List_Param  */
  YYSYMBOL_File_Param = 59,                /* File_Param  */
  YYSYMBOL_Double_Param = 60,              /* Double_Param  */
  YYSYMBOL_Dimension_Param = 61,           /* Dimension_Param  */
  YYSYMBOL_Boolean_Param = 62,             /* Boolean_Param  */
  YYSYMBOL_Curve_Param = 63,               /* Curve_Param  */
  YYSYMBOL_Typed_Param = 64,               /* Typed_Param  */
  YYSYMBOL_Parameter = 65,                 /* Parameter  */
  YYSYMBOL_Parameters = 66,                /* Parameters  */
  YYSYMBOL_Standard_Value = 67,            /* Standard_Value  */
  YYSYMBOL_Standard_Values = 68,           /* Standard_Values  */
  YYSYMBOL_A_Printer = 69,                 /* A_Printer  */
  YYSYMBOL_Printers = 70,                  /* Printers  */
  YYSYMBOL_Current_Printer = 71,           /* Current_Printer  */
  YYSYMBOL_Show_All_Paper_Sizes = 72,      /* Show_All_Paper_Sizes  */
  YYSYMBOL_Global = 73,                    /* Global  */
  YYSYMBOL_Old_Globals = 74,               /* Old_Globals  */
  YYSYMBOL_New_Global_Setting = 75,        /* New_Global_Setting  */
  YYSYMBOL_Global_Setting = 76,            /* Global_Setting  */
  YYSYMBOL_Global_Settings = 77,           /* Global_Settings  */
  YYSYMBOL_Global_Subblock = 78,           /* Global_Subblock  */
  YYSYMBOL_Global_Block = 79,              /* Global_Block  */
  YYSYMBOL_Thing = 80                      /* Thing  */
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
typedef yytype_int8 yy_state_t;

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
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   73

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  70
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  114

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   293


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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    96,    96,   107,   114,   124,   134,   144,   154,   161,
     168,   175,   182,   189,   196,   203,   224,   231,   238,   241,
     258,   276,   294,   311,   328,   349,   372,   372,   372,   372,
     373,   373,   373,   376,   379,   379,   382,   382,   382,   382,
     383,   383,   383,   383,   383,   384,   384,   384,   384,   385,
     385,   388,   388,   391,   394,   394,   397,   401,   411,   411,
     414,   417,   428,   428,   431,   431,   434,   437,   437,   437,
     440
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
  "\"end of file\"", "error", "\"invalid token\"", "tNUMBER", "tBOOLEAN",
  "tSTRING", "tWORD", "tGSWORD", "CURRENT_PRINTER", "SHOW_ALL_PAPER_SIZES",
  "PRINTER", "DESTINATION", "SCALING", "ORIENTATION",
  "AUTOSIZE_ROLL_PAPER", "UNIT", "DRIVER", "LEFT", "TOP",
  "CUSTOM_PAGE_WIDTH", "CUSTOM_PAGE_HEIGHT", "OUTPUT_TYPE", "PRINTRC_HDR",
  "PARAMETER", "QUEUE_NAME", "OUTPUT_FILENAME", "EXTRA_PRINTER_OPTIONS",
  "CUSTOM_COMMAND", "COMMAND_TYPE", "GLOBAL_SETTINGS", "GLOBAL",
  "END_GLOBAL_SETTINGS", "pINT", "pSTRING_LIST", "pFILE", "pDOUBLE",
  "pDIMENSION", "pBOOLEAN", "pCURVE", "$accept", "Printer", "Destination",
  "Queue_Name", "Output_Filename", "Extra_Printer_Options",
  "Custom_Command", "Command_Type", "Scaling", "Orientation",
  "Autosize_Roll_Paper", "Unit", "Left", "Top", "Output_Type",
  "Custom_Page_Width", "Custom_Page_Height", "Empty", "Int_Param",
  "String_List_Param", "File_Param", "Double_Param", "Dimension_Param",
  "Boolean_Param", "Curve_Param", "Typed_Param", "Parameter", "Parameters",
  "Standard_Value", "Standard_Values", "A_Printer", "Printers",
  "Current_Printer", "Show_All_Paper_Sizes", "Global", "Old_Globals",
  "New_Global_Setting", "Global_Setting", "Global_Settings",
  "Global_Subblock", "Global_Block", "Thing", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-26)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -20,    -2,    14,    10,   -26,   -26,     7,   -26,   -26,   -26,
     -26,   -26,   -26,    -5,    13,   -26,   -26,     8,    15,   -26,
     -26,   -26,   -26,   -26,   -26,   -26,    16,   -26,   -26,   -26,
      17,   -26,    18,   -26,    19,    22,    31,    37,    38,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    55,   -26,
     -26,   -26,   -26,   -26,   -26,   -26,   -26,   -26,   -26,   -26,
     -26,   -26,   -26,   -26,   -26,    29,   -26,   -26,   -26,   -26,
     -26,   -26,   -26,   -26,   -26,   -26,   -26,   -26,   -26,   -26,
     -26,   -26,    53,   -26,   -25,   -26,   -26,   -26,   -26,   -26,
     -26,   -26,   -26,    56,    57,    58,    59,    60,    61,    62,
      64,    63,    65,    66,    68,    69,    67,   -26,   -26,   -26,
     -26,   -26,   -26,   -26
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    18,     0,     0,    18,    69,     0,    68,    67,    18,
       1,    56,    65,     0,     0,    60,    55,    70,     0,    66,
      58,    59,    62,    63,    64,    57,     0,    18,    54,    61,
       0,    52,    18,     2,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    36,
      46,    47,    48,    49,    50,    37,    38,    39,    40,    41,
      42,    45,    43,    44,    35,    53,    51,     3,     9,    10,
      11,    12,    13,    14,    16,    17,    15,     4,     5,     6,
       7,     8,     0,    34,     0,    26,    27,    28,    29,    32,
      30,    31,    33,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    19,    20,    21,
      22,    23,    24,    25
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -26,   -26,   -26,   -26,   -26,   -26,   -26,   -26,   -26,   -26,
     -26,   -26,   -26,   -26,   -26,   -26,   -26,    -4,   -26,   -26,
     -26,   -26,   -26,   -26,   -26,   -26,   -26,   -26,   -26,   -26,
     -26,   -26,     6,    40,   -26,   -26,   -26,   -26,   -26,   -26,
     -26,   -26
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,    27,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,     5,    85,    86,
      87,    88,    89,    90,    91,    92,    83,    65,    66,    32,
      28,    17,     6,    15,    22,     7,    23,    24,    13,     8,
       9,     2
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      12,    18,     1,     3,    14,    16,     3,    93,    94,    95,
      96,    97,    98,    99,    10,    11,    14,    25,    26,    20,
      29,    30,    33,    31,    67,    68,    19,     4,    64,    34,
      35,    36,    37,    38,    69,    39,    40,    41,    42,    43,
      70,    71,    44,    45,    46,    47,    48,    72,    73,    74,
      75,    76,    82,    21,    77,    78,    79,    80,    81,    84,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   110,
     109,   111,   113,   112
};

static const yytype_int8 yycheck[] =
{
       4,     6,    22,     8,     9,     9,     8,    32,    33,    34,
      35,    36,    37,    38,     0,     5,     9,     4,    10,    13,
       5,     5,     5,    27,     5,     3,    31,    29,    32,    11,
      12,    13,    14,    15,     3,    17,    18,    19,    20,    21,
       3,     3,    24,    25,    26,    27,    28,     3,     3,     3,
       3,     3,    23,    13,     5,     5,     5,     5,     3,     6,
       4,     4,     4,     4,     4,     4,     4,     3,     5,     3,
       5,     3,     5,     4
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    22,    80,     8,    29,    56,    71,    74,    78,    79,
       0,     5,    56,    77,     9,    72,    56,    70,     6,    31,
      71,    72,    73,    75,    76,     4,    10,    40,    69,     5,
       5,    56,    68,     5,    11,    12,    13,    14,    15,    17,
      18,    19,    20,    21,    24,    25,    26,    27,    28,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    66,    67,     5,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     5,     5,     5,
       5,     3,    23,    65,     6,    57,    58,    59,    60,    61,
      62,    63,    64,    32,    33,    34,    35,    36,    37,    38,
       4,     4,     4,     4,     4,     4,     4,     3,     5,     5,
       3,     3,     4,     5
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    64,    64,    64,
      64,    64,    64,    65,    66,    66,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    68,    68,    69,    70,    70,    71,    72,    73,    73,
      74,    75,    76,    76,    77,    77,    78,    79,    79,    79,
      80
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     0,     4,
       4,     4,     4,     4,     4,     4,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     3,     2,     1,     2,     2,     1,     1,
       2,     2,     1,     1,     2,     1,     3,     1,     1,     1,
       3
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
  case 2: /* Printer: PRINTER tSTRING tSTRING  */
#line 97 "printrcy.y"
        {
	  current_printer = stpui_plist_create((yyvsp[-1].sval), (yyvsp[0].sval));
	  g_free((yyvsp[-1].sval));
	  g_free((yyvsp[0].sval));
	}
#line 1369 "printrcy.c"
    break;

  case 3: /* Destination: DESTINATION tSTRING  */
#line 108 "printrcy.y"
        {
	  if ((yyvsp[0].sval))
	    g_free((yyvsp[0].sval));
	}
#line 1378 "printrcy.c"
    break;

  case 4: /* Queue_Name: QUEUE_NAME tSTRING  */
#line 115 "printrcy.y"
        {
	  if (current_printer && (yyvsp[0].sval))
	    {
	      stpui_plist_set_queue_name(current_printer, (yyvsp[0].sval));
	      g_free((yyvsp[0].sval));
	    }
	}
#line 1390 "printrcy.c"
    break;

  case 5: /* Output_Filename: OUTPUT_FILENAME tSTRING  */
#line 125 "printrcy.y"
        {
	  if (current_printer && (yyvsp[0].sval))
	    {
	      stpui_plist_set_output_filename(current_printer, (yyvsp[0].sval));
	      g_free((yyvsp[0].sval));
	    }
	}
#line 1402 "printrcy.c"
    break;

  case 6: /* Extra_Printer_Options: EXTRA_PRINTER_OPTIONS tSTRING  */
#line 135 "printrcy.y"
        {
	  if (current_printer && (yyvsp[0].sval))
	    {
	      stpui_plist_set_extra_printer_options(current_printer, (yyvsp[0].sval));
	      g_free((yyvsp[0].sval));
	    }
	}
#line 1414 "printrcy.c"
    break;

  case 7: /* Custom_Command: CUSTOM_COMMAND tSTRING  */
#line 145 "printrcy.y"
        {
	  if (current_printer && (yyvsp[0].sval))
	    {
	      stpui_plist_set_custom_command(current_printer, (yyvsp[0].sval));
	      g_free((yyvsp[0].sval));
	    }
	}
#line 1426 "printrcy.c"
    break;

  case 8: /* Command_Type: COMMAND_TYPE tNUMBER  */
#line 155 "printrcy.y"
        {
	  if (current_printer)
	    stpui_plist_set_command_type(current_printer, (int) (yyvsp[0].dval));
	}
#line 1435 "printrcy.c"
    break;

  case 9: /* Scaling: SCALING tNUMBER  */
#line 162 "printrcy.y"
        {
	  if (current_printer)
	    current_printer->scaling = (yyvsp[0].dval);
	}
#line 1444 "printrcy.c"
    break;

  case 10: /* Orientation: ORIENTATION tNUMBER  */
#line 169 "printrcy.y"
        {
	  if (current_printer)
	    current_printer->orientation = (int) (yyvsp[0].dval);
	}
#line 1453 "printrcy.c"
    break;

  case 11: /* Autosize_Roll_Paper: AUTOSIZE_ROLL_PAPER tNUMBER  */
#line 176 "printrcy.y"
        {
	  if (current_printer)
	    current_printer->auto_size_roll_feed_paper = (int) (yyvsp[0].dval);
	}
#line 1462 "printrcy.c"
    break;

  case 12: /* Unit: UNIT tNUMBER  */
#line 183 "printrcy.y"
        {
	  if (current_printer)
	    current_printer->unit = (int) (yyvsp[0].dval);
	}
#line 1471 "printrcy.c"
    break;

  case 13: /* Left: LEFT tNUMBER  */
#line 190 "printrcy.y"
        {
	  if (current_printer)
	    stp_set_left(current_printer->v, (yyvsp[0].dval));
	}
#line 1480 "printrcy.c"
    break;

  case 14: /* Top: TOP tNUMBER  */
#line 197 "printrcy.y"
        {
	  if (current_printer)
	    stp_set_top(current_printer->v, (yyvsp[0].dval));
	}
#line 1489 "printrcy.c"
    break;

  case 15: /* Output_Type: OUTPUT_TYPE tNUMBER  */
#line 204 "printrcy.y"
        {
	  if (current_printer)
	    {
	      switch ((int) (yyvsp[0].dval))
		{
		case 0:
		  stp_set_string_parameter
		    (current_printer->v, "PrintingMode", "BW");
		  break;
		case 1:
		case 2:
		default:
		  stp_set_string_parameter
		    (current_printer->v, "PrintingMode", "Color");
		  break;
		}
	    }
	}
#line 1512 "printrcy.c"
    break;

  case 16: /* Custom_Page_Width: CUSTOM_PAGE_WIDTH tNUMBER  */
#line 225 "printrcy.y"
        {
	  if (current_printer)
	    stp_set_page_width(current_printer->v, (yyvsp[0].dval));
	}
#line 1521 "printrcy.c"
    break;

  case 17: /* Custom_Page_Height: CUSTOM_PAGE_HEIGHT tNUMBER  */
#line 232 "printrcy.y"
        {
	  if (current_printer)
	    stp_set_page_height(current_printer->v, (yyvsp[0].dval));
	}
#line 1530 "printrcy.c"
    break;

  case 19: /* Int_Param: tWORD pINT tBOOLEAN tNUMBER  */
#line 242 "printrcy.y"
        {
	  if (current_printer)
	    {
	      stp_set_int_parameter(current_printer->v, (yyvsp[-3].sval), (int) (yyvsp[0].dval));
	      if (strcmp((yyvsp[-1].sval), "False") == 0)
		stp_set_int_parameter_active(current_printer->v, (yyvsp[-3].sval),
					     STP_PARAMETER_INACTIVE);
	      else
		stp_set_int_parameter_active(current_printer->v, (yyvsp[-3].sval),
					     STP_PARAMETER_ACTIVE);
	    }
	  g_free((yyvsp[-3].sval));
	  g_free((yyvsp[-1].sval));
	}
#line 1549 "printrcy.c"
    break;

  case 20: /* String_List_Param: tWORD pSTRING_LIST tBOOLEAN tSTRING  */
#line 259 "printrcy.y"
        {
	  if (current_printer)
	    {
	      stp_set_string_parameter(current_printer->v, (yyvsp[-3].sval), (yyvsp[0].sval));
	      if (strcmp((yyvsp[-1].sval), "False") == 0)
		stp_set_string_parameter_active(current_printer->v, (yyvsp[-3].sval),
						STP_PARAMETER_INACTIVE);
	      else
		stp_set_string_parameter_active(current_printer->v, (yyvsp[-3].sval),
						STP_PARAMETER_ACTIVE);
	    }
	  g_free((yyvsp[-3].sval));
	  g_free((yyvsp[-1].sval));
	  g_free((yyvsp[0].sval));
	}
#line 1569 "printrcy.c"
    break;

  case 21: /* File_Param: tWORD pFILE tBOOLEAN tSTRING  */
#line 277 "printrcy.y"
        {
	  if (current_printer)
	    {
	      stp_set_file_parameter(current_printer->v, (yyvsp[-3].sval), (yyvsp[0].sval));
	      if (strcmp((yyvsp[-1].sval), "False") == 0)
		stp_set_file_parameter_active(current_printer->v, (yyvsp[-3].sval),
					      STP_PARAMETER_INACTIVE);
	      else
		stp_set_file_parameter_active(current_printer->v, (yyvsp[-3].sval),
					      STP_PARAMETER_ACTIVE);
	    }
	  g_free((yyvsp[-3].sval));
	  g_free((yyvsp[-1].sval));
	  g_free((yyvsp[0].sval));
	}
#line 1589 "printrcy.c"
    break;

  case 22: /* Double_Param: tWORD pDOUBLE tBOOLEAN tNUMBER  */
#line 295 "printrcy.y"
        {
	  if (current_printer)
	    {
	      stp_set_float_parameter(current_printer->v, (yyvsp[-3].sval), (yyvsp[0].dval));
	      if (strcmp((yyvsp[-1].sval), "False") == 0)
		stp_set_float_parameter_active(current_printer->v, (yyvsp[-3].sval),
					       STP_PARAMETER_INACTIVE);
	      else
		stp_set_float_parameter_active(current_printer->v, (yyvsp[-3].sval),
					       STP_PARAMETER_ACTIVE);
	    }
	  g_free((yyvsp[-3].sval));
	  g_free((yyvsp[-1].sval));
	}
#line 1608 "printrcy.c"
    break;

  case 23: /* Dimension_Param: tWORD pDIMENSION tBOOLEAN tNUMBER  */
#line 312 "printrcy.y"
        {
	  if (current_printer)
	    {
	      stp_set_dimension_parameter(current_printer->v, (yyvsp[-3].sval), (yyvsp[0].dval));
	      if (strcmp((yyvsp[-1].sval), "False") == 0)
		stp_set_dimension_parameter_active(current_printer->v, (yyvsp[-3].sval),
						   STP_PARAMETER_INACTIVE);
	      else
		stp_set_dimension_parameter_active(current_printer->v, (yyvsp[-3].sval),
						   STP_PARAMETER_ACTIVE);
	    }
	  g_free((yyvsp[-3].sval));
	  g_free((yyvsp[-1].sval));
	}
#line 1627 "printrcy.c"
    break;

  case 24: /* Boolean_Param: tWORD pBOOLEAN tBOOLEAN tBOOLEAN  */
#line 329 "printrcy.y"
        {
	  if (current_printer)
	    {
	      if (strcmp((yyvsp[0].sval), "False") == 0)
		stp_set_boolean_parameter(current_printer->v, (yyvsp[-3].sval), 0);
	      else
		stp_set_boolean_parameter(current_printer->v, (yyvsp[-3].sval), 1);
	      if (strcmp((yyvsp[-1].sval), "False") == 0)
		stp_set_boolean_parameter_active(current_printer->v, (yyvsp[-3].sval),
						 STP_PARAMETER_INACTIVE);
	      else
		stp_set_boolean_parameter_active(current_printer->v, (yyvsp[-3].sval),
						 STP_PARAMETER_ACTIVE);
	    }
	  g_free((yyvsp[-3].sval));
	  g_free((yyvsp[-1].sval));
	  g_free((yyvsp[0].sval));
	}
#line 1650 "printrcy.c"
    break;

  case 25: /* Curve_Param: tWORD pCURVE tBOOLEAN tSTRING  */
#line 350 "printrcy.y"
        {
	  if (current_printer)
	    {
	      stp_curve_t *curve = stp_curve_create_from_string((yyvsp[0].sval));
	      if (curve)
		{
		  stp_set_curve_parameter(current_printer->v, (yyvsp[-3].sval), curve);
		  if (strcmp((yyvsp[-1].sval), "False") == 0)
		    stp_set_curve_parameter_active(current_printer->v, (yyvsp[-3].sval),
						   STP_PARAMETER_INACTIVE);
		  else
		    stp_set_curve_parameter_active(current_printer->v, (yyvsp[-3].sval),
						   STP_PARAMETER_ACTIVE);
		  stp_curve_destroy(curve);
		}
	    }
	  g_free((yyvsp[-3].sval));
	  g_free((yyvsp[-1].sval));
	  g_free((yyvsp[0].sval));
	}
#line 1675 "printrcy.c"
    break;

  case 56: /* Current_Printer: CURRENT_PRINTER tSTRING  */
#line 398 "printrcy.y"
        { stpui_printrc_current_printer = (yyvsp[0].sval); }
#line 1681 "printrcy.c"
    break;

  case 57: /* Show_All_Paper_Sizes: SHOW_ALL_PAPER_SIZES tBOOLEAN  */
#line 402 "printrcy.y"
        {
	  if (strcmp((yyvsp[0].sval), "True") == 0)
	    stpui_show_all_paper_sizes = 1;
	  else
	    stpui_show_all_paper_sizes = 0;
	  g_free((yyvsp[0].sval));
	}
#line 1693 "printrcy.c"
    break;

  case 61: /* New_Global_Setting: tWORD tSTRING  */
#line 418 "printrcy.y"
        {
	  if ((yyvsp[0].sval))
	    {
	      stpui_set_global_parameter((yyvsp[-1].sval), (yyvsp[0].sval));
	      g_free((yyvsp[0].sval));
	    }
	  g_free((yyvsp[-1].sval));
	}
#line 1706 "printrcy.c"
    break;


#line 1710 "printrcy.c"

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

#line 443 "printrcy.y"

