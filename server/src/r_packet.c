/*
** r_packet.c for Project-Master in /home/guicha/tek2/PSU_2016_zappy/server/src
** 
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
** 
** Started on  Thu Jun 15 22:22:38 2017 guicha_t
** Last update Fri Jun 16 01:30:14 2017 guicha_t
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>

#include "h.h"
#include "fdlist.h"
#include "event.h"
#include "debug.h"
#include "struct.h"
#include "stdlib.h"
#include "stdio.h"
#include "command.h"

int	cmd_advance()
{
  return (0);
}

static t_token	get_token(char *buf, char *buf_token)
{
  t_token	token;
  static int	offset;
  char		*next_token;

  next_token = NULL;
  if (buf_token)
    offset = 0;
  bzero(&token, sizeof(t_token));
  if ((next_token = memchr(buf, '\n', 4096)))
    token.is_over = 1;
  if (next_token)
    *((char*)next_token) = 0;
  token.token = buf + offset;
  offset = next_token - buf + 1;
  return (token);
}

static t_command	*get_command()
{
  static t_command	cmd_entry[MAX_COMMAND_SIZE] =
    {
      { "Advance", &cmd_advance},
      /* { "Right", &cmd_right }, */
      /* { "Left", &cmd_left }, */
      /* { "See", &cmd_see }, */
      /* { "Inventory", &cmd_inventory }, */
      /* { "Broadcast", &cmd_broadcast }, */
      /* { "Connect_nbr", &cmd_connect_nbr }, */
      /* { "Fork", &cmd_fork }, */
      /* { "Eject", &cmd_eject }, */
      /* { "Take_object", &cmd_take_object }, */
      /* { "Set_object", &cmd_set_object }, */
      /* { "Incantation", &cmd_incantation } */
    };
  
  return (cmd_entry);
}

void		check_cmd_exist(t_token *token, t_player *ply)
{
  t_command	*command_list;
  int		i;
  
  i = 0;
  printf("%s\n", token->token);
  command_list = get_command();
  while (i < MAX_COMMAND_SIZE)
    {
      if (strcasecmp(token->token, command_list[i].title) == 0)
	{
	  dprintf(ply->net_info.fd, "Successfully\r\n");
	  // Add to player's queue (Token + *func)
	  break;
	}
      i++;
    }
  dprintf(ply->net_info.fd, "Cmd unknown\r\n");
}

int		read_on_fd(t_player *ply)
{
  char		buf[4096];
  t_token	token;
  int		len_not_over;

  memset(buf, 0, 4096);
  if (recv(ply->net_info.fd, buf, 4096, 0) == -1)
    write(1, "recv error\n", 11);
  token = get_token(buf, buf);
  while (1)
    {
      if (!token.token)
	break;
      if (!token.is_over)
	{
	  len_not_over = strlen(token.token);
	  memmove(buf, token.token, len_not_over);
	  return (0);
	}
      else
	check_cmd_exist(&token, ply);
      token = get_token(buf, NULL);
    }
  return (0);
}
