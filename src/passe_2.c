#include <stdio.h>

#include "defs.h"
#include "passe_2.h"
#include "miniccutils.h"
#include "instBuffer.h"
#include "instCreation.h"
#include <string.h>


int wreckOffset=0;
int varDecl = 0;

int getStartOffset(node_t root){
    if (root->nops > 1)
	{
	  return root->opr[1]->offset;
	}
      else
	{
	  return root->opr[0]->offset;
	}
}

void r_passe_2_print(node_t root){
    instWoutArg a;
    int32_t r1 = 0;
            
    if(root != NULL){
        switch(root->nature){
            case NODE_LIST:
                r_passe_2_print(root->opr[0]);
                r_passe_2_print(root->opr[1]);
                break;
            case NODE_STRINGVAL : 
                create_inst_asciiz(NULL,root->str);
                // Retrouver l'adresse de data
                a.duo = create_inst_lui;
                addToInstBuffer(a,4, 0x1001,0);    
                
                a.tre = create_inst_addiu;
                // Incrémenter l'adresse de data selon l'offset
                if(!wreckOffset){
                    wreckOffset = root->offset;
                    addToInstBuffer(a,4,4,varDecl<<2);
                }else{
                    addToInstBuffer(a,4,4,root->offset-wreckOffset+(varDecl<<2));  
                }
                
                
                /*
                // Charger l'adresse dans le syscall
                a.tre = create_inst_addu;
                addToInstBuffer(a,4,0,r1);    */
                
                //Charger le code du print
                a.tre = create_inst_addiu;
                addToInstBuffer(a,2,0,4);

                a.zer =  create_inst_syscall;
                addToInstBuffer(a,0,0,0);
                break;
            case NODE_IDENT :
                    // Récupérer la valeur dans un registre
                    r1 = get_current_reg();
                    a.duo = create_inst_lui;
                    addToInstBuffer(a,r1, 0x1001,0);   
 
                    a.tre = create_inst_lw;
                    addToInstBuffer(a,4,root->offset-4,r1);
               
                    a.tre = create_inst_addiu;
                    addToInstBuffer(a,2,0,1);
                    // Mettre la valeur a afficher dans le syscall
                    a.zer =  create_inst_syscall;
                    addToInstBuffer(a,0,0,0);
                break;
        }
    }   
}

void r_passe_2(node_t root){
    
    instWoutArg a;
    int32_t label;
    int32_t r1 = 0 ,r2 = 0;
    if(root != NULL){
        switch(root->nature){
            case NODE_PROGRAM:
                if (root->nops > 1)
                {
                    r_passe_2(root->opr[1]);
                }
                else
                {
                   r_passe_2(root->opr[0]);
                }
            case NODE_MUL:
                mul_inst(root);
                break;   
            case NODE_MINUS:
                moins_inst(root);
                break;
            case NODE_FUNC :
                r_passe_2(root->opr[0]);
                r_passe_2(root->opr[1]);
                r_passe_2(root->opr[2]);
                create_inst_text_sec();
                create_inst_stack_allocation();
                releaseInstBuffer();
                create_inst_stack_deallocation(root->offset + get_temporary_max_offset());
                create_inst_addiu(2,0,10);
                create_inst_syscall();
                break;
            case NODE_IDENT:
                
                break;
            case NODE_BLOCK:
                r_passe_2(root->opr[0]);
                r_passe_2(root->opr[1]);
                break;
            case NODE_INTVAL:
                
                break;
            case NODE_AFFECT:
                r_passe_2(root->opr[0]);
                r_passe_2(root->opr[1]);
                break;
            case NODE_DECLS:
                r_passe_2(root->opr[0]);
                r_passe_2(root->opr[1]);
                break;
            case NODE_DECL:

                varDecl++;
                if(root->opr[1]){
                        // Si la variable est une déclaration initialisée
                    if( root->opr[1]->nature == NODE_INTVAL &&
                        root->opr[0]->nature == NODE_IDENT){
                        create_inst_word(root->opr[0]->ident,root->opr[1]->value);
                    }
                    else{
                        create_inst_word(root->opr[0]->ident,root->opr[1]->value);
                        
                        if( root->opr[0]->nature == NODE_IDENT  ){
                            r_passe_2(root->opr[0]);
                            r_passe_2(root->opr[1]);
                            r1 = get_current_reg();
                            if(reg_available()){
                                allocate_reg();
                                r2 = get_current_reg();
                                a.duo = create_inst_lui;
                                addToInstBuffer(a,r2, 0x1001,0);    
                                a.tre = create_inst_sw;
                                addToInstBuffer(a,r1,root->opr[0]->offset,r2);
                            }else{
                            }
                        }
                    }  
                }
                break;
            case NODE_PLUS:
                plus_inst(root);
                break;
            case NODE_STRINGVAL:
                create_inst_asciiz(NULL,root->str);
                break;
            case NODE_LIST:
                r_passe_2(root->opr[0]);
                r_passe_2(root->opr[1]);
                break;
            case NODE_PRINT:

                r_passe_2_print(root->opr[0]);

                if(root->nops > 1)
                  r_passe_2_print(root->opr[1]);
                 
           
            default:

                break;
        }
    }
}
void global_var(node_t root){
 instWoutArg a;
    int32_t label;
    if(root != NULL){
        switch(root->nature){
            case NODE_PROGRAM:
            
                if (root->nops > 1)
                {
                    r_passe_2(root->opr[1]);
                }
                else
                {
                   r_passe_2(root->opr[0]);
                }
                break;
            case NODE_FUNC :
                r_passe_2(root->opr[1]);
                r_passe_2(root->opr[2]);
                r_passe_2(root->opr[0]);
                create_inst_text_sec();
                create_inst_stack_allocation();
                releaseInstBuffer();
                create_inst_stack_deallocation(root->offset + get_temporary_max_offset());
                break;
            case NODE_IDENT:
                break;
            case NODE_BLOCK:
                r_passe_2(root->opr[0]);
                r_passe_2(root->opr[1]);
                break;
            case NODE_INTVAL:
                break;
            case NODE_AFFECT:
                r_passe_2(root->opr[0]);
                r_passe_2(root->opr[1]);
                break;
            case NODE_DECLS:
                global_var(root->opr[0]);
                global_var(root->opr[1]);
                break;
            case NODE_DECL:
                if(!root->opr[1]){
                    create_inst_word(root->ident,0);
                }
                else{
                    create_inst_word(root->ident,root->opr[1]->value);
                }
                break;
            case NODE_PLUS:
                plus_inst(root);
                break;
            case NODE_LIST:
                r_passe_2(root->opr[0]);
                r_passe_2(root->opr[1]);
                break;
            default:
                break;
        }
    }
}

void gen_code_passe_2(node_t root) {
    
    int32_t offset = getStartOffset(root); 
    int32_t tmpOffset;
    
    set_temporary_start_offset(offset);

    create_inst_data_sec();

    if (root->nops > 1)
	{
        global_var(root->opr[0]);
        r_passe_2(root->opr[1]);
    }else{
        r_passe_2(root->opr[0]);
    }
        
    



    
}
