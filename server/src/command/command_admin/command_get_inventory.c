/*
** command_get_inventory.c for Project-Master in /home/guicha/tek2/Zappy/server/src/command/command_admin
** 
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
** 
** Started on  Sun Jul  2 20:31:05 2017 guicha_t
** Last update Sun Jul  2 22:06:36 2017 guicha_t
*/

#include <stdlib.h>
#include <string.h>

#include "command.h"
#include "struct.h"
#include "h.h"

void		catch_each_param_inventory(char *token, char *src)
{
  static int	i = 13;
  int		is;

  is = 0;
  while (token[i] != ' ' && token[i] != '\0')
    src[is++] = token[i++];
  if (token[i] != '\0')
    i++;
  else
    i = 9;
}

int		get_player_inventory(t_client *client,
				     t_team *team, int fd)
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
	  print_getinventory(client, tmp_p, p);
	  return (1);
	}
      pos_p = pos_p->next;
    }
  return (0);
}

void		convert_param_getinventory(t_client *c, char *sfd)
{
  t_list_head	*head;
  t_list_head	*pos;
  t_team	*team;
  int		fd;
  int		res;

  fd = atoi(sfd);
  head = &game.teams;
  pos = list_get_first(head);
  while (pos != head)
    {
      team = list_entry(pos, t_team, list);
      res = get_player_inventory(c, team, fd);
      pos = pos->next;
    }
  if (res == 0)
    queue_packet(c, SIMPLE_PACKET, "ko: fd not found\n");
  else
    queue_packet(c, SIMPLE_PACKET, "--END OF GETINVENTORY--\n");
}


void	get_param_getinventory(t_client *client, char *token)
{
  char	*sfd;

  if (!(sfd = malloc(sizeof(char) * strlen(token))))
    return ((void)zappy_exit());
  memset(sfd, '\0', strlen(token));
  catch_each_param_inventory(token, sfd);
  convert_param_getinventory(client, sfd);
  free(sfd);
}

  int	cmd_get_inventory(t_client *client, char *token)
  {
  char	*epured_token;
  int	nb_word;

  epured_token = strepur(token);
  nb_word = my_count_word(epured_token, ' ');
  if (nb_word != 2)
    queue_packet(client, SIMPLE_PACKET,
		 "ko: getinventory <fd player>\n");
  else
    get_param_getinventory(client, epured_token);
  free(epured_token);
  return (0);
}
