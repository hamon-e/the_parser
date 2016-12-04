/*
** parser.h for PSU_2015_42sh in sources/generic/init
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Fri May 27 21:21:40 2016 Benoit Hamon
** Last update Sun Dec 04 15:31:40 2016 Benoit Hamon
*/

#ifndef PARSER_H_
# define PARSER_H_

# define ESCAPE_SEQUENCE	"abtnvfr"

typedef struct		s_tree
{
  t_token_type		token;
  bool			save;
  t_quantifier_type	quantity;
  void			*data;
  struct s_tree		*left;
  struct s_tree		*right;
}			t_tree;

typedef struct		s_rules_list
{
  char const		*name;
  t_tree		*expr;
  struct s_rules_list	*next;
}			t_rules_list;

typedef struct		s_rule
{
  char const		*name;
  t_tree		*node;
}			t_rule;

typedef struct		s_grammar
{
  t_rule		begin;
  t_rules_list		*list;
}			t_grammar;

typedef struct		s_range
{
  char			begin;
  char			end;
}			t_range;

typedef struct		s_parse_func
{
  int			token;
  void			*(*f)();
}			t_parse_func;

typedef struct		s_ope_func
{
  t_tree		*(*f)();
  t_token_type		type;
}			t_ope_func;

t_tree			*parser(t_token_list **token,
				int index);
t_tree			*find_begin(t_rules_list *list);
t_rules_list		*init(char const *file, int debug);

void			*parse_char();
void			*parse_quote();
void			*parse_range();
void			*parse_rule();

t_tree			*create_node(t_token_type token,
				     t_tree *left,
				     t_tree *right);

#endif /* end of include guard: PARSER_H_ */
