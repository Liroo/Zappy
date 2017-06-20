/*
** auth.c for auth in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Mon Jun 19 22:15:36 2017 Pierre Monge
** Last update Tue Jun 20 02:18:52 2017 Pierre Monge
*/

#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "debug.h"
#include "packet.h"
#include "struct.h"
#include "h.h"

static void	register_player_in_team(t_player *player,
					t_team *team)
{
  if (team->empty_slot <= 0)
    {
      queue_packet(player, "ko\n");
      return ;
    }
  PRINT_DEBUG("Player %d added to the team %s\n", player->net_info.fd,
	      team->name);
  srand(time(NULL));
  list_del(player->list.prev, player->list.next);
  list_add_tail(&player->list, &team->list);
  player->elevation = 1;
  player->pos_x = rand() % game.map_size_x;
  player->pos_y = rand() % game.map_size_y;
  // game.map[player->pos_y][player->pox_x].player += 1;
  player->is_logged = 1;
  player->team = team;
  team->empty_slot -= 1;
  queue_packet(player, "%d\n%d %d\n", team->empty_slot,
	       player->pos_x, player->pos_y);
}

void		auth_player(t_packet packet, t_player *player)
{
  t_list_head	*pos;
  t_list_head	*head;
  t_team	*team;

  head = &game.teams;
  pos = list_get_first(head);
  while (pos != head)
    {
      team = list_entry(pos, t_team, list);
      if (strcmp(packet.block, team->name) == 0)
	{
	  register_player_in_team(player, team);
	  return ;
	}
      pos = pos->next;
    }
  queue_packet(player, "ko\n");
}
