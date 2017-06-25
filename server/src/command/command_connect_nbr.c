/*
** cmd_connect_nbr.c for Project-Master in /home/guicha/tek2/Zappy/server/src/cmds
**
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
**
** Started on  Wed Jun 21 02:31:05 2017 guicha_t
** Last update Sun Jun 25 01:36:31 2017 Pierre Monge
*/

#include "debug.h"
#include "struct.h"
#include "h.h"

int		cmd_connect_nbr(t_client *client, char *token)
{
  t_player	*player;

  player = client->data;
  (void)token;
  queue_packet(client, SIMPLE_PACKET, "%d\n", player->team->empty_slot);
  player->command_is_running = 1;
  return (0);
}
