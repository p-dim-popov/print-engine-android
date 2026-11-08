/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

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
