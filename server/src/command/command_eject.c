/*
** eject.c for zappy in /home/thomas/Rendu/Zappy/server
**
** Made by Thomas
** Login   <thomas@epitech.net>
**
** Started on  Fri Jun 23 01:28:13 2017 Thomas
** Last update Sun Jul  2 07:59:01 2017 guicha_t
*/

#include "debug.h"
#include "struct.h"
#include "h.h"
#include "rfc.h"
#include "log.h"

static void	send_eject(t_client *client, t_player *target_p, t_player *p)
{
  if (target_p->direction == p->direction)
    queue_packet(client, SIMPLE_PACKET, "eject: 5\n");
  else if ((p->direction + 1 == target_p->direction)
	   || (p->direction == 3 && target_p->direction == 0))
    queue_packet(client, SIMPLE_PACKET, "eject: 7\n");
  else if ((p->direction - 1 == target_p->direction)
	   || (p->direction == 0 && target_p->direction == 3))
    queue_packet(client, SIMPLE_PACKET, "eject: 3\n");
  else
    queue_packet(client, SIMPLE_PACKET, "eject: 1\n");
  print_log("Player %d from %s: Ejected\n", client->net_info.fd,
	    target_p->team->name);
}

static void	eject_player(t_client *client, t_player *p)
{
  t_player	*target_p;
  int		x;
  int		y;

  target_p = client->data;
  x = (p->direction % 2 == 0) ? -(p->direction - 1) : 0;
  y = (p->direction % 2 == 1) ? -(p->direction - 2) : 0;
  target_p->pos_x += x;
  target_p->pos_y += y;
  if (target_p->pos_x < 0)
    target_p->pos_x = game.map_size_x;
  else if (target_p->pos_x >= (int)game.map_size_x)
    target_p->pos_x = 0;
  if (target_p->pos_y < 0)
    target_p->pos_y = game.map_size_y;
  else if (target_p->pos_y >= (int)game.map_size_y)
    target_p->pos_y = 0;
  game.map[target_p->pos_x][target_p->pos_y].player++;
  send_eject(client, target_p, p);
}

static void	find_player(t_client *client,
			    t_player *p, t_team	*team)
{
  t_list_head	*head_p;
  t_list_head	*pos_p;
  t_client	*tmp_p;
  t_player	*in;

  head_p = &team->players;
  pos_p = list_get_first(head_p);
  while (pos_p != head_p)
    {
      tmp_p = list_entry(pos_p, t_client, list);
      in = tmp_p->data;
      if (in->pos_x == p->pos_x && in->pos_y == p->pos_y
	  && client->net_info.fd != tmp_p->net_info.fd)
	eject_player(tmp_p, p);
      pos_p = pos_p->next;
    }
}

int	cmd_eject(t_client *client, char *token)
{
  t_list_head	*head;
  t_list_head	*pos;
  t_team	*tmp;
  t_player	*p;

  (void)token;
  p = client->data;
  if (game.map[p->pos_x][p->pos_y].player <= 1)
    {
      queue_packet(client, SIMPLE_PACKET, RPL_KO);
      return (0);
    }
  print_log("Player %d from %s: EJECT\n", client->net_info.fd,
	    p->team->name);
  head = &game.teams;
  pos = list_get_first(head);
  while (pos != head)
    {
      tmp = list_entry(pos, t_team, list);
      find_player(client, p, tmp);
      pos = pos->next;
    }
  queue_packet(client, SIMPLE_PACKET, RPL_OK);
  rfc_11(NULL, client);
  return (0);
}
