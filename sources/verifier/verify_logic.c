/*
** verify_logic.c for PSU_2015_42sh in sources/parser
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Mon May 30 01:50:34 2016 Benoit Hamon
** Last update Thu Dec 01 19:55:29 2016 Benoit Hamon
*/

#include <stdbool.h>
#include <stddef.h>
#include "tools/tools.h"
#include "parser/lexer.h"
#include "parser/parser.h"
#include "verifier/verify.h"

t_return			verify_or(t_tree *node,
					  char const *str,
					  int *i)
{
  t_return			value;

  if ((value = verify(node->left, str, i)).ok)
    return (value);
  return (verify(node->right, str, i));
}

t_return			verify_and(t_tree *node,
					   char const *str,
					   int *i)
{
  t_return			value1;
  t_return			value2;

  if ((value1 = verify(node->left, str, i)).ok
      && (value2 = verify(node->right, str, i)).ok)
  {
    the_pushback((void **)&value1.graph,
		 value2.graph,
		 offsetof(t_graph, next));
    return (value1);
  }
  value1.ok = false;
  value1.graph = NULL;
  return (value1);
}
