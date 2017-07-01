/*
** g_f.c for getopt f in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sat Jul  1 02:17:47 2017 Pierre Monge
** Last update Sat Jul  1 02:43:11 2017 Pierre Monge
*/

#include <stdlib.h>
#include <stdio.h>

#include "struct.h"

int	getopt_f(char **argv[])
{
  (*argv)++;
  game.freq = atoi(**argv);
  (*argv)++;
  if (game.freq < 2 || game.freq > 10000)
    {
      printf("\n-f option only accepts integer values");
      printf(" between 2 and 10000\n\n");
      return (-1);
    }
  return (0);
}
