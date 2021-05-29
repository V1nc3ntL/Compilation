
#include <stdio.h>

#include "defs.h"
#include "passe_2.h"
#include "miniccutils.h"

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

     int32_t tmp = 0, r1 = 0, r2 = 0 , r3 = 0;

                if(root->opr[0]->nature == NODE_INTVAL){
                    tmp = root->opr[0]->value;

                    if(reg_available()){
                        r1 = get_current_reg();
                        allocate_reg();
                    }else{
                        r1 = get_current_reg();
                        push_temporary(r1);
                    }
                }else{
                    r_passe_2(root->opr[0]);
                    tmp = root->opr[0]->value;

                    if(reg_available()){
                        r1 = get_current_reg();
                        allocate_reg();
                    }else{
                        r1 = get_current_reg();
                        push_temporary(r1);
                        
                    }
                }
                create_inst_addiu(r1,0,tmp);
               
                
                if(root->opr[1]->nature == NODE_INTVAL){
                    tmp = root->opr[1]->value;
                    if(reg_available()){
                        allocate_reg();
                        
                        r1 = get_current_reg();
                     
                        create_inst_addiu(r1,0 , tmp );
                        
                    }else{
                        push_temporary(r1);
                        create_inst_addiu(r1,0 , tmp);

                        //stack allocation
                    }
                    
                }else{
                    
                    r_passe_2(root->opr[1]);
                    
                    if(reg_available()){  
                        r1 = get_current_reg();
                        allocate_reg();
                        r2=get_current_reg(); 
                      
                        create_inst_addu(r1,r1,r2);
                        release_reg();
                    }else{  
                        r1=get_current_reg();
                        r3 = get_restore_reg();
                        pop_temporary(r3);      
                       
                        create_inst_addu(r1,r3,r1);
                        pop_temporary(r3);
                        
                        create_inst_addu(r1,r3,r1);    
                    }
                  release_reg();
                }
               
}             

void r_passe_2(node_t root){


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
                create_inst_stack_allocation();

                r_passe_2(root->opr[1]);
                r_passe_2(root->opr[2]);
                r_passe_2(root->opr[0]);
                get_temporary_max_offset();
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
                    push_temporary(get_current_reg());
                }
                    
                
                break;

            case NODE_PLUS:
                plus_inst(root);
                break;

            case NODE_STRINGVAL:
                create_inst_asciiz(root->ident,root->str);
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
    
    
}
