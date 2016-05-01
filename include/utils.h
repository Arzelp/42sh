/*
** utils.h for utils in /include/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Thu Apr 28 12:42:47 2016 Frederic ODDOU
** Last update Sat Apr 30 11:02:54 2016 oddou_f
*/

#ifndef UTILS_H_
# define UTILS_H_

# include "shell.h"

/*
** Gestion des commandes (Ajout / Suppression / Vide / Purge / Back)
*/
t_commands		*utils_commands_add_right(t_commands	*commands,
						  char		*str,
						  short		index_delim);
void			utils_commands_delete_elem(t_shell	*shell,
						   t_commands	*commands);
void			utils_commands_delete_list(t_commands	*commands);
void			utils_commands_purge_elem(t_commands	*commands);
t_commands		*utils_commands_go_back(t_commands	*commands);

/*
** Gestion de la liste (Ajout / Suppression / Vide / Back)
*/
t_list			*utils_list_add_right(t_list		*list,
					      t_commands	*commands,
					      short		type_separator);
void			utils_list_delete_elem(t_shell		*shell,
					       t_list		*list);
void			utils_list_delete_list(t_list		*list);
t_list			*utils_list_go_back(t_list		*list);

/*
** Gestion des pipes (Ajout / Suppression / Vide / Back)
*/
t_pipe			*utils_pipe_add_right(t_pipe		*pipe,
					      t_commands	*commands);
void			utils_pipe_delete_elem(t_list		*list,
					       t_pipe		*pipe);
void			utils_pipe_delete_list(t_pipe		*pipe);
t_pipe			*utils_pipe_go_back(t_pipe		*pipe);

/*
** Convertie les commandes en tab
*/
bool			utils_commands_to_tab(t_pipe		*pipe);

#endif
