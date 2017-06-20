/*
** delete.c for delete in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sat Jun 17 00:26:45 2017 Pierre Monge
** Last update Tue Jun 20 02:28:22 2017 Pierre Monge
*/

#include <stdlib.h>

#include "struct.h"
#include "event.h"
#include "h.h"
#include "list.h"
#include "debug.h"

static void	delete_registered_player(t_player *player)
{
  if (!player->team)
    return ;
  player->team->empty_slot += 1;
  // game.map[player->pos_y][player->pox_x].player -= 1;
}

void		delete_player(t_player *player)
{
  int		i;
  t_list_head	*pos;
  t_list_head	*next;

  PRINT_DEBUG("Deleting player used by fd: %d\n", player->net_info.fd);
  list_del(player->list.prev, player->list.next);
  fd_set_select(player->net_info.fd, FD_SELECT_NO_EVENT, NULL);
  fd_close(player->net_info.fd);
  free(player->r_packet.block);
  i = 0;
  while (player->command_queue[i].command && (i < COMMAND_QUEUE_SIZE))
    free(player->command_queue[i++].command);
  pos = list_get_first(&player->w_packet);
  while (pos != &player->w_packet)
    {
      next = pos->next;
      if (((t_packet *)container_of(pos, t_packet, list))->block)
	free(((t_packet *)container_of(pos, t_packet, list))->block);
      free((void *)(container_of(pos, t_packet, list)));
      list_del(pos->prev, next);
      pos = next;
    }
  delete_registered_player(player);
  free(player);
}

static void		delete_team(t_team *team)
{
  t_list_head	*pos;
  t_list_head	*next;

  if (team->name)
    free(team->name);
  pos = list_get_first(&team->players);
  while (pos != &team->players)
    {
      next = pos->next;
      delete_player(list_entry(pos, t_player, list));
      pos = next;
    }
  free(team);
}

void		delete_teams()
{
  t_list_head	*pos;
  t_list_head	*next;

  pos = list_get_first(&game.teams);
  while (pos != &game.teams)
    {
      next = pos->next;
      delete_team(list_entry(pos, t_team, list));
      pos = next;
    }
}
