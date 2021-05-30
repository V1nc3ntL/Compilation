#include <stdio.h>

#include "defs.h"
#include "passe_2.h"
#include "miniccutils.h"
#include "instBuffer.h"

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
    
    int32_t tmp = 0, r1 = 0, r2 = 0 , r3 = 0;

                if(root->opr[0]->nature == NODE_INTVAL){
                    tmp = root->opr[0]->value;

                    if(reg_available()){
                        r1 = get_current_reg();
                        allocate_reg();
                    }else{
                        release_reg();
                        r1 = get_current_reg();
                        a.uno = push_temporary;
                        addToInstBuffer(a,r1,0,0);
                        allocate_reg();
                    }
                }else{
                    r_passe_2(root->opr[0]);
                    tmp = root->opr[0]->value;

                    if(reg_available()){
                        r1 = get_current_reg();
                        allocate_reg();
                    }else{
                        release_reg();
                        a.uno = push_temporary;
                        addToInstBuffer(a,r1,0,0);
                        r1 = get_current_reg();
                        
                    }
                }
                
                a.tre = create_inst_addiu;
                addToInstBuffer(a,r1,0,tmp);
                
                
                if(root->opr[1]->nature == NODE_INTVAL){
                    tmp = root->opr[1]->value;
                    if(reg_available()){
                        r1 = get_current_reg();
                        release_reg();
                        a.tre = create_inst_addiu;
                        addToInstBuffer(a,r1,0,tmp);
                        
                    }else{

                        a.uno = push_temporary;
                        addToInstBuffer(a,r1,0,0);
                        a.tre = create_inst_addiu;
                        addToInstBuffer(a,r1,0,tmp);
                    }
                    
                }else{
                    
                    r_passe_2(root->opr[1]);


                    if(reg_available()){  
                        allocate_reg();
                        r1 = get_current_reg();
                        release_reg();
                        r2=get_current_reg();               
                        a.tre = create_inst_addu;
                        addToInstBuffer(a,r2,r2,r1);
                        release_reg();
                        
                    }else{  
                          
                        r1=get_current_reg();
                        r3 = get_restore_reg(); 
                        a.uno = pop_temporary;
                        addToInstBuffer(a,r3,0,0);   

                        a.tre = create_inst_addu;
                        addToInstBuffer(a,r1,r3,r1);

                        a.uno = pop_temporary;
                        addToInstBuffer(a,r3,0,0); 

                        release_reg();
                        r1 = get_current_reg();

                        a.tre = create_inst_addu;
                        addToInstBuffer(a,r1,r3,r1);
                    }
                }
}            


void r_passe_2_print(node_t root){
  instWoutArg a;

                
    
    
                 if(root != NULL){
        switch(root->nature){
            case NODE_LIST:
                r_passe_2_print(root->opr[0]);
                r_passe_2_print(root->opr[1]);
                printf("list");
                break;
            case NODE_STRINGVAL :
                printf("stringval");  
                // Traduire 
                create_inst_asciiz(NULL,root->str);
      
                a.tre = create_inst_lw;
                addToInstBuffer(a,4,root->offset,29);     
                break;
            case NODE_IDENT :
               
                a.tre = create_inst_lw;
                addToInstBuffer(a,4,root->offset,29);     
                printf("ident");
                // Traduire le chiffre
                break;
        }
    }

                a.tre = create_inst_addiu;
                addToInstBuffer(a,2,0,4);
}

void r_passe_2(node_t root){
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

                if(reg_available()){
                    allocate_reg();
                    a.uno = push_temporary;
                    addToInstBuffer(a,get_current_reg(),0,0);
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
                label = get_new_label();
                create_inst_label(label);
                r_passe_2_print(root->opr[0]);
                if(root->nops > 1)
                  r_passe_2_print(root->opr[1]);
                 
           
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
    /*
    if (root->nops > 1)
	{
        create_inst_data_sec();
	  return root->opr[1]->offset;
	}
      else
	{
	  return root->opr[0]->offset;
	}
    */

    create_inst_data_sec();

    
    r_passe_2(root);
    
    create_inst_addiu(2,0,10);

    
}
