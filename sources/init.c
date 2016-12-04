/*
** init.c for the_parser in sources
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Thu Dec 01 19:35:43 2016 Benoit Hamon
** Last update Sun Dec 04 15:26:38 2016 Benoit Hamon
*/

#include <stdlib.h>
#include <stdbool.h>
#include "tools/tools.h"
#include "parser/lexer.h"
#include "parser/parser.h"
#include "parser/rules.h"
#include "verifier/verify.h"

void			*init_parser(char const *gramz, int debug)
{
  t_grammar		*grammar;

  if (!(grammar = malloc(sizeof(t_grammar)))
      || !(grammar->list = init(gramz, debug))
      || !(grammar->begin.node = find_begin(grammar->list)))
      return (NULL);
  grammar->begin.name = RULE_BEGIN;
  return (grammar);
}

t_return		launch_parser(t_grammar *grammar,
				      char const *str,
				      int *index)
{
  t_return		parse;

  *index = 0;
  parse = verify_rule(NULL, str, index, &grammar->begin);
  return (parse);
}

void			end_parser(t_grammar *grammar)
{
  the_free(1, FREE_LST_RULES, grammar->list);
  free(grammar);
}
