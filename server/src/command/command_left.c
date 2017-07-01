/*
** cmd_left.c for Project-Master in /home/guicha/tek2/Zappy/server/src/cmds
**
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
**
** Started on  Wed Jun 21 01:01:36 2017 guicha_t
** Last update Sat Jul  1 01:20:00 2017 guicha_t
*/

#include "h.h"
#include "log.h"
#include "debug.h"
#include "game.h"
#include "chrono.h"
#include "struct.h"
#include "packet.h"

int		cmd_left(t_client *client, char *token)
{
  t_player	*player;

  player = client->data;
  (void)token;
  --player->direction;
  if (player->direction < 0)
    player->direction = 3;
  print_log("Player %d from %s: Left.\n",
	    client->net_info.fd,
	    player->team->name);
  queue_packet(client, SIMPLE_PACKET, RPL_OK);
  player->command_is_running = 1;
  queue_chrono(CHRONO_LEFT, client, C_EVENT_COMMAND);
  return (0);
}
