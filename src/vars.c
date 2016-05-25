/*
** vars.c for vars in /home/oddou_f/rendu/B2-Systeme-Unix/PSU_2015_42sh/src/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Tue Apr 26 22:19:57 2016 Frederic ODDOU
** Last update Mon May 23 16:59:27 2016 Arthur Josso
*/

#include <stdlib.h>
#include <signal.h>
#include "builtin.h"
#include "sig_mess.h"
#include "parser.h"

t_sig_mess		g_sig_mess[] =
  {
    {SIGHUP, "Hangup"},
    {SIGINT, "Interrupt"},
    {SIGQUIT, "Quit"},
    {SIGILL, "Illegal instruction"},
    {SIGTRAP, "Trace trap"},
    {SIGABRT, "Abort"},
    {SIGIOT, "IOT trap"},
    {SIGBUS, "BUS error"},
    {SIGFPE, "Floating exception"},
    {SIGKILL, "Kill"},
    {SIGUSR1, "User-defined signal 1"},
    {SIGSEGV, "Segmentation fault"},
    {SIGUSR2, "User-defined signal 2"},
    {SIGPIPE, ""},
    {SIGALRM, "Alarm clock"},
    {SIGTERM, "Termination"},
    {SIGSTKFLT, "Stack fault"},
    {SIGCHLD, "Child status has changed"},
    {SIGCONT, "Continue"},
    {SIGSTOP, "Stop"},
    {SIGTSTP, "Keyboard stop"},
    {SIGTTIN, "Background read from tty"},
    {SIGTTOU, "Background write to tty"},
    {SIGURG, "Urgent condition on socket"},
    {SIGXCPU, "CPU limit exceeded"},
    {SIGXFSZ, "File size limit exceeded"},
    {SIGVTALRM, "Virtual alarm clock"},
    {SIGPROF, "Profiling alarm clock"},
    {SIGWINCH, "Window size change"},
    {SIGIO, "I/O now possible"},
    {SIGPWR, "Power failure restart"},
    {SIGSYS, "Bad system call"},
    {0, NULL}
  };

t_builtin		g_builtin[] =
  {
    {"cd", b_cd},
    {"exit", b_exit},
    {"which", b_which},
    {"env", b_env},
    {"export", b_export},
    {"setenv", b_setenv},
    {"unsetenv", b_unsetenv},
    {"echo", NULL},
    {"history", b_history},
    {"jobs", b_jobs},
    {"fg", b_fg},
    {"set", b_set},
    {"builtins", b_builtins},
    {"alias", b_alias},
    {"sort", b_sort},
    {NULL, NULL},
  };

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
