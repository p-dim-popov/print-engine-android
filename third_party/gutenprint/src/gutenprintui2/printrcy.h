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
