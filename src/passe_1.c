
#include <stdio.h>

#include "defs.h"
#include "passe_1.h"
#include "miniccutils.h"
#include "stdlib.h"
#include "common.h"
int trace_level;


void analyse_node_ident(node_t n)
{

	//n -> type        = TYPE_STRING;
	node_t tmp;



	if(env_add_element(n -> ident,n) >= 0)
	{
		n -> offset  = add_string(n -> ident);
	}
	else
	{
		tmp   = get_decl_node(n -> ident);
		n -> offset =  tmp->offset;

	}


}

void analyse_node_func(node_t n)
{
	node_t tmp;
	//Faire analyse node
	
	n -> offset = get_env_current_offset();
	
	/*if(env_add_element(n -> ident,n) >= 0)
	{
		n -> offset  = add_string(n -> ident);
	}
	else
	{
		tmp   = get_decl_node(n -> ident);
		n -> offset =  tmp->offset;
	}*/

	
}

void analyse_node_stringval(node_t n)
{
	n -> offset = add_string(n -> str);
}

void analyse_node_program(node_t n)
{
	push_context();
	n -> offset = add_string(n -> str);
	pop_context();
}

void analyse_passe_1(node_t root)
{
	if(!root)
	{
		return; 
	}

	switch(root -> nature)
	{

		case NODE_PROGRAM:
			push_global_context();

			if(root->nops > 1){
				root -> opr[0]->global_decl = true;
				analyse_passe_1(root -> opr[0]);
				analyse_passe_1(root -> opr[1]);
			}else{
				analyse_passe_1(root -> opr[1]);
			}
			
			pop_context();
			break;

		case NODE_IDENT:
			analyse_node_ident(root);
			break;
			
		case NODE_LIST:
			analyse_passe_1(root -> opr[0]);
			analyse_passe_1(root -> opr[1]);
			break;
		case NODE_DECLS:
			push_context();
			root->decl_node = root;
			analyse_passe_1(root -> opr[0]);
			analyse_passe_1(root -> opr[1]);
			pop_context();
			break;
		case NODE_DECL:

			analyse_passe_1(root -> opr[0]);
			analyse_passe_1(root -> opr[1]);

			if(root->decl_node){
				if(root->decl_node->type != 
			 root->opr[1]->type )
			 	exit(-1);
				 else{
					root->opr[0]->type =  root->decl_node->type;
				 }
			}
			else{
				root->decl_node = root;
				root->opr[0]->type = root->opr[1]->type;
				root->opr[0]->offset = get_env_current_offset();
			}

			break;
		case NODE_FUNC:

			root->opr[1]->type = root->opr[0]->type;
			analyse_passe_1(root -> opr[0]);
			analyse_passe_1(root -> opr[1]);
			analyse_passe_1(root -> opr[2]);
			analyse_node_func(root);
			break;
		case NODE_BLOCK:

			analyse_passe_1(root -> opr[0]);
			analyse_passe_1(root -> opr[1]);
			break;
		case NODE_FOR:
			push_context();
			analyse_passe_1(root -> opr[0]);
			analyse_passe_1(root -> opr[1]);
			analyse_passe_1(root -> opr[2]);
			analyse_passe_1(root -> opr[3]);

			break;
		case NODE_LT:

			analyse_passe_1(root -> opr[0]);
			analyse_passe_1(root -> opr[1]);

			break;
		case NODE_AFFECT:

			analyse_passe_1(root -> opr[0]);
			analyse_passe_1(root -> opr[1]);

			break;
		case NODE_PLUS:
			analyse_passe_1(root -> opr[0]);
			analyse_passe_1(root -> opr[1]);
			break;
		case NODE_PRINT:
			analyse_passe_1(root -> opr[0]);
			break;
		case NODE_STRINGVAL:
			analyse_node_stringval(root);
			break;

		default:
			break;


	}
}
