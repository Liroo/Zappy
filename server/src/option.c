/*
** option.c for zappy in /home/thomas/Rendu/PSU_2016_zappy/server/src
**
** Made by Thomas
** Login   <thomas@epitech.net>
**
** Started on  Tue Jun 13 22:53:02 2017 Thomas
** Last update Mon Jun 19 17:37:54 2017 Thomas
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "option.h"

void		p_opt(t_game *game, int ac, char *av[])
{
  (void)ac;
  (void)av;
  game->net_info.port = atoi(optarg);
}

void		c_opt(t_game *game, int ac, char *av[])
{
  t_list_head	*head;
  t_list_head	*pos;
  t_team	*tmp;

  (void)ac;
  (void)av;
  game->nb_client_max = atoi(optarg);
  head = &game->teams;
  if (list_empty(head) != 0)
    return;
  pos = list_get_first(head);
  while (pos != head)
    {
      tmp = list_entry(pos, t_team, list);
      tmp->size = game->nb_client_max;
      pos = pos->next;
    }
}

void	f_opt(t_game *game, int ac, char *av[])
{
  (void)ac;
  (void)av;
  game->time = atoi(optarg);
}

void		n_opt(t_game *game, int ac, char *av[])
{
  t_team	*tmp;
  t_team	*new;

  if ((tmp = malloc(sizeof(t_team))) == NULL)
    return;
  memset(tmp, 0, sizeof(t_team));
  tmp->name = strdup(optarg);
  list_add_tail(&tmp->list, &game->teams);
  while (optind < ac && *av[optind] != '-')
    {
      if ((new = malloc(sizeof(t_team))) == NULL)
	return;
      memset(new, 0, sizeof(t_team));
      new->name = strdup(av[optind]);
      list_add_tail(&new->list, &game->teams);
      optind++;
    }
}

void	x_opt(t_game *game, int ac, char *av[])
{
  (void)ac;
  (void)av;
  game->map_size_x = atoi(optarg);
}

void	y_opt(t_game *game, int ac, char *av[])
{
  (void)ac;
  (void)av;
  game->map_size_y = atoi(optarg);
}
