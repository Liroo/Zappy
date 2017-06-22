/*
** cmd_set.c for Project-Master in /home/guicha/tek2/Zappy/server/src/cmds
** 
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
** 
** Started on  Thu Jun 22 00:49:52 2017 guicha_t
** Last update Thu Jun 22 06:05:25 2017 guicha_t
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "packet.h"
#include "debug.h"
#include "h.h"
#include "struct.h"

void    deposit_on_tile(t_player *p, int offset)
{
  if (*(((char *)&p->inventory) + offset) <= 0)
    queue_packet(p, SIMPLE_PACKET, RPL_KO);
  else
    {
      REMOVE_OBJECT(&p->inventory, offset);
      INSERT_OBJECT(&game.map[p->pos_x][p->pos_y], offset);
      queue_packet(p, SIMPLE_PACKET, RPL_OK);
    }
}

int     cmd_set(t_player *p, char *token)
{
  char          *rsc;
  char          *clean_token;

  clean_token = epur_str(token);
  rsc = parse_param(clean_token);
  if (strcasecmp(rsc, "linemate") == 0)
    deposit_on_tile(p, LINEMATE_OFFSET);
  else if (strcasecmp(rsc, "deraumere") == 0)
    deposit_on_tile(p, DERAUMERE_OFFSET);
  else if (strcasecmp(rsc, "sibur") == 0)
    deposit_on_tile(p, SIBUR_OFFSET);
  else if (strcasecmp(rsc, "mendiane") == 0)
    deposit_on_tile(p, MENDIANE_OFFSET);
  else if (strcasecmp(rsc, "phiras") == 0)
    deposit_on_tile(p, PHIRAS_OFFSET);
  else if (strcasecmp(rsc, "thystame") == 0)
    deposit_on_tile(p, THYSTAME_OFFSET);
  else if (strcasecmp(rsc, "food") == 0)
    deposit_on_tile(p, FOOD_OFFSET);
  else
    queue_packet(p, SIMPLE_PACKET, RPL_KO);
  free(clean_token);
  free(rsc);
  return (0);
}
