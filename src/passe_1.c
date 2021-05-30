
#include <stdio.h>

#include "defs.h"
#include "passe_1.h"
#include "miniccutils.h"
#include "stdlib.h"
int trace_level;

void
analyse_node_ident (node_t n)
{
  int32_t off;
  //n -> type        = TYPE_STRING;
  n->decl_node = get_decl_node (n->ident);
  
         
  if (n->decl_node)
    {
      n->offset = n->decl_node->offset;
      n->type = n->decl_node->type;

    }
  else
    {

      off = env_add_element (n->ident, n);

      if (off >= 0)
	{
	  add_string (n->ident);
	  n->offset = off;
	}
      else
	{
 
        
	  n->offset = n->decl_node->offset;

	  n->type = n->decl_node->type;

	}
  
    }

}

void
analyse_node_global_ident (node_t n)
{
  int32_t off;

  //n -> type        = TYPE_STRING;
  n->decl_node = get_decl_node (n->ident);
  n->global_decl = true;

  if (n->decl_node)
    {
      n->offset = n->decl_node->offset;
      n->type = n->decl_node->type;
 
    }
  else
    {
      if (off = env_add_element (n->ident, n) >= 0)
	{
	  n->offset = off;

	}
      else
	{

	  n->offset = n->decl_node->offset;
	  n->type = n->decl_node->type;
	}

    }


}

void
analyse_node_func (node_t n)
{

  //reset_env_current_offset();
  //Faire analyse node

  n->offset = get_env_current_offset ();

}

void
analyse_node_stringval (node_t n)
{
  n->offset = add_string (n->str);
}

void
analyse_node_program (node_t n)
{

  n->offset = add_string (n->str);
}

void
analyse_global (node_t root)
{
  if (!root)
    {
      return;
    }

  switch (root->nature)
    {

    case NODE_PROGRAM:
      push_global_context ();
      if (root->nops > 1)
	{
	  analyse_global (root->opr[0]);
	  analyse_passe_1 (root->opr[1]);
	}
      else
	{
	  analyse_passe_1 (root->opr[1]);
	}
      pop_context ();
      break;

    case NODE_IDENT:
      analyse_node_global_ident (root);
      break;

    case NODE_LIST:
      root->opr[0]->type = root->type;
      root->opr[1]->type = root->type;
      analyse_passe_1 (root->opr[0]);
      analyse_passe_1 (root->opr[1]);
      break;
    case NODE_DECLS:

      root->opr[0]->decl_node = root;
      root->opr[1]->decl_node = root;

      
      analyse_passe_1 (root->opr[0]);
      root->type = root->opr[0]->type;
      analyse_passe_1 (root->opr[1]);

      break;
    case NODE_DECL:
    
          
    
      if (root->decl_node)
	{
	  if (root->decl_node->type != root->opr[1]->type
	      || root->decl_node->type != root->opr[0]->type)
	    exit (-1);
	  else
	    {
	      root->opr[0]->type = root->decl_node->type;
	      root->opr[1]->type = root->decl_node->type;
	    }
	}
      else
	{
	  root->opr[0]->type = root->opr[1]->type;
	}
      analyse_passe_1 (root->opr[0]);
      analyse_passe_1 (root->opr[1]);


      break;
    case NODE_FUNC:

      analyse_passe_1 (root->opr[0]);
      analyse_passe_1 (root->opr[1]);
      analyse_passe_1 (root->opr[2]);
      analyse_node_func (root);
      break;
    case NODE_BLOCK:
      analyse_passe_1 (root->opr[0]);
      analyse_passe_1 (root->opr[1]);
      break;
    case NODE_FOR:
      analyse_passe_1 (root->opr[0]);
      analyse_passe_1 (root->opr[1]);
      analyse_passe_1 (root->opr[2]);
      analyse_passe_1 (root->opr[3]);
      break;
    case NODE_LT:
      analyse_passe_1 (root->opr[0]);
      analyse_passe_1 (root->opr[1]);
      break;
    case NODE_AFFECT:
      analyse_passe_1 (root->opr[0]);
      analyse_passe_1 (root->opr[1]);
      break;
    case NODE_PLUS:
      analyse_passe_1 (root->opr[0]);
      analyse_passe_1 (root->opr[1]);
      break;
    case NODE_PRINT:
      analyse_passe_1 (root->opr[0]);
      break;
    case NODE_STRINGVAL:
      analyse_node_stringval (root);
      break;

    default:
      break;


    }
}

void
analyse_passe_1 (node_t root)
{
  if (!root)
    {
      return;
    }

  switch (root->nature)
    {

    case NODE_PROGRAM:
      push_global_context ();
      if (root->nops > 1)
	{
	  analyse_global (root->opr[0]);
	  analyse_passe_1 (root->opr[1]);
	}
      else
	{
	  analyse_passe_1 (root->opr[0]);
	}
      pop_context ();
      break;

    case NODE_IDENT:
      analyse_node_ident (root);
      break;

    case NODE_LIST:
      root->opr[0]->type = root->type;
      root->opr[1]->type = root->opr[0]->type;
      analyse_passe_1 (root->opr[0]);
      analyse_passe_1 (root->opr[1]);
      break;
    case NODE_DECLS:   
      
      root->decl_node = root;
      analyse_passe_1 (root->opr[0]);
      root->decl_node->type = root->opr[0]->type;
      
      root->opr[1]->decl_node = root;
      root->opr[0]->decl_node = root;
      analyse_passe_1 (root->opr[1]);

      break;
    case NODE_DECL:
    

     if (root->decl_node)
	  {

	      root->opr[0]->type = root->decl_node->type;
	      root->opr[1]->type = root->decl_node->type;
	    
	  }
      analyse_passe_1 (root->opr[0]);
      analyse_passe_1 (root->opr[1]);
      if (root->decl_node->type != root->opr[1]->type)
	    {
        printf("\nError line %d: wrong type assignment",root->lineno,root->ident);
	      exit (-1);
	    }
     break;
    case NODE_FUNC:
      reset_env_current_offset ();
      push_context ();
      analyse_passe_1 (root->opr[0]);
      //      analyse_passe_1(root -> opr[1]);
      analyse_passe_1 (root->opr[2]);
      analyse_node_func (root);
      pop_context ();
      break;
    case NODE_BLOCK:
      push_context ();
      analyse_passe_1 (root->opr[0]);
      analyse_passe_1 (root->opr[1]);
      pop_context ();
      break;
    case NODE_FOR:
      analyse_passe_1 (root->opr[0]);
      analyse_passe_1 (root->opr[1]);
      analyse_passe_1 (root->opr[2]);
      analyse_passe_1 (root->opr[3]);
      break;
    case NODE_LT:
      analyse_passe_1 (root->opr[0]);
      analyse_passe_1 (root->opr[1]);
      break;
    case NODE_AFFECT:
      analyse_passe_1 (root->opr[0]);
      analyse_passe_1 (root->opr[1]);
      break;
    case NODE_PLUS:
      analyse_passe_1 (root->opr[0]);
      analyse_passe_1 (root->opr[1]);
      break;
    case NODE_PRINT:
      analyse_passe_1 (root->opr[0]);
      break;
    case NODE_STRINGVAL:
      analyse_node_stringval (root);
      break;

    default:
      break;


    }
}
