/*
** command.c<event> for command in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Thu Jun 22 22:20:11 2017 Pierre Monge
** Last update Sat Jul  1 07:03:46 2017 Pierre Monge
*/

#include <stdlib.h>

#include "struct.h"
#include "debug.h"

void		event_command(void *data)
{
  t_client	*client;
  t_player	*player;
  int		i;

  client = data;
  player = client->data;
  if ((*player->command_queue).exec)
    (*player->command_queue).exec(client, (*player->command_queue).command);
  free((*player->command_queue).command);
  (*player->command_queue).command = NULL;
  i = 0;
  while (i < player->command_in_queue)
    {
      player->command_queue[i] = player->command_queue[i + 1];
      i++;
    }
  player->command_in_queue -= 1;
  player->command_is_running = 0;
}
