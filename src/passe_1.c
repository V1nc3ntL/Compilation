
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
  // On regarde
  n -> decl_node = get_decl_node (n -> ident);

  // S'il existe une première définition de la variable

  if (n -> decl_node)
  { 
    /// On met a jour l'offset
    n -> offset = n -> decl_node->offset;

    //On met a jour le type
    n -> type   = n -> decl_node->type;
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
      // On met à jour l'offset
      n -> offset = n -> decl_node->offset;

      //On met a jour le type
      n -> type   = n -> decl_node->type;
    }
  }
}

void analyse_node_global_ident (node_t n)
{
  int32_t off;
  n -> decl_node   = get_decl_node (n -> ident);
  n -> global_decl = true;

  if (n -> decl_node)
  {
    n -> offset = n -> decl_node->offset;
    n -> type   = n -> decl_node -> type;
  }

  else
  {
    if (off = env_add_element (n -> ident, n) >= 0)
    {
      n -> offset = off;
    }

    else
    {
      n -> offset = n -> decl_node->offset;
      n -> type   = n -> decl_node->type;
    }
  }
}

void analyse_node_func (node_t n)
{
  //On met a jour le type pour le NODE_IDENT
  n -> opr[1] -> type = n -> opr[0] -> type;

  // On met a jour l'offset
  n -> offset = get_env_current_offset();
}

void analyse_node_stringval (node_t n)
{
  // On met a jour l'offset
  n -> offset = add_string (n -> str);
}

void analyse_node_program (node_t n)
{
  // On met a jour l'offset
  n -> offset = add_string (n -> str);
}

