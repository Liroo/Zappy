/*
** getplayer.c for Project-Master in /home/guicha/tek2/Zappy/server/src/command/command_admin
**
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
**
** Started on  Thu Jun 29 10:02:43 2017 guicha_t
** Last update Sun Jul  2 22:39:03 2017 Pierre Monge
*/

#include "debug.h"
#include "command.h"
#include "struct.h"
#include "h.h"

void	display_informations(t_client *client, t_client *tmp_p,
			     t_player *player)
{
  char	dir;

  if (player->direction == 0)
    dir = 'N';
  else if (player->direction == 1)
    dir = 'E';
  else if (player->direction == 2)
    dir = 'S';
  else
    dir = 'W';
  queue_packet(client, SIMPLE_PACKET,
	       "fd %d - [%d][%d] dir:%c lvl:%d\n",
	       tmp_p->net_info.fd,
	       player->pos_x,
	       player->pos_y,
	       dir, player->elevation);
}

void		find_player_in_team(t_client *client, t_team *team)
{
  t_list_head	*head_p;
  t_list_head	*pos_p;
  t_client	*tmp_p;
  t_player	*player;

  head_p = &team->players;
  pos_p = list_get_first(head_p);
  while (pos_p != head_p)
    {
      tmp_p = list_entry(pos_p, t_client, list);
      player = tmp_p->data;
      display_informations(client, tmp_p, player);
      pos_p = pos_p->next;
    }
}

int		cmd_getplayer(t_client *client, char *token)
{
  t_list_head	*head;
  t_list_head	*pos;
  t_team	*team;

  (void)token;
  head = &game.teams;
  pos = list_get_first(head);
  while (pos != head)
    {
      team = list_entry(pos, t_team, list);
      find_player_in_team(client, team);
      pos = pos->next;
    }
  queue_packet(client, SIMPLE_PACKET, "--END OF GETINFO--\n");
  return (0);
}
