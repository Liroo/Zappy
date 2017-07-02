/*
** print_get_inventory.c for Project-Master in /home/guicha/tek2/Zappy/server/src/command/command_admin
** 
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
** 
** Started on  Sun Jul  2 21:52:36 2017 guicha_t
** Last update Sun Jul  2 21:54:07 2017 guicha_t
*/

#include "struct.h"
#include "command.h"
#include "h.h"

void	print_getinventory(t_client *client, t_client *player,
			   t_player *p)
{
  queue_packet(client, SIMPLE_PACKET,
	       GET_INVENTORY,
	       player->net_info.fd,
	       p->inventory.food,
	       p->inventory.linemate,
	       p->inventory.deraumere,
	       p->inventory.sibur,
	       p->inventory.mendiane,
	       p->inventory.phiras,
	       p->inventory.thystame);
}

