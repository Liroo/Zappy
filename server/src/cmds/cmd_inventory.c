/*
** cmd_inventory.c for Project-Master in /home/guicha/tek2/Zappy/server/src/cmds
** 
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
** 
** Started on  Wed Jun 21 02:43:02 2017 guicha_t
** Last update Thu Jun 22 06:11:50 2017 guicha_t
*/

#include "h.h"
#include "struct.h"
#include "debug.h"

int	cmd_inventory(t_player *p, char *token)
{
  (void)token;
  queue_packet(p,
	       SIMPLE_PACKET,
	       "[food %d, linemate %d, deraumere %d, "
	       "sibur %d, mendiane %d, phiras %d, thystame %d]\n",
	       p->inventory.food,
	       p->inventory.linemate,
	       p->inventory.deraumere,
	       p->inventory.sibur,
	       p->inventory.mendiane,
	       p->inventory.phiras,
	       p->inventory.thystame);
  return (0);
}
