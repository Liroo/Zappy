/*
** command.c for command in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sat Jun 17 04:55:41 2017 Pierre Monge
** Last update Sat Jun 24 00:27:46 2017 Thomas
*/

#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "struct.h"
#include "debug.h"
#include "h.h"

static t_command	*get_command_list()
{
  static t_command	command_list[MAX_COMMAND_SIZE] =
    {
      { "Forward", 7, &cmd_forward },
      { "Right", 5, &cmd_right },
      { "Left", 4, &cmd_left },
      { "Look", 4, &cmd_look },
      { "Inventory", 9, &cmd_inventory },
      { "Broadcast", 9, &cmd_broadcast },
      { "Connect_nbr", 11, &cmd_connect_nbr },
      { "Fork", 4, NULL },
      { "Eject", 5, &cmd_eject },
      { "Take", 4, &cmd_take },
      { "Set", 3, &cmd_set },
      { "Incantation", 11, NULL }
    };

  return (command_list);
}

static void		queue_command(t_packet packet,
				      t_player *player)
{
  t_command		*command_list;
  int			i;
  t_command_queue	*command_queue;

  i = 0;
  command_list = get_command_list();
  while (i < MAX_COMMAND_SIZE)
    {
      while (*packet.block && *packet.block == ' ')
	packet.block++;
      if (strncasecmp(packet.block, command_list[i].title,
		      command_list[i].title_len) == 0)
	{
	  if (player->command_in_queue >= COMMAND_QUEUE_SIZE)
	    return ;
	  command_queue = &player->command_queue[player->command_in_queue];
	  if (!(command_queue->command = strdup(packet.block)))
	    return ;
	  command_queue->exec = command_list[i].exec;
	  player->command_in_queue++;
	  break;
	}
      i++;
    }
}

void			convert_packet_to_command(t_packet packet,
						  t_player *player)
{
  PRINT_DEBUG("fd: %d received packet:\n%s\n",
	      player->net_info.fd, packet.block);
  if (packet.block[packet.size] == '\r')
    packet.block[packet.size] = 0;
  if (player->is_logged)
    queue_command(packet, player);
  else
    auth_player(packet, player);
}
