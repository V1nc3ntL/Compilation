
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


void r_passe_2(node_t root){
 int32_t r1 = 0, r2 = 0 , r3 = 0;

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
                r3 = root->value;
                break;
            case NODE_AFFECT:
                r_passe_2(root->opr[0]);
                r_passe_2(root->opr[1]);
                create_inst_sw(r1, r2, r3);
                break;
            case NODE_DECLS:
                r_passe_2(root->opr[0]);
                r_passe_2(root->opr[1]);
                break;
            case NODE_DECL:
                //printf("DECL encountered");
                r_passe_2(root->opr[0]);
                
                r_passe_2(root->opr[1]);
                
                if(root->opr[1]->nature == NODE_PLUS){
                    r1 = get_current_reg();
                    // Trouver l"adresse donnée
                    push_temporary(r1);

                }
                break;

            case NODE_PLUS:


                
              
                if(root->opr[0]->nature == NODE_INTVAL){

                    if(reg_available()){
                        allocate_reg();
                        r1 = get_current_reg();
                        create_inst_addiu(r1,r2 , root->opr[0]->value );

                    }else{

                        r1 = get_current_reg();
                        printf("NO MORE REG left son\n");
                        push_temporary(r1);
                        release_reg();
                                               
                        //stack allocation
                        //pop_tempora
                    }
                
                }
                 
                if(root->opr[1]->nature == NODE_INTVAL){
                    
                    if(reg_available()){
                        allocate_reg();
                        r1 = get_current_reg();
                        create_inst_addiu(r1,r2 , root->opr[1]->value );

                    }else{
                        r1 = get_current_reg();
                        push_temporary(r1);
                        release_reg();
                       // push_temporary(r1);
                        //stack allocation
                    }
                    
                }

               r_passe_2(root->opr[0]);
      
                
                if(reg_available()){            
                    allocate_reg();
                    r3=get_current_reg();      
                    release_reg();
                    r2 = get_current_reg();
                     r_passe_2(root->opr[1]);
                    
                    create_inst_addu(r2,r3,r2);

                }else{
                    push_temporary(r1);
                    r3=get_current_reg();      
                    release_reg();
                    r2 = get_current_reg();
                    r_passe_2(root->opr[1]);
                    create_inst_addu(r2,r3,r2);

                    pop_temporary(r1);
                }
             
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
