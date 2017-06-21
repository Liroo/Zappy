/*
** auth.c for auth in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Mon Jun 19 22:15:36 2017 Pierre Monge
** Last update Wed Jun 21 06:02:02 2017 Pierre Monge
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
      queue_packet(player, SIMPLE_PACKET, RPL_KO);
      return ;
    }
  PRINT_DEBUG("Player %d added to the team %s\n", player->net_info.fd,
	      team->name);
  srand(time(NULL));
  list_del(player->list.prev, player->list.next);
  list_add_tail(&player->list, &team->players);
  player->elevation = 1;
  player->pos_x = rand() % game.map_size_x;
  player->pos_y = rand() % game.map_size_y;
  INSERT_OBJECT(&(game.map[player->pos_y][player->pos_x]), PLAYER_OFFSET);
  player->is_logged = 1;
  player->team = team;
  team->empty_slot -= 1;
  queue_packet(player, SIMPLE_PACKET, "%d\n", team->empty_slot);
  queue_packet(player, SIMPLE_PACKET, "%d %d\n", player->pos_x, player->pos_y);
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
  queue_packet(player, SIMPLE_PACKET, RPL_KO);
}
