/*
** free_gramz.c for tekcalc in sources/parser/tools/free
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Mon Jun 06 23:18:45 2016 Benoit Hamon
** Last update Sun Dec 04 15:57:13 2016 Benoit Hamon
*/

#include <stdbool.h>
#include <stdlib.h>
#include "parser/lexer.h"
#include "parser/parser.h"
#include "tools/tools.h"

void			*free_rules_list(t_rules_list *list)
{
  if (list)
  {
    free_rules_list(list->next);
    free((char *)list->name);
    the_free(1, FREE_TREE, list->expr);
    free(list);
  }
  return (NULL);
}
