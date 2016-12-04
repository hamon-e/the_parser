/*
** free_graph.c for PSU_2015_42sh in sources/tools/free
**
** Made by Nicolas Goudal
** Login   <goudal_n@epitech.net>
**
** Started on  Sun Jun 05 21:33:48 2016 Nicolas Goudal
** Last update Sun Dec 04 14:37:45 2016 Benoit Hamon
*/

#include <stdbool.h>
#include <stdlib.h>
#include "parser/lexer.h"
#include "parser/parser.h"
#include "verifier/verify.h"

void			*free_graph(t_graph *graph)
{
  if (graph)
  {
    free_graph(graph->detail);
    free_graph(graph->next);
    free(graph);
  }
  return (NULL);
}
