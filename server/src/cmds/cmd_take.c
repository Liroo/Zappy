/*
** cmd_take.c for Project-Master in /home/guicha/tek2/Zappy/server/src/cmds
** 
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
** 
** Started on  Wed Jun 21 02:09:58 2017 guicha_t
** Last update Thu Jun 22 06:04:07 2017 guicha_t
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "debug.h"
#include "h.h"
#include "struct.h"
#include "packet.h"

void	extract(t_player *p, int offset)
{
  if (*(((char *)&game.map[p->pos_x][p->pos_y]) + offset) <= 0)
    queue_packet(p, SIMPLE_PACKET, RPL_KO);
  else
    {
      REMOVE_OBJECT(&game.map[p->pos_x][p->pos_y], offset);
      INSERT_OBJECT(&p->inventory, offset);
      queue_packet(p, SIMPLE_PACKET, RPL_OK);
    }
}

int	cmd_take(t_player *p, char *token)
{
  char		*rsc;
  char		*clean_token;
  
  clean_token = epur_str(token);
  rsc = parse_param(clean_token);
  if (strcasecmp(rsc, "linemate") == 0)
    extract(p, LINEMATE_OFFSET);
  else if (strcasecmp(rsc, "deraumere") == 0)
    extract(p, DERAUMERE_OFFSET);
  else if (strcasecmp(rsc, "sibur") == 0)
    extract(p, SIBUR_OFFSET);
  else if (strcasecmp(rsc, "mendiane") == 0)
    extract(p, MENDIANE_OFFSET);
  else if (strcasecmp(rsc, "phiras") == 0)
    extract(p, PHIRAS_OFFSET);
  else if (strcasecmp(rsc, "thystame") == 0)
    extract(p, THYSTAME_OFFSET);
  else if (strcasecmp(rsc, "food") == 0)
    extract(p, FOOD_OFFSET);
  else
    queue_packet(p, SIMPLE_PACKET, RPL_KO);
  free(clean_token);
  free(rsc);
  return (0);
}
