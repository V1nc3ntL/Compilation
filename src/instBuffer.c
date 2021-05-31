#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "instBuffer.h"

buffer* buf = NULL;

void allocateArg(inst* in,int32_t a,int32_t b,int32_t c){
       
        int32_t args[3] = {a,b,c};

        in->nArg = 3;
        in -> arg = (int32_t*)malloc(in->nArg*sizeof(int32_t));


        for(int i = 0 ; i < in->nArg; in->arg[i] = args[i], i++ );

       
}

void addToInstBuffer(instWoutArg i,int32_t a,int32_t b,int32_t c){
    
    if(buf != NULL){
        
        buf -> bf = (inst**) realloc(buf -> bf ,sizeof(inst*)*(buf->size+1));

        buf -> bf[buf->size] = (inst*) malloc(sizeof(inst));
        
        buf -> bf[buf->size] -> in = i;
        
        allocateArg(buf->bf[buf->size],a,b,c);
        
        buf->size+=1;
    }else{
        buf = (buffer*) malloc(sizeof(buffer));
        buf -> bf = (inst**) malloc(sizeof(inst*));
        buf -> bf[0] = (inst*) malloc(sizeof(inst));
        buf -> bf[0] -> in = i;
        allocateArg(buf->bf[0],a,b,c);
        buf->size=1;
    }
}

void releaseInstBuffer(){

    for(int i = 0 ; i < buf->size  ; i++){
        
        switch(buf -> bf[i] -> nArg){
            case 1:
             (buf -> bf[i]->in.uno)( buf -> bf[i]->arg[0]) ;
                break;
            case 2:
             (buf -> bf[i]->in.duo)( buf -> bf[i]->arg[0],buf -> bf[i]->arg[1]) ;
                break;
            case 3:
            (buf -> bf[i]->in.tre)( buf -> bf[i]->arg[0],buf -> bf[i]->arg[1],buf -> bf[i]->arg[2]) ;
                break;
            case 0:
                 (buf -> bf[i]->in.zer);
            default:
                exit(-1);
        }
        if(buf -> bf[i] -> nArg)
            free(buf -> bf[i]->arg);
        free(buf -> bf[i]);
    }
    free(buf->bf);

    free(buf);
}