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
#line 21 "testpatterny.y"


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include "testpattern.h"

extern int mylineno;

extern int yylex(void);
char *quotestrip(const char *i);
char *endstrip(const char *i);

extern char* yytext;

static int yyerror( const char *s )
{
	fprintf(stderr,"stdin:%d: %s before '%s'\n",mylineno,s,yytext);
	return 0;
}

typedef struct
{
  const char *name;
  int channel;
} color_t;

static color_t color_map[] =
  {
    { "black", 0 },
    { "cyan", 1 },
    { "red", 1 },
    { "magenta", 2 },
    { "green", 2 },
    { "yellow", 3 },
    { "blue", 3 },
    { "l_black", 4 },
    { "l_cyan", 5 },
    { "l_magenta", 6 },
    { "d_yellow", 4 },
    { "l_l_black", 7 },
    { NULL, -1 }
  };

static int current_index = 0;
static testpattern_t *current_testpattern;
extern FILE *yyin;

static int
find_color(const char *name)
{
  int i = 0;
  while (color_map[i].name)
    {
      if (strcasecmp(color_map[i].name, name) == 0)
	return color_map[i].channel;
      i++;
    }
  return -1;
}


#line 139 "testpatterny.c"

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
#ifndef YY_YY_TESTPATTERNY_H_INCLUDED
# define YY_YY_TESTPATTERNY_H_INCLUDED
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
    tINT = 258,                    /* tINT  */
    tDOUBLE = 259,                 /* tDOUBLE  */
    tSTRING = 260,                 /* tSTRING  */
    COLOR = 261,                   /* COLOR  */
    GAMMA = 262,                   /* GAMMA  */
    LEVEL = 263,                   /* LEVEL  */
    STEPS = 264,                   /* STEPS  */
    INK_LIMIT = 265,               /* INK_LIMIT  */
    PRINTER = 266,                 /* PRINTER  */
    PARAMETER = 267,               /* PARAMETER  */
    PARAMETER_INT = 268,           /* PARAMETER_INT  */
    PARAMETER_BOOL = 269,          /* PARAMETER_BOOL  */
    PARAMETER_FLOAT = 270,         /* PARAMETER_FLOAT  */
    PARAMETER_CURVE = 271,         /* PARAMETER_CURVE  */
    DENSITY = 272,                 /* DENSITY  */
    TOP = 273,                     /* TOP  */
    LEFT = 274,                    /* LEFT  */
    SIZE_MODE = 275,               /* SIZE_MODE  */
    RELATIVE = 276,                /* RELATIVE  */
    PT = 277,                      /* PT  */
    IN = 278,                      /* IN  */
    MM = 279,                      /* MM  */
    HSIZE = 280,                   /* HSIZE  */
    VSIZE = 281,                   /* VSIZE  */
    BLACKLINE = 282,               /* BLACKLINE  */
    COLORLINE = 283,               /* COLORLINE  */
    NOSCALE = 284,                 /* NOSCALE  */
    PATTERN = 285,                 /* PATTERN  */
    XPATTERN = 286,                /* XPATTERN  */
    EXTENDED = 287,                /* EXTENDED  */
    IMAGE = 288,                   /* IMAGE  */
    GRID = 289,                    /* GRID  */
    SEMI = 290,                    /* SEMI  */
    CHANNEL = 291,                 /* CHANNEL  */
    CMYK = 292,                    /* CMYK  */
    KCMY = 293,                    /* KCMY  */
    RGB = 294,                     /* RGB  */
    CMY = 295,                     /* CMY  */
    GRAY = 296,                    /* GRAY  */
    WHITE = 297,                   /* WHITE  */
    MODE = 298,                    /* MODE  */
    PAGESIZE = 299,                /* PAGESIZE  */
    ROUND = 300,                   /* ROUND  */
    MESSAGE = 301,                 /* MESSAGE  */
    OUTPUT = 302,                  /* OUTPUT  */
    START_JOB = 303,               /* START_JOB  */
    END_JOB = 304,                 /* END_JOB  */
    END = 305                      /* END  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define tINT 258
#define tDOUBLE 259
#define tSTRING 260
#define COLOR 261
#define GAMMA 262
#define LEVEL 263
#define STEPS 264
#define INK_LIMIT 265
#define PRINTER 266
#define PARAMETER 267
#define PARAMETER_INT 268
#define PARAMETER_BOOL 269
#define PARAMETER_FLOAT 270
#define PARAMETER_CURVE 271
#define DENSITY 272
#define TOP 273
#define LEFT 274
#define SIZE_MODE 275
#define RELATIVE 276
#define PT 277
#define IN 278
#define MM 279
#define HSIZE 280
#define VSIZE 281
#define BLACKLINE 282
#define COLORLINE 283
#define NOSCALE 284
#define PATTERN 285
#define XPATTERN 286
#define EXTENDED 287
#define IMAGE 288
#define GRID 289
#define SEMI 290
#define CHANNEL 291
#define CMYK 292
#define KCMY 293
#define RGB 294
#define CMY 295
#define GRAY 296
#define WHITE 297
#define MODE 298
#define PAGESIZE 299
#define ROUND 300
#define MESSAGE 301
#define OUTPUT 302
#define START_JOB 303
#define END_JOB 304
#define END 305

/* Value type.  */


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_TESTPATTERNY_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_tINT = 3,                       /* tINT  */
  YYSYMBOL_tDOUBLE = 4,                    /* tDOUBLE  */
  YYSYMBOL_tSTRING = 5,                    /* tSTRING  */
  YYSYMBOL_COLOR = 6,                      /* COLOR  */
  YYSYMBOL_GAMMA = 7,                      /* GAMMA  */
  YYSYMBOL_LEVEL = 8,                      /* LEVEL  */
  YYSYMBOL_STEPS = 9,                      /* STEPS  */
  YYSYMBOL_INK_LIMIT = 10,                 /* INK_LIMIT  */
  YYSYMBOL_PRINTER = 11,                   /* PRINTER  */
  YYSYMBOL_PARAMETER = 12,                 /* PARAMETER  */
  YYSYMBOL_PARAMETER_INT = 13,             /* PARAMETER_INT  */
  YYSYMBOL_PARAMETER_BOOL = 14,            /* PARAMETER_BOOL  */
  YYSYMBOL_PARAMETER_FLOAT = 15,           /* PARAMETER_FLOAT  */
  YYSYMBOL_PARAMETER_CURVE = 16,           /* PARAMETER_CURVE  */
  YYSYMBOL_DENSITY = 17,                   /* DENSITY  */
  YYSYMBOL_TOP = 18,                       /* TOP  */
  YYSYMBOL_LEFT = 19,                      /* LEFT  */
  YYSYMBOL_SIZE_MODE = 20,                 /* SIZE_MODE  */
  YYSYMBOL_RELATIVE = 21,                  /* RELATIVE  */
  YYSYMBOL_PT = 22,                        /* PT  */
  YYSYMBOL_IN = 23,                        /* IN  */
  YYSYMBOL_MM = 24,                        /* MM  */
  YYSYMBOL_HSIZE = 25,                     /* HSIZE  */
  YYSYMBOL_VSIZE = 26,                     /* VSIZE  */
  YYSYMBOL_BLACKLINE = 27,                 /* BLACKLINE  */
  YYSYMBOL_COLORLINE = 28,                 /* COLORLINE  */
  YYSYMBOL_NOSCALE = 29,                   /* NOSCALE  */
  YYSYMBOL_PATTERN = 30,                   /* PATTERN  */
  YYSYMBOL_XPATTERN = 31,                  /* XPATTERN  */
  YYSYMBOL_EXTENDED = 32,                  /* EXTENDED  */
  YYSYMBOL_IMAGE = 33,                     /* IMAGE  */
  YYSYMBOL_GRID = 34,                      /* GRID  */
  YYSYMBOL_SEMI = 35,                      /* SEMI  */
  YYSYMBOL_CHANNEL = 36,                   /* CHANNEL  */
  YYSYMBOL_CMYK = 37,                      /* CMYK  */
  YYSYMBOL_KCMY = 38,                      /* KCMY  */
  YYSYMBOL_RGB = 39,                       /* RGB  */
  YYSYMBOL_CMY = 40,                       /* CMY  */
  YYSYMBOL_GRAY = 41,                      /* GRAY  */
  YYSYMBOL_WHITE = 42,                     /* WHITE  */
  YYSYMBOL_MODE = 43,                      /* MODE  */
  YYSYMBOL_PAGESIZE = 44,                  /* PAGESIZE  */
  YYSYMBOL_ROUND = 45,                     /* ROUND  */
  YYSYMBOL_MESSAGE = 46,                   /* MESSAGE  */
  YYSYMBOL_OUTPUT = 47,                    /* OUTPUT  */
  YYSYMBOL_START_JOB = 48,                 /* START_JOB  */
  YYSYMBOL_END_JOB = 49,                   /* END_JOB  */
  YYSYMBOL_END = 50,                       /* END  */
  YYSYMBOL_YYACCEPT = 51,                  /* $accept  */
  YYSYMBOL_NUMBER = 52,                    /* NUMBER  */
  YYSYMBOL_cmykspec = 53,                  /* cmykspec  */
  YYSYMBOL_kcmyspec = 54,                  /* kcmyspec  */
  YYSYMBOL_rgbspec = 55,                   /* rgbspec  */
  YYSYMBOL_cmyspec = 56,                   /* cmyspec  */
  YYSYMBOL_grayspec = 57,                  /* grayspec  */
  YYSYMBOL_whitespec = 58,                 /* whitespec  */
  YYSYMBOL_extendedspec = 59,              /* extendedspec  */
  YYSYMBOL_modespec1 = 60,                 /* modespec1  */
  YYSYMBOL_modespec2 = 61,                 /* modespec2  */
  YYSYMBOL_modespec = 62,                  /* modespec  */
  YYSYMBOL_round = 63,                     /* round  */
  YYSYMBOL_inputspec = 64,                 /* inputspec  */
  YYSYMBOL_level = 65,                     /* level  */
  YYSYMBOL_channel_level = 66,             /* channel_level  */
  YYSYMBOL_gamma = 67,                     /* gamma  */
  YYSYMBOL_channel_gamma = 68,             /* channel_gamma  */
  YYSYMBOL_global_gamma = 69,              /* global_gamma  */
  YYSYMBOL_steps = 70,                     /* steps  */
  YYSYMBOL_ink_limit = 71,                 /* ink_limit  */
  YYSYMBOL_printer = 72,                   /* printer  */
  YYSYMBOL_page_size_name = 73,            /* page_size_name  */
  YYSYMBOL_page_size_custom = 74,          /* page_size_custom  */
  YYSYMBOL_page_size = 75,                 /* page_size  */
  YYSYMBOL_parameter_string = 76,          /* parameter_string  */
  YYSYMBOL_parameter_int = 77,             /* parameter_int  */
  YYSYMBOL_parameter_bool = 78,            /* parameter_bool  */
  YYSYMBOL_parameter_float = 79,           /* parameter_float  */
  YYSYMBOL_parameter_curve = 80,           /* parameter_curve  */
  YYSYMBOL_parameter = 81,                 /* parameter  */
  YYSYMBOL_density = 82,                   /* density  */
  YYSYMBOL_top = 83,                       /* top  */
  YYSYMBOL_left = 84,                      /* left  */
  YYSYMBOL_size_relative = 85,             /* size_relative  */
  YYSYMBOL_size_in = 86,                   /* size_in  */
  YYSYMBOL_size_pt = 87,                   /* size_pt  */
  YYSYMBOL_size_mm = 88,                   /* size_mm  */
  YYSYMBOL_size_mode_1 = 89,               /* size_mode_1  */
  YYSYMBOL_size_mode = 90,                 /* size_mode  */
  YYSYMBOL_hsize = 91,                     /* hsize  */
  YYSYMBOL_vsize = 92,                     /* vsize  */
  YYSYMBOL_blackline = 93,                 /* blackline  */
  YYSYMBOL_colorline = 94,                 /* colorline  */
  YYSYMBOL_noscale = 95,                   /* noscale  */
  YYSYMBOL_color_block1 = 96,              /* color_block1  */
  YYSYMBOL_color_blocks1a = 97,            /* color_blocks1a  */
  YYSYMBOL_color_blocks1b = 98,            /* color_blocks1b  */
  YYSYMBOL_color_blocks1 = 99,             /* color_blocks1  */
  YYSYMBOL_color_block2a = 100,            /* color_block2a  */
  YYSYMBOL_color_block2b = 101,            /* color_block2b  */
  YYSYMBOL_color_block2 = 102,             /* color_block2  */
  YYSYMBOL_color_blocks2a = 103,           /* color_blocks2a  */
  YYSYMBOL_color_blocks2 = 104,            /* color_blocks2  */
  YYSYMBOL_color_blocks = 105,             /* color_blocks  */
  YYSYMBOL_patvars = 106,                  /* patvars  */
  YYSYMBOL_pattern = 107,                  /* pattern  */
  YYSYMBOL_xpattern = 108,                 /* xpattern  */
  YYSYMBOL_grid = 109,                     /* grid  */
  YYSYMBOL_image = 110,                    /* image  */
  YYSYMBOL_Message = 111,                  /* Message  */
  YYSYMBOL_Messages = 112,                 /* Messages  */
  YYSYMBOL_message = 113,                  /* message  */
  YYSYMBOL_Output0 = 114,                  /* Output0  */
  YYSYMBOL_Output1 = 115,                  /* Output1  */
  YYSYMBOL_output = 116,                   /* output  */
  YYSYMBOL_start_job = 117,                /* start_job  */
  YYSYMBOL_end_job = 118,                  /* end_job  */
  YYSYMBOL_A_Rule = 119,                   /* A_Rule  */
  YYSYMBOL_Rule = 120,                     /* Rule  */
  YYSYMBOL_A_Pattern = 121,                /* A_Pattern  */
  YYSYMBOL_Pattern = 122,                  /* Pattern  */
  YYSYMBOL_Patterns = 123,                 /* Patterns  */
  YYSYMBOL_Image = 124,                    /* Image  */
  YYSYMBOL_Rules = 125,                    /* Rules  */
  YYSYMBOL_Print = 126,                    /* Print  */
  YYSYMBOL_EOF = 127,                      /* EOF  */
  YYSYMBOL_Thing = 128,                    /* Thing  */
  YYSYMBOL_129_1 = 129                     /* $@1  */
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
#define YYFINAL  66
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   182

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  79
/* YYNRULES -- Number of rules.  */
#define YYNRULES  134
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  188

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   305


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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   145,   145,   145,   150,   160,   170,   180,   190,   200,
     210,   220,   220,   220,   220,   220,   220,   220,   223,   231,
     231,   234,   241,   244,   254,   263,   273,   282,   289,   296,
     303,   312,   321,   330,   330,   333,   343,   352,   361,   370,
     384,   384,   384,   384,   384,   386,   393,   400,   407,   414,
     421,   428,   435,   435,   435,   435,   437,   439,   446,   453,
     461,   469,   477,   492,   492,   495,   495,   498,   501,   515,
     528,   528,   531,   531,   534,   534,   537,   537,   540,   555,
     558,   573,   584,   601,   608,   608,   611,   614,   624,   630,
     630,   633,   637,   641,   641,   641,   641,   641,   641,   642,
     642,   642,   642,   642,   642,   642,   643,   643,   643,   643,
     643,   643,   644,   644,   644,   644,   644,   644,   647,   651,
     651,   651,   651,   654,   658,   658,   661,   665,   665,   668,
     668,   671,   671,   676,   675
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
  "\"end of file\"", "error", "\"invalid token\"", "tINT", "tDOUBLE",
  "tSTRING", "COLOR", "GAMMA", "LEVEL", "STEPS", "INK_LIMIT", "PRINTER",
  "PARAMETER", "PARAMETER_INT", "PARAMETER_BOOL", "PARAMETER_FLOAT",
  "PARAMETER_CURVE", "DENSITY", "TOP", "LEFT", "SIZE_MODE", "RELATIVE",
  "PT", "IN", "MM", "HSIZE", "VSIZE", "BLACKLINE", "COLORLINE", "NOSCALE",
  "PATTERN", "XPATTERN", "EXTENDED", "IMAGE", "GRID", "SEMI", "CHANNEL",
  "CMYK", "KCMY", "RGB", "CMY", "GRAY", "WHITE", "MODE", "PAGESIZE",
  "ROUND", "MESSAGE", "OUTPUT", "START_JOB", "END_JOB", "END", "$accept",
  "NUMBER", "cmykspec", "kcmyspec", "rgbspec", "cmyspec", "grayspec",
  "whitespec", "extendedspec", "modespec1", "modespec2", "modespec",
  "round", "inputspec", "level", "channel_level", "gamma", "channel_gamma",
  "global_gamma", "steps", "ink_limit", "printer", "page_size_name",
  "page_size_custom", "page_size", "parameter_string", "parameter_int",
  "parameter_bool", "parameter_float", "parameter_curve", "parameter",
  "density", "top", "left", "size_relative", "size_in", "size_pt",
  "size_mm", "size_mode_1", "size_mode", "hsize", "vsize", "blackline",
  "colorline", "noscale", "color_block1", "color_blocks1a",
  "color_blocks1b", "color_blocks1", "color_block2a", "color_block2b",
  "color_block2", "color_blocks2a", "color_blocks2", "color_blocks",
  "patvars", "pattern", "xpattern", "grid", "image", "Message", "Messages",
  "message", "Output0", "Output1", "output", "start_job", "end_job",
  "A_Rule", "Rule", "A_Pattern", "Pattern", "Patterns", "Image", "Rules",
  "Print", "EOF", "Thing", "$@1", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-146)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -146,     9,     4,    57,    -1,     5,    29,    36,    40,    41,
      62,    71,    73,    29,    29,    29,    27,    29,    29,    59,
      76,    77,    33,    37,  -146,  -146,    78,  -146,  -146,  -146,
    -146,  -146,  -146,  -146,  -146,  -146,  -146,  -146,  -146,  -146,
    -146,  -146,  -146,  -146,  -146,  -146,  -146,  -146,  -146,  -146,
    -146,  -146,  -146,  -146,  -146,  -146,  -146,  -146,  -146,  -146,
    -146,  -146,  -146,    46,  -146,    49,  -146,    29,  -146,    29,
    -146,    29,    29,  -146,  -146,  -146,  -146,    79,    82,    83,
      29,    84,  -146,  -146,  -146,  -146,  -146,  -146,  -146,  -146,
    -146,  -146,  -146,  -146,  -146,  -146,  -146,  -146,  -146,    85,
    -146,  -146,  -146,  -146,  -146,  -146,  -146,  -146,  -146,  -146,
    -146,  -146,  -146,    87,  -146,  -146,    88,  -146,    89,  -146,
    -146,    90,  -146,    13,  -146,    42,  -146,  -146,  -146,  -146,
    -146,  -146,  -146,  -146,  -146,  -146,  -146,  -146,  -146,  -146,
      92,    29,     3,    93,  -146,  -146,  -146,  -146,    52,  -146,
      63,  -146,  -146,    29,     3,    29,    94,    29,    29,  -146,
    -146,  -146,  -146,    -5,  -146,  -146,  -146,  -146,  -146,    29,
    -146,    29,    29,    29,  -146,    29,  -146,  -146,    29,    29,
      29,  -146,  -146,    29,  -146,    29,  -146,  -146
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
     127,   133,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    21,    84,    87,    91,    92,   116,
     109,    95,    96,    93,    94,    97,    98,    99,   100,    33,
      34,   110,    40,    41,    44,    42,    43,   101,   102,   103,
     104,   115,   105,   106,   107,   117,   108,   111,    89,    90,
     112,   113,   114,     0,   128,   124,     1,     3,     2,     0,
      27,     0,     0,    28,     3,    29,    30,     0,     0,     0,
       0,     0,    45,    46,    47,    48,    50,    49,    51,    52,
      54,    53,    55,    56,    57,    58,    59,    60,    61,     0,
       4,     5,     6,     7,     8,     9,    11,    12,    13,    14,
      15,    16,    17,    19,    20,    22,     0,    31,    86,    88,
     118,     0,   126,   129,   130,   131,    26,    25,    24,    23,
      35,    36,    37,    38,    39,    10,    18,    32,    83,    85,
       0,     0,    74,     0,   119,   120,   121,   122,     0,   125,
       0,   134,    82,     0,    74,     0,     0,     0,    65,    76,
      70,    71,    72,    75,    77,    80,    81,   123,   132,     0,
      79,     0,     0,     0,    63,    66,    67,    73,     0,     0,
       0,    62,    64,     0,    68,     0,    78,    69
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -146,    -3,  -146,  -146,  -146,  -146,  -146,  -146,  -146,  -146,
    -146,  -146,  -146,  -146,  -146,  -146,  -146,  -146,  -146,  -146,
    -146,  -146,  -146,  -146,  -146,  -146,  -146,  -146,  -146,  -146,
    -146,  -146,  -146,  -146,  -146,  -146,  -146,  -146,  -146,  -146,
    -146,  -146,  -146,  -146,  -146,  -145,  -146,  -146,  -146,  -146,
    -146,   -64,  -146,  -146,   -54,  -146,  -146,  -146,  -146,  -146,
    -146,  -146,   -22,  -146,  -146,  -146,  -146,  -146,  -146,  -146,
    -146,  -146,  -146,  -146,  -146,  -146,  -146,  -146,  -146
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,   157,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    89,    90,    91,    92,    93,    51,
      52,    53,    54,    55,    56,   158,   175,   176,   159,   160,
     161,   162,   163,   164,   165,   154,   144,   145,   146,   122,
     139,   118,    57,    58,    59,    60,    61,    62,    63,    64,
     148,   149,   123,   124,     1,   125,   151,     2,    65
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      70,   155,    71,    75,    66,    72,    74,    68,    73,   155,
      82,    83,    84,   174,    94,    95,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
     182,   156,    74,    68,    17,    18,    19,    20,    21,   156,
     116,    76,   117,   141,   142,    77,    78,   143,    85,    86,
      87,    88,    22,    23,    24,    25,    26,    27,    28,    25,
      67,    68,    96,    69,   126,    99,   127,    79,   128,   129,
     100,   101,   102,   103,   104,   105,    80,   133,    81,    97,
      98,   120,   121,   119,   130,   131,   132,   167,   135,   134,
     136,   137,   150,   140,   138,   152,   166,   172,   168,   177,
     170,   147,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   153,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     169,     0,   171,     0,   173,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   178,     0,   179,   180,
     181,     0,     0,     0,     0,   183,   184,   185,     0,     0,
     186,     0,   187
};

