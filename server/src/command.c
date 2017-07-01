/*
** command.c for command in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sat Jun 17 04:55:41 2017 Pierre Monge
** Last update Sat Jul  1 16:21:38 2017 Pierre Monge
*/

#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>

#include "struct.h"
#include "debug.h"
#include "h.h"

static int		queue_command(t_packet packet,
				      t_command_queue *command_queue,
				      int *command_in_queue,
				      t_command *command_list)
{
  int			i;
  t_command_queue	*new_command;

  i = 0;
  while (command_list[i].title)
    {
      while (*packet.block && *packet.block == ' ')
	packet.block++;
      if (strncasecmp(packet.block, command_list[i].title,
		      command_list[i].title_len) == 0)
	{
	  if (*command_in_queue >= COMMAND_QUEUE_SIZE)
	    return (-1);
	  new_command = &(command_queue[(*command_in_queue)]);
	  if (!(new_command->command = strdup(packet.block)))
	    return zappy_exit();
	  new_command->exec = command_list[i].exec;
	  new_command->pre_exec = command_list[i].pre_exec;
	  new_command->duration = command_list[i].duration;
	  (*command_in_queue)++;
	  return (0);
	}
      i++;
    }
  return (-1);
}

void		queue_command_player(t_packet packet, t_client *client)
{
  t_command	*command_list;
  t_player	*player;

  player = client->data;
  command_list = get_command_list_player();
  if (queue_command(packet, (t_command_queue *)player->command_queue,
		    &player->command_in_queue, command_list) == -1)
    {
      queue_packet(client, SIMPLE_PACKET, RPL_KO);
      return ;
    }
}

void	queue_command_spectator(t_packet packet, t_client *client)
{
  (void)packet;
  queue_packet(client, SIMPLE_PACKET, RPL_KO);
}

void	queue_command_admin(t_packet packet, t_client *client)
{
  t_command	*command_list;
  t_admin	*admin;

  admin = client->data;
  command_list = get_command_list_admin();
  if (queue_command(packet, (t_command_queue *)admin->command_queue,
		    &admin->command_in_queue, command_list) == -1)
    {
      queue_packet(client, SIMPLE_PACKET, RPL_KO);
      return ;
    }
}
