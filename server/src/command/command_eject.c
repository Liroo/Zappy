/*
** eject.c for zappy in /home/thomas/Rendu/Zappy/server
**
** Made by Thomas
** Login   <thomas@epitech.net>
**
** Started on  Fri Jun 23 01:28:13 2017 Thomas
** Last update Mon Jun 26 00:33:39 2017 Thomas
*/

#include "struct.h"
#include "h.h"

static void	eject_horizontal(t_client *client)
{
  t_player      *target_p;

  target_p = client->data;
  if (target_p->direction == 1)
    {
      if (target_p->pos_x + 1 <= (int)game.map_size_x)
	target_p->pos_x++;
      else
	target_p->pos_x = 0;
      queue_packet(client, SIMPLE_PACKET, "eject: 3\n");
    }
  else if (target_p->direction == 3)
    {
      if (target_p->pos_x - 1 >= 0)
	target_p->pos_x--;
      else
	target_p->pos_x = game.map_size_x;
      queue_packet(client, SIMPLE_PACKET, "eject: 1\n");
    }
  else
    queue_packet(client, SIMPLE_PACKET, RPL_KO);
}

static void	eject_player(t_client *client)
{
  t_player	*target_p;

  target_p = client->data;
  if (target_p->direction == 0)
    {
      if (target_p->pos_y + 1 <= (int)game.map_size_y)
	target_p->pos_y++;
      else
	target_p->pos_y = 0;
      queue_packet(client, SIMPLE_PACKET, "eject: 2\n");
    }
  else if (target_p->direction == 2)
    {
      if (target_p->pos_y - 1 >= 0)
	target_p->pos_y--;
      else
	target_p->pos_y = game.map_size_y;
      queue_packet(client, SIMPLE_PACKET, "eject: 0\n");
    }
  else
    eject_horizontal(client);
}

static void	find_player(t_player *p, t_team	*team)
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
      if (in->pos_x != p->pos_x && in->pos_y != p->pos_y)
	eject_player(tmp_p);
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
  if (game.map[p->pos_y][p->pos_x].player <= 0)
    {
      queue_packet(client, SIMPLE_PACKET, RPL_KO);
      return (1);
    }
  head = &game.teams;
  pos = list_get_first(head);
  while (pos != head)
    {
      tmp = list_entry(pos, t_team, list);
      find_player(p, tmp);
      pos = pos->next;
    }
  queue_packet(client, SIMPLE_PACKET, RPL_OK);
  queue_chrono(CHRONO_EJECT, client, C_EVENT_COMMAND);
  return (0);
}
