/*
** verify_oth.c for PSU_2015_42sh in sources/parser
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Mon May 30 01:50:39 2016 Benoit Hamon
** Last update Sun Dec 04 15:36:32 2016 Benoit Hamon
*/

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include "tools/tools.h"
#include "parser/lexer.h"
#include "parser/parser.h"
#include "verifier/verify.h"

t_return		verify_char(t_tree __attribute((__unused__))*node,
				    char const *str,
				    int *i,
				    char *c)
{
  t_return		value;

  value.ok = false;
  value.graph = NULL;
  if (str[*i] == *c)
  {
    ++*i;
    value.ok = true;
  }
  return (value);
}

t_return		verify_quote(t_tree __attribute((__unused__))*node,
				     char const *str,
				     int *i,
				     char *s)
{
  t_return		value;
  int			n;

  value.ok = false;
  value.graph = NULL;
  n = strlen(s);
  if (!strncmp(str + *i, s, n))
  {
    *i += n;
    value.ok = true;
  }
  return (value);
}

t_return		verify_range(t_tree __attribute((__unused__))*node,
				     char const *str,
				     int *i,
				     t_range *range)
{
  t_return		value;

  value.ok = false;
  value.graph = NULL;
  if (str[*i] >= range->begin
      && str[*i] <= range->end)
  {
    ++*i;
    value.ok = true;
  }
  return (value);
}

t_return		verify_all(t_tree __attribute((__unused__))*node,
				   char const *str,
				   int *i)
{
  t_return		value;

  value.ok = false;
  value.graph = NULL;
  if (str[*i])
  {
    ++*i;
    value.ok = true;
  }
  return (value);
}

t_return		verify_rule(t_tree __attribute((__unused__))*node,
				    char const *str,
				    int *i,
				    t_rule *rule)
{
  t_return		value;
  t_return		tmp;
  int			index;

  index = *i;
  value.ok = false;
  if ((tmp = verify(rule->node, str, &index)).ok)
  {
    if (!(value.graph = malloc(sizeof(t_graph))))
      return (value);
    value.ok = true;
    *value.graph = (t_graph)
    {rule->name, str + *i, index - *i, NULL, tmp.graph};
    *i = index;
    return (value);
  }
  return (value);
}
