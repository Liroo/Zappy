/*
** cmd_left.c for Project-Master in /home/guicha/tek2/Zappy/server/src/cmds
** 
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
** 
** Started on  Wed Jun 21 01:01:36 2017 guicha_t
** Last update Fri Jun 23 16:38:22 2017 guicha_t
*/

#include "h.h"
#include "debug.h"
#include "game.h"
#include "chrono.h"
#include "struct.h"
#include "packet.h"

int	cmd_left(t_player *p, char *token)
{
  (void)token;
  --p->direction;
  if (p->direction < 0)
    p->direction = 3;
  queue_packet(p, SIMPLE_PACKET, RPL_OK);
  p->command_is_running = 1;
  queue_chrono(CHRONO_LEFT, p, C_EVENT_COMMAND);
  return (0);
}
