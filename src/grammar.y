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
/* A completer */
%left TOK_OR
%left TOK_AND
%left TOK_BOR
%left TOK_BXOR
%left TOK_BAND
%left TOK_EQ TOK_NE
%left TOK_GT TOK_LT TOK_GE TOK_LE
%left TOK_SRL TOK_SRA TOK_SLL TOK_SLA
%left TOK_PLUS TOK_MINUS
%left TOK_MUL TOK_DIV TOK_MOD
%left TOK_UMINUS TOK_NOT TOK_BNOT
%type <intval> TOK_INTVAL
%type <strval> TOK_IDENT TOK_STRING

%type <ptr> program listdecl listdeclnonnull vardecl ident type listtypedecl decl maindecl listinst listinstnonnull inst block expr listparamprint paramprint
%type <ptr> listinst listinstnonnull inst block expr listparamprint paramprint
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
                    $$ = make_node(NODE_LIST,1,NULL,$1); 
                }
                | listdeclnonnull vardecl
                {
                    $$ = make_node(NODE_LIST,2,$1,$2);
                };

maindecl:
        type ident TOK_LPAR TOK_RPAR block
        { 
            $$ = make_node(NODE_FUNC,2,$1,$2); 
        };

listdecl:
        listdeclnonnull
        {
            $$ = make_node(NODE_LIST,1,NULL,$1);
        };

vardecl:
        type listtypedecl TOK_SEMICOL
        {
            $$ = NULL;
        };

decl:
        ident
        {
            $$ = NULL;
        }
        | ident TOK_AFFECT expr
        {
            $$ = NULL; 
        };

ident:
        TOK_IDENT
        {$$ = NULL;};

type:
    TOK_INT
    | TOK_BOOL
    {$$ = NULL;}
    | TOK_VOID
    {$$ = NULL;};

paramprint:
         ident
        {$$ = NULL;}
        | TOK_STRING
        {$$ = NULL;};

listparamprint:
            listparamprint TOK_COMMA paramprint
            { $$ = NULL;}
            | paramprint
            { $$ = NULL;};

expr:
     expr TOK_MUL expr
    { $$ = NULL;}
    | expr TOK_DIV expr
    { $$ = NULL;}
    | expr TOK_PLUS expr
    { $$ = NULL;}
    | expr TOK_MINUS expr
    { $$ = NULL;}
    | expr TOK_MOD expr
    { $$ = NULL;}
    | expr TOK_LT expr
    { $$ = NULL;}
    | expr TOK_GT expr
    { $$ = NULL;}
    | TOK_MINUS expr %prec TOK_UMINUS
    { $$ = NULL;}
    | expr TOK_GE expr
    { $$ = NULL;}
    | expr TOK_LE expr
    { $$ = NULL;}
    | expr TOK_EQ expr
    { $$ = NULL;};


block:
    TOK_LACC listdecl listinst TOK_RACC
    {$$ = NULL;};

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
                 {$$ = NULL;}
                | listinstnonnull inst
                {$$ = NULL;};

listinst:
        listinstnonnull
        {$$ = NULL;}
        |
        {$$ = NULL;};

listtypedecl:
            decl
            {$$ = NULL;}
            | listtypedecl TOK_COMMA decl
            {$$ = NULL;};
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