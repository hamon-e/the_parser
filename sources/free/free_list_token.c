/*
** free_list_token.c for PSU_2015_42sh in sources/tools/free
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 21:33:52 2016 Nicolas Goudal
** Last update Sun Dec 04 15:52:23 2016 Benoit Hamon
*/

#include <stdlib.h>
#include <stdbool.h>
#include "parser/lexer.h"
#include "parser/parser.h"

void		*free_token_list(t_token_list *list)
{
  if (list)
  {
    free_token_list(list->next);
    free(list);
  }
  return (NULL);
}
