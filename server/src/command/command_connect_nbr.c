/*
** cmd_connect_nbr.c for Project-Master in /home/guicha/tek2/Zappy/server/src/cmds
**
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
**
** Started on  Wed Jun 21 02:31:05 2017 guicha_t
** Last update Sat Jul  1 06:14:39 2017 guicha_t
*/

#include "debug.h"
#include "struct.h"
#include "h.h"
#include "log.h"

int		cmd_connect_nbr(t_client *client, char *token)
{
  t_player	*player;

  player = client->data;
  (void)token;
  queue_packet(client, SIMPLE_PACKET, "%d\n",
	       player->team->empty_slot + player->team->egg_slot);
  print_log("Player %d from %s: CONNECT_NBR (%d)\n",
	    client->net_info.fd,
	    player->team->name,
	    player->team->empty_slot + player->team->egg_slot);
  return (0);
}
