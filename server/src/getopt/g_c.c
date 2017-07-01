/*
** g_c.c for getopt c in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sat Jul  1 02:14:41 2017 Pierre Monge
** Last update Sat Jul  1 02:43:08 2017 Pierre Monge
*/

#include <stdlib.h>
#include <stdio.h>

#include "struct.h"

int	getopt_c(char **argv[])
{
  (*argv)++;
  game.nb_client_max = atoi(**argv);
  (*argv)++;
  if (game.nb_client_max < 1)
    {
      printf("\n-c option only accepts integer value");
      printf(" greater or equal to 1\n\n");
      return (-1);
    }
  return (0);
}
