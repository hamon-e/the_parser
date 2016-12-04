/*
** parser.c for PSU_2015_42sh in sources/init
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Mon May 30 01:49:42 2016 Benoit Hamon
** Last update Sun Dec 04 15:30:57 2016 Benoit Hamon
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include "tools/msg.h"
#include "tools/tools.h"
#include "parser/lexer.h"
#include "parser/parser.h"

static t_tree			*parse_oth(t_token_list **token);

static const t_ope_func		g_dico_ope[] =
{
  {parser, TKN_OR},
  {parser, TKN_AND},
  {parse_oth, 0}
};

static const t_parse_func	g_parser_func_dico[] =
{
  {TKN_CHAR, parse_char},
  {TKN_QUOTE, parse_quote},
  {TKN_RANGE, parse_range},
  {TKN_RULE, parse_rule},
  {0, NULL}
};

static t_quantifier_type	parse_quantity(t_token_list **token)
{
  t_token_list			*tmp;
  t_quantifier_type		quantity;

  tmp = *token;
  quantity = QUANT_ONE;
  if (tmp && tmp->token > QUANT_ONE)
  {
    quantity = tmp->token;
    tmp = tmp->next;
    *token = tmp;
  }
  return (quantity);
}

static t_tree			*parse_simple(t_token_list **token)
{
  t_token_list			*tmp;
  t_tree			*node;
  int				j;

  tmp = *token;
  j = 0;
  while (g_parser_func_dico[j].token
	 && g_parser_func_dico[j].token != tmp->token)
    ++j;
  if ((!g_parser_func_dico[j].token && tmp->token != TKN_ALL)
      || !(node = create_node(tmp->token, NULL, NULL)))
    return (NULL);
  node->data = NULL;
  if (g_parser_func_dico[j].f
      && !(node->data = g_parser_func_dico[j].f(tmp)))
    return (NULL);
  *token = tmp->next;
  return (node);
}

static t_tree			*parse_pth(t_token_list **token)
{
  t_token_list			*tmp;
  t_tree			*node;

  tmp = *token;
  tmp = tmp->next;
  if (!(node = parser(&tmp, 0)))
    return (NULL);
  if (!tmp || tmp->token != TKN_CPTH)
    return (the_free(1, FREE_TREE, node));
  tmp = tmp->next;
  *token = tmp;
  return (node);
}

static t_tree			*parse_oth(t_token_list **token)
{
  t_token_list			*tmp;
  t_tree			*node;
  bool				save;

  tmp = *token;
  save = (tmp->token != TKN_NOSAVE);
  if (!save)
    tmp = tmp->next;
  if (tmp && tmp->token == TKN_OPTH)
  {
    if (!(node = parse_pth(&tmp)))
      return (NULL);
  }
  else
    if (!tmp || !(node = parse_simple(&tmp)))
      return (NULL);
  if (!save && (!tmp || tmp->token != TKN_NOSAVE))
    return (NULL);
  if (!save)
    tmp = tmp->next;
  node->quantity = parse_quantity(&tmp);
  *token = tmp;
  node->save = save;
  return (node);
}

t_tree				*parser(t_token_list **token,
					int index)
{
  t_token_list			*tmp;
  t_tree			*node;
  t_tree			*node1;

  tmp = *token;
  if (!tmp || !(node = g_dico_ope[index].f(&tmp, index + 1)))
    return (NULL);
  *token = tmp;
  if (g_dico_ope[index].f == parse_oth)
    return (node);
  while (tmp && tmp->token == (int)g_dico_ope[index].type)
  {
    if (!(node1 = create_node(g_dico_ope[index].type, node, NULL)))
      return (node);
    tmp = tmp->next;
    if (!tmp || !(node1->right = g_dico_ope[index].f(&tmp, index + 1)))
      return (node);
    *token = tmp;
    node = node1;
  }
  return (node);
}
