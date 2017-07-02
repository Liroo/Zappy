/*
** command_elevation.c<command> for cmd elevation in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sat Jul  1 15:53:48 2017 Pierre Monge
** Last update Sun Jul  2 06:40:40 2017 Pierre Monge
*/

#include "struct.h"
#include "log.h"
#include "rfc.h"
#include "packet.h"
#include "h.h"

static int		check_player_on_tile(int elevation, int x, int y)
{
  static int		elevation_stats[7] = { 1, 2, 2, 4, 4, 6,6 };
  t_list_head		*team;
  t_list_head		*client;
  t_team		*team_ptr;
  int			nb_players;
  t_player		*p;

  nb_players = 0;
  team = list_get_first(&game.teams);
  while (team != &game.teams)
    {
      team_ptr = list_entry(team, t_team, list);
      client = list_get_first(&team_ptr->players);
      while (client != &team_ptr->players)
	{
	  p = ((t_client *)list_entry(client, t_client, list))->data;
	  if (p->pos_x == x && p->pos_y == y && p->elevation == elevation)
	    nb_players += 1;
	  client = client->next;
	}
      team = team->next;
    }
  return ((int)game.map[x][y].player == nb_players &&
	  nb_players == elevation_stats[elevation - 1]);
}

static int	check_object_on_tile(int elevation, int x, int y)
{
  static int	elevation_stats[7][6] = {
    { 1, 0, 0, 0, 0, 0 },
    { 1, 1, 1, 0, 0, 0 },
    { 2, 0, 1, 0, 2, 0 },
    { 1, 1, 2, 0, 1, 0 },
    { 1, 2, 1, 3, 0, 0 },
    { 1, 2, 3, 0, 1, 0 },
    { 2, 2, 2, 2, 2, 1 },
  };
  t_inventory	tile;

  tile = game.map[x][y];
  return (((int)tile.linemate == elevation_stats[elevation - 1][0]) &&
	  ((int)tile.deraumere == elevation_stats[elevation - 1][1]) &&
	  ((int)tile.sibur == elevation_stats[elevation - 1][2]) &&
	  ((int)tile.mendiane == elevation_stats[elevation - 1][3]) &&
	  ((int)tile.phiras == elevation_stats[elevation - 1][4]) &&
	  ((int)tile.thystame == elevation_stats[elevation - 1][5]));
}

int		cmd_pre_elevation(t_client *client,
				  char *token __attribute__((unused)))
{
  t_player	*player;

  player = client->data;
  print_log("Player %d from %s: start an incantation to reach elevation %d\n",
	    client->net_info.fd, player->team->name, player->elevation + 1);
  rfc_17(NULL, client);
  if (player->elevation >= 8)
    {
      queue_packet(client, SIMPLE_PACKET, RPL_KO);
      player->incantation_status = INCANTATION_FAILED;
    }
  else if (check_object_on_tile(player->elevation, player->pos_x, player->pos_y) &&
      check_player_on_tile(player->elevation, player->pos_x, player->pos_y))
    {
      queue_packet(client, SIMPLE_PACKET, RPL_UNDER_ELEVATION);
      player->incantation_status = INCANTATION_PROCESSING;
    }
  else
    {
      queue_packet(client, SIMPLE_PACKET, RPL_KO);
      player->incantation_status = INCANTATION_FAILED;
    }
  return (0);
}

int		cmd_elevation(t_client *client,
			      char *token __attribute__((unused)))
{
  t_player	*player;

  player = client->data;
  if (player->elevation >= 8)
    {
      player->incantation_status = INCANTATION_NONE;
      queue_packet(client, SIMPLE_PACKET, RPL_KO);
    }
  if (check_object_on_tile(player->elevation, player->pos_x, player->pos_y) &&
      check_player_on_tile(player->elevation, player->pos_x, player->pos_y))
    {
      elevate_players(player->pos_x, player->pos_y);
      if (player->elevation == 8)
	check_winning_condition();
    }
  else
    {
      player->incantation_status = INCANTATION_NONE;
      queue_packet(client, SIMPLE_PACKET, RPL_KO);
    }
  rfc_18(NULL, client);
  (void)client;
  return (0);
}
