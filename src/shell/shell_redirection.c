/*
** shell_redirection.c for redi in /src/shell/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Mon May  9 09:37:29 2016 Frederic ODDOU
** Last update Mon May 09 10:17:38 2016 oddou_f
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "shell.h"
#include "my.h"

static void		shell_redirection_prompt()
{
  if (isatty(STDIN_FILENO))
    {
      printf("> ");
      fflush(stdout);
    }
}

static char		*shell_redirection_realloc(char		*concat,
						   char		*str)
{
  int			len;
  int			len_concat;

  len_concat = strlen(concat);
  len = len_concat + strlen(str) + 2;
  if ((concat = realloc(concat, sizeof(char) * len)) == NULL)
    return (NULL);
  concat = strcat(concat, str);
  concat = strcat(concat, "\n");
  return (concat);
}

static char		*shell_redirection_gnl(char		*red_in)
{
  char			*str;
  char			*concat;

  str = NULL;
  if ((concat = malloc(1)) == NULL)
    return (NULL);
  concat[0] = '\0';
  shell_redirection_prompt();
  while ((str = get_next_line(STDIN_FILENO)) != NULL
	 && strncmp(red_in, str, strlen(red_in)))
    {
      if ((concat = shell_redirection_realloc(concat, str)) == NULL)
	return (NULL);
      free(str);
      str = NULL;
      shell_redirection_prompt();
    }
  if (str != NULL)
    free(str);
  return (concat);
}

static int		shell_redirection_two_left(t_shell	*shell,
						   t_pipe	*mypipe)
{
  int			p[2];
  char			*concat;

  if ((concat = shell_redirection_gnl(mypipe->redi[RED_TWO_LEFT])) == NULL)
    return (-1);
  if (pipe(p) == -1)
    {
      fprintf(stderr, ERROR_FUNCTION, "pipe");
      shell_close(shell, EXIT_FAILURE);
    }
  write(p[1], concat, strlen(concat));
  close(p[1]);
  if (dup2(p[0], 0) == -1)
    {
      fprintf(stderr, ERROR_FUNCTION, "dup2");
      shell_close(shell, EXIT_FAILURE);
    }
  if (concat != NULL)
    free(concat);
  return (p[0]);
}

void			shell_redirection(t_shell 		*shell,
					  t_pipe 		*pipe,
					  int			*fd)
{
  int			flags;

  if (pipe->redi[RED_RIGHT])
    {
      flags = O_RDONLY | O_CREAT | O_RDWR | O_TRUNC;
      fd[FD_OUT] = open(pipe->redi[RED_RIGHT], flags, 0644);
    }
  if (pipe->redi[RED_TWO_RIGHT])
    {
      flags = O_RDONLY | O_CREAT | O_RDWR | O_APPEND;
      fd[FD_OUT] = open(pipe->redi[RED_TWO_RIGHT], flags, 0644);
    }
  if (pipe->redi[RED_LEFT])
    {
      flags = O_RDONLY;
      fd[FD_IN] = open(pipe->redi[RED_LEFT], flags);
    }
  if (pipe->redi[RED_TWO_LEFT])
    fd[FD_IN] = shell_redirection_two_left(shell, pipe);
}