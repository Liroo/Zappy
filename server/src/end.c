/*
** end.c for end in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sun Jul  2 07:12:58 2017 Pierre Monge
** Last update Sun Jul  2 07:42:48 2017 Pierre Monge
*/

#include "struct.h"
#include "log.h"
#include "rfc.h"
#include "h.h"

static void	break_client_list(t_list_head *head)
{
  t_list_head	*pos;
  t_list_head	*next;

  pos = list_get_first(head);
  while (pos != head)
    {
      next = pos->next;
      delete_client(list_entry(pos, t_client, list));
      pos = next;
    }
}

static void	break_teams()
{
  t_list_head	*pos;
  t_team	*team;

  pos = list_get_first(&game.teams);
  while (pos != &game.teams)
    {
      team = list_entry(pos, t_team, list);
      break_client_list(&team->players);
      pos = pos->next;
    }
}

void	end_server(t_team *team)
{
  game.game_ended = 1;
  rfc_20(NULL, team);
  break_teams();
  print_log("%s won the game. Game is stopping...\n", team->name);
}

int		is_server_ended()
{
  t_list_head	*pos;
  t_client	*client;

  pos = list_get_first(&game.admins);
  while (pos != &game.admins)
    {
      client = list_entry(pos, t_client, list);
      if (!list_empty(&client->w_packet))
	return (0);
      pos = pos->next;
    }
  pos = list_get_first(&game.spectators);
  while (pos != &game.spectators)
    {
      client = list_entry(pos, t_client, list);
      if (!list_empty(&client->w_packet))
	return (0);
      pos = pos->next;
    }
  return (1);
}
