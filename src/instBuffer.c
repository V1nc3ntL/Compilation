#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "instBuffer.h"

buffer* buf = NULL;

void allocateArg(inst* i,int32_t a,int32_t b,int32_t c){
       

            i -> nArg = 3;

        i -> arg = (int32_t*)malloc(3*sizeof(int32_t));
        i -> arg[0] = a;
        i -> arg[1] = b;
        i -> arg[2] = c;
       
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
            default:
                exit(-1);
        }

        free(buf -> bf[i]->arg);
        free(buf -> bf[i]);
    }
    free(buf->bf);
   

    free(buf);


}