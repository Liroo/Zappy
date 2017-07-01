/*
** g_y.c for getopt y in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sat Jul  1 02:23:42 2017 Pierre Monge
** Last update Sat Jul  1 02:43:24 2017 Pierre Monge
*/

#include <stdlib.h>
#include <stdio.h>

#include "struct.h"

int	getopt_y(char **argv[])
{
  (*argv)++;
  game.map_size_y = atoi(**argv);
  (*argv)++;
  if (game.map_size_y < 10 || game.map_size_y > 30)
    {
      printf("\n-y option only accepts integer values");
      printf(" between 10 and 30\n\n");
      return (-1);
    }
  return (0);
}
