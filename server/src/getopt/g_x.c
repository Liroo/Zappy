/*
** g_x.c for getopt p in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sat Jul  1 02:23:02 2017 Pierre Monge
** Last update Sat Jul  1 02:43:22 2017 Pierre Monge
*/

#include <stdlib.h>
#include <stdio.h>

#include "struct.h"

int	getopt_x(char **argv[])
{
  (*argv)++;
  game.map_size_x = atoi(**argv);
  (*argv)++;
  if (game.map_size_x < 10 || game.map_size_x > 30)
    {
      printf("\n-x option only accepts integer values");
      printf(" between 10 and 30\n\n");
      return (-1);
    }
  return (0);
}
