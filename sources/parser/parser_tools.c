/*
** parser_tools.c for PSU_2015_42sh in sources/init
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Mon May 30 01:49:34 2016 Benoit Hamon
** Last update Thu Dec 01 19:54:46 2016 Benoit Hamon
*/

#include <stdlib.h>
#include <stdbool.h>
#include "tools/msg.h"
#include "tools/tools.h"
#include "parser/lexer.h"
#include "parser/parser.h"

t_tree			*create_node(t_token_type token,
				     t_tree *left,
				     t_tree *right)
{
  t_tree		*node;

  if (!(node = malloc(sizeof(t_tree))))
    return (the_puterror(ERR_MSG_MALLOC, NULL));
  *node = (t_tree){token, true, QUANT_ONE, NULL, left, right};
  return (node);
}
