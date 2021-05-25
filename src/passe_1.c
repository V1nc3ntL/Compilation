
#include <stdio.h>

#include "defs.h"
#include "passe_1.h"

extern int trace_level;

void analyse_passe_1(node_t root)
{
	// if(root == NONE)
	// {
	// 	return 
	// }
	for (int i = 0; i < root -> nops; i++)
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
}

