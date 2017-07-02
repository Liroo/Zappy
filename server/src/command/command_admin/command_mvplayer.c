/*
** command_mvplayer.c for Project-Master in /home/guicha/tek2/Zappy/server/src/command/command_admin
**
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
**
** Started on  Sat Jul  1 17:47:57 2017 guicha_t
** Last update Sun Jul  2 22:37:10 2017 Pierre Monge
*/

#include <stdlib.h>
#include <string.h>

#include "debug.h"
#include "command.h"
#include "struct.h"
#include "h.h"

void		catch_each_param(char *token, char *src)
{
  static int	i = 9;
  int		is;

  is = 0;
  while (token[i] != ' ' && token[i] != '\0')
    src[is++] = token[i++];
  if (token[i] != '\0')
    i++;
  else
    i = 9;
}

int		get_player_mvplayer(t_team *team, int fd,
				    int x, int y)
{
  t_list_head	*head_p;
  t_list_head	*pos_p;
  t_client	*tmp_p;
  t_player	*p;

  head_p = &team->players;
  pos_p = list_get_first(head_p);
  while (pos_p != head_p)
    {
      tmp_p = list_entry(pos_p, t_client, list);
      if (tmp_p->net_info.fd == fd)
	{
	  p = tmp_p->data;
	  game.map[p->pos_x][p->pos_y].player--;
	  p->pos_x = x;
	  p->pos_y = y;
	  game.map[p->pos_x][p->pos_y].player++;
	  return (1);
	}
      pos_p = pos_p->next;
    }
  return (0);
}

void		convert_param_id(t_client *c, char *sfd,
			       char *sx, char *sy)
{
  t_list_head	*head;
  t_list_head	*pos;
  t_team	*team;
  int		fd;
  int		x;
  int		y;
  int		res;

  fd = atoi(sfd);
  x = atoi(sx);
  y = atoi(sy);
  if (x >= (int)game.map_size_x || y >= (int)game.map_size_y
      || x < 0 || y < 0)
    return ((void)queue_packet(c, SIMPLE_PACKET, "ko: Out of map\n"));
  head = &game.teams;
  pos = list_get_first(head);
  while (pos != head)
    {
      team = list_entry(pos, t_team, list);
      res = get_player_mvplayer(team, fd, x, y);
      pos = pos->next;
    }
  if (res == 0)
    queue_packet(c, SIMPLE_PACKET, "ko: fd not found\n");
}

void	get_param_mvplayer(t_client *client, char *token)
{
  char	*sfd;
  char	*sx;
  char	*sy;

  if (!(sfd = malloc(sizeof(char) * strlen(token))) ||
      !(sx = malloc(sizeof(char) * strlen(token))) ||
      !(sy = malloc(sizeof(char) * strlen(token))))
    return ((void)zappy_exit());
  memset(sfd, '\0', strlen(token));
  memset(sx, '\0', strlen(token));
  memset(sy, '\0', strlen(token));
  catch_each_param(token, sfd);
  catch_each_param(token, sx);
  catch_each_param(token, sy);
  convert_param_id(client, sfd, sx, sy);
  free(sfd);
  free(sx);
  free(sy);
}

int	cmd_mvplayer(t_client *client, char *token)
{
  char	*epured_token;
  int	nb_word;

  epured_token = strepur(token);
  nb_word = my_count_word(epured_token, ' ');
  if (nb_word != 4)
    queue_packet(client, SIMPLE_PACKET,
		 "ko: mvplayer <fd player> <new x> <new y>\n");
  else
    get_param_mvplayer(client, epured_token);
  free(epured_token);
  return (0);
}
