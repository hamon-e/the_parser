/*
** debug_grammar.c for PSU_2015_42sh in sources/init
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Mon May 30 01:50:00 2016 Benoit Hamon
** Last update Thu Dec 01 10:02:25 2016
*/

#include <stdio.h>
#include <stdbool.h>
#include "parser/lexer.h"
#include "parser/parser.h"
#include "verifier/verify.h"
#include "verifier/debug_grammar.h"

static const t_debug	g_debug[] =
{
  {TKN_CHAR, "char"},
  {TKN_QUOTE, "quote"},
  {TKN_RANGE, "range"},
  {TKN_ALL, "all"},
  {TKN_RULE, "rule"},
  {TKN_OPTH, "("},
  {TKN_CPTH, ")"},
  {TKN_OR, "or"},
  {TKN_AND, "and"},
  {TKN_NOSAVE, "#"},
  {QUANT_ONE, ""},
  {QUANT_POSITIVE, "+"},
  {QUANT_BINARY, "?"},
  {QUANT_MIN, "-"},
  {QUANT_MAX, "*"},
  {QUANT_NONE, "!"},
  {0, NULL}
};

void			print_rules(t_token_list *list, char const *str)
{
  int			j;

  printf("NAME : %s\n", str);
  while (list)
  {
    j = 0;
    while (g_debug[j].str && list->token != g_debug[j].token)
      ++j;
    printf("%s ", g_debug[j].str);
    list = list->next;
  }
  printf("\n\n");
}

void			print_parse(t_graph *graph, int index)
{
  int			i;

  while (graph)
  {
    i = 0;
    while (i < index)
    {
      printf(" ");
      ++i;
    }
    printf("%s : %.*s#\n", graph->rule, graph->size, graph->str);
    print_parse(graph->detail, index + 2);
    graph = graph->next;
  }
}
