/*
** cmd_set.c for Project-Master in /home/guicha/tek2/Zappy/server/src/cmds
** 
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
** 
** Started on  Thu Jun 22 00:49:52 2017 guicha_t
** Last update Mon Jun 26 00:05:03 2017 guicha_t
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "packet.h"
#include "game.h"
#include "chrono.h"
#include "debug.h"
#include "h.h"
#include "struct.h"

void		deposit_on_tile(t_player *p, t_client *c, int offset)
{
  if (*(((char *)&p->inventory) + offset) <= 0)
    queue_packet(c, SIMPLE_PACKET, RPL_KO);
  else
    {
      REMOVE_OBJECT(&p->inventory, offset);
      INSERT_OBJECT(&game.map[p->pos_x][p->pos_y], offset);
      queue_packet(c, SIMPLE_PACKET, RPL_OK);
    }
}

int		cmd_set(t_client *client, char *token)
{
  char          *rsc;
  char          *clean_token;
  t_player	*p;

  p = client->data;
  clean_token = strepur(token);
  rsc = parse_param(clean_token);
  if (strcasecmp(rsc, "linemate") == 0)
    deposit_on_tile(p, client, LINEMATE_OFFSET);
  else if (strcasecmp(rsc, "deraumere") == 0)
    deposit_on_tile(p, client, DERAUMERE_OFFSET);
  else if (strcasecmp(rsc, "sibur") == 0)
    deposit_on_tile(p, client, SIBUR_OFFSET);
  else if (strcasecmp(rsc, "mendiane") == 0)
    deposit_on_tile(p, client, MENDIANE_OFFSET);
  else if (strcasecmp(rsc, "phiras") == 0)
    deposit_on_tile(p, client, PHIRAS_OFFSET);
  else if (strcasecmp(rsc, "thystame") == 0)
    deposit_on_tile(p, client, THYSTAME_OFFSET);
  else if (strcasecmp(rsc, "food") == 0)
    deposit_on_tile(p, client, FOOD_OFFSET);
  else
    queue_packet(client, SIMPLE_PACKET, RPL_KO);
  free(clean_token);
  free(rsc);
  p->command_is_running = 1;
  queue_chrono(CHRONO_SET, client, C_EVENT_COMMAND);
  return (0);
}
