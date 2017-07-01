/*
** map.c for map in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Tue Jun 20 22:09:29 2017 Pierre Monge
** Last update Sat Jul  1 02:45:16 2017 guicha_t
*/

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "h.h"
#include "struct.h"
#include "game.h"

void	insert_objects_in_map(int offset, int nb)
{
  int	x;
  int	y;

  x = 0;
  y = 0;
  srand(time(NULL));
  while (nb > 0)
    {
      y = rand() % game.map_size_y;
      x = rand() % game.map_size_x;
      INSERT_OBJECT(&(game.map[x][y]),
		    offset);
      nb--;
    }
}

static void		spawn_stone()
{
  t_list_head	*pos;
  int		team_nb;

  pos = list_get_first(&game.teams);
  team_nb = 0;
  while (pos != &game.teams)
    {
      team_nb += 1;
      pos = pos->next;
    }
  insert_objects_in_map(LINEMATE_OFFSET, MIN_LINEMATE_PER_TEAM * team_nb);
  insert_objects_in_map(DERAUMERE_OFFSET, MIN_DERAUMERE_PER_TEAM * team_nb);
  insert_objects_in_map(SIBUR_OFFSET, MIN_SIBUR_PER_TEAM * team_nb);
  insert_objects_in_map(MENDIANE_OFFSET, MIN_MENDIANE_PER_TEAM * team_nb);
  insert_objects_in_map(PHIRAS_OFFSET, MIN_PHIRAS_PER_TEAM * team_nb);
  insert_objects_in_map(THYSTAME_OFFSET, MIN_THYSTAME_PER_TEAM * team_nb);
}

#include "debug.h"

int	generate_map()
{
  int	i;

  i = 0;
  if (!(game.map = malloc(sizeof(t_inventory *) * game.map_size_x)))
    return (zappy_exit(), -1);
  while (i < (int)game.map_size_x)
    {
      if (!(game.map[i] = malloc(sizeof(t_inventory) * game.map_size_y)))
	return (zappy_exit(), -1);
      memset(game.map[i], 0, sizeof(t_inventory) * game.map_size_y);
      i++;
    }
  spawn_stone();
  return (0);
}
