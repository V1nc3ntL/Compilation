#include <stdio.h>
#include "argparser.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "defs.h"
#include "common.h"
#include "argparser.h"
#include "y.tab.h"
#include "passe_1.h"
extern char * infile;
extern char * outfile ;
extern  bool stop_after_syntax;
extern bool stop_after_verif ;
extern int trace_level;


int argparser(int argc, char ** argv, int * tstIndex){
    
    int curArg , code = 0, nRegister = MAX_REG, traceLvl;
    
    if(argc == 1)
        return -1;

    while((curArg=getopt(argc,argv,"botrsvh"))!=-1){
        
        *tstIndex += 2;

        if(code & B_OPTION){
            return -1;
        }
            
            
        if(code & H_OPTION){
            printf(OPTIONS_DESC);
            *tstIndex = 0;
            return 0;
        }

        switch(curArg){
            case 'b':
                if(argc > 2)
                    return 1;
                else{
                    *tstIndex = 0;
                    printf(BANNER);
                    return 0;
                }
            case 'h':
                printf(OPTIONS_DESC);
                *tstIndex = 0;
                return 0;

            case 't': 
                traceLvl = atoi(argv[*tstIndex]);
                code |= T_OPTION;
                if( (traceLvl < MIN_TRACE) || (traceLvl > MAX_TRACE))   
                    return -1;
                else
                    trace_level = traceLvl;
                break;

            case 'r':
                nRegister = atoi(argv[*tstIndex]);
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
                outfile = strdup( argv[(*tstIndex)]);
                code |= O_OPTION;
                if(!outfile)
                    return -1;
                break;
            default:
                break;
        }

    }

    if(code == V_OPTION)
        *tstIndex = 2;
    if(!code)
        *tstIndex = 1;

    return 0;
}