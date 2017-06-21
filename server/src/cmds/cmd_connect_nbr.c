/*
** cmd_connect_nbr.c for Project-Master in /home/guicha/tek2/Zappy/server/src/cmds
** 
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
** 
** Started on  Wed Jun 21 02:31:05 2017 guicha_t
** Last update Wed Jun 21 02:37:21 2017 guicha_t
*/

#include "debug.h"
#include "struct.h"
#include "h.h"

int	cmd_connect_nbr(t_player *p, char *token)
{
  (void)token;
  queue_packet(p, "%d\n", p->team->empty_slot);
  return (0);
}