void analyse_global (node_t root)
{
  // Si la node est NULL
  if (!root)
  {
    return;
  }

  //Switch en fonction de la nature de la node
  switch (root -> nature)
  {
    case NODE_PROGRAM:
    // On push le context au tout début de l'arbre
    push_global_context ();
    //Dans le cas, ou il des variables globales en plus
    if (root -> nops > 1)
    {
      analyse_global(root -> opr[0]);
      analyse_passe_1(root -> opr[1]);
    }
    //  dans le cas où on a que le main
    else
    {
      analyse_passe_1(root -> opr[1]);
    }
    // On pop le context apres la création de l'abre
    pop_context ();
    break;

    case NODE_IDENT:

      // On effectue les opérations sur les champs de la NODE_IDENT
      analyse_node_global_ident(root);
      break;

    case NODE_LIST:

      // on transmet le type aux fils de la NODE_LIST
      root -> opr[0] -> type  = root -> type;
      root -> opr[1] -> type  = root -> type;
      //Appels récursifs
      analyse_passe_1 (root -> opr[0]);
      analyse_passe_1 (root -> opr[1]);
      break;

    case NODE_DECLS:

      // On met a jour le champ decl_node pour les fils
      root -> opr[0] -> decl_node = root;
      root -> opr[1] -> decl_node = root;
      root -> type = root -> opr[0] -> type;
      //Appels récursifs
      analyse_passe_1 (root -> opr[0]);
      analyse_passe_1 (root -> opr[1]);
      break;

    case NODE_DECL:

      if (root -> decl_node)
      {
        // En cas d'erreur
        if (root -> decl_node -> type != root -> opr[1] -> type || root -> decl_node -> type != root -> opr[0] -> type)
        {
          exit (-1);
        }
        else
        {
          //Met a jour les types pour les fils
          root->opr[0] -> type = root -> decl_node -> type;
          root->opr[1] -> type = root -> decl_node -> type;
        }
      }
      else
      {
        // On donne le type du second fils au premier fils 
        root -> opr[0] -> type = root -> opr[1] -> type;
      }
      //Appels récursifs
      analyse_passe_1 (root -> opr[0]);
      analyse_passe_1 (root -> opr[1]);
      break;

    case NODE_FUNC:

      //Appels récursifs
      analyse_passe_1 (root -> opr[0]);
      analyse_passe_1 (root -> opr[1]);
      analyse_passe_1 (root -> opr[2]);
      // Opérations sur la NODE_FUNC
      analyse_node_func (root);
      break;

    case NODE_BLOCK:

      // Appels récursifs
      analyse_passe_1 (root -> opr[0]);
      analyse_passe_1 (root -> opr[1]);
      break;

    case NODE_FOR:

      // Appels récursifs
      analyse_passe_1 (root -> opr[0]);
      analyse_passe_1 (root -> opr[1]);
      analyse_passe_1 (root -> opr[2]);
      analyse_passe_1 (root -> opr[3]);
      break;

    case NODE_LT:

      // Appels récursifs
      analyse_passe_1 (root -> opr[0]);
      analyse_passe_1 (root -> opr[1]);
      break;

    case NODE_AFFECT:

      // Appels récursifs
      analyse_passe_1 (root -> opr[0]);
      analyse_passe_1 (root -> opr[1]);
      break;

    case NODE_PLUS:

      // Appels récursifs
      analyse_passe_1 (root -> opr[0]);
      analyse_passe_1 (root -> opr[1]);
      // On vérifie que le l'addition se fait sur deux
      // entités du même type

      if(root -> opr[0] -> type == root -> opr[1] -> type)
      {
        // On attibue le type à la NODE_PLUS
        root -> type = root -> opr[0] -> type;
      }      
      break;


    case NODE_MINUS:

      // Appels récursifs
      analyse_passe_1 (root -> opr[0]);
      analyse_passe_1 (root -> opr[1]);

      if(root -> opr[0] -> type == root -> opr[1] -> type)
      {
        // On attibue le type à la NODE_PLUS
        root -> type = root -> opr[0] -> type;
      }      
      break;

    case NODE_MUL:

      // Appels récursifs
      analyse_passe_1 (root -> opr[0]);
      analyse_passe_1 (root -> opr[1]);

      if(root -> opr[0] -> type == root -> opr[1] -> type)
      {
        // On attibue le type à la NODE_PLUS
        root -> type = root -> opr[0] -> type;
      }      
      break;

    case NODE_DIV:

      // Appels récursifs
      analyse_passe_1 (root -> opr[0]);
      analyse_passe_1 (root -> opr[1]);

      if(root -> opr[0] -> type == root -> opr[1] -> type)
      {
        // On attibue le type à la NODE_PLUS
        root -> type = root -> opr[0] -> type;
      }      
      break;

    case NODE_PRINT:

      // Appels récursifs
      analyse_passe_1 (root -> opr[0]);
      break;

    case NODE_STRINGVAL:

      // Opérations sur la NODE_STRINGVAL
      analyse_node_stringval (root);
      break;

    // Pour toutes les autres nodes non définies dans le switch
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

    case NODE_PROGRAM:

      push_global_context ();
      if (root -> nops > 1)
      {
         analyse_global  (root -> opr[0]);
         analyse_passe_1 (root -> opr[1]);
      }
      else
      {
         analyse_passe_1 (root -> opr[0]);
      }
      pop_context ();
      break;

    case NODE_IDENT:

      analyse_node_ident (root);
      break;

    case NODE_LIST:

      root -> opr[0] -> type = root -> type;
      root -> opr[1] -> type = root -> opr[0] -> type;
      
      if(root -> opr[0] -> nature == NODE_STRINGVAL)
      {
        root -> opr[0] -> type = TYPE_STRING;
      }
      else if(root -> opr[1] -> nature == NODE_STRINGVAL)
      {
        root -> opr[1] -> type = TYPE_STRING;
      }

      analyse_passe_1(root -> opr[0]);
      analyse_passe_1(root -> opr[1]);
      break;

    case NODE_DECLS:   
      
      root -> decl_node = root;
      analyse_passe_1 (root -> opr[0]);
      root -> decl_node -> type   = root -> opr[0] -> type;
      root -> opr[1] -> decl_node = root;
      root -> opr[0] -> decl_node = root;

      root -> opr[1] -> type = root -> opr[0] -> type;
      analyse_passe_1(root -> opr[1]);
      break;

    case NODE_DECL:

      if(root -> opr[1] == NULL)
      {
        root -> opr[0] -> type = root -> type;
      }

      if (root -> decl_node)
      {
        root->opr[0] -> type = root -> decl_node -> type;
        root->opr[1] -> type = root -> decl_node -> type;
      }

      analyse_passe_1(root -> opr[0]);
      analyse_passe_1(root -> opr[1]);

      if(root -> opr[1] != NULL && root -> opr[0] != NULL)
      {
        if(root -> opr[0] -> nature == root -> opr[1] -> nature)
        {
          if(root -> opr[0] -> type == TYPE_NONE)
          {
            root -> opr[0] -> type = root -> opr[1] -> type;
            // printf("je passe ici");
            // printf("nature : %s\n",node_nature2string(root -> opr[0] -> nature));
            // printf("type : %s\n",node_type2string(root -> opr[0] -> type));
            // printf("ident : %s\n\n",root -> opr[0] -> ident);

          }
        }
      }

     //  if (root->decl_node->type != root->opr[1]->type)
      // {
     //    printf("\nError line %d: wrong type assignment %s\n",root->lineno,root->ident);
      //   exit (-1);
      // }
     break;

    case NODE_FUNC:

      push_context ();
      analyse_passe_1(root -> opr[0]);
      analyse_passe_1(root -> opr[1]);
      analyse_passe_1(root -> opr[2]);
      analyse_node_func(root);
      pop_context ();
      break;

    case NODE_BLOCK:

      push_context ();
      analyse_passe_1 (root -> opr[0]);
      analyse_passe_1 (root -> opr[1]);
      pop_context ();
      break;

    case NODE_FOR:

      analyse_passe_1 (root->opr[0]);
      analyse_passe_1 (root->opr[1]);
      analyse_passe_1 (root -> opr[2]);
      analyse_passe_1 (root -> opr[3]);
      break;

    case NODE_LT:

      analyse_passe_1 (root -> opr[0]);
      analyse_passe_1 (root -> opr[1]);
      break;

    case NODE_AFFECT:

      analyse_passe_1 (root -> opr[0]);
      analyse_passe_1 (root -> opr[1]);
      break;

    case NODE_PLUS:

      analyse_passe_1 (root -> opr[0]);
      analyse_passe_1 (root -> opr[1]);
      // On vérifie que le l'addition se fait sur deux
      // entités du même type

      if(root -> opr[0] -> type == root -> opr[1] -> type)
      {
        // On attibue le type à la NODE_PLUS
        root -> type = root -> opr[0] -> type;
      }      
      break;


    case NODE_MINUS:

      analyse_passe_1 (root -> opr[0]);
      analyse_passe_1 (root -> opr[1]);
      if(root -> opr[0] -> type == root -> opr[1] -> type)
      {
        // On attibue le type à la NODE_PLUS
        root -> type = root -> opr[0] -> type;
      }      
      break;

    case NODE_MUL:

      analyse_passe_1 (root -> opr[0]);
      analyse_passe_1 (root -> opr[1]);
      if(root -> opr[0] -> type == root -> opr[1] -> type)
      {
        // On attibue le type à la NODE_PLUS
        root -> type = root -> opr[0] -> type;
      }      
      break;

    case NODE_DIV:
    
      analyse_passe_1 (root -> opr[0]);
      analyse_passe_1 (root -> opr[1]);
      if(root -> opr[0] -> type == root -> opr[1] -> type)
      {
        // On attibue le type à la NODE_PLUS
        root -> type = root -> opr[0] -> type;
      }      
      break;

    case NODE_PRINT:

      analyse_passe_1 (root -> opr[0]);
      break;

    case NODE_STRINGVAL:

      analyse_node_stringval (root);
      break;

    default:
      break;
    }
}
