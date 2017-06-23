/*
** auth.c for auth in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Mon Jun 19 22:15:36 2017 Pierre Monge
** Last update Sat Jun 24 00:05:38 2017 Pierre Monge
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
  player->auth_status = AUTH;
  player->client_type = PLAYER;
  player->team = team;
  player->inventory.food = 10;
  team->empty_slot -= 1;
  queue_packet(player, SIMPLE_PACKET, "%d\n", team->empty_slot);
  queue_packet(player, SIMPLE_PACKET, "%d %d\n", player->pos_x, player->pos_y);
  delete_chrono_player(player);
  queue_chrono(LIFETIME_WITHOUT_FOOD, player, C_EVENT_LIFETIME);
}

static void	register_admin(t_packet packet, t_player *player)
{
  if (player->auth_status == NO_AUTH)
    {
      PRINT_DEBUG("Player %d asking to become an admin\n", player->net_info.fd);
      player->auth_status = REQUIRE_PASSWORD_ADMIN;
      queue_packet(player, SIMPLE_PACKET, RPL_PASSWD);
    }
  else if (strcmp(packet.block, ADMIN_TEAM_PASSWD) == 0)
    {
      PRINT_DEBUG("Player %d joining admin team\n", player->net_info.fd);
      player->auth_status = AUTH;
      player->client_type = ADMIN;
      list_del(player->list.prev, player->list.next);
      list_add_tail(&player->list, &game.admins);
      delete_chrono_player(player);
      queue_packet(player, SIMPLE_PACKET, RPL_OK);
    }
  else
    queue_packet(player, DEAD_PACKET, RPL_WRONG_PASSWD);
}

static void	register_spectator(t_packet packet, t_player *player)
{
  if (player->auth_status == NO_AUTH)
    {
      PRINT_DEBUG("Player %d asking to become a spectator\n", player->net_info.fd);
      player->auth_status = REQUIRE_PASSWORD_SPECTATOR;
      queue_packet(player, SIMPLE_PACKET, RPL_PASSWD);
    }
  else if (strcmp(packet.block, SPECTATOR_TEAM_PASSWD) == 0)
    {
      PRINT_DEBUG("Player %d joining spectator team\n", player->net_info.fd);
      player->auth_status = AUTH;
      player->client_type = SPECTATOR;
      list_del(player->list.prev, player->list.next);
      list_add_tail(&player->list, &game.spectators);
      delete_chrono_player(player);
      queue_packet(player, SIMPLE_PACKET, RPL_OK);
    }
  else
    queue_packet(player, DEAD_PACKET, RPL_WRONG_PASSWD);
}

void		auth_player(t_packet packet, t_player *player)
{
  t_list_head	*pos;
  t_list_head	*head;
  t_team	*team;

  if (player->auth_status == REQUIRE_PASSWORD_ADMIN ||
      strcasecmp(packet.block, ADMIN_TEAM) == 0)
    return (void)register_admin(packet, player);
  else if (player->auth_status == REQUIRE_PASSWORD_SPECTATOR ||
	   strcasecmp(packet.block, SPECTATOR_TEAM) == 0)
    return (void)register_spectator(packet, player);
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
