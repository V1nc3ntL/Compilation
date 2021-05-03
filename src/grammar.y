%{
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

%}

%parse-param { node_t * program_root }

%union {
    int32_t intval;
    char * strval;
    node_t ptr;
};


/* Definir les token ici avec leur associativite, dans le bon ordre */
%token TOK_VOID    TOK_INT      TOK_INTVAL  TOK_BOOL   TOK_TRUE  TOK_FALSE
%token TOK_IDENT   TOK_IF       TOK_ELSE    TOK_WHILE  TOK_FOR   TOK_PRINT
%token TOK_SEMICOL TOK_COMMA    TOK_LPAR    TOK_RPAR   TOK_LACC  TOK_RACC
%token TOK_STRING  TOK_DO
%token TOK_GT TOK_LT

%nonassoc TOK_THEN
%nonassoc TOK_ELSE

%right TOK_AFFECT

/* A completer */
%left TOK_OR
%left TOK_AND
%left TOK_BOR
%left TOK_BXOR
%left TOK_BAND
%left TOK_EQ TOK_NE
%left TOK_GT TOK_LT TOK_GE TOK_LE
%left TOK_SRL TOK_SRA TOK_SLL
%left TOK_PLUS TOK_MINUS
%left TOK_MUL TOK_DIV TOK_MOD
%left TOK_UMINUS TOK_NOT TOK_BNOT

%type <intval> TOK_INTVAL
%type <strval> TOK_IDENT TOK_STRING

%type <ptr> program listdecl listdeclnonnull vardecl ident type listtypedecl decl maindecl listinst listinstnonnull inst block expr listparamprint paramprint

%%

/* Completer les regles et la creation de l'arbre */
program:
        listdeclnonnull maindecl
        {
            $$ = make_node(NODE_PROGRAM, 2, $1, $2);
            *program_root = $$;
        }
        | maindecl
        {
            $$ = make_node(NODE_PROGRAM, 2, NULL, $1);
            *program_root = $$;
        }
        ;

listdeclnonnull:
                vardecl
                { 
                    $$ = make_node(NODE_LIST,2,NULL,$1); 
                }
                | listdeclnonnull vardecl
                {
                    $$ = make_node(NODE_LIST,2,$1,$2);
                };

maindecl:
        type ident TOK_LPAR TOK_RPAR block
        { 
            $$ = make_node(NODE_FUNC,3,$1,$2,$5); /* A REVOIR */
        };

listdecl:
        listdeclnonnull
        {
            $$ = make_node(NODE_LIST,2,NULL,$1);
        };

vardecl:
        type listtypedecl TOK_SEMICOL
        {
            $$ = make_node(NODE_DECLS,2,$1,$2);
        };

decl:
        ident
        {
            $$ = make_node(NODE_DECL,2,NULL,$1);
        }
        | ident TOK_AFFECT expr
        {
            $$ = make_node(NODE_DECL,2,$1,$3); 
        };

ident:
        TOK_IDENT
        {$$ = make_node(NODE_IDENT,2,NULL,$1);};

type:
    TOK_INT
    {$$ = make_node(NODE_TYPE,2,NULL,NULL);}
    | TOK_BOOL
    {$$ = make_node(NODE_TYPE,2,NULL,NULL);}
    | TOK_VOID
    {$$ = make_node(NODE_TYPE,2,NULL,NULL);}

paramprint:
         ident
        {$$ = make_node(NODE_PRINT,2,NULL,$1);}
        | TOK_STRING
        {$$ = make_node(NODE_PRINT,2,NULL,NULL);};

listparamprint:
            listparamprint TOK_COMMA paramprint
            { $$ = make_node(NODE_PRINT,2,$1,$3);}
            | paramprint
            { $$ = make_node(NODE_PRINT,2,NULL,$1);};

expr:
     expr TOK_MUL expr
    { $$ = make_node(NODE_MUL,2,$1,$3);}
    | expr TOK_DIV expr
    { $$ = make_node(NODE_DIV,2,$1,$3);}
    | expr TOK_PLUS expr
    { $$ = make_node(NODE_PLUS,2,$1,$3);}
    | expr TOK_MINUS expr
    { $$ = make_node(NODE_MINUS,2,$1,$3);}
    | expr TOK_MOD expr
    { $$ = make_node(NODE_MOD,2,$1,$3);}
    | expr TOK_LT expr
    { $$ = make_node(NODE_LT,2,$1,$3);}
    | expr TOK_GT expr
    { $$ = make_node(NODE_GT,2,$1,$3);}
    | TOK_MINUS expr %prec TOK_UMINUS
    { $$ = NULL;}
    | expr TOK_GE expr
    { $$ = make_node(NODE_GE,2,$1,$3);}
    | expr TOK_LE expr
    { $$ = make_node(NODE_LE,2,$1,$3);}
    | expr TOK_EQ expr
    { $$ = make_node(NODE_EQ,2,$1,$3);};


block:
    TOK_LACC listdecl listinst TOK_RACC
    {$$ = make_node(NODE_BLOCK,2,$2,$3);};

inst:
    expr TOK_SEMICOL
    {$$ = NULL;}
    | TOK_IF TOK_LPAR expr TOK_RPAR inst TOK_ELSE inst
    {$$ = NULL;} 
    | TOK_IF TOK_LPAR expr TOK_RPAR inst %prec TOK_THEN
    {$$ = NULL;}
    | TOK_WHILE TOK_LPAR expr TOK_RPAR inst
    {$$ = NULL;}
    | TOK_FOR TOK_LPAR expr TOK_SEMICOL expr TOK_SEMICOL expr TOK_RPAR inst
    {$$ = NULL;}
    | TOK_DO inst TOK_WHILE TOK_LPAR expr TOK_RPAR TOK_SEMICOL
    {$$ = NULL;}
    | block
    {$$ = NULL;}
    | TOK_SEMICOL
    {$$ = NULL;}
    | TOK_PRINT TOK_LPAR listparamprint TOK_RPAR TOK_SEMICOL
    {$$ = NULL;};

listinstnonnull:
                inst
                {$$ = make_node(NODE_LIST,1,NULL,$1);}
                | listinstnonnull inst
                {$$ = make_node(NODE_LIST,2,N);};

listinst:
        listinstnonnull
        {$$ = make_node(NODE_LIST,1,NULL,$1);}
        |
        {$$ = NULL;};

listtypedecl:
            decl
            {$$ = make_node(NODE_LIST,1,NULL,$1);}
            | listtypedecl TOK_COMMA decl
            {$$ = make_node(NODE_LIST,2,$1,$3);};
%%

/* A completer et/ou remplacer avec d'autres fonctions */
node_t make_node(node_nature nature, int nops, ...) {
    va_list ap;
    return NULL;
}


void analyse_tree(node_t root) {
    //dump_tree(root, "apres_syntaxe.dot");
    if (!stop_after_syntax) {
        analyse_passe_1(root);
        //dump_tree(root, "apres_passe_1.dot");
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
