/*
** parser.h for the_parser in headers_public/the_parser
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Sun Dec 04 14:06:34 2016 Benoit Hamon
** Last update Sun Dec 04 15:27:58 2016 Benoit Hamon
*/

#ifndef HEADERS_PUBLIC_THE_PARSER_PARSER_H_
# define HEADERS_PUBLIC_THE_PARSER_PARSER_H_

typedef struct		s_graph
{
  char const		*rule;
  char const		*str;
  int			size;
  struct s_graph	*next;
  struct s_graph	*detail;
}			t_graph;

typedef struct		s_return
{
  bool			ok;
  t_graph		*graph;
}			t_return;

void			*init_parser(char const *gramz, int debug);
t_return		launch_parser(void *grammar,
				      char const *str,
				      int *index);
void			end_parser(void *grammar);

void			print_parse(t_graph *graph, int index);

#endif /* end of include guard: HEADERS_PUBLIC_THE_PARSER_PARSER_H_ */
