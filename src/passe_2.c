#include <stdio.h>

#include "defs.h"
#include "passe_2.h"
#include "miniccutils.h"
#include "instBuffer.h"
#include <string.h>
#define ALIGN(a) ( a % 4 ? a - a % 4 + 4 : a)

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


void plus_inst(node_t root){
    
    instWoutArg a;
    int allocated = 0;
    bool pushed = 0;
    int32_t tmp = 0, r1 = 0, r2 = 0 , r3 = 0;

        if(root->opr[0]->nature == NODE_INTVAL){

            tmp = root->opr[0]->value;
            r1 = get_current_reg();
            if(reg_available()){
                
                allocate_reg();
                allocated++;
                a.tre = create_inst_addiu;
                addToInstBuffer(a,r1,0,tmp);                        
            }else{

                /*
                a.uno = push_temporary;
                addToInstBuffer(a,r1,0,0);
                release_reg();*/
            }

        }else{
                r_passe_2(root->opr[0]);
                
                if(reg_available()){
                    r2 = get_current_reg();
                    allocate_reg();
                    r1 = get_current_reg();
                    allocated++;
                    /*a.tre = create_inst_addu;
                    addToInstBuffer(a,r2,r2,r1);*/
                }else{
                    /*a.uno = push_temporary;
                    addToInstBuffer(a,r1,0,0);
                    r1 = get_current_reg();
                    */
                }
             
        }


        if(root->opr[1]->nature == NODE_INTVAL){
            tmp = root->opr[1]->value;
           
            if(reg_available()){

                r2 = get_current_reg();
                a.tre = create_inst_addiu;
                addToInstBuffer(a,r2,0,tmp);
                release_reg();
                allocated--;
                r1 = get_current_reg();
                a.tre = create_inst_addu;
                addToInstBuffer(a,r1,r1,r2);
                
            }else{
                pushed = true;
                allocated--;
                release_reg();
                r1 = get_current_reg();
                a.uno = push_temporary;
                addToInstBuffer(a,r1,0,0);
                a.tre = create_inst_addiu;
                addToInstBuffer(a,r1,0,tmp);
                
            }
              
        }else{
                r_passe_2(root->opr[1]);
                
                if(reg_available()){
                    r2 = get_current_reg();
                    release_reg();
                    r1 = get_current_reg();
                    allocated--;
                    a.tre = create_inst_addu;
                    addToInstBuffer(a,r1,r1,r2);
                }else{
                    
                }
        }

  /*          r1 = get_current_reg();
            allocate_reg();
            allocated++;
            r2 = get_current_reg();
            a.tre = create_inst_addu;
            addToInstBuffer(a,r1,r1,r2);
    */
        
        if(pushed){
                pushed = true;
                a.uno = pop_temporary;
                addToInstBuffer(a,get_restore_reg(),0,0);
                r1 = get_current_reg();
                a.tre = create_inst_addu;
                addToInstBuffer(a,r1,r1,get_restore_reg());
        }
        for(int i = allocated; i > 0;release_reg(), --i);
}            

int paramPrintAddr = 0;

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
                    a.tre = create_inst_lw;
                    if(root->type == TYPE_INT)
                        addToInstBuffer(a,4,root->decl_node->offset-4,r1);
                    else{
                        addToInstBuffer(a,4,root->decl_node->offset,r1);
                    }
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
                // Si la variable est une déclaration initialisée
                if( root->opr[1]->nature == NODE_INTVAL &&
                    root->opr[0]->nature == NODE_IDENT){
                    create_inst_word(root->opr[0]->ident,root->opr[1]->value);
                }
                else{
                    create_inst_word(root->opr[0]->ident,root->opr[1]->value);
                    
                    if( root->opr[1]->nature == NODE_PLUS &&
                        root->opr[0]->nature == NODE_IDENT  ){
                        r_passe_2(root->opr[0]);
                        r_passe_2(root->opr[1]);
                        r1 = get_current_reg();
                        if(reg_available()){
                            allocate_reg();
                            r2 = get_current_reg();
                            a.duo = create_inst_lui;
                            addToInstBuffer(a,r2, 0x1001,0);    
                            a.tre = create_inst_sw;
                            addToInstBuffer(a,r1,root->opr[0]->offset-4,r2);
                        }else{
                        }
                    }
                }  
               /*  *//*
                // Retrouver l'adresse de data
               
                    
                    allocate_reg();
                    
                    
                    release_reg();
                }*/
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
                //create_inst_sw(r1, r2, r3);
                break;
            case NODE_DECLS:
                r_passe_2(root->opr[0]);
                r_passe_2(root->opr[1]);
                break;
            case NODE_DECL:
        
                r_passe_2(root->opr[0]);
                r_passe_2(root->opr[1]);

                if(!reg_available()){
                    a.uno = push_temporary;
                    addToInstBuffer(a,get_current_reg(),0,0);
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
             //   r_passe_2(root->opr[0]);
               
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
