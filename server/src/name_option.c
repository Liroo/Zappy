/*
** name_option.c for zappy in /home/thomas/Rendu/Zappy/server
**
** Made by Thomas
** Login   <thomas@epitech.net>
**
** Started on  Thu Jun 22 05:41:03 2017 Thomas
** Last update Fri Jun 23 02:57:10 2017 guicha_t
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "list.h"
#include "struct.h"
#include "option.h"

void		n_opt(t_game *game, int ac, char *av[])
{
  t_team	*tmp;
  t_team	*new;

  if ((tmp = malloc(sizeof(t_team))) == NULL)
    return ;
  memset(tmp, 0, sizeof(t_team));
  tmp->name = strdup(optarg);
  list_init(&tmp->players);
  list_add_tail(&tmp->list, &game->teams);
  while (optind < ac && *av[optind] != '-')
    {
      if ((new = malloc(sizeof(t_team))) == NULL)
	return ;
      memset(new, 0, sizeof(t_team));
      new->name = strdup(av[optind]);
      list_init(&new->players);
      list_add_tail(&new->list, &game->teams);
      optind++;
    }
}
