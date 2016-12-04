/*
** lexer.h for sources in /home/hamon_e/Documents/Tech/Unix/test/parser/sources
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Thu Apr 07 11:09:10 2016 Benoit Hamon
** Last update Thu Dec 01 19:53:26 2016 Benoit Hamon
*/

#ifndef LEXER_H
# define LEXER_H

typedef enum		e_token_type
{
  TKN_CHAR = 1,
  TKN_QUOTE,
  TKN_RANGE,
  TKN_ALL,
  TKN_RULE
}			t_token_type;

typedef enum		e_bnf_type
{
  TKN_OPTH = 6,
  TKN_CPTH,
  TKN_OR,
  TKN_AND,
  TKN_NOSAVE
}			t_bnf_type;

typedef enum		e_quantifier_type
{
  QUANT_ONE = 11,
  QUANT_POSITIVE,
  QUANT_BINARY,
  QUANT_MIN,
  QUANT_MAX,
  QUANT_NONE
}			t_quantifier_type;

typedef struct		s_token_list
{
  int			token;
  char const		*str;
  int			size;
  struct s_token_list	*next;
}			t_token_list;

typedef struct		s_lex_char
{
  int			token;
  char			*str;
}			t_lex_char;

typedef struct		s_lex_func
{
  int			token;
  bool			(*f)();
}			t_lex_func;

t_token_list		*init_lex(char const *str);
int			init_lex_dico(char const *str, int *i);

#endif /* !LEXER_H */
