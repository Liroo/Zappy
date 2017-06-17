/*
** command.c for command in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sat Jun 17 04:55:41 2017 Pierre Monge
** Last update Sat Jun 17 05:25:22 2017 Pierre Monge
*/

#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "struct.h"
#include "debug.h"

static t_command	*get_command_list()
{
  static t_command	command_list[MAX_COMMAND_SIZE] =
    {
      { "Forward", 7, NULL},
      { "Right", 5, NULL },
      { "Left", 4, NULL },
      { "Look", 4, NULL },
      { "Inventory", 9, NULL },
      { "Broadcast", 8, NULL },
      { "Connect_nbr", 11, NULL },
      { "Fork", 4, NULL },
      { "Eject", 5, NULL },
      { "Take", 4, NULL },
      { "Set", 3, NULL },
      { "Incantation", 11, NULL }
    };

  return (command_list);
}

void			convert_packet_to_command(t_packet packet,
						  t_player *player)
{
  t_command		*command_list;
  int			i;
  t_command_queue	*command_queue;

  PRINT_DEBUG("fd: %d received packet:\n%s\n", player->net_info.fd, packet.block);
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
	  command_queue = &player->command_queue[player->command_in_queue + 1];
	  if (!(command_queue->command = strdup(packet.block)))
	    return ;
	  command_queue->exec = command_list[i].exec;
	  player->command_in_queue++;
	  break;
	}
      i++;
    }
}
