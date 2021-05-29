/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20170709

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "grammar.y"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>

#include "defs.h"
#include "common.h"
#include "miniccutils.h"
#include "passe_1.h"
#include "passe_2.h"



/* Global variables */
extern bool stop_after_syntax;
extern bool stop_after_verif;
extern char * outfile;


/* prototypes */
int yylex(void);
extern int yylineno;

void yyerror(node_t * program_root, char * s);
void analyse_tree(node_t root);
node_t make_node(node_nature nature, int nops, ...);
/* A completer */

#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#line 37 "grammar.y"
typedef union {
    int32_t intval;
    char * strval;
    node_t ptr;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 66 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(node_t *program_root)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(node_t *program_root, const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(program_root, msg)
#endif

extern int YYPARSE_DECL();

#define TOK_VOID 257
#define TOK_INT 258
#define TOK_INTVAL 259
#define TOK_BOOL 260
#define TOK_TRUE 261
#define TOK_FALSE 262
#define TOK_IDENT 263
#define TOK_IF 264
#define TOK_ELSE 265
#define TOK_WHILE 266
#define TOK_FOR 267
#define TOK_PRINT 268
#define TOK_SEMICOL 269
#define TOK_COMMA 270
#define TOK_LPAR 271
#define TOK_RPAR 272
#define TOK_LACC 273
#define TOK_RACC 274
#define TOK_STRING 275
#define TOK_DO 276
#define TOK_GT 277
#define TOK_LT 278
#define TOK_THEN 279
#define TOK_AFFECT 280
#define TOK_OR 281
#define TOK_AND 282
#define TOK_BOR 283
#define TOK_BXOR 284
#define TOK_BAND 285
#define TOK_EQ 286
#define TOK_NE 287
#define TOK_GE 288
#define TOK_LE 289
#define TOK_SRL 290
#define TOK_SRA 291
#define TOK_SLL 292
#define TOK_PLUS 293
#define TOK_MINUS 294
#define TOK_MUL 295
#define TOK_DIV 296
#define TOK_MOD 297
#define TOK_UMINUS 298
#define TOK_NOT 299
#define TOK_BNOT 300
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    0,    2,    2,    8,    1,    1,    3,    7,    7,
    4,    5,    5,    5,   15,   15,   14,   14,   13,   13,
   13,   13,   13,   13,   13,   13,   13,   13,   13,   13,
   13,   13,   13,   13,   13,   13,   13,   13,   13,   13,
   13,   13,   13,   13,   13,   13,   12,   11,   11,   11,
   11,   11,   11,   11,   11,   11,   10,   10,    9,    9,
    6,    6,
};
static const YYINT yylen[] = {                            2,
    2,    1,    1,    2,    5,    1,    0,    3,    1,    3,
    1,    1,    1,    1,    1,    1,    3,    1,    3,    3,
    3,    3,    3,    3,    3,    2,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    2,    2,
    3,    3,    1,    1,    1,    1,    4,    2,    7,    5,
    5,    9,    7,    1,    1,    5,    1,    2,    1,    0,
    1,    3,
};
static const YYINT yydefred[] = {                         0,
   14,   12,   13,    0,    0,    3,    0,    2,    4,    1,
   11,    0,    0,   61,    0,    0,    8,    0,    0,   43,
   44,   45,    0,    0,    0,    0,    0,    0,    0,   62,
    0,    5,    0,   26,   39,   40,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   41,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   19,   20,   23,
    0,    0,    0,    0,   55,    0,    0,    0,   57,   54,
    0,    0,    0,    0,    0,    0,   47,   58,   48,    0,
    0,    0,   16,   15,    0,   18,    0,    0,    0,    0,
    0,    0,    0,    0,   51,    0,   17,   56,    0,    0,
    0,    0,   49,    0,   53,    0,   52,
};
static const YYINT yydgoto[] = {                          4,
   57,    5,    6,   27,    7,   13,   14,    8,   87,   88,
   89,   90,   91,  105,  106,
};
static const YYINT yysindex[] = {                      -240,
    0,    0,    0,    0, -240,    0, -262,    0,    0,    0,
    0, -265, -258,    0, -267, -214,    0, -262, -254,    0,
    0,    0, -214, -214, -214, -214, -238,  305, -228,    0,
 -240,    0,   56,    0,    0,    0, -214, -214, -214, -214,
 -214, -214, -214, -214, -214, -214, -214, -214, -214, -214,
 -214, -214, -214, -214, -214, -214,  -94, -240, -262,    0,
  305, -106, -106,  326,  347,  368,  389,  410,  504,  504,
 -106, -106,  -52,  -52,  -52, -213, -213,    0,    0,    0,
 -212, -207, -202, -200,    0,  -94, -187,  -94,    0,    0,
  -29, -214, -214, -214, -259, -192,    0,    0,    0,   82,
  108,    1,    0,    0, -191,    0, -179,  -94,  -94, -214,
 -259, -161, -214, -147,    0,   30,    0,    0,  134,  -94,
 -214, -156,    0,  160,    0,  -94,    0,
};
static const YYINT yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -174,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  -58, -116, -174,    0,
 -201,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, -154, -152,    0,    0,
 -219,  439,  460, -226, -120, -126,  -89, -181,  533,  540,
  481,  502,  241,  265,  289,  189,  215,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, -145,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, -136,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,
};
static const YYINT yygindex[] = {                         0,
    0,  103,   -2,   -5,  -17,    0,  118,  136,    0,    0,
   90,  120,  -16,    0,   34,
};
#define YYTABLESIZE 827
static const YYINT yytable[] = {                         28,
   11,   12,    9,   11,   19,   15,   33,   34,   35,   36,
   17,   18,   29,   59,   16,  103,    1,    2,   31,    3,
   61,   62,   63,   64,   65,   66,   67,   68,   69,   70,
   71,   72,   73,   74,   75,   76,   77,   78,   79,   80,
   59,   37,   32,   32,   20,   32,   21,   22,   11,   42,
   42,   16,   42,   29,   32,    9,   23,    7,   92,    7,
    7,    7,    7,   93,    7,    7,    7,    7,   94,    7,
   95,    7,    7,  107,    7,  100,  101,  102,  111,   24,
  112,   54,   55,   56,   25,   26,   97,   33,   33,  104,
   33,  113,    7,  116,    9,    9,  119,    7,    7,   33,
   33,   33,   33,   33,  124,  104,    6,  118,    6,    6,
    6,    6,  125,    6,    6,    6,    6,  120,    6,   60,
    6,    6,   50,    6,   50,   50,   50,   50,   59,   50,
   50,   50,   50,   58,   50,   30,   50,   50,   32,   50,
   10,    6,   34,   34,  117,   34,    6,    6,   31,   31,
    0,   31,   10,   10,   34,   34,   34,   50,    0,    0,
   31,   31,   50,   50,   20,    0,   21,   22,   11,   81,
    0,   82,   83,   84,   85,   96,   23,   98,   31,   35,
   35,   86,   35,   49,   50,   51,   52,   53,   54,   55,
   56,   35,   35,   35,   35,    0,    0,  114,  115,   24,
    0,    0,    0,    0,   25,   26,    0,    0,    0,  123,
   46,   46,    0,   46,    0,  127,    0,    0,   46,   46,
    0,    0,   46,   46,   46,   46,   46,   46,   46,   46,
   46,   46,   46,   46,   46,   46,   46,   46,   46,   99,
   52,   53,   54,   55,   56,    0,    0,   38,   39,    0,
    0,   40,   41,   42,   43,   44,   45,   46,   47,   48,
   49,   50,   51,   52,   53,   54,   55,   56,    0,  110,
    0,    0,    0,    0,    0,    0,    0,   38,   39,    0,
    0,   40,   41,   42,   43,   44,   45,   46,   47,   48,
   49,   50,   51,   52,   53,   54,   55,   56,  121,    0,
    0,    0,    0,    0,    0,    0,   38,   39,    0,    0,
   40,   41,   42,   43,   44,   45,   46,   47,   48,   49,
   50,   51,   52,   53,   54,   55,   56,   60,    0,    0,
    0,    0,   38,   39,    0,    0,   40,   41,   42,   43,
   44,   45,   46,   47,   48,   49,   50,   51,   52,   53,
   54,   55,   56,  108,    0,    0,    0,    0,   38,   39,
    0,    0,   40,   41,   42,   43,   44,   45,   46,   47,
   48,   49,   50,   51,   52,   53,   54,   55,   56,  109,
    0,    0,    0,    0,   38,   39,    0,    0,   40,   41,
   42,   43,   44,   45,   46,   47,   48,   49,   50,   51,
   52,   53,   54,   55,   56,  122,    0,    0,    0,    0,
   38,   39,    0,    0,   40,   41,   42,   43,   44,   45,
   46,   47,   48,   49,   50,   51,   52,   53,   54,   55,
   56,  126,    0,    0,    0,    0,   38,   39,    0,    0,
   40,   41,   42,   43,   44,   45,   46,   47,   48,   49,
   50,   51,   52,   53,   54,   55,   56,   21,   21,    0,
   21,    0,    0,    0,    0,   21,   21,    0,    0,   21,
   21,   21,   21,   21,   21,   21,   21,   21,   21,   21,
   21,   21,   21,   22,   22,    0,   22,    0,    0,    0,
    0,   22,   22,    0,    0,   22,   22,   22,   22,   22,
   22,   22,   22,   22,   22,   22,   22,   22,   22,   36,
   36,    0,   36,    0,    0,    0,    0,   36,   36,    0,
    0,   36,   36,   36,   36,   36,   36,   36,   36,   36,
   36,   36,   36,   37,   37,    0,   37,    0,    0,    0,
    0,   37,   37,    0,    0,   37,   37,   37,   37,   37,
   37,   37,   37,   37,   37,   37,   37,   38,   38,    0,
   38,    0,    0,    0,    0,   38,   38,    0,    0,   38,
   38,   38,   38,   38,   38,   38,   38,   38,   38,   38,
   38,   38,   39,    0,    0,   40,   41,   42,   43,   44,
   45,   46,   47,   48,   49,   50,   51,   52,   53,   54,
   55,   56,   38,   39,    0,    0,    0,   41,   42,   43,
   44,   45,   46,   47,   48,   49,   50,   51,   52,   53,
   54,   55,   56,   38,   39,    0,    0,    0,    0,   42,
   43,   44,   45,   46,   47,   48,   49,   50,   51,   52,
   53,   54,   55,   56,   38,   39,    0,    0,    0,    0,
    0,   43,   44,   45,   46,   47,   48,   49,   50,   51,
   52,   53,   54,   55,   56,   38,   39,    0,    0,    0,
    0,    0,    0,   44,   45,   46,   47,   48,   49,   50,
   51,   52,   53,   54,   55,   56,   38,   39,    0,    0,
    0,    0,    0,    0,    0,   45,   46,   47,   48,   49,
   50,   51,   52,   53,   54,   55,   56,   25,   25,    0,
   25,    0,    0,    0,    0,   25,   25,    0,    0,   25,
   25,   25,   25,   25,   25,   25,   25,   25,   24,   24,
    0,   24,    0,    0,    0,    0,   24,   24,    0,    0,
   24,   24,   24,   24,   24,   24,   24,   24,   24,   27,
   27,    0,   27,    0,    0,    0,    0,   27,   27,    0,
    0,   27,   27,   27,   27,   27,   27,   27,   27,   27,
   28,   28,    0,   28,    0,    0,    0,    0,   28,   28,
   38,   39,   28,   28,   28,   28,   28,   28,   28,   28,
   28,   47,   48,   49,   50,   51,   52,   53,   54,   55,
   56,   29,   29,    0,   29,    0,    0,    0,   30,   30,
    0,   30,    0,   29,   29,   29,   29,   29,   29,   29,
   30,   30,   30,   30,   30,   30,   30,
};
static const YYINT yycheck[] = {                         16,
  263,    7,    5,  263,  272,  271,   23,   24,   25,   26,
  269,  270,   18,   31,  280,  275,  257,  258,  273,  260,
   37,   38,   39,   40,   41,   42,   43,   44,   45,   46,
   47,   48,   49,   50,   51,   52,   53,   54,   55,   56,
   58,  280,  269,  270,  259,  272,  261,  262,  263,  269,
  270,  280,  272,   59,  281,   58,  271,  259,  271,  261,
  262,  263,  264,  271,  266,  267,  268,  269,  271,  271,
  271,  273,  274,  266,  276,   92,   93,   94,  270,  294,
  272,  295,  296,  297,  299,  300,  274,  269,  270,   95,
  272,  271,  294,  110,  269,  270,  113,  299,  300,  281,
  282,  283,  284,  285,  121,  111,  259,  269,  261,  262,
  263,  264,  269,  266,  267,  268,  269,  265,  271,  274,
  273,  274,  259,  276,  261,  262,  263,  264,  274,  266,
  267,  268,  269,   31,  271,   18,  273,  274,   19,  276,
    5,  294,  269,  270,  111,  272,  299,  300,  269,  270,
   -1,  272,  269,  270,  281,  282,  283,  294,   -1,   -1,
  281,  282,  299,  300,  259,   -1,  261,  262,  263,  264,
   -1,  266,  267,  268,  269,   86,  271,   88,  273,  269,
  270,  276,  272,  290,  291,  292,  293,  294,  295,  296,
  297,  281,  282,  283,  284,   -1,   -1,  108,  109,  294,
   -1,   -1,   -1,   -1,  299,  300,   -1,   -1,   -1,  120,
  269,  270,   -1,  272,   -1,  126,   -1,   -1,  277,  278,
   -1,   -1,  281,  282,  283,  284,  285,  286,  287,  288,
  289,  290,  291,  292,  293,  294,  295,  296,  297,  269,
  293,  294,  295,  296,  297,   -1,   -1,  277,  278,   -1,
   -1,  281,  282,  283,  284,  285,  286,  287,  288,  289,
  290,  291,  292,  293,  294,  295,  296,  297,   -1,  269,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  277,  278,   -1,
   -1,  281,  282,  283,  284,  285,  286,  287,  288,  289,
  290,  291,  292,  293,  294,  295,  296,  297,  269,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  277,  278,   -1,   -1,
  281,  282,  283,  284,  285,  286,  287,  288,  289,  290,
  291,  292,  293,  294,  295,  296,  297,  272,   -1,   -1,
   -1,   -1,  277,  278,   -1,   -1,  281,  282,  283,  284,
  285,  286,  287,  288,  289,  290,  291,  292,  293,  294,
  295,  296,  297,  272,   -1,   -1,   -1,   -1,  277,  278,
   -1,   -1,  281,  282,  283,  284,  285,  286,  287,  288,
  289,  290,  291,  292,  293,  294,  295,  296,  297,  272,
   -1,   -1,   -1,   -1,  277,  278,   -1,   -1,  281,  282,
  283,  284,  285,  286,  287,  288,  289,  290,  291,  292,
  293,  294,  295,  296,  297,  272,   -1,   -1,   -1,   -1,
  277,  278,   -1,   -1,  281,  282,  283,  284,  285,  286,
  287,  288,  289,  290,  291,  292,  293,  294,  295,  296,
  297,  272,   -1,   -1,   -1,   -1,  277,  278,   -1,   -1,
  281,  282,  283,  284,  285,  286,  287,  288,  289,  290,
  291,  292,  293,  294,  295,  296,  297,  269,  270,   -1,
  272,   -1,   -1,   -1,   -1,  277,  278,   -1,   -1,  281,
  282,  283,  284,  285,  286,  287,  288,  289,  290,  291,
  292,  293,  294,  269,  270,   -1,  272,   -1,   -1,   -1,
   -1,  277,  278,   -1,   -1,  281,  282,  283,  284,  285,
  286,  287,  288,  289,  290,  291,  292,  293,  294,  269,
  270,   -1,  272,   -1,   -1,   -1,   -1,  277,  278,   -1,
   -1,  281,  282,  283,  284,  285,  286,  287,  288,  289,
  290,  291,  292,  269,  270,   -1,  272,   -1,   -1,   -1,
   -1,  277,  278,   -1,   -1,  281,  282,  283,  284,  285,
  286,  287,  288,  289,  290,  291,  292,  269,  270,   -1,
  272,   -1,   -1,   -1,   -1,  277,  278,   -1,   -1,  281,
  282,  283,  284,  285,  286,  287,  288,  289,  290,  291,
  292,  277,  278,   -1,   -1,  281,  282,  283,  284,  285,
  286,  287,  288,  289,  290,  291,  292,  293,  294,  295,
  296,  297,  277,  278,   -1,   -1,   -1,  282,  283,  284,
  285,  286,  287,  288,  289,  290,  291,  292,  293,  294,
  295,  296,  297,  277,  278,   -1,   -1,   -1,   -1,  283,
  284,  285,  286,  287,  288,  289,  290,  291,  292,  293,
  294,  295,  296,  297,  277,  278,   -1,   -1,   -1,   -1,
   -1,  284,  285,  286,  287,  288,  289,  290,  291,  292,
  293,  294,  295,  296,  297,  277,  278,   -1,   -1,   -1,
   -1,   -1,   -1,  285,  286,  287,  288,  289,  290,  291,
  292,  293,  294,  295,  296,  297,  277,  278,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  286,  287,  288,  289,  290,
  291,  292,  293,  294,  295,  296,  297,  269,  270,   -1,
  272,   -1,   -1,   -1,   -1,  277,  278,   -1,   -1,  281,
  282,  283,  284,  285,  286,  287,  288,  289,  269,  270,
   -1,  272,   -1,   -1,   -1,   -1,  277,  278,   -1,   -1,
  281,  282,  283,  284,  285,  286,  287,  288,  289,  269,
  270,   -1,  272,   -1,   -1,   -1,   -1,  277,  278,   -1,
   -1,  281,  282,  283,  284,  285,  286,  287,  288,  289,
  269,  270,   -1,  272,   -1,   -1,   -1,   -1,  277,  278,
  277,  278,  281,  282,  283,  284,  285,  286,  287,  288,
  289,  288,  289,  290,  291,  292,  293,  294,  295,  296,
  297,  269,  270,   -1,  272,   -1,   -1,   -1,  269,  270,
   -1,  272,   -1,  281,  282,  283,  284,  285,  286,  287,
  281,  282,  283,  284,  285,  286,  287,
};
#define YYFINAL 4
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 300
#define YYUNDFTOKEN 318
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"TOK_VOID","TOK_INT","TOK_INTVAL",
"TOK_BOOL","TOK_TRUE","TOK_FALSE","TOK_IDENT","TOK_IF","TOK_ELSE","TOK_WHILE",
"TOK_FOR","TOK_PRINT","TOK_SEMICOL","TOK_COMMA","TOK_LPAR","TOK_RPAR",
"TOK_LACC","TOK_RACC","TOK_STRING","TOK_DO","TOK_GT","TOK_LT","TOK_THEN",
"TOK_AFFECT","TOK_OR","TOK_AND","TOK_BOR","TOK_BXOR","TOK_BAND","TOK_EQ",
"TOK_NE","TOK_GE","TOK_LE","TOK_SRL","TOK_SRA","TOK_SLL","TOK_PLUS","TOK_MINUS",
"TOK_MUL","TOK_DIV","TOK_MOD","TOK_UMINUS","TOK_NOT","TOK_BNOT",0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : program",
"program : listdeclnonnull maindecl",
"program : maindecl",
"listdeclnonnull : vardecl",
"listdeclnonnull : listdeclnonnull vardecl",
"maindecl : type ident TOK_LPAR TOK_RPAR block",
"listdecl : listdeclnonnull",
"listdecl :",
"vardecl : type listtypedecl TOK_SEMICOL",
"decl : ident",
"decl : ident TOK_AFFECT expr",
"ident : TOK_IDENT",
"type : TOK_INT",
"type : TOK_BOOL",
"type : TOK_VOID",
"paramprint : ident",
"paramprint : TOK_STRING",
"listparamprint : listparamprint TOK_COMMA paramprint",
"listparamprint : paramprint",
"expr : expr TOK_MUL expr",
"expr : expr TOK_DIV expr",
"expr : expr TOK_PLUS expr",
"expr : expr TOK_MINUS expr",
"expr : expr TOK_MOD expr",
"expr : expr TOK_LT expr",
"expr : expr TOK_GT expr",
"expr : TOK_MINUS expr",
"expr : expr TOK_GE expr",
"expr : expr TOK_LE expr",
"expr : expr TOK_EQ expr",
"expr : expr TOK_NE expr",
"expr : expr TOK_AND expr",
"expr : expr TOK_OR expr",
"expr : expr TOK_BAND expr",
"expr : expr TOK_BOR expr",
"expr : expr TOK_BXOR expr",
"expr : expr TOK_SRL expr",
"expr : expr TOK_SRA expr",
"expr : expr TOK_SLL expr",
"expr : TOK_NOT expr",
"expr : TOK_BNOT expr",
"expr : TOK_LPAR expr TOK_RPAR",
"expr : ident TOK_AFFECT expr",
"expr : TOK_INTVAL",
"expr : TOK_TRUE",
"expr : TOK_FALSE",
"expr : ident",
"block : TOK_LACC listdecl listinst TOK_RACC",
"inst : expr TOK_SEMICOL",
"inst : TOK_IF TOK_LPAR expr TOK_RPAR inst TOK_ELSE inst",
"inst : TOK_IF TOK_LPAR expr TOK_RPAR inst",
"inst : TOK_WHILE TOK_LPAR expr TOK_RPAR inst",
"inst : TOK_FOR TOK_LPAR expr TOK_SEMICOL expr TOK_SEMICOL expr TOK_RPAR inst",
"inst : TOK_DO inst TOK_WHILE TOK_LPAR expr TOK_RPAR TOK_SEMICOL",
"inst : block",
"inst : TOK_SEMICOL",
"inst : TOK_PRINT TOK_LPAR listparamprint TOK_RPAR TOK_SEMICOL",
"listinstnonnull : inst",
"listinstnonnull : listinstnonnull inst",
"listinst : listinstnonnull",
"listinst :",
"listtypedecl : decl",
"listtypedecl : listtypedecl TOK_COMMA decl",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 252 "grammar.y"

