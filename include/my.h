/*
** my.h for my h in /include/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sat Apr 16 11:25:05 2016 Frederic ODDOU
** Last update Sat Apr 30 21:18:56 2016 oddou_f
*/

#ifndef MY_H_
# define MY_H_

# include <stdbool.h>
# include <stdarg.h>

# define READ_SIZE (4096)

char		*get_next_line(const int	fd);
int		my_tab_len(char			**tab);
char		**my_tab_cpy(char		**tab);
bool		my_tab_free(char		**tab);
bool		my_tab_realloc(char		**tab,
			       char		*str);
bool		my_tab_delete_elem(char		**tab,
				   char		*str);
unsigned int	my_count_char(char		*str,
			      char		c);
char		**my_str_to_wordtab(char	*str,
				    char	c);

#endif
