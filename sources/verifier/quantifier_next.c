/*
** quantifier_next.c for PSU_2015_42sh in sources/parser
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Tue May 31 23:20:59 2016 Benoit Hamon
** Last update Thu Dec 01 19:55:15 2016 Benoit Hamon
*/

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include "tools/tools.h"
#include "parser/lexer.h"
#include "parser/parser.h"
#include "verifier/verify.h"

t_return			quantify_min(t_tree *node,
					     char const *str,
					     int *i,
					     t_return (*f)())
{
  int				index;
  t_return			value;

  index = *i;
  value = f(node, str, &index, node->data);
  if (index == *i)
    value.ok = false;
  *i = index;
  return (value);
}
