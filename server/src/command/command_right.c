/*
** cmd_right.c for Project-Master in /home/guicha/tek2/Zappy/server/src/cmds
** 
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
** 
** Started on  Wed Jun 21 01:12:18 2017 guicha_t
** Last update Fri Jun 23 16:38:02 2017 guicha_t
*/

#include "h.h"
#include "debug.h"
#include "game.h"
#include "chrono.h"
#include "struct.h"
#include "packet.h"

int	cmd_right(t_player *p, char *token)
{
  (void)token;
  ++p->direction;
  if (p->direction > 3)
    p->direction = 0;
  queue_packet(p, SIMPLE_PACKET, RPL_OK);
  p->command_is_running = 1;
  queue_chrono(CHRONO_RIGHT, p, C_EVENT_COMMAND);
  return (0);
}
