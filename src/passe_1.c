
#include <stdio.h>

#include "defs.h"
#include "passe_1.h"
#include "miniccutils.h"
#include "stdlib.h"
#include "common.h"
int trace_level;

void analyse_node_ident (node_t n)
{

  int32_t off;
  node_t tmp = get_decl_node(n->ident);

  if (tmp)
  {
     

    n -> offset = tmp->offset;
    n -> type   = tmp->type;
    n -> decl_node = tmp;
       
  }
        
  else
  {

    off = env_add_element (n -> ident, n);

    if (off >= 0)
    { 
      add_string (n -> ident);
      n -> offset = off;
    }

    else
    {
      printf("Error line %d: variable already declared",n->lineno);
     exit(-1);
    }
  }


}

void analyse_node_global_ident (node_t n)
{
  int32_t off;
  
    n -> global_decl = true;
    
    off = env_add_element (n -> ident, n);
    
    if (off >= 0)
    {

      n -> offset = off;
    }
    // Affectation de variables globales dans une variable globale
    else
    {
      n -> offset = ((node_t) get_decl_node(n->ident))->offset;
      
    }
}

void analyse_node_func (node_t n)
{
  //Faire analyse node
  n -> opr[1] -> type = n -> opr[0] -> type;
  n -> offset = get_env_current_offset();
}

void analyse_node_stringval (node_t n)
{
  n -> offset = add_string (n -> str);
}

void analyse_node_program (node_t n)
{
  n -> offset = add_string (n -> str);
}

void analyse_global (node_t root)
{
  if (!root)
  {
    return;
  }

  switch (root -> nature)
  {
    case NODE_PROGRAM:

    push_global_context ();
    if (root -> nops > 1)
    {
      analyse_global(root -> opr[0]);
      analyse_passe_1(root -> opr[1]);
    }
    else
    {
      analyse_passe_1(root -> opr[1]);
    }
    pop_context ();
    break;

    case NODE_IDENT:
      analyse_node_global_ident(root);
      break;

    case NODE_LIST:
      root -> opr[0] -> type = root->type;
      root -> opr[1] -> type = root->type;

      /*if(root->opr[0])
        root -> opr[0]-> type  = root->decl_node->type;
      if(root->opr[1])
        root -> opr[1] -> type = root->decl_node->type;
     */ 
      analyse_global (root -> opr[0]);
      analyse_global (root -> opr[1]);
      break;

    case NODE_DECLS:

      root -> opr[0] -> decl_node = root;
      root -> opr[1] -> decl_node = root;
      
      if(root -> opr[0] ->nature == NODE_TYPE)
        root -> type = root -> opr[0] -> type;

        
      root -> opr[0] -> type = root->type;
      root -> opr[1] -> type= root->type;

      analyse_global (root -> opr[0]);
      analyse_global (root -> opr[1]);
      break;

    case NODE_DECL:
      
      root->opr[0]->type = root->type;
      if(root->opr[1])
        root->opr[1]->type = root->type;
      
      analyse_global (root->opr[0]);
      analyse_global (root->opr[1]);
      break;

    case NODE_AFFECT:

      analyse_passe_1 (root->opr[0]);
      analyse_passe_1 (root->opr[1]);


      break;

    case NODE_PLUS:
      analyse_passe_1 (root->opr[0]);
      analyse_passe_1 (root->opr[1]);
      break;

    default:
      break;

    }
}

void analyse_passe_1 (node_t root)
{
  if (!root)
  {
    return;
  }

  switch (root -> nature)
  {
    case NODE_MUL:
    analyse_passe_1 (root -> opr[0]);
    analyse_passe_1 (root -> opr[1]);
      break;
    case NODE_PROGRAM:
      push_global_context ();
      if (root -> nops > 1)
      {
         analyse_global  (root -> opr[0]);
         analyse_passe_1 (root -> opr[1]);
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
      root -> opr[0] -> type = root -> type;
      root -> opr[1] -> type = root -> opr[0] -> type;
      analyse_passe_1(root -> opr[0]);
      analyse_passe_1(root -> opr[1]);
      break;

    case NODE_DECLS:   
      
      root -> decl_node = root;
      analyse_passe_1 (root -> opr[0]);
      
      if(root->opr[0]->nature == NODE_TYPE){
        root -> type   = root -> opr[0] -> type;
        root->opr[1]->type = root->type;
      }
      
      root -> opr[1] -> decl_node = root;
      root -> opr[0] -> decl_node = root;

      analyse_passe_1(root -> opr[1]);
      break;

    case NODE_DECL:

      if(root -> opr[1] == NULL)
      {
        root -> opr[0] -> type = root -> type;
      }
      else if(root -> opr[0] == NULL)
      {
         root -> type = root -> opr[1] -> type ;
      }else{
          if(root -> opr[0] -> nature == root -> opr[1] -> nature)
        {
          if(root -> opr[0] -> type == TYPE_NONE)
          {
            root -> opr[0] -> type = root -> opr[1] -> type;
          }
        }
      }
     break;

    case NODE_FUNC:

      push_context ();
      analyse_passe_1 (root->opr[0]);
      analyse_passe_1(root -> opr[1]);
      analyse_passe_1 (root->opr[2]);
      analyse_node_func(root);
      pop_context ();
      break;

    case NODE_BLOCK:
     // push_context ();
      analyse_passe_1 (root->opr[0]);
      analyse_passe_1 (root->opr[1]);
      //pop_context ();
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
    case NODE_GT:
      analyse_passe_1 (root->opr[0]);
      analyse_passe_1 (root->opr[1]);
      break;
      case NODE_IF:
        analyse_passe_1 (root->opr[0]);
        analyse_passe_1 (root->opr[1]);
        break;
      case NODE_MINUS:
        analyse_passe_1 (root->opr[0]);
        analyse_passe_1 (root->opr[1]);
        break;
      case NODE_WHILE:
        analyse_passe_1 (root->opr[0]);
        analyse_passe_1 (root->opr[1]);
        break;

    case NODE_AFFECT:
      analyse_passe_1 (root->opr[0]);
      analyse_passe_1 (root->opr[1]);

      if(root->opr[0]->type != root->opr[1]->type ){
        printf("Error line %d: Wrong affectation\n",root->lineno);
        exit(-1);
      }
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
