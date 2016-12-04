/*
** free_tree.c for PSU_2015_42sh in sources/tools/free
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 21:34:05 2016 Nicolas Goudal
** Last update Sun Dec 04 14:42:55 2016 Benoit Hamon
*/

#include <stdlib.h>
#include <stdbool.h>
#include "parser/lexer.h"
#include "parser/parser.h"

void			*free_tree(t_tree *tree)
{
  t_rule		*rule;

  if (tree)
  {
    free_tree(tree->left);
    free_tree(tree->right);
    if (tree->token == TKN_RULE && tree->data)
    {
      rule = tree->data;
      free((char *)rule->name);
    }
    free(tree->data);
    free(tree);
  }
  return (NULL);
}
