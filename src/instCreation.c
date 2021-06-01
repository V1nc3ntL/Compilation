#include "defs.h"
#include "instCreation.h"
#include "miniccutils.h"
#include "instBuffer.h"

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
        
                a.uno = push_temporary;
                addToInstBuffer(a,r1,0,0);
                release_reg();
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


void moins_inst(node_t root){
    
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
        
                a.uno = push_temporary;
                addToInstBuffer(a,r1,0,0);
                release_reg();
            }

        }else{
                r_passe_2(root->opr[0]);
                
                if(reg_available()){
                    r2 = get_current_reg();
                    allocate_reg();
                    r1 = get_current_reg();
                    allocated++;
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
                a.tre = create_inst_subu;
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
                    a.tre = create_inst_subu;
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
                a.tre = create_inst_subu;
                addToInstBuffer(a,r1,r1,get_restore_reg());
        }
        for(int i = allocated; i > 0;release_reg(), --i);
}      