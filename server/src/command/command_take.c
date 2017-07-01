/*
** cmd_take.c for Project-Master in /home/guicha/tek2/Zappy/server/src/cmds
**
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
**
** Started on  Wed Jun 21 02:09:58 2017 guicha_t
** Last update Sat Jul  1 05:08:24 2017 guicha_t
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "debug.h"
#include "game.h"
#include "chrono.h"
#include "h.h"
#include "struct.h"
#include "packet.h"
#include "log.h"

void	extract(t_player *p, t_client *client, int offset, char *rsc)
{
  if (*(((char *)&game.map[p->pos_x][p->pos_y]) + offset) <= 0)
    queue_packet(client, SIMPLE_PACKET, RPL_KO);
  else
    {
      REMOVE_OBJECT(&game.map[p->pos_x][p->pos_y], offset);
      INSERT_OBJECT(&p->inventory, offset);
      print_log("Player %d from %s: TAKE [%s].\n",
		client->net_info.fd,
		p->team->name,
		rsc);
      queue_packet(client, SIMPLE_PACKET, RPL_OK);
    }
}

void	take_picking(char *rsc, t_client *client, t_player *p)
{
  if (strcasecmp(rsc, "linemate") == 0)
    extract(p, client, LINEMATE_OFFSET, rsc);
  else if (strcasecmp(rsc, "deraumere") == 0)
    extract(p, client, DERAUMERE_OFFSET, rsc);
  else if (strcasecmp(rsc, "sibur") == 0)
    extract(p, client, SIBUR_OFFSET, rsc);
  else if (strcasecmp(rsc, "mendiane") == 0)
    extract(p, client, MENDIANE_OFFSET, rsc);
  else if (strcasecmp(rsc, "phiras") == 0)
    extract(p, client, PHIRAS_OFFSET, rsc);
  else if (strcasecmp(rsc, "thystame") == 0)
    extract(p, client, THYSTAME_OFFSET, rsc);
  else if (strcasecmp(rsc, "food") == 0)
    extract(p, client, FOOD_OFFSET, rsc);
  else
    queue_packet(client, SIMPLE_PACKET, RPL_KO);
}

int	cmd_take(t_client *client, char *token)
{
  char		*rsc;
  char		*clean_token;
  t_player	*p;

  p = client->data;
  clean_token = strepur(token);
  rsc = parse_param(clean_token);
  take_picking(rsc, client, p);
  free(clean_token);
  free(rsc);
  return (0);
}
