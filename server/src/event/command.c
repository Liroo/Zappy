/*
** command.c<event> for command in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Thu Jun 22 22:20:11 2017 Pierre Monge
** Last update Fri Jun 23 00:43:10 2017 Pierre Monge
*/

#include "struct.h"
#include "debug.h"

void		event_command(void *data)
{
  t_player	*player;

  player = (t_player *)data;
  player->command_is_running = 0;
}
