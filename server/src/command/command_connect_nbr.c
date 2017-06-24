/*
** cmd_connect_nbr.c for Project-Master in /home/guicha/tek2/Zappy/server/src/cmds
** 
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
** 
** Started on  Wed Jun 21 02:31:05 2017 guicha_t
** Last update Fri Jun 23 03:49:10 2017 guicha_t
*/

#include "debug.h"
#include "struct.h"
#include "h.h"

int	cmd_connect_nbr(t_player *p, char *token)
{
  (void)token;
  queue_packet(p, SIMPLE_PACKET, "%d\n", p->team->empty_slot);
  p->command_is_running = 1;
  return (0);
}
