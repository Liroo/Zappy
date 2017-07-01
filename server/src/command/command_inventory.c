/*
** cmd_inventory.c for Project-Master in /home/guicha/tek2/Zappy/server/src/cmds
** 
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
** 
** Started on  Wed Jun 21 02:43:02 2017 guicha_t
** Last update Sat Jul  1 01:32:32 2017 guicha_t
*/

#include "h.h"
#include "struct.h"
#include "game.h"
#include "chrono.h"
#include "debug.h"
#include "log.h"

int	cmd_inventory(t_client *client, char *token)
{
  t_player	*p;

  p = client->data;
  (void)token;
  queue_packet(client,
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
  print_log("Player %d from %s: INVENTORY.\n",
	    client->net_info.fd,
	    p->team->name);
  p->command_is_running = 1;
  queue_chrono(CHRONO_INVENTORY, client, C_EVENT_COMMAND);
  return (0);
}
