/*
** parser_func.c for PSU_2015_42sh in sources/init
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Mon May 30 01:50:55 2016 Benoit Hamon
** Last update Sun Dec 04 15:32:30 2016 Benoit Hamon
*/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tools/msg.h"
#include "tools/tools.h"
#include "parser/lexer.h"
#include "parser/parser.h"

void			*parse_char(t_token_list *token)
{
  char			*c;
  int			i;

  if (!(c = malloc(sizeof(char))))
    return (the_puterror(ERR_MSG_MALLOC, NULL));
  if (token->str[1] == '\\' && token->str[2] != '\'')
  {
    i = 0;
    while (ESCAPE_SEQUENCE[i] && ESCAPE_SEQUENCE[i] != token->str[2])
      ++i;
    *c = ESCAPE_SEQUENCE[i] ? '\a' + i : token->str[2];
  }
  else
    *c = token->str[1];
  return (c);
}

void			*parse_quote(t_token_list *token)
{
  char			*str;

  if (!(str = strndup(token->str + 1, token->size - 2)))
    return (the_puterror(ERR_MSG_MALLOC, NULL));
  return (str);
}

void			*parse_range(t_token_list *token)
{
  t_range		*range;

  if (!(range = malloc(sizeof(t_range))))
    return (the_puterror(ERR_MSG_MALLOC, NULL));
  range->begin = token->str[1];
  range->end = token->str[4];
  return (range);
}

void			*parse_rule(t_token_list *token)
{
  t_rule		*rule;

  if (!(rule = malloc(sizeof(t_rule)))
      || !(rule->name = strndup(token->str, token->size)))
    return (the_puterror(ERR_MSG_MALLOC, NULL));
  rule->node = NULL;
  return (rule);
}
