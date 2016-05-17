/*
** parser.h for parser in /include/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Thu Apr 28 14:44:52 2016 Frederic ODDOU
** Last update Sun May 15 00:21:34 2016 oddou_f
*/

#pragma once

#include <stdbool.h>
#include "shell.h"
#include "enum.h"

#define ERR_NULL	"Invalid null command."
#define ERR_UNMATCH	"Unmatched %s.\n"
#define ERR_AMBIOUT	"Ambiguous output redirect."
#define ERR_AMBIIN	"Ambiguous input redirect."
#define ERR_MISSNAME	"Missing name for redirect."
#define ERR_PARENTHESE	"Badly placed ()'s.\n"
#define GET_TYPE(n)	(g_parser_delimit[n].type)
#define GET_ID(n)	(g_parser_delimit[n].id)
#define IF_SEP(n)	((GET_TYPE(n) == D_SEPARATOR) ? true : false)
#define IF_PIPE(n)	((GET_ID(n) == ID_PIPE) ? true : false)

typedef struct		s_parser
{
  char			*delimit;
  char			*end;
  short			type;
  short			id;
}			t_parser;

bool			parser_commands(t_shell			*shell,
					char			*str);
bool			parser_control(t_shell			*shell,
				       char			*str);
bool			parser_check_separator(t_shell		*shell);
void			parser_list(t_shell			*shell);
bool			parser_pipe(t_shell			*shell);
bool			parser_redi(t_list			*list);
void			parser_commands_backslash(t_commands	*commands);

extern t_parser		g_parser_delimit[];
