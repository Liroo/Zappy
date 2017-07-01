/*
** g_n.c for getopt n in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sat Jul  1 02:26:10 2017 Pierre Monge
** Last update Sat Jul  1 02:44:40 2017 Pierre Monge
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "struct.h"
#include "h.h"

static void	make_team(char *name)
{
  t_team	*team;

  if (!(team = malloc(sizeof(t_team))))
    return ((void)zappy_exit());
  memset(team, 0, sizeof(t_team));
  if (!(team->name = strdup(name)))
    return (free(team), (void)zappy_exit());
  list_init(&team->players);
  list_add_tail(&team->list, &game.teams);
}

int	getopt_n(char **argv[])
{
  (*argv)++;
  while (**argv && (**argv)[0] != '-')
    {
      if (strcmp(**argv, "admin") == 0
	  || strcmp(**argv, "spectator") == 0)
	printf("\n-n%s reserved team name, ignored\n\n", **argv);
      else
	make_team(**argv);
      (*argv)++;
    }
  return (0);
}
