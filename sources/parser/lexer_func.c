/*
** lexer_func.c for $PROJ in .
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Sat May 28 10:40:22 2016 Benoit Hamon
** Last update Thu Dec 01 19:54:19 2016 Benoit Hamon
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include "tools/msg.h"
#include "tools/tools.h"
#include "parser/lexer.h"

static const t_lex_char		g_lexer_char_dico[] =
{
  {TKN_ALL, "."},
  {TKN_OPTH, "("},
  {TKN_CPTH, ")"},
  {TKN_OR, " | "},
  {TKN_AND, " "},
  {QUANT_POSITIVE, "+"},
  {QUANT_BINARY, "?"},
  {QUANT_MIN, "!"},
  {QUANT_MAX, "*"},
  {QUANT_NONE, "-"},
  {0, NULL}
};

static bool			lex_char(char const *str, int *i)
{
  int				index;

  index = *i;
  if (str[index++] != '\'')
    return (false);
  if (str[index] == '\\' && str[index + 1] != '\'')
    ++index;
  if (!str[index++])
    return (false);
  if (str[index++] != '\'')
    return (false);
  *i = index;
  return (true);
}

static bool			lex_quote(char const *str, int *i)
{
  int				index;

  index = *i;
  if (str[index] != '"')
    return (false);
  ++index;
  while (str[index])
  {
    if (str[index] == '"' && (!index || str[index - 1] != '\\'))
    {
      *i = index + 1;
      return (true);
    }
    ++index;
  }
  return (false);
}

static bool			lex_range(char const *str, int *i)
{
  int				index;

  index = *i;
  if (str[index++] != '{'
      || !str[index++]
      || str[index++] != '.'
      || str[index++] != '.'
      || !str[index++]
      || str[index++] != '}')
    return (false);
  *i = index;
  return (true);
}

static bool			lex_rule(char const *str, int *i)
{
  int				index;

  index = *i;
  while ((str[index] >= 'a' && str[index] <= 'z')
	 || (str[index] >= 'A' && str[index] <= 'Z')
	 || str[index] == '_')
    ++index;
  if (*i - index == 0)
    return (false);
  *i = index;
  return (true);
}

static bool			lex_nosave(char const *str, int *i)
{
  if (str[*i] != '[' && str[*i] != ']')
    return (false);
  ++*i;
  return (true);
}

static const t_lex_func		g_lexer_func_dico[] =
{
  {TKN_CHAR, lex_char},
  {TKN_QUOTE, lex_quote},
  {TKN_RANGE, lex_range},
  {TKN_RULE, lex_rule},
  {TKN_NOSAVE, lex_nosave},
  {0, NULL}
};

int				init_lex_dico(char const *str, int *i)
{
  int				j;

  j = 0;
  while (g_lexer_char_dico[j].str)
  {
    if (!strncmp(g_lexer_char_dico[j].str,
		 str + *i,
		 strlen(g_lexer_char_dico[j].str)))
    {
      *i += strlen(g_lexer_char_dico[j].str);
      return (g_lexer_char_dico[j].token);
    }
    ++j;
  }
  j = 0;
  while (g_lexer_func_dico[j].f)
  {
    if (g_lexer_func_dico[j].f(str, i))
      return (g_lexer_func_dico[j].token);
    ++j;
  }
  return (0);
}