/* A completer et/ou remplacer avec d'autres fonctions */
node_t make_node(node_nature nature, int nops, ...){

    va_list ap;
    int i = 0;
    node_t node = NULL; 
  
    node = (node_t) malloc(sizeof(node_s));
    
    if(node == NULL)
        exit(-1);

    node -> offset = 0;
    node -> global_decl = false;    
    node -> decl_node = NULL;
    node->ident = NULL;
    node->str = NULL;
    node->opr = NULL;
    node->value = 0;
    node->nops = 0;
    node->type = TYPE_NONE;
    node -> nature = nature; // Définition de la nature de la node
    node -> lineno = yylineno; // Définit la ligne avec la variable globale
    node -> nops = nops; // On définit le nombre d'opérandes
    node->node_num = 0;
    
    // On vérifie bien qu'il y ait au moins 1 enfant

    if(nops != 0) 
    {
        node -> opr = (node_t*) malloc(nops * sizeof(node_t));
        va_start(ap,nops);

        // On met les enfants dans la liste opr

        for(i = 0; i < nops; i++) 
        {
            // On cherche le prochain élément dans la liste qui est une node
            node -> opr[i] = va_arg(ap,node_t);
        }
    }

    // Si pas d'enfant

    else if(nops == 0)
    {
        node -> opr = NULL;
    }
    
    // On remplit TYPE ou VALUE ou le champ de caractères (IDENT ou STR) suivant le type de node
    switch(nature)
    {
        case NODE_DECLS:
         node -> type = va_arg(ap,node_type);
         break;
    case NODE_TYPE:
        va_start(ap,nops);
        node -> type = va_arg(ap,node_type);
        break;
    case NODE_INTVAL:
        va_start(ap,nops);
        node -> type = va_arg(ap,node_type);
        node -> value = yylval.intval;
        break;
    case NODE_IDENT:
        //va_start(ap,nops);
        node->ident = strdup(yylval.strval);
        node->nature = NODE_IDENT;
        break;
    case NODE_BOOLVAL:
        va_start(ap,nops);
        node->type = va_arg(ap,node_type);
        node->value = va_arg(ap,node_type);
        break;
    case NODE_STRINGVAL:
        //va_start(ap,nops);
        node -> type = TYPE_STRING;
        node -> str = strdup(yylval.strval);
        break;
    
    }
    
    va_end(ap);
    return node;
}


