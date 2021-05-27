
#include <stdio.h>

#include "defs.h"
#include "passe_1.h"
#include "miniccutils.h"

extern int trace_level;

void analyse_passe_1(node_t root)
{
	if(!root)
	{
		return; 
	}

	switch(root -> nature)
	{
		case NODE_PROGRAM:
			analyse_passe_1(root -> opr[0]);
			analyse_passe_1(root -> opr[1]);
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

void analyse_node_ident(node_t n)
{
	n -> type        = TYPE_STRING;
	n -> global_decl = true;
	n -> decl_node   = get_decl_node(n -> ident);

/*	if(env_add_element(n -> ident,n) >= 0)
	{
		n -> offset  = add_string(n -> ident);
	}
	else
	{
		n -> offset =  get_env_current_offset();
	}
*/
}

void analyse_node_func(node_t n)
{
	n -> offset = get_env_current_offset();
}

void analyse_node_stringval(node_t n)
{
	n -> offset = add_string(n -> str);
}

/*	for (int i = 0; i < root -> nops; i++)
	{
		switch(root -> opr[i] -> nature)
		{
			case NODE_IDENT:
				printf("JE SUIS LA 1\n");
				root -> opr[i] -> type = TYPE_STRING;
				analyse_passe_1(root -> opr[i]);
				break;
			case NODE_FUNC:
				printf("JE SUIS LA 2\n");
				analyse_passe_1(root -> opr[i]);
				break;
			case NODE_LIST:
				printf("JE SUIS LA 3\n");
				analyse_passe_1(root -> opr[i]);
				break;
			case NODE_DECLS:
				printf("JE SUIS LA 4\n");
				analyse_passe_1(root -> opr[i]);
				break;
			case NODE_FOR:
				printf("JE SUIS LA 5\n");
				analyse_passe_1(root -> opr[i]);
				break;
			case NODE_DECL:
				printf("JE SUIS LA 6\n");
				analyse_passe_1(root -> opr[i]);
				break;
			case NODE_AFFECT:
				printf("JE SUIS LA 7\n");
				analyse_passe_1(root -> opr[i]);
				break;
			case NODE_BLOCK:
				printf("JE SUIS LA 8\n");
				analyse_passe_1(root -> opr[i]);
				break;
			case NODE_PLUS:
				printf("JE SUIS LA 9\n");
				analyse_passe_1(root -> opr[i]);
				break;
			case NODE_PRINT:
				printf("JE SUIS LA 10\n");
				analyse_passe_1(root -> opr[i]);
				break;
			case NODE_LT:
				printf("JE SUIS LA 11\n");
				analyse_passe_1(root -> opr[i]);
				break;
			case NONE:
				break;
			default: 
				break;
		}
	}
*/

