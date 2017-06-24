/*
** cmd_broadcast.c for Project-Master in /home/guicha/tek2/Zappy/server/src/cmds
** 
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
** 
** Started on  Thu Jun 22 07:01:19 2017 guicha_t
** Last update Sat Jun 24 20:09:04 2017 guicha_t
*/

#include <stdlib.h>
#include <string.h>

#include "debug.h"
#include "game.h"
#include "chrono.h"
#include "struct.h"
#include "h.h"
#include "packet.h"

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
  PRINT_DEBUG("real dir %d\n", real_dir);
  return (real_dir);
}

void	send_broadcast_message(t_player *p, char *msg, int dir)
{
  int	new_dir;

  new_dir = convert_dir_about_dest(p->direction, dir);
  queue_packet(p, SIMPLE_PACKET, "message %d, %s\n", new_dir, msg);
}

char	*get_only_message_from_token(char *token)
{
  char	*msg;
  int	it;
  int	im;

  it = 0;
  im = 0;
  msg = malloc(sizeof(char) * strlen(token));
  memset(msg, '\0', strlen(token));
  while (token[it] != ' ' && token[it] != '\0')
    it++;
  it++;
  while (token[it] != '\0')
    {
      msg[im] = token[it];
      it++;
      im++;
    }
  return (msg);
}

void	find_player_broadcast(t_player *send, t_team *team, char *t)
{
  t_list_head	*head_p;
  t_list_head	*pos_p;
  t_player	*tmp_p;
  char		*msg;
  int		dir;

  head_p = &team->players;
  pos_p = list_get_first(head_p);
  msg = get_only_message_from_token(t);
  while (pos_p != head_p)
    {
      tmp_p = list_entry(pos_p, t_player, list);
      if (tmp_p != send)
	{
	  dir = algorithme_vector(send, tmp_p);
	  send_broadcast_message(tmp_p, msg, dir);
	}
      pos_p = pos_p->next;
    }
  free(msg);
}

int	cmd_broadcast(t_player *p, char *token)
{
  t_list_head	*head;
  t_list_head	*pos;
  t_team	*team;

  head = &game.teams;
  pos = list_get_first(head);
  while (pos != head)
    {
      team = list_entry(pos, t_team, list);
      find_player_broadcast(p, team, token);
      pos = pos->next;
    }
  queue_packet(p, SIMPLE_PACKET, RPL_OK);
  p->command_is_running = 1;
  queue_chrono(CHRONO_BROADCAST, p, C_EVENT_COMMAND);
  return (0);
}
