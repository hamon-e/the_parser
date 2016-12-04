/*
** init_tools.c for PSU_2015_42sh in sources/init
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Mon May 30 01:50:10 2016 Benoit Hamon
** Last update Wed Nov 30 18:16:15 2016
*/

#include <string.h>
#include <stdbool.h>
#include "parser/rules.h"
#include "parser/lexer.h"
#include "parser/parser.h"

t_tree			*find_begin(t_rules_list *list)
{
  while (list)
  {
    if (!strcmp(RULE_BEGIN, list->name))
      return (list->expr);
    list = list->next;
  }
  return (NULL);
}
