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
IDF             [a-zA-Z_][a-zA-Z0-9_]*
ENTIER          [0-9]+
CHAINE_CAR      [^\"\\]
CHAINE          \"({CHAINE_CAR}|{BACK}|\015)*\"
LETTRE          [a-zA-Z]
BACK            \\n
COMMENTAIRE     \/\/.*
ENTIER_DEC      [0-9]+
ENTIER_HEXA     [0-9a-fA-F]+



%%

"void"           return TOK_VOID;
"int"            return TOK_INT;
"bool"           return TOK_BOOL;
"true"           return TOK_TRUE;
"false"          return TOK_FALSE;
"if"             return TOK_IF;
"else"           return TOK_ELSE;
"while"          return TOK_WHILE;
"for"            return TOK_FOR;
"do"             return TOK_DO;
"print"          return TOK_PRINT;
"+"              return TOK_PLUS;
"-"              return TOK_MINUS;
"*"              return TOK_MUL;
"/"              return TOK_DIV;
"%"              return TOK_MOD;
">"              return TOK_GT;
"<"              return TOK_LT;
"!"              return TOK_NOT;
"~"              return TOK_BNOT;
"&"              return TOK_BAND;
"|"              return TOK_BOR;
"^"              return TOK_BXOR;
"="              return TOK_AFFECT;
";"              return TOK_SEMICOL;
","              return TOK_COMMA;
"("              return TOK_LPAR;
")"              return TOK_RPAR;
"{"              return TOK_LACC;
"}"              return TOK_RACC;
">>"             return TOK_SRL;
">>>"            return TOK_SRA;
"<<"             return TOK_SLL;
">="             return TOK_GE;
"<="             return TOK_LE;
"=="             return TOK_EQ;
"!="             return TOK_NE;
"&&"             return TOK_AND;
"||"             return TOK_OR;
             
{IDF} {
                yylval.strval = yytext;
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
   
    node_t program_root ;
    int traceLvl = 0;
    char* outName = NULL;
    
    int curArg , code = 0, nRegister = MAX_REG;

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
                if(argc > 2)
                    return 1;
                else
                    printf(BANNER);
                    return 0;
            case 'h':
                printf(OPTIONS_DESC);
                return 0;

            case 't': 
                traceLvl = atoi(argv[i+1]);
                code |= T_OPTION;
                if( (traceLvl < MIN_TRACE) || (traceLvl > MAX_TRACE))   
                    return -1;
                else
                    trace_level = traceLvl;
                break;

            case 'r':
                nRegister = atoi(argv[i+1]);
                code |= R_OPTION;
                if( (nRegister < MIN_REG) || (nRegister > MAX_REG))   
                    return -1;
                else
                    set_max_registers(nRegister);
                break;

            case 's':
                if(code & V_OPTION)
                    return -1;
                else                
                    code |= S_OPTION;
                    stop_after_syntax = true;
                break;

            case 'v':
                if(code & S_OPTION)
                    return -1;
                else
                    code |= V_OPTION;
                    stop_after_verif = true;
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

    if(!(code & O_OPTION)){
        outfile = DEFAULT_OUTFILE;
    }else{
        outfile = strdup(argv[2]);
    }
    if(!code)
        yyin = fopen(argv[1], "r");
    else {
        if((code & O_OPTION ) || (code & T_OPTION) || (code & R_OPTION) )
            yyin = fopen(argv[3], "r");
        else
            yyin = fopen(argv[2], "r");
    }
    

    yyparse(&program_root);
    fclose(yyin);
    analyse_tree(program_root);
    yylex_destroy();

    if(outName != NULL)
        free(outName);
    if(outfile != DEFAULT_OUTFILE)
       free(outfile); 

    return 0;
}




