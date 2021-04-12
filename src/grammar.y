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
%left TOK_SRL TOK_SRA TOK_SLL
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
            { $$ = NULL; }
        ;

maindecl:
            { $$ = NULL; }
        ;

listdecl:
            { $$ = NULL; }
        ;

vardecl:
            { $$ = NULL; }
        ;

decl :
    { $$ = NULL; }
        ;

ident :
    { $$ = NULL; }
        ;

type :
    { $$ = NULL; }
        ;

paramprint:
    { $$ = NULL; }
        ;

listparamprint:
    { $$ = NULL; }
        ;

expr:
    { $$ = NULL; }
        ;

block:
    { $$ = NULL; }
        ;

inst:
    { $$ = NULL; }
        ;

listinstnonnull:
    { $$ = NULL; }
        ;

listinst:
    { $$ = NULL; }
        ;

listtypedecl:
    { $$ = NULL; }
        ;
%%

/* A completer et/ou remplacer avec d'autres fonctions */
node_t make_node(node_nature nature, int nops, ...) {
    va_list ap;
    va_start(ap,nops);
    
    node_t ret = malloc(sizeof(node_s));
    ret->nops = nops;
    ret->lineno= yylineno;    
    ret->nature = nature;

    if( (ret->type == TYPE_NONE) || (ret->type == TYPE_VOID )){
        ret->value = NULL;
    }else{
        if(ret-type == TYPE_STRING)
            // récupérer la valeur
            //ret->value = yyy
        else   
            // récupérer la valeur
            //ret->value = yyy
    }
    // Cas token sans rien
    if(!nops){    
        ret->type = TYPE_NONE;
        ret->opr = NULL;
        ret->decl_node = NULL;
    }
    // Cas token avec au moins 2 arguments
    else{
        ret1 = make_node();
        ret2 = make_node();

        (*opr) = ret1;
    //  (*(opr+1)) = ret2;
      
    }
    
    va_end(ap);

    return ret;
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

