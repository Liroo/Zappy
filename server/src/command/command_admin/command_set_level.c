/*
** command_set_level.c for Project-Master in /home/guicha/tek2/Zappy/server/src/command/command_admin
**
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
**
** Started on  Sun Jul  2 07:19:35 2017 guicha_t
** Last update Sun Jul  2 22:07:08 2017 guicha_t
*/

#include <stdlib.h>
#include <string.h>

#include "command.h"
#include "struct.h"
#include "h.h"

int		get_player_setlvl(t_team *team, int fd, int lvl)
{
  t_list_head   *head_p;
  t_list_head   *pos_p;
  t_client      *tmp_p;
  t_player      *p;

  head_p = &team->players;
  pos_p = list_get_first(head_p);
  while (pos_p != head_p)
    {
      tmp_p = list_entry(pos_p, t_client, list);
      if (tmp_p->net_info.fd == fd)
	{
	  p = tmp_p->data;
	  p->elevation = lvl;
	  return (1);
	}
      pos_p = pos_p->next;
    }
  return (0);
}

void	convert_param_setlvl(t_client *c, char *sfd,
			 char *slvl)
{
  t_list_head	*head;
  t_list_head	*pos;
  t_team	*team;
  int		fd;
  int		lvl;
  int           res;

  fd = atoi(sfd);
  lvl = atoi(slvl);
  if (lvl < 1 || lvl > 8)
    return ((void)queue_packet(c, SIMPLE_PACKET,
			       "ko: Level not available\n"));
  head = &game.teams;
  pos = list_get_first(head);
  while (pos != head)
    {
      team = list_entry(pos, t_team, list);
      res = get_player_setlvl(team, fd, lvl);
      pos = pos->next;
    }
  if (res == 0)
    queue_packet(c, SIMPLE_PACKET, "ko: fd not found\n");
  else
    queue_packet(c, SIMPLE_PACKET, "ok\n");
}

void	get_param_setlevel(t_client *client, char *token)
{
  char  *sfd;
  char  *slvl;

  if (!(sfd = malloc(sizeof(char) * strlen(token))) ||
      !(slvl = malloc(sizeof(char) * strlen(token))))
    return ((void)zappy_exit());
  memset(sfd, '\0', strlen(token));
  memset(slvl, '\0', strlen(token));
  catch_each_param(token, sfd);
  catch_each_param(token, slvl);
  convert_param_setlvl(client, sfd, slvl);
  free(sfd);
  free(slvl);
}

int	cmd_set_level(t_client *client, char *token)
{
  char	*epured_token;
  int	nb_word;

  epured_token = strepur(token);
  nb_word = my_count_word(epured_token, ' ');
  if (nb_word != 3)
    queue_packet(client, SIMPLE_PACKET,
		 "ko: setlevel <fd player> <new level>\n");
  else
    {
      get_param_setlevel(client, epured_token);
      check_winning_condition();
    }
  free(epured_token);
  return (0);
}
