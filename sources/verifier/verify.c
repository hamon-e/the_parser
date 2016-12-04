/*
** verify.c for PSU_2015_42sh in sources/parser
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Mon May 30 01:50:27 2016 Benoit Hamon
** Last update Thu Dec 01 19:55:24 2016 Benoit Hamon
*/

#include <stdbool.h>
#include <stdlib.h>
#include "tools/tools.h"
#include "parser/lexer.h"
#include "parser/parser.h"
#include "verifier/verify.h"

static const t_verify_token		g_verify_token[] =
{
  {TKN_OR, verify_or},
  {TKN_AND, verify_and},
  {TKN_CHAR, verify_char},
  {TKN_QUOTE, verify_quote},
  {TKN_RANGE, verify_range},
  {TKN_ALL, verify_all},
  {TKN_RULE, verify_rule}
};

static const t_verify_quantifier	g_verify_quantifier[] =
{
  {QUANT_ONE, quantify_one},
  {QUANT_POSITIVE, quantify_positive},
  {QUANT_BINARY, quantify_binary},
  {QUANT_MAX, quantify_max},
  {QUANT_MIN, quantify_min},
  {QUANT_NONE, quantify_none}
};

t_return				verify(t_tree *node,
					       char const *str,
					       int *i)
{
  int					j;
  int					k;
  t_return				res;

  j = 0;
  k = 0;
  while (g_verify_token[j].token != node->token)
    ++j;
  while (g_verify_quantifier[k].quantity != node->quantity)
    ++k;
  res = g_verify_quantifier[k].f(node, str, i, g_verify_token[j].f);
  if (!node->save)
    res.graph = the_free(1, FREE_GRAPH, res.graph);
  return (res);
}