void analyse_tree(node_t root) {
    dump_tree(root, "apres_syntaxe.dot");
    
    if (!stop_after_syntax) {
        analyse_passe_1(root);
        dump_tree(root, "apres_passe_1.dot");
        if (!stop_after_verif) {
            create_program(); 
            gen_code_passe_2(root);
            dump_mips_program(outfile);
            free_program();
        }
        free_global_strings();
    }
    free_nodes(root);

}



/* Cette fonction est appelee automatiquement si une erreur de syntaxe est rencontree
 * N'appelez pas cette fonction vous-meme :
 * la valeur donnee par yylineno ne sera plus correcte apres l'analyse syntaxique
 */
void yyerror(node_t * program_root, char * s) {
    fprintf(stderr, "Error line %d: %s\n", yylineno, s);
    exit(1);
}
#line 630 "y.tab.c"

#if YYDEBUG
#include <stdio.h>	/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yym = 0;
    yyn = 0;
    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        yychar = YYLEX;
        if (yychar < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if (((yyn = yysindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if (((yyn = yyrindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag != 0) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab; /* redundant goto avoids 'unused label' warning */
yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if (((yyn = yysindex[*yystack.s_mark]) != 0) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym > 0)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);

    switch (yyn)
    {
case 1:
#line 81 "grammar.y"
	{
            yyval.ptr = make_node(NODE_PROGRAM, 2, yystack.l_mark[-1].ptr, yystack.l_mark[0].ptr);
            *program_root = yyval.ptr;
        }
break;
case 2:
#line 86 "grammar.y"
	{
            yyval.ptr = make_node(NODE_PROGRAM, 1, yystack.l_mark[0].ptr );
            *program_root = yyval.ptr;
        }
break;
case 3:
#line 94 "grammar.y"
	{yyval.ptr = yystack.l_mark[0].ptr;}
break;
case 4:
#line 96 "grammar.y"
	{yyval.ptr = make_node(NODE_LIST,2,yystack.l_mark[-1].ptr,yystack.l_mark[0].ptr);}
break;
case 5:
#line 100 "grammar.y"
	{yyval.ptr = make_node(NODE_FUNC,3,yystack.l_mark[-4].ptr,yystack.l_mark[-3].ptr,yystack.l_mark[0].ptr);}
break;
case 6:
#line 104 "grammar.y"
	{
            yyval.ptr = yystack.l_mark[0].ptr;
        }
break;
case 7:
#line 108 "grammar.y"
	{yyval.ptr = NULL;}
break;
case 8:
#line 112 "grammar.y"
	{
            yyval.ptr = make_node(NODE_DECLS,2,yystack.l_mark[-2].ptr,yystack.l_mark[-1].ptr);
        }
break;
case 9:
#line 118 "grammar.y"
	{
            yyval.ptr = yystack.l_mark[0].ptr;
        }
break;
case 10:
#line 122 "grammar.y"
	{
            yyval.ptr = make_node(NODE_DECL,2,yystack.l_mark[-2].ptr,yystack.l_mark[0].ptr); 
        }
break;
case 11:
#line 128 "grammar.y"
	{yyval.ptr = make_node(NODE_IDENT,0);}
break;
case 12:
#line 132 "grammar.y"
	{yyval.ptr = make_node(NODE_TYPE,0,TYPE_INT);}
break;
case 13:
#line 134 "grammar.y"
	{yyval.ptr = make_node(NODE_TYPE,0,TYPE_BOOL);}
break;
case 14:
#line 136 "grammar.y"
	{yyval.ptr = make_node(NODE_TYPE,0,TYPE_VOID);}
break;
case 15:
#line 140 "grammar.y"
	{yyval.ptr = yystack.l_mark[0].ptr;}
break;
case 16:
#line 142 "grammar.y"
	{yyval.ptr = make_node(NODE_STRINGVAL,0);}
break;
case 17:
#line 146 "grammar.y"
	{ yyval.ptr = make_node(NODE_LIST,2,yystack.l_mark[-2].ptr,yystack.l_mark[0].ptr);}
break;
case 18:
#line 148 "grammar.y"
	{ yyval.ptr = yystack.l_mark[0].ptr;}
break;
case 19:
#line 154 "grammar.y"
	{ yyval.ptr = make_node(NODE_MUL,2,yystack.l_mark[-2].ptr,yystack.l_mark[0].ptr);}
break;
case 20:
#line 156 "grammar.y"
	{ yyval.ptr = make_node(NODE_DIV,2,yystack.l_mark[-2].ptr,yystack.l_mark[0].ptr);}
break;
case 21:
#line 158 "grammar.y"
	{ yyval.ptr = make_node(NODE_PLUS,2,yystack.l_mark[-2].ptr,yystack.l_mark[0].ptr);}
break;
case 22:
#line 160 "grammar.y"
	{ yyval.ptr = make_node(NODE_MINUS,2,yystack.l_mark[-2].ptr,yystack.l_mark[0].ptr);}
break;
case 23:
#line 162 "grammar.y"
	{ yyval.ptr = make_node(NODE_MOD,2,yystack.l_mark[-2].ptr,yystack.l_mark[0].ptr);}
break;
case 24:
#line 164 "grammar.y"
	{ yyval.ptr = make_node(NODE_LT,2,yystack.l_mark[-2].ptr,yystack.l_mark[0].ptr);}
break;
case 25:
#line 166 "grammar.y"
	{ yyval.ptr = make_node(NODE_GT,2,yystack.l_mark[-2].ptr,yystack.l_mark[0].ptr);}
break;
case 26:
#line 168 "grammar.y"
	{ yyval.ptr = make_node(NODE_UMINUS,1,yystack.l_mark[0].ptr);}
break;
case 27:
#line 170 "grammar.y"
	{ yyval.ptr = make_node(NODE_GE,2,yystack.l_mark[-2].ptr,yystack.l_mark[0].ptr);}
break;
case 28:
#line 172 "grammar.y"
	{ yyval.ptr = make_node(NODE_LE,2,yystack.l_mark[-2].ptr,yystack.l_mark[0].ptr);}
break;
case 29:
#line 174 "grammar.y"
	{ yyval.ptr = make_node(NODE_EQ,2,yystack.l_mark[-2].ptr,yystack.l_mark[0].ptr);}
break;
case 30:
#line 176 "grammar.y"
	{yyval.ptr = make_node(NODE_NE,2,yystack.l_mark[-2].ptr,yystack.l_mark[0].ptr);}
break;
case 31:
#line 178 "grammar.y"
	{yyval.ptr = make_node(NODE_AND,2,yystack.l_mark[-2].ptr,yystack.l_mark[0].ptr);}
break;
case 32:
#line 180 "grammar.y"
	{yyval.ptr = make_node(NODE_OR,2,yystack.l_mark[-2].ptr,yystack.l_mark[0].ptr);}
break;
case 33:
#line 182 "grammar.y"
	{yyval.ptr = make_node(NODE_BAND,2,yystack.l_mark[-2].ptr,yystack.l_mark[0].ptr);}
break;
case 34:
#line 184 "grammar.y"
	{yyval.ptr = make_node(NODE_BOR,2,yystack.l_mark[-2].ptr,yystack.l_mark[0].ptr);}
break;
case 35:
#line 186 "grammar.y"
	{yyval.ptr = make_node(NODE_BXOR,2,yystack.l_mark[-2].ptr,yystack.l_mark[0].ptr);}
break;
case 36:
#line 188 "grammar.y"
	{yyval.ptr = make_node(NODE_SRL,2,yystack.l_mark[-2].ptr,yystack.l_mark[0].ptr);}
break;
case 37:
#line 190 "grammar.y"
	{yyval.ptr = make_node(NODE_SRA,2,yystack.l_mark[-2].ptr,yystack.l_mark[0].ptr);}
break;
case 38:
#line 192 "grammar.y"
	{yyval.ptr = make_node(NODE_SLL,2,yystack.l_mark[-2].ptr,yystack.l_mark[0].ptr);}
break;
case 39:
#line 194 "grammar.y"
	{yyval.ptr = make_node(NODE_NOT,1,yystack.l_mark[0].ptr);}
break;
case 40:
#line 196 "grammar.y"
	{yyval.ptr = make_node(NODE_BNOT,1,yystack.l_mark[0].ptr);}
break;
case 41:
#line 198 "grammar.y"
	{yyval.ptr = yystack.l_mark[-1].ptr;}
break;
case 42:
#line 200 "grammar.y"
	{yyval.ptr = make_node(NODE_AFFECT,2,yystack.l_mark[-2].ptr,yystack.l_mark[0].ptr);}
break;
case 43:
#line 202 "grammar.y"
	{yyval.ptr = make_node(NODE_INTVAL,0,TYPE_INT);}
break;
case 44:
#line 204 "grammar.y"
	{yyval.ptr = make_node(NODE_BOOLVAL,0,TYPE_BOOL,1);}
break;
case 45:
#line 206 "grammar.y"
	{yyval.ptr = make_node(NODE_BOOLVAL,0,TYPE_BOOL,0);}
break;
case 46:
#line 208 "grammar.y"
	{ yyval.ptr = yystack.l_mark[0].ptr;}
break;
case 47:
#line 212 "grammar.y"
	{yyval.ptr = make_node(NODE_BLOCK,2,yystack.l_mark[-2].ptr,yystack.l_mark[-1].ptr);}
break;
case 48:
#line 216 "grammar.y"
	{yyval.ptr = yystack.l_mark[-1].ptr;}
break;
case 49:
#line 218 "grammar.y"
	{yyval.ptr = make_node(NODE_IF,3,yystack.l_mark[-4].ptr,yystack.l_mark[-2].ptr,yystack.l_mark[0].ptr);}
break;
case 50:
#line 220 "grammar.y"
	{yyval.ptr = make_node(NODE_IF,2,yystack.l_mark[-2].ptr,yystack.l_mark[0].ptr);}
break;
case 51:
#line 222 "grammar.y"
	{yyval.ptr = make_node(NODE_WHILE,2,yystack.l_mark[-2].ptr,yystack.l_mark[0].ptr);}
break;
case 52:
#line 224 "grammar.y"
	{yyval.ptr = make_node(NODE_FOR,4,yystack.l_mark[-6].ptr,yystack.l_mark[-4].ptr,yystack.l_mark[-2].ptr,yystack.l_mark[0].ptr);}
break;
case 53:
#line 226 "grammar.y"
	{yyval.ptr = make_node(NODE_DOWHILE,2,yystack.l_mark[-5].ptr,yystack.l_mark[-2].ptr);}
break;
case 54:
#line 228 "grammar.y"
	{yyval.ptr = yystack.l_mark[0].ptr;}
break;
case 55:
#line 230 "grammar.y"
	{yyval.ptr = NULL;}
break;
case 56:
#line 232 "grammar.y"
	{yyval.ptr = make_node(NODE_PRINT,1,yystack.l_mark[-2].ptr);}
break;
case 57:
#line 236 "grammar.y"
	{yyval.ptr = yystack.l_mark[0].ptr;}
break;
case 58:
#line 238 "grammar.y"
	{yyval.ptr = make_node(NODE_LIST,2,yystack.l_mark[-1].ptr,yystack.l_mark[0].ptr);}
break;
case 59:
#line 242 "grammar.y"
	{yyval.ptr = yystack.l_mark[0].ptr;}
break;
case 60:
#line 244 "grammar.y"
	{yyval.ptr = NULL;}
break;
case 61:
#line 248 "grammar.y"
	{yyval.ptr = yystack.l_mark[0].ptr;}
break;
case 62:
#line 250 "grammar.y"
	{yyval.ptr = make_node(NODE_LIST,2,yystack.l_mark[-2].ptr,yystack.l_mark[0].ptr);}
break;
#line 1091 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            yychar = YYLEX;
            if (yychar < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if (((yyn = yygindex[yym]) != 0) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
