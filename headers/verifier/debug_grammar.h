/*
** debug_grammar.h for PSU_2015_42sh in include/shell
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Thu Jun 02 12:01:50 2016 Benoit Hamon
** Last update Thu Dec 01 10:00:23 2016
*/

#ifndef DEBUG_GRAMMAR_H_
# define DEBUG_GRAMMAR_H_

# define DEBUG_ALL	0
# define DEBUG_LEXER	0
# define DEBUG_PARSER	0

typedef struct		s_debug
{
  int			token;
  char const		*str;
}			t_debug;

void			print_rules(t_token_list *list, char const *str);
void			print_parse(t_graph *graph, int index);

#endif /* end of include guard: DEBUG_GRAMMAR_H_ */
