/*
** cmd_broadcast.c for Project-Master in /home/guicha/tek2/Zappy/server/src/cmds
** 
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
** 
** Started on  Thu Jun 22 07:01:19 2017 guicha_t
** Last update Sat Jul  1 06:14:31 2017 guicha_t
*/

#include <stdlib.h>
#include <string.h>

#include "debug.h"
#include "game.h"
#include "chrono.h"
#include "struct.h"
#include "h.h"
#include "packet.h"
#include "log.h"
#include "rfc.h"

int	convert_dir_about_dest(int pdir, int dir)
{
  int	real_dir;

  real_dir = 0;
  if (pdir == 0)
    real_dir = dir;
  else if (pdir == 1)
    {
      real_dir = dir + 2;
      if (real_dir > 8)
	real_dir = real_dir - 8;
    }
  else if (pdir == 2)
    {
      real_dir = dir + 4;
      if (real_dir > 8)
	real_dir = real_dir - 8;
    }
  else if (pdir == 3)
    {
      real_dir = dir + 6;
      if (real_dir > 8)
	real_dir = real_dir - 8;
    }
  return (real_dir);
}

void	send_broadcast_message(t_client *c, char *msg, int dir)
{
  int		new_dir;
  t_player	*p;

  p = c->data;
  if (dir != 0)
    new_dir = convert_dir_about_dest(p->direction, dir);
  else
    new_dir = 0;
  if (msg != NULL)
    queue_packet(c, SIMPLE_PACKET, "message %d, %s\n", new_dir, msg);
  else
    queue_packet(c, SIMPLE_PACKET, "message %d\n", new_dir, msg);
  print_log("Player %d from %s: receive BROADCAST\n",
	    c->net_info.fd,
	    p->team->name);
}

char	*get_only_message_from_token(char *token)
{
  char	*msg;
  int	it;
  int	im;

  it = 0;
  im = 0;
  if (!(msg = malloc(sizeof(char) * strlen(token))))
    return (zappy_exit(), NULL);
  memset(msg, '\0', strlen(token));
  while (token[it] != ' ' && token[it] != '\0')
    it++;
  if (token[it] == '\0')
    return (NULL);
  it++;
  while (token[it] != '\0')
    {
      msg[im] = token[it];
      it++;
      im++;
    }
  return (msg);
}

void	find_player_broadcast(t_client *send, t_team *team, char *t)
{
  t_list_head	*head_p;
  t_list_head	*pos_p;
  t_client	*tmp_p;
  t_player	*pdest;
  t_player	*psend;
  char		*msg;
  int		dir;

  head_p = &team->players;
  pos_p = list_get_first(head_p);
  psend = send->data;
  msg = get_only_message_from_token(t);
  rfc_10(NULL, send, msg);
  while (pos_p != head_p)
    {
      tmp_p = list_entry(pos_p, t_client, list);
      pdest = tmp_p->data;
      if (tmp_p != send)
	{
	  dir = algorithme_vector(psend, pdest);
	  send_broadcast_message(tmp_p, msg, dir);
	}
      pos_p = pos_p->next;
    }
  free(msg);
}

int	cmd_broadcast(t_client *client, char *token)
{
  t_list_head	*head;
  t_list_head	*pos;
  t_team	*team;
  t_player	*psend;

  psend = client->data;
  head = &game.teams;
  pos = list_get_first(head);
  print_log("Player %d from %s: BROADCAST\n",
	    client->net_info.fd,
	    psend->team->name);
  while (pos != head)
    {
      team = list_entry(pos, t_team, list);
      find_player_broadcast(client, team, token);
      pos = pos->next;
    }
  queue_packet(client, SIMPLE_PACKET, RPL_OK);
  return (0);
}
