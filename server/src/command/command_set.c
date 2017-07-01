/*
** cmd_set.c for Project-Master in /home/guicha/tek2/Zappy/server/src/cmds
**
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
**
** Started on  Thu Jun 22 00:49:52 2017 guicha_t
** Last update Sat Jul  1 07:45:28 2017 Pierre Monge
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
#include "log.h"
#include "rfc.h"

void		deposit_on_tile(t_player *p, t_client *c,
				int offset, char *rsc)
{
  if (*(((char *)&p->inventory) + offset) <= 0)
    queue_packet(c, SIMPLE_PACKET, RPL_KO);
  else
    {
      REMOVE_OBJECT(&p->inventory, offset);
      INSERT_OBJECT(&game.map[p->pos_x][p->pos_y], offset);
      print_log("Player %d from %s: SET [%s]\n",
		c->net_info.fd,
		p->team->name,
		rsc);
      rfc_14(NULL, c, rsc);
      rfc_map(NULL);
      queue_packet(c, SIMPLE_PACKET, RPL_OK);
    }
}

void		set_picking(char *rsc, t_client *client, t_player *p)
{
  if (strcasecmp(rsc, "linemate") == 0)
    deposit_on_tile(p, client, LINEMATE_OFFSET, rsc);
  else if (strcasecmp(rsc, "deraumere") == 0)
    deposit_on_tile(p, client, DERAUMERE_OFFSET, rsc);
  else if (strcasecmp(rsc, "sibur") == 0)
    deposit_on_tile(p, client, SIBUR_OFFSET, rsc);
  else if (strcasecmp(rsc, "mendiane") == 0)
    deposit_on_tile(p, client, MENDIANE_OFFSET, rsc);
  else if (strcasecmp(rsc, "phiras") == 0)
    deposit_on_tile(p, client, PHIRAS_OFFSET, rsc);
  else if (strcasecmp(rsc, "thystame") == 0)
    deposit_on_tile(p, client, THYSTAME_OFFSET, rsc);
  else if (strcasecmp(rsc, "food") == 0)
    deposit_on_tile(p, client, FOOD_OFFSET, rsc);
  else
    queue_packet(client, SIMPLE_PACKET, RPL_KO);
}

int		cmd_set(t_client *client, char *token)
{
  char          *rsc;
  char          *clean_token;
  t_player	*p;

  p = client->data;
  clean_token = strepur(token);
  rsc = parse_param(clean_token);
  set_picking(rsc, client, p);
  free(clean_token);
  free(rsc);
  return (0);
}
