/*
** sig.c for sig in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Thu Jun 15 05:11:54 2017 Pierre Monge
** Last update Thu Jun 15 06:14:06 2017 Pierre Monge
*/

#include <signal.h>
#include <stdio.h>

#include "struct.h"
#include "debug.h"

void	sig_handler(int sig __attribute__((__unused__)))
{
  PRINT_DEBUG("sig handled: %d\n", sig);
  game.sig_handled = 1;
}

int			sig_set(char to_handle)
{
  sigset_t		blockset;
  struct sigaction	sa;

  sigemptyset(&blockset);
  sigaddset(&blockset, SIGINT);
  sigprocmask(SIG_BLOCK, &blockset, NULL);
  sa.sa_handler = to_handle ? sig_handler : SIG_DFL;
  sa.sa_flags = 0;
  sigemptyset(&sa.sa_mask);
  if (sigaction(SIGINT, &sa, NULL) == -1)
    return (perror("sigaction"), -1);
  return (0);
}
