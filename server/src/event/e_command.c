/*
** command.c<event> for command in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Thu Jun 22 22:20:11 2017 Pierre Monge
** Last update Sat Jun 24 23:54:29 2017 Pierre Monge
*/

#include "struct.h"
#include "debug.h"

void		event_command(void *data)
{
  t_client	*client;
  t_player	*player;

  client = data;
  player = client->data;
  player->command_is_running = 0;
}
