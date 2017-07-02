/*
** r_auth.c for rfc auth in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Fri Jun 30 22:28:39 2017 Pierre Monge
** Last update Sun Jul  2 22:35:49 2017 Pierre Monge
*/

#include "struct.h"
#include "rfc.h"

void		rfc_auth_list_client(t_client *spectator, t_team *team)
{
  t_list_head	*pos;

  pos = list_get_first(&team->players);
  while (pos != &team->players)
    {
      rfc_03(spectator, list_entry(pos, t_client, list));
      pos = pos->next;
    }
}

static void	rfc_auth_list_team(t_client *spectator)
{
  t_list_head	*pos;

  pos = list_get_first(&game.teams);
  while (pos != &game.teams)
    {
      rfc_02(spectator, list_entry(pos, t_team, list));
      rfc_auth_list_client(spectator, list_entry(pos, t_team, list));
      pos = pos->next;
    }
}

void		rfc_map(t_client *spectator)
{
  int		x;
  int		y;

  x = 0;
  while (x < (int)game.map_size_x)
    {
      y = 0;
      while (y < (int)game.map_size_y)
	{
	  rfc_04(spectator, x, y);
	  y++;
	}
      x++;
    }
}

void	rfc_auth(t_client *spectator)
{
  rfc_01(spectator);
  rfc_auth_list_team(spectator);
  rfc_map(spectator);
}
