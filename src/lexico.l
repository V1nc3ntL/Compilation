%{
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "defs.h"
#include "common.h"
#include "argparser.h"
#include "y.tab.h"

int yyparse(node_t * program_root);
void analyse_tree(node_t root);

char * infile = NULL;
char * outfile = DEFAULT_OUTFILE;
bool stop_after_syntax = false;
bool stop_after_verif = false;

#if YYDEBUG
extern int yydebug;
#endif


%}

%option yylineno



/* A completer ; fausses definitions pour passer la compilation */
IDF             [a-zA-Z_][a-zA-Z0-9_]+
ENTIER          [0-9]
CHAINE          \'*\'
LETTRE          [a-zA-Z]
COMMENTAIRE     \/\/.*
ENTIER_DEC      [0-9]+[,.][0-9]
ENTIER_HEXA     [0-9a-fA-F]



%%

"void"           TOK_VOID;
"int"            TOK_INT;
"bool"           TOK_BOOL;
"true"           TOK_TRUE;
"false"          TOK_FALSE;
"if"             TOK_IF;
"else"           TOK_ELSE;
"while"          TOK_WHILE;
"for"            TOK_FOR;
"do"             TOK_DO;
"print"          TOK_PRINT;

"+"              TOK_PLUS;
"-"              TOK_MINUS;
"*"              TOK_MUL;
"/"              TOK_DIV;
"%"              TOK_MOD;
">"              TOK_GT;
"<"              TOK_LT;
"!"              TOK_NOT;
"~"              TOK_BNOT;
"&"              TOK_BAND;
"|"              TOK_BOR;
"^"              TOK_BXOR;
"="              TOK_EQ;
";"              TOK_SEMICOL;
","              TOK_COMMA;
"("              TOK_LPAR;
")"              TOK_RPAR;
"{"              TOK_LACC;
"}"              TOK_RACC;
">>"             TOK_SRL;
">>>"            TOK_SRA;
"<<"             TOK_SLL;
">="             TOK_GE;
"<="             TOK_LE;
"=="             TOK_EQ;
"!="             TOK_NE;
"&&"             TOK_AND;
"||"             TOK_OR;

{IDF} {
                yylval.strval = strdup(yytext);
                return TOK_IDENT;
}

{ENTIER} {
                yylval.intval = atoi(yytext);
                return TOK_INTVAL;
}

{CHAINE} {
                yylval.strval = strdup(yytext);
                return TOK_STRING;
}

{COMMENTAIRE} {
                
}

[ \t\n]+

. {
                fprintf(stderr, "Error line %d: Lexical error\n", yylineno);
                exit(1);
}


%%

int yywrap(void) {
    return 1;
}


int main(int argc, char ** argv) {
    node_t program_root;
    int hOption=0,voption = 0,traceLvl = 0;
    char* outName = NULL;
    
    int curArg, code = 0, nRegister = MAX_REG;

    #if YYDEBUG
    yydebug = 1;
    #endif
    int i = 0 ;

    while((curArg=getopt(argc,argv,"botrsvh"))!=-1){
        
        i++;

        if(code & B_OPTION)
            return -1;
            
        if(code & H_OPTION){
            printf(OPTIONS_DESC);
            return 0;
        }

        switch(curArg){
            case 'b':
                code |= B_OPTION;
                break;
            case 'h':
                printf(OPTIONS_DESC);
                return 0;

            case 't': 
                traceLvl = atoi(argv[i+1]);
                code |= T_OPTION;
                if( (traceLvl < MIN_TRACE) || (traceLvl > MAX_TRACE))   
                    return -1;
                break;

            case 'r':
                nRegister = atoi(argv[i+1]);
                code |= R_OPTION;
                if( (nRegister < MIN_REG) || (nRegister > MAX_REG))   
                    return -1;
                break;

            case 's':
                if(code & V_OPTION)
                    return -1;
                else                
                    code |= S_OPTION;
                break;

            case 'v':
                if(code & S_OPTION)
                    return -1;
                else
                    code |= V_OPTION;
                break;
            
            case 'o':
                outName = strdup( argv[i+1]);
                if(!outName)
                    return -1;
                break;
            default:
                break;
        }
    }

    if(code & B_OPTION){
        printf(BANNER);
        return 0;
    }

    if(!(code & S_OPTION)) {
        //Faire ce qu'il y a après syntaxique analysis
    }

    if(!(code & V_OPTION)) {
        //Faire ce qu'il y a après première passe
    }

    if(!(code & O_OPTION)){
        // Fichier out est DEFAULT_OUTFILE
    }else{
        // Fichier est outName;
    }

    yyin = fopen(argv[1], "r");
    yyparse(&program_root);
    fclose(yyin);
    analyse_tree(program_root);
    yylex_destroy();

    
    return 0;
}




