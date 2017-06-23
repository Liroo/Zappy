/*
** delete.c for delete in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sat Jun 17 00:26:45 2017 Pierre Monge
** Last update Fri Jun 23 02:55:54 2017 Pierre Monge
*/

#include <stdlib.h>

#include "event.h"
#include "h.h"
#include "list.h"
#include "debug.h"
#include "struct.h"
#include "chrono.h"

static void	delete_registered_player(t_player *player)
{
  if (!player->team)
    return ;
  player->team->empty_slot += 1;
  REMOVE_OBJECT(&(game.map[player->pos_y][player->pos_x]), PLAYER_OFFSET);
}

void		delete_player(t_player *player)
{
  int		i;
  t_list_head	*pos;
  t_list_head	*next;

  PRINT_DEBUG("Deleting player used by fd: %d...\n", player->net_info.fd);
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
      list_del(pos->prev, next);
      clear_packet(container_of(pos, t_packet, list));
      pos = next;
    }
  delete_registered_player(player);
  delete_chrono_player(player);
  free(player);
}

static void		delete_team(t_team *team)
{
  t_list_head	*pos;
  t_list_head	*next;

  PRINT_DEBUG("Deleting team: %s...\n", team->name);
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
  t_list_head	*head;

  head = &game.teams;
  pos = list_get_first(head);
  while (pos != head)
    {
      next = pos->next;
      delete_team(list_entry(pos, t_team, list));
      pos = next;
    }
}

void		delete_game()
{
  t_list_head	*pos;
  t_list_head	*next;
  int		i;

  PRINT_DEBUG("Deleting game...\n");
  pos = list_get_first(&game.connection_queue);
  while (pos != &game.connection_queue)
    {
      next = pos->next;
      delete_player(list_entry(pos, t_player, list));
      pos = next;
    }
  pos = list_get_first(&game.chrono_queue);
  while (pos != &game.chrono_queue)
    {
      next = pos->next;
      free(list_entry(pos, t_chrono_queue, list));
      pos = next;
    }
  i = 0;
  while (i < (int)game.map_size_y)
    free(game.map[i++]);
  free(game.map);
}
