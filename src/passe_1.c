
#include <stdio.h>

#include "defs.h"
#include "passe_1.h"
#include "miniccutils.h"

int trace_level;


void analyse_node_ident(node_t n)
{

	n -> type        = TYPE_STRING;
	n -> global_decl = true;

	push_context();

	if(n->ident)
		n -> decl_node   = get_decl_node(n -> ident);
	
	
	if(env_add_element(n -> ident,n) >= 0)
	{
		n -> offset  = add_string(n -> ident);
	}

	else
	{
		n -> offset =  get_env_current_offset();
	}
	pop_context();

}

void analyse_node_func(node_t n)
{

	//reset_env_current_offset();
	//Faire analyse node

	n -> offset = get_env_current_offset();

}

void analyse_node_stringval(node_t n)
{
	n -> offset = add_string(n -> str);
}

void analyse_node_program(node_t n)
{
	
	n -> offset = add_string(n -> str);
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

			analyse_passe_1(root -> opr[0]);
			analyse_passe_1(root -> opr[1]);
			root->opr[0]->type = root->opr[1]->type;
			break;
		case NODE_DECL:
			analyse_passe_1(root -> opr[0]);
			analyse_passe_1(root -> opr[1]);
			break;
		case NODE_FUNC:
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
