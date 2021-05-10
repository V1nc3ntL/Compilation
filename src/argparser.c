#include "argparser.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "defs.h"
#include "common.h"


int argParser(int argc, char** argv){
    int ret = 0;
    if(argc == 2){
            if(!strcmp("-b",argv[1])){
                           
                ret = B_OPTION;
                }
            else{
            
            }
    }
    
    return ret;
}
    
    