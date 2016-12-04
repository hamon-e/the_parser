/*
** lexer.c for PSU_2015_42sh in sources/init
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Mon May 30 01:49:53 2016 Benoit Hamon
** Last update Sun Dec 04 15:01:21 2016 Benoit Hamon
*/

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include "tools/msg.h"
#include "tools/tools.h"
#include "parser/lexer.h"
#include "parser/parser.h"
#include "verifier/verify.h"
#include "verifier/debug_grammar.h"

t_token_list		*init_lex(char const *str)
{
  t_token_list		*list;
  t_token_list		*elem;
  int			token;
  int			i;
  int			save;

  list = NULL;
  i = 0;
  save = 0;
  while ((token = init_lex_dico(str, &i)))
  {
    if (!(elem = malloc(sizeof(t_token_list))))
      return (the_puterror(ERR_MSG_MALLOC, NULL));
    elem->token = token;
    elem->str = str + save;
    elem->size = i - save;
    elem->next = NULL;
    the_pushback((void **)&list, elem, offsetof(t_token_list, next));
    save = i;
  }
  return (str[i] ? the_free(1, FREE_LST_TKN, list) : list);
}
