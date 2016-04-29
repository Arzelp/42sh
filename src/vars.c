/*
** vars.c for vars in /home/oddou_f/rendu/B2-Systeme-Unix/PSU_2015_42sh/src/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Tue Apr 26 22:19:57 2016 Frederic ODDOU
** Last update Fri Apr 29 16:46:03 2016 oddou_f
*/

#include <stdlib.h>
#include "parser.h"

t_parser		g_parser_delimit[] =
  {
    {" ", "", D_NORMAL, ID_SPACE},
    {"\t", "", D_NORMAL, ID_TAB},
    {"\"", "\"", D_DELIM, ID_DOUBLE_QUOTE},
    {"'", "'", D_DELIM, ID_SIMPLE_QUOTE},
    {"`", "`", D_DELIM, ID_BACK_QUOTE},
    {"(", ")", D_DELIM, ID_PARENTHESE},
    {">&", "", D_GET, ID_REDIRECTION},
    {">>", "", D_GET, ID_DOUBLE_RIGHT},
    {">", "", D_GET, ID_RIGHT},
    {"<<", "", D_GET, ID_DOUBLE_LEFT},
    {"<", "", D_GET, ID_LEFT},
    {"||", "", D_SEPARATOR, ID_OR},
    {"&&", "", D_SEPARATOR, ID_AND},
    {";", "", D_SEPARATOR, ID_SEP},
    {"|", "", D_GET, ID_PIPE},
    {"&", "", D_GET, ID_BACKGROUND},
    {NULL, NULL, ID_WITHOUT, ID_WITHOUT},
  };
