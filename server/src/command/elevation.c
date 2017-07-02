/*
** elevation.c for elevation in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sun Jul  2 02:53:23 2017 Pierre Monge
** Last update Sun Jul  2 07:29:10 2017 Pierre Monge
*/

#include "packet.h"
#include "struct.h"
#include "list.h"
#include "rfc.h"
#include "log.h"
#include "h.h"

static void	elevate_single_player(t_client *client)
{
  t_player	*player;

  player = client->data;
  player->elevation++;
  rfc_03(NULL, client);
  print_log("Player %d from %s: elevation to %d\n", client->net_info.fd,
	    player->team->name, player->elevation);
  queue_packet(client, SIMPLE_PACKET, RPL_ELEVATION, player->elevation);
}

void		elevate_players(int x, int y)
{
  t_list_head		*team;
  t_list_head		*client;
  t_team		*team_ptr;
  t_player		*p;

  team = list_get_first(&game.teams);
  while (team != &game.teams)
    {
      team_ptr = list_entry(team, t_team, list);
      client = list_get_first(&team_ptr->players);
      while (client != &team_ptr->players)
	{
	  p = ((t_client *)list_entry(client, t_client, list))->data;
	  if (p->pos_x == x && p->pos_y == y)
	    elevate_single_player(((t_client *)list_entry(client,
							  t_client, list)));
	  client = client->next;
	}
      team = team->next;
    }
}

static int	check_winning_team(t_team *team)
{
  t_list_head	*client;
  t_client	*client_ptr;
  int		players_elevated;

  players_elevated = 0;
  client = list_get_first(&team->players);
  while (client != &team->players)
    {
      client_ptr = list_entry(client, t_client, list);
      if (((t_player *)client_ptr->data)->elevation >= 8)
	players_elevated += 1;
      client = client->next;
    }
  return (players_elevated >= DFL_PLAYERS_ELEVATED_WIN);
}

void		check_winning_condition()
{
  t_list_head	*team;

  team = list_get_first(&game.teams);
  while (team != &game.teams)
    {
      if (check_winning_team(list_entry(team, t_team, list)))
	return ((void)end_server(list_entry(team, t_team, list)));
      team = team->next;
    }
}
