/*
** init.c for PSU_2015_42sh in sources/init
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Sat May 28 19:05:59 2016 Benoit Hamon
** Last update Sun Dec 04 15:57:57 2016 Benoit Hamon
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdbool.h>
#include "tools/msg.h"
#include "tools/tools.h"
#include "parser/lexer.h"
#include "parser/parser.h"
#include "verifier/verify.h"
#include "verifier/debug_grammar.h"

static bool		apply_rules(t_rules_list *rules, t_tree *node)
{
  if (node->right)
    if (!apply_rules(rules, node->right))
      return (false);
  if (node->left)
    if (!apply_rules(rules, node->left))
      return (false);
  if (node->token == TKN_RULE)
  {
    while (rules)
    {
      if (!strcmp(rules->name, ((t_rule *)node->data)->name))
      {
	((t_rule *)node->data)->node = rules->expr;
	return (true);
      }
      rules = rules->next;
    }
    the_puterror(ERR_MSG_RULE, ((t_rule *)node->data)->name);
    return (false);
  }
  return (true);
}

static bool		find_rules(t_rules_list *rules)
{
  t_rules_list		*save;

  save = rules;
  while (rules)
  {
    if (!apply_rules(save, rules->expr))
      return (false);
    rules = rules->next;
  }
  return (true);
}

static t_tree		*init_tree(char const *str,
				   char const *name,
				   int debug)
{
  t_token_list		*list;
  t_token_list		*tmp;
  t_tree		*node;

  list = init_lex(str);
  if (!list)
    return (the_puterror(ERR_MSG_LEX, NULL));
  if (debug == 1)
    print_rules(list, name);
  tmp = list;
  node = parser(&tmp, 0);
  if (!node || tmp)
    return (the_puterror(ERR_MSG_PARSE, NULL));
  the_free(1, FREE_LST_TKN, list);
  return (node);
}

static char		*init_name(char *str)
{
  int			n;

  n = strlen(str);
  if (n < 2 || str[n - 1] != ':')
  {
    the_puterror(ERR_MSG_RULE_NAME, str);
    return (the_free(1, FREE_STR, str));
  }
  str[n - 1] = 0;
  return (str);
}

t_rules_list		*init(char const *file, int debug)
{
  t_rules_list		*list;
  t_rules_list		*elem;
  char			*str;
  int			fd;

  list = NULL;
  if ((fd = open(file, O_RDONLY)) == -1)
    return (the_puterror(ERR_MSG_OPEN, file));
  while ((str = get_next_line(fd)))
  {
    if (!*str || *str == '#')
      continue ;
    if (!(elem = malloc(sizeof(t_rules_list))))
      return (the_puterror(ERR_MSG_MALLOC, NULL));
    elem->next = NULL;
    if (!(elem->name = init_name(str))
	|| !(str = get_next_line(fd))
	|| !(elem->expr = init_tree(str, elem->name, debug)))
      return (NULL);
    the_free(1, FREE_STR, str);
    the_pushback((void **)&list, elem, offsetof(t_rules_list, next));
  }
  if (!find_rules(list))
    return (the_free(1, FREE_LST_RULES, list));
  return (list);
}
