/*
** auth.c for auth in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Mon Jun 19 22:15:36 2017 Pierre Monge
** Last update Wed Jun 28 18:17:07 2017 Pierre Monge
*/

#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "debug.h"
#include "packet.h"
#include "struct.h"
#include "h.h"

static t_player	*make_player(t_team *team)
{
  t_player	*player;

  if (!(player = malloc(sizeof(t_player))))
    return (NULL);
  memset(player, 0, sizeof(t_player));
  player->elevation = 1;
  player->pos_x = rand() % game.map_size_x;
  player->pos_y = rand() % game.map_size_y;
  player->direction = rand() % 4;
  INSERT_OBJECT(&(game.map[player->pos_x][player->pos_y]), PLAYER_OFFSET);
  player->team = team;
  player->inventory.food = 10;
  team->empty_slot -= 1;
  return (player);

}

static void	register_client_in_team(t_client *client,
					t_team *team)
{
  if (team->empty_slot <= 0)
    {
      queue_packet(client, SIMPLE_PACKET, RPL_KO);
      return ;
    }
  if (!(client->data = make_player(team)))
    {
      delete_client(client);
      return (void)zappy_exit();;
    }
  PRINT_DEBUG("Client %d added to the team %s\n", client->net_info.fd,
	      team->name);
  srand(time(NULL));
  list_del(client->list.prev, client->list.next);
  list_add_tail(&client->list, &team->players);
  client->auth_status = AUTH;
  client->client_type = PLAYER;
  client->process_r_packet = queue_command_player;
  queue_packet(client, SIMPLE_PACKET, "%d\n", team->empty_slot);
  queue_packet(client, SIMPLE_PACKET, "%d %d\n",
	       ((t_player *)client->data)->pos_x,
	       ((t_player *)client->data)->pos_y);
  delete_chrono_client(client);
  queue_chrono(LIFETIME_WITHOUT_FOOD, client, C_EVENT_LIFETIME);
}

static void	register_admin(t_packet packet, t_client *client)
{
  if (client->auth_status == NO_AUTH)
    {
      PRINT_DEBUG("Client %d asking to become an admin\n", client->net_info.fd);
      client->auth_status = REQUIRE_PASSWORD_ADMIN;
      queue_packet(client, SIMPLE_PACKET, RPL_PASSWD);
    }
  else if (strcmp(packet.block, ADMIN_TEAM_PASSWD) == 0)
    {
      client->process_r_packet = queue_command_admin;
      if (!(client->data = malloc(sizeof(t_admin))))
	{
	  delete_client(client);
	  return (void)zappy_exit();
	}
      memset(client->data, 0, sizeof(t_admin));
      PRINT_DEBUG("Client %d joining admin team\n", client->net_info.fd);
      client->auth_status = AUTH;
      client->client_type = ADMIN;
      list_del(client->list.prev, client->list.next);
      list_add_tail(&client->list, &game.admins);
      delete_chrono_client(client);
      queue_packet(client, SIMPLE_PACKET, RPL_OK);
    }
  else
    queue_packet(client, DEAD_PACKET, RPL_WRONG_PASSWD);
}

static void	register_spectator(t_packet packet, t_client *client)
{
  if (client->auth_status == NO_AUTH)
    {
      PRINT_DEBUG("Client %d asking to become a spectator\n", client->net_info.fd);
      client->auth_status = REQUIRE_PASSWORD_SPECTATOR;
      queue_packet(client, SIMPLE_PACKET, RPL_PASSWD);
    }
  else if (strcmp(packet.block, SPECTATOR_TEAM_PASSWD) == 0)
    {
      client->process_r_packet = queue_command_spectator;
      PRINT_DEBUG("Client %d joining spectator team\n", client->net_info.fd);
      client->auth_status = AUTH;
      client->client_type = SPECTATOR;
      list_del(client->list.prev, client->list.next);
      list_add_tail(&client->list, &game.spectators);
      delete_chrono_client(client);
      queue_packet(client, SIMPLE_PACKET, RPL_OK);
    }
  else
    queue_packet(client, DEAD_PACKET, RPL_WRONG_PASSWD);
}

void		auth_client(t_packet packet, t_client *client)
{
  t_list_head	*pos;
  t_list_head	*head;
  t_team	*team;

  if (client->auth_status == REQUIRE_PASSWORD_ADMIN ||
      strcasecmp(packet.block, ADMIN_TEAM) == 0)
    return (void)register_admin(packet, client);
  else if (client->auth_status == REQUIRE_PASSWORD_SPECTATOR ||
	   strcasecmp(packet.block, SPECTATOR_TEAM) == 0)
    return (void)register_spectator(packet, client);
  head = &game.teams;
  pos = list_get_first(head);
  while (pos != head)
    {
      team = list_entry(pos, t_team, list);
      if (strcmp(packet.block, team->name) == 0)
	{
	  register_client_in_team(client, team);
	  return ;
	}
      pos = pos->next;
    }
  queue_packet(client, SIMPLE_PACKET, RPL_KO);
}
