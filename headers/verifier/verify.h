/*
** verify.h for PSU_2015_42sh in include
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Fri May 27 22:26:52 2016 Benoit Hamon
** Last update Thu Dec 01 19:49:53 2016 Benoit Hamon
*/

#ifndef VERIFY_H_
# define VERIFY_H_

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

t_return		verify_rule(t_tree *node,
				    char const *str,
				    int *i,
				    t_rule *rule);

typedef struct		s_verify_token
{
  t_token_type		token;
  t_return		(*f)();
}			t_verify_token;

typedef struct		s_verify_quantifier
{
  t_quantifier_type	quantity;
  t_return		(*f)();
}			t_verify_quantifier;

t_return		verify(t_tree *node,
			       char const *str,
			       int *i);

t_return		quantify_none();
t_return		quantify_one();
t_return		quantify_positive();
t_return		quantify_binary();
t_return		quantify_max();
t_return		quantify_min();

t_return		verify_or();
t_return		verify_and();

t_return		verify_char();
t_return		verify_quote();
t_return		verify_range();
t_return		verify_all();
t_return		verify_rule();

#endif /* end of include guard: VERIFY_H_ */
