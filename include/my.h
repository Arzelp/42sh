/*
** my.h for my h in /include/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sat Apr 16 11:25:05 2016 Frederic ODDOU
** Last update Thu May 19 12:50:23 2016 oddou_f
*/

#pragma once

#include <stdbool.h>
#include <stdarg.h>

#define READ_SIZE (4096)

char		*get_next_line(const int fd, char **next, int *size);
int		my_tab_len(char			**tab);
char		**my_tab_cpy(char		**tab);
bool		my_tab_free(char		**tab);
char		**my_tab_realloc(char		**tab,
				 char		*str);
char		**my_tab_delete_elem(char	**tab,
				     char	*str);
unsigned int	my_count_char(char		*str,
			      char		c);
char		**my_str_to_wordtab(char	*str,
				    char	c);
int		my_atoi(char			*str);
bool		my_tabn_cmp(char		**tab1,
			    char		**tab2,
			    int			n);
void		my_tab_cat(char			**tab1,
			   char			**tab2);
void		my_tab_cat_dyn(char		**tab1,
			       char		**tab2);