static const yytype_int16 yycheck[] =
{
       3,     6,     3,     6,     0,     6,     3,     4,     3,     6,
      13,    14,    15,   158,    17,    18,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
     175,    36,     3,     4,    25,    26,    27,    28,    29,    36,
       3,     5,     5,    30,    31,     5,     5,    34,    21,    22,
      23,    24,    43,    44,    45,    46,    47,    48,    49,    46,
       3,     4,     3,     6,    67,    32,    69,     5,    71,    72,
      37,    38,    39,    40,    41,    42,     5,    80,     5,     3,
       3,    35,    33,     5,     5,     3,     3,    35,     3,     5,
       3,     3,    50,     3,     5,     3,     3,     3,    35,   163,
     154,   123,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   141,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     153,    -1,   155,    -1,   157,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   169,    -1,   171,   172,
     173,    -1,    -1,    -1,    -1,   178,   179,   180,    -1,    -1,
     183,    -1,   185
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   125,   128,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    25,    26,    27,
      28,    29,    43,    44,    45,    46,    47,    48,    49,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    90,    91,    92,    93,    94,    95,   113,   114,   115,
     116,   117,   118,   119,   120,   129,     0,     3,     4,     6,
      52,     3,     6,     3,     3,    52,     5,     5,     5,     5,
       5,     5,    52,    52,    52,    21,    22,    23,    24,    85,
      86,    87,    88,    89,    52,    52,     3,     3,     3,    32,
      37,    38,    39,    40,    41,    42,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,     3,     5,   112,     5,
      35,    33,   110,   123,   124,   126,    52,    52,    52,    52,
       5,     3,     3,    52,     5,     3,     3,     3,     5,   111,
       3,    30,    31,    34,   107,   108,   109,   113,   121,   122,
      50,   127,     3,    52,   106,     6,    36,    52,    96,    99,
     100,   101,   102,   103,   104,   105,     3,    35,    35,    52,
     105,    52,     3,    52,    96,    97,    98,   102,    52,    52,
      52,    52,    96,    52,    52,    52,    52,    52
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    51,    52,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    60,    60,    60,    60,    60,    60,    61,    62,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    75,    76,    77,    78,    79,    80,
      81,    81,    81,    81,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    89,    89,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    97,    98,    98,    99,   100,   101,
     102,   102,   103,   103,   104,   104,   105,   105,   106,   107,
     108,   109,   110,   111,   112,   112,   113,   114,   115,   116,
     116,   117,   118,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   120,   121,
     121,   121,   121,   122,   123,   123,   124,   125,   125,   126,
     126,   127,   127,   129,   128
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     2,     3,     3,     3,     3,     2,     2,     2,
       2,     2,     3,     1,     1,     3,     3,     3,     3,     3,
       1,     1,     1,     1,     1,     2,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     2,     2,
       2,     2,     3,     1,     2,     0,     1,     2,     4,     5,
       1,     1,     1,     2,     0,     1,     1,     1,     5,     3,
       2,     2,     3,     1,     0,     2,     2,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     2,     0,     2,     1,     0,     2,     1,
       1,     0,     2,     0,     4
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
  case 3: /* NUMBER: tINT  */
#line 146 "testpatterny.y"
        {
	}
#line 1546 "testpatterny.c"
    break;

  case 4: /* cmykspec: CMYK  */
#line 151 "testpatterny.y"
        {
	  if (getenv("STP_TESTPATTERN_DEBUG"))
	    fprintf(stderr, ">>>cmykspec\n");
	  global_image_type = "CMYK";
	  global_channel_depth = 4;
	  global_invert_data = 0;
	}
#line 1558 "testpatterny.c"
    break;

  case 5: /* kcmyspec: KCMY  */
#line 161 "testpatterny.y"
        {
	  if (getenv("STP_TESTPATTERN_DEBUG"))
	    fprintf(stderr, ">>>kcmyspec\n");
	  global_image_type = "KCMY";
	  global_channel_depth = 4;
	  global_invert_data = 0;
	}
#line 1570 "testpatterny.c"
    break;

  case 6: /* rgbspec: RGB  */
#line 171 "testpatterny.y"
        {
	  if (getenv("STP_TESTPATTERN_DEBUG"))
	    fprintf(stderr, ">>>rgbspec\n");
	  global_image_type = "RGB";
	  global_channel_depth = 3;
	  global_invert_data = 1;
	}
#line 1582 "testpatterny.c"
    break;

  case 7: /* cmyspec: CMY  */
#line 181 "testpatterny.y"
        {
	  if (getenv("STP_TESTPATTERN_DEBUG"))
	    fprintf(stderr, ">>>cmyspec\n");
	  global_image_type = "CMY";
	  global_channel_depth = 3;
	  global_invert_data = 0;
	}
#line 1594 "testpatterny.c"
    break;

  case 8: /* grayspec: GRAY  */
#line 191 "testpatterny.y"
        {
	  if (getenv("STP_TESTPATTERN_DEBUG"))
	    fprintf(stderr, ">>>grayspec\n");
	  global_image_type = "Grayscale";
	  global_channel_depth = 1;
	  global_invert_data = 0;
	}
#line 1606 "testpatterny.c"
    break;

  case 9: /* whitespec: WHITE  */
#line 201 "testpatterny.y"
        {
	  if (getenv("STP_TESTPATTERN_DEBUG"))
	    fprintf(stderr, ">>>whitespec\n");
	  global_image_type = "Whitescale";
	  global_channel_depth = 1;
	  global_invert_data = 1;
	}
#line 1618 "testpatterny.c"
    break;

  case 10: /* extendedspec: EXTENDED tINT  */
#line 211 "testpatterny.y"
        {
	  if (getenv("STP_TESTPATTERN_DEBUG"))
	    fprintf(stderr, ">>>extendedspec %d\n", (yyvsp[0].ival));
	  global_image_type = "Raw";
	  global_invert_data = 0;
	  global_channel_depth = (yyvsp[0].ival);
	}
#line 1630 "testpatterny.c"
    break;

  case 18: /* modespec2: modespec1 tINT  */
#line 224 "testpatterny.y"
        {
	  if (getenv("STP_TESTPATTERN_DEBUG"))
	    fprintf(stderr, ">>>modespec2 %d\n", (yyvsp[0].ival));
	  if ((yyvsp[0].ival) == 8 || (yyvsp[0].ival) == 16)
	    global_bit_depth = (yyvsp[0].ival);
	}
#line 1641 "testpatterny.c"
    break;

  case 21: /* round: ROUND  */
#line 235 "testpatterny.y"
        {
	  if (getenv("STP_TESTPATTERN_DEBUG"))
	    fprintf(stderr, ">>>round\n");
	  global_round_size = 1;
	}
#line 1651 "testpatterny.c"
    break;

  case 23: /* level: LEVEL COLOR NUMBER  */
#line 245 "testpatterny.y"
        {
	  int channel = find_color((yyvsp[-1].sval));
	  if (getenv("STP_TESTPATTERN_DEBUG"))
	    fprintf(stderr, ">>>level %s %f\n", (yyvsp[-1].sval), (yyvsp[0].dval));
	  if (channel >= 0)
	    global_levels[channel] = (yyvsp[0].dval);
	}
#line 1663 "testpatterny.c"
    break;

  case 24: /* channel_level: LEVEL tINT NUMBER  */
#line 255 "testpatterny.y"
        {
	  if (getenv("STP_TESTPATTERN_DEBUG"))
	    fprintf(stderr, ">>>channel_level %d %f\n", (yyvsp[-1].ival), (yyvsp[0].dval));
	  if ((yyvsp[-1].ival) >= 0 && (yyvsp[-1].ival) <= STP_CHANNEL_LIMIT)
	    global_levels[(yyvsp[-1].ival)] = (yyvsp[0].dval);
	}
#line 1674 "testpatterny.c"
    break;

  case 25: /* gamma: GAMMA COLOR NUMBER  */
#line 264 "testpatterny.y"
        {
	  int channel = find_color((yyvsp[-1].sval));
	  if (getenv("STP_TESTPATTERN_DEBUG"))
	    fprintf(stderr, ">>>gamma %s %f\n", (yyvsp[-1].sval), (yyvsp[0].dval));
	  if (channel >= 0)
	    global_gammas[channel] = (yyvsp[0].dval);
	}
#line 1686 "testpatterny.c"
    break;

  case 26: /* channel_gamma: GAMMA tINT NUMBER  */
#line 274 "testpatterny.y"
        {
	  if (getenv("STP_TESTPATTERN_DEBUG"))
	    fprintf(stderr, ">>>channel_gamma %d %f\n", (yyvsp[-1].ival), (yyvsp[0].dval));
	  if ((yyvsp[-1].ival) >= 0 && (yyvsp[-1].ival) <= STP_CHANNEL_LIMIT)
	    global_gammas[(yyvsp[-1].ival)] = (yyvsp[0].dval);
	}
#line 1697 "testpatterny.c"
    break;

  case 27: /* global_gamma: GAMMA NUMBER  */
#line 283 "testpatterny.y"
        {
	  if (getenv("STP_TESTPATTERN_DEBUG"))
	    fprintf(stderr, ">>>global_gamma %f\n", (yyvsp[0].dval));
	  global_gamma = (yyvsp[0].dval);
	}
#line 1707 "testpatterny.c"
    break;

  case 28: /* steps: STEPS tINT  */
#line 290 "testpatterny.y"
        {
	  if (getenv("STP_TESTPATTERN_DEBUG"))
	    fprintf(stderr, ">>>steps %d\n", (yyvsp[0].ival));
	  global_steps = (yyvsp[0].ival);
	}
#line 1717 "testpatterny.c"
    break;

  case 29: /* ink_limit: INK_LIMIT NUMBER  */
#line 297 "testpatterny.y"
        {
	  if (getenv("STP_TESTPATTERN_DEBUG"))
	    fprintf(stderr, ">>>ink_limit %f\n", (yyvsp[0].dval));
	  global_ink_limit = (yyvsp[0].dval);
	}
#line 1727 "testpatterny.c"
    break;

  case 30: /* printer: PRINTER tSTRING  */
#line 304 "testpatterny.y"
        {
	  if (getenv("STP_TESTPATTERN_DEBUG"))
	    fprintf(stderr, ">>>printer %s\n", (yyvsp[0].sval));
	  global_printer = stp_strdup((yyvsp[0].sval));
	  free((yyvsp[0].sval));
	}
#line 1738 "testpatterny.c"
    break;

  case 31: /* page_size_name: PAGESIZE tSTRING  */
#line 313 "testpatterny.y"
        {
	  if (getenv("STP_TESTPATTERN_DEBUG"))
	    fprintf(stderr, ">>>page_size_name %s\n", (yyvsp[0].sval));
	  stp_set_string_parameter(global_vars, "PageSize", (yyvsp[0].sval));
	  free((yyvsp[0].sval));
	}
#line 1749 "testpatterny.c"
    break;

  case 32: /* page_size_custom: PAGESIZE tINT tINT  */
#line 322 "testpatterny.y"
        {
	  if (getenv("STP_TESTPATTERN_DEBUG"))
	    fprintf(stderr, ">>>page_size_custom %d %d\n", (yyvsp[-1].ival), (yyvsp[0].ival));
	  stp_set_page_width(global_vars, (yyvsp[-1].ival));
	  stp_set_page_height(global_vars, (yyvsp[0].ival));
	}
#line 1760 "testpatterny.c"
    break;

  case 35: /* parameter_string: PARAMETER tSTRING tSTRING  */
#line 334 "testpatterny.y"
        {
	  if (getenv("STP_TESTPATTERN_DEBUG"))
	    fprintf(stderr, ">>>parameter_string %s %s\n", (yyvsp[-1].sval), (yyvsp[0].sval));
	  stp_set_string_parameter(global_vars, (yyvsp[-1].sval), (yyvsp[0].sval));
	  free((yyvsp[-1].sval));
	  free((yyvsp[0].sval));
	}
#line 1772 "testpatterny.c"
    break;

  case 36: /* parameter_int: PARAMETER_INT tSTRING tINT  */
#line 344 "testpatterny.y"
        {
	  if (getenv("STP_TESTPATTERN_DEBUG"))
	    fprintf(stderr, ">>>parameter_int %s %d\n", (yyvsp[-1].sval), (yyvsp[0].ival));
	  stp_set_int_parameter(global_vars, (yyvsp[-1].sval), (yyvsp[0].ival));
	  free((yyvsp[-1].sval));
	}
#line 1783 "testpatterny.c"
    break;

  case 37: /* parameter_bool: PARAMETER_BOOL tSTRING tINT  */
#line 353 "testpatterny.y"
        {
	  if (getenv("STP_TESTPATTERN_DEBUG"))
	    fprintf(stderr, ">>>parameter_bool %s %d\n", (yyvsp[-1].sval), (yyvsp[0].ival));
	  stp_set_boolean_parameter(global_vars, (yyvsp[-1].sval), (yyvsp[0].ival));
	  free((yyvsp[-1].sval));
	}
#line 1794 "testpatterny.c"
    break;

  case 38: /* parameter_float: PARAMETER_FLOAT tSTRING NUMBER  */
#line 362 "testpatterny.y"
        {
	  if (getenv("STP_TESTPATTERN_DEBUG"))
	    fprintf(stderr, ">>>parameter_float %s %f\n", (yyvsp[-1].sval), (yyvsp[0].dval));
	  stp_set_float_parameter(global_vars, (yyvsp[-1].sval), (yyvsp[0].dval));
	  free((yyvsp[-1].sval));
	}
#line 1805 "testpatterny.c"
    break;

  case 39: /* parameter_curve: PARAMETER_CURVE tSTRING tSTRING  */
#line 371 "testpatterny.y"
        {
	  stp_curve_t *curve = stp_curve_create_from_string((yyvsp[0].sval));
	  if (getenv("STP_TESTPATTERN_DEBUG"))
	    fprintf(stderr, ">>>parameter_curve %s %s\n", (yyvsp[-1].sval), (yyvsp[0].sval));
	  if (curve)
	    {
	      stp_set_curve_parameter(global_vars, (yyvsp[-1].sval), curve);
	      stp_curve_destroy(curve);
	    }
	  free((yyvsp[-1].sval));
	}
#line 1821 "testpatterny.c"
    break;

  case 45: /* density: DENSITY NUMBER  */
#line 387 "testpatterny.y"
        {
	  if (getenv("STP_TESTPATTERN_DEBUG"))
	    fprintf(stderr, ">>>density %f\n", (yyvsp[0].dval));
	  global_density = (yyvsp[0].dval);
	}
#line 1831 "testpatterny.c"
    break;

  case 46: /* top: TOP NUMBER  */
#line 394 "testpatterny.y"
        {
	  if (getenv("STP_TESTPATTERN_DEBUG"))
	    fprintf(stderr, ">>>top %f\n", (yyvsp[0].dval));
	  global_xtop = (yyvsp[0].dval);
	}
#line 1841 "testpatterny.c"
    break;

  case 47: /* left: LEFT NUMBER  */
#line 401 "testpatterny.y"
        {
	  if (getenv("STP_TESTPATTERN_DEBUG"))
 	    fprintf(stderr, ">>>left %f\n", (yyvsp[0].dval));
	  global_xleft = (yyvsp[0].dval);
	}
#line 1851 "testpatterny.c"
    break;

  case 48: /* size_relative: RELATIVE  */
#line 408 "testpatterny.y"
        {
	  if (getenv("STP_TESTPATTERN_DEBUG"))
 	    fprintf(stderr, ">>>relative size\n");
	  global_size_mode = SIZE_RELATIVE;
	}
#line 1861 "testpatterny.c"
    break;

  case 49: /* size_in: IN  */
#line 415 "testpatterny.y"
        {
	  if (getenv("STP_TESTPATTERN_DEBUG"))
 	    fprintf(stderr, ">>>size inches\n");
	  global_size_mode = SIZE_IN;
	}
#line 1871 "testpatterny.c"
    break;

  case 50: /* size_pt: PT  */
#line 422 "testpatterny.y"
        {
	  if (getenv("STP_TESTPATTERN_DEBUG"))
 	    fprintf(stderr, ">>>size pt\n");
	  global_size_mode = SIZE_PT;
	}
#line 1881 "testpatterny.c"
    break;

  case 51: /* size_mm: MM  */
#line 429 "testpatterny.y"
        {
	  if (getenv("STP_TESTPATTERN_DEBUG"))
 	    fprintf(stderr, ">>>size mm\n");
	  global_size_mode = SIZE_MM;
	}
#line 1891 "testpatterny.c"
    break;

  case 57: /* hsize: HSIZE NUMBER  */
#line 440 "testpatterny.y"
        {
	  if (getenv("STP_TESTPATTERN_DEBUG"))
	    fprintf(stderr, ">>>hsize %f\n", (yyvsp[0].dval));
	  global_hsize = (yyvsp[0].dval);
	}
#line 1901 "testpatterny.c"
    break;

  case 58: /* vsize: VSIZE NUMBER  */
#line 447 "testpatterny.y"
        {
	  if (getenv("STP_TESTPATTERN_DEBUG"))
	    fprintf(stderr, ">>>vsize %f\n", (yyvsp[0].dval));
	  global_vsize = (yyvsp[0].dval);
	}
#line 1911 "testpatterny.c"
    break;

  case 59: /* blackline: BLACKLINE tINT  */
#line 454 "testpatterny.y"
        {
	  if (getenv("STP_TESTPATTERN_DEBUG"))
	    fprintf(stderr, ">>>blackline %d\n", (yyvsp[0].ival));
	  global_noblackline = !((yyvsp[0].ival));
	}
#line 1921 "testpatterny.c"
    break;

  case 60: /* colorline: COLORLINE tINT  */
#line 462 "testpatterny.y"
        {
	  if (getenv("STP_TESTPATTERN_DEBUG"))
	    fprintf(stderr, ">>>colorline %d\n", (yyvsp[0].ival));
	  global_colorline = ((yyvsp[0].ival) != 0);
	}
#line 1931 "testpatterny.c"
    break;

  case 61: /* noscale: NOSCALE tINT  */
#line 470 "testpatterny.y"
        {
	  if (getenv("STP_TESTPATTERN_DEBUG"))
	    fprintf(stderr, ">>>noscale %d\n", (yyvsp[0].ival));
	  global_noscale = (yyvsp[0].ival);
	}
#line 1941 "testpatterny.c"
    break;

  case 62: /* color_block1: NUMBER NUMBER NUMBER  */
#line 478 "testpatterny.y"
        {
	  if (getenv("STP_TESTPATTERN_DEBUG"))
	    fprintf(stderr, ">>>color_block1 %f %f %f (%d)\n", (yyvsp[-2].dval), (yyvsp[-1].dval), (yyvsp[0].dval),
		    current_index);
	  if (current_index < STP_CHANNEL_LIMIT)
	    {
	      current_testpattern->d.pattern.mins[current_index] = (yyvsp[-2].dval);
	      current_testpattern->d.pattern.vals[current_index] = (yyvsp[-1].dval);
	      current_testpattern->d.pattern.gammas[current_index] = (yyvsp[0].dval);
	      current_index++;
	    }
	}
#line 1958 "testpatterny.c"
    break;

  case 68: /* color_block2a: COLOR NUMBER NUMBER NUMBER  */
#line 502 "testpatterny.y"
        {
	  int channel = find_color((yyvsp[-3].sval));
	  if (getenv("STP_TESTPATTERN_DEBUG"))
	    fprintf(stderr, ">>>color_block2a %s %f %f %f\n", (yyvsp[-3].sval), (yyvsp[-2].dval), (yyvsp[-1].dval), (yyvsp[0].dval));
	  if (channel >= 0 && channel < STP_CHANNEL_LIMIT)
	    {
	      current_testpattern->d.pattern.mins[channel] = (yyvsp[-2].dval);
	      current_testpattern->d.pattern.vals[channel] = (yyvsp[-1].dval);
	      current_testpattern->d.pattern.gammas[channel] = (yyvsp[0].dval);
	    }
	}
#line 1974 "testpatterny.c"
    break;

  case 69: /* color_block2b: CHANNEL tINT NUMBER NUMBER NUMBER  */
#line 516 "testpatterny.y"
        {
	  if (getenv("STP_TESTPATTERN_DEBUG"))
	    fprintf(stderr, ">>>color_block2b %d %f %f %f\n", (yyvsp[-3].ival), (yyvsp[-2].dval), (yyvsp[-1].dval), (yyvsp[0].dval));
	  if ((yyvsp[-3].ival) >= 0 && (yyvsp[-3].ival) < STP_CHANNEL_LIMIT)
	    {
	      current_testpattern->d.pattern.mins[(yyvsp[-3].ival)] = (yyvsp[-2].dval);
	      current_testpattern->d.pattern.vals[(yyvsp[-3].ival)] = (yyvsp[-1].dval);
	      current_testpattern->d.pattern.gammas[(yyvsp[-3].ival)] = (yyvsp[0].dval);
	    }
	}
#line 1989 "testpatterny.c"
    break;

  case 78: /* patvars: NUMBER NUMBER NUMBER NUMBER NUMBER  */
#line 541 "testpatterny.y"
        {
	  if (getenv("STP_TESTPATTERN_DEBUG"))
	    fprintf(stderr, ">>>patvars %f %f %f %f %f\n", (yyvsp[-4].dval), (yyvsp[-3].dval), (yyvsp[-2].dval), (yyvsp[-1].dval), (yyvsp[0].dval));
	  current_testpattern->type = E_PATTERN;
	  current_testpattern->d.pattern.lower = (yyvsp[-4].dval);
	  current_testpattern->d.pattern.upper = (yyvsp[-3].dval);
	  current_testpattern->d.pattern.levels[1] = (yyvsp[-2].dval);
	  current_testpattern->d.pattern.levels[2] = (yyvsp[-1].dval);
	  current_testpattern->d.pattern.levels[3] = (yyvsp[0].dval);
	  current_testpattern = get_next_testpattern();
	  current_index = 0;
	}
#line 2006 "testpatterny.c"
    break;

  case 80: /* xpattern: XPATTERN color_blocks  */
#line 559 "testpatterny.y"
        {
	  if (getenv("STP_TESTPATTERN_DEBUG"))
	    fprintf(stderr, ">>>xpattern\n");
	  if (global_channel_depth == 0)
	    {
	      fprintf(stderr, "xpattern may only be used with extended color depth\n");
	      exit(1);
	    }
	  current_testpattern->type = E_XPATTERN;
	  current_testpattern = get_next_testpattern();
	  current_index = 0;
	}
#line 2023 "testpatterny.c"
    break;

  case 81: /* grid: GRID tINT  */
#line 574 "testpatterny.y"
        {
	  if (getenv("STP_TESTPATTERN_DEBUG"))
	    fprintf(stderr, ">>>grid %d\n", (yyvsp[0].ival));
	  current_testpattern->type = E_GRID;
	  current_testpattern->d.grid.ticks = (yyvsp[0].ival);
	  current_testpattern = get_next_testpattern();
	  current_index = 0;
	}
#line 2036 "testpatterny.c"
    break;

  case 82: /* image: IMAGE tINT tINT  */
#line 585 "testpatterny.y"
        {
	  if (getenv("STP_TESTPATTERN_DEBUG"))
	    fprintf(stderr, ">>>image %d %d\n", (yyvsp[-1].ival), (yyvsp[0].ival));
	  current_testpattern->type = E_IMAGE;
	  current_testpattern->d.image.x = (yyvsp[-1].ival);
	  current_testpattern->d.image.y = (yyvsp[0].ival);
	  if (current_testpattern->d.image.x <= 0 ||
	      current_testpattern->d.image.y <= 0)
	    {
	      fprintf(stderr, "image width and height must be greater than zero\n");
	      exit(1);
	    }
	  return 0;
	}
#line 2055 "testpatterny.c"
    break;

  case 83: /* Message: tSTRING  */
#line 602 "testpatterny.y"
        {
	  fprintf(stderr,"%s",(yyvsp[0].sval));
	  free((yyvsp[0].sval));
	}
#line 2064 "testpatterny.c"
    break;

  case 87: /* Output0: OUTPUT  */
#line 615 "testpatterny.y"
        {
	  close_output();
	  if (global_output)
	    free(global_output);
	  global_output = NULL;
	  output = stdout;
	}
#line 2076 "testpatterny.c"
    break;

  case 88: /* Output1: OUTPUT tSTRING  */
#line 625 "testpatterny.y"
        {
	  global_output = (yyvsp[0].sval);
	}
#line 2084 "testpatterny.c"
    break;

  case 91: /* start_job: START_JOB  */
#line 634 "testpatterny.y"
        { start_job = 1; }
#line 2090 "testpatterny.c"
    break;

  case 92: /* end_job: END_JOB  */
#line 638 "testpatterny.y"
        { end_job = 1; }
#line 2096 "testpatterny.c"
    break;

  case 118: /* Rule: A_Rule SEMI  */
#line 648 "testpatterny.y"
        { global_did_something = 1; }
#line 2102 "testpatterny.c"
    break;

  case 123: /* Pattern: A_Pattern SEMI  */
#line 655 "testpatterny.y"
        { global_did_something = 1; }
#line 2108 "testpatterny.c"
    break;

  case 126: /* Image: image  */
#line 662 "testpatterny.y"
        { global_did_something = 1; }
#line 2114 "testpatterny.c"
    break;

  case 132: /* EOF: END SEMI  */
#line 672 "testpatterny.y"
        { return 0; }
#line 2120 "testpatterny.c"
    break;

  case 133: /* $@1: %empty  */
#line 676 "testpatterny.y"
        {
	  current_testpattern = get_next_testpattern();
	}
#line 2128 "testpatterny.c"
    break;


#line 2132 "testpatterny.c"

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

#line 682 "testpatterny.y"

