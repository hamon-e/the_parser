/*
** quantifier.c for PSU_2015_42sh in sources/parser
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Mon May 30 01:50:16 2016 Benoit Hamon
** Last update Thu Dec 01 19:55:06 2016 Benoit Hamon
*/

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include "tools/tools.h"
#include "parser/lexer.h"
#include "parser/parser.h"
#include "verifier/verify.h"

t_return			quantify_none(t_tree *node,
					      char const *str,
					      int *i,
					      t_return (*f)())
{
  int				index;
  t_return			value;

  index = *i;
  value = f(node, str, &index, node->data);
  value.ok = !value.ok;
  return (value);
}

t_return			quantify_one(t_tree *node,
					     char const *str,
					     int *i,
					     t_return (*f)())
{
  int				index;
  t_return			value;

  index = *i;
  if ((value = f(node, str, &index, node->data)).ok)
    *i = index;
  return (value);
}

t_return			quantify_positive(t_tree *node,
						  char const *str,
						  int *i,
						  t_return (*f)())
{
  t_return			value;
  t_return			tmp;
  int				index;

  value.ok = false;
  value.graph = NULL;
  index = *i;
  while ((tmp = f(node, str, &index, node->data)).ok)
  {
    value.ok = true;
    the_pushback((void **)&value.graph, tmp.graph, offsetof(t_graph, next));
    *i = index;
  }
  return (value);
}

t_return			quantify_binary(t_tree *node,
						char const *str,
						int *i,
						t_return (*f)())
{
  t_return			value;
  t_return			tmp;
  int				index;

  value.ok = true;
  value.graph = NULL;
  index = *i;
  if ((tmp = f(node, str, &index, node->data)).ok)
  {
    value.graph = tmp.graph;
    *i = index;
  }
  return (value);
}

t_return			quantify_max(t_tree *node,
					     char const *str,
					     int *i,
					     t_return (*f)())
{
  t_return			value;
  t_return			tmp;
  int				index;

  value.ok = true;
  value.graph = NULL;
  index = *i;
  while ((tmp = f(node, str, &index, node->data)).ok)
  {
    the_pushback((void **)&value.graph, tmp.graph, offsetof(t_graph, next));
    *i = index;
  }
  return (value);
}
