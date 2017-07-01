/*
** g_p.c for getopt p in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sat Jul  1 02:21:26 2017 Pierre Monge
** Last update Sat Jul  1 02:22:43 2017 Pierre Monge
*/

#include <stdlib.h>

#include "struct.h"

int	getopt_p(char **argv[])
{
  (*argv)++;
  game.net_info.port = atoi(**argv);
  (*argv)++;
  return (0);
}
