/*
** name_option.c for zappy in /home/thomas/Rendu/Zappy/server
**
** Made by Thomas
** Login   <thomas@epitech.net>
**
** Started on  Thu Jun 22 05:41:03 2017 Thomas
** Last update Fri Jun 23 01:47:38 2017 Thomas
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "list.h"
#include "struct.h"
#include "option.h"

static int	check_name(char *f_team, int ac, char *av[], int index)
{
  int		save;
  int		cmp_it;

  save = index;
  cmp_it = index;
  while (index < ac && *av[index] != '-')
    {
      if (strcmp(f_team, av[index]) == 0)
	return (0);
      while (cmp_it < ac && *av[cmp_it] != '-')
	{
	  if (strcmp(av[cmp_it], av[index]) == 0)
	    return (0);
	  cmp_it++;
	}
      index++;
      cmp_it = save;
    }
  return (1);
}

void	init_opt(t_game *game)
{
  game->nb_client_max = 6;
  game->freq = 100;
  game->net_info.port = 1024;
  game->map_size_x = 10;
  game->map_size_y = 10;
}

static void	create_default_team(t_game *game, char *av[])
{
  t_team	*new;

  (void)av;
  if ((new = malloc(sizeof(t_team))) == NULL)
    return;
  memset(new, 0, sizeof(t_team));
  new->name = strdup("Trantorien");
  new->size = game->nb_client_max;
  new->empty_slot = game->nb_client_max;
  list_add_tail(&new->list, &game->teams);
}

int		c_opt(t_game *game, int ac, char *av[])
{
  t_list_head	*head;
  t_list_head	*pos;
  t_team	*tmp;

  game->nb_client_max = atoi(optarg);
  if (game->nb_client_max < 1)
    {
      printf("\n-c option only accepts integer value");
      printf(" greater or equal to 1\n\n");
      return (0);
    }
  if (list_empty(&game->teams) != 0)
    return (1);
  else if (list_empty(&game->teams) != 0 && optind >= ac)
    create_default_team(game, av);
  head = &game->teams;
  pos = list_get_first(head);
  while (pos != head)
    {
      tmp = list_entry(pos, t_team, list);
      tmp->size = game->nb_client_max;
      tmp->empty_slot = game->nb_client_max;
      pos = pos->next;
    }
  return (1);
}

int		n_opt(t_game *game, int ac, char *av[])
{
  t_team	*tmp;
  t_team	*new;

  if (check_name(optarg, ac, av, optind) == 0)
    {
      printf("\n-n option only accepts unique team names\n\n");
      return (0);
    }
  if ((tmp = malloc(sizeof(t_team))) == NULL)
    return (0);
  memset(tmp, 0, sizeof(t_team));
  tmp->name = strdup(optarg);
  list_init(&tmp->players);
  list_add_tail(&tmp->list, &game->teams);
  while (optind < ac && *av[optind] != '-')
    {
      if ((new = malloc(sizeof(t_team))) == NULL)
	return (0);
      memset(new, 0, sizeof(t_team));
      new->name = strdup(av[optind]);
      list_init(&new->players);
      list_add_tail(&new->list, &game->teams);
      optind++;
    }
  return (1);
}
