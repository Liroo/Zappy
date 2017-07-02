/*
** e_fork.c for fork in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sat Jul  1 06:14:34 2017 Pierre Monge
** Last update Sun Jul  2 08:12:43 2017 Pierre Monge
*/

#include <stdlib.h>
#include <string.h>

#include "struct.h"
#include "log.h"
#include "rfc.h"
#include "debug.h"
#include "h.h"

int		event_fork(void *data)
{
  t_waiting_egg	*waiting_egg;
  t_egg		*egg;

  waiting_egg = data;
  if (!(egg = malloc(sizeof(t_egg))))
    return ((void)zappy_exit(), 0);
  memset(egg, 0, sizeof(t_egg));
  egg->pos_x = waiting_egg->pos_x;
  egg->pos_y = waiting_egg->pos_y;
  waiting_egg->team->egg_slot++;
  list_add_tail(&egg->list, &waiting_egg->team->eggs);
  rfc_16(NULL, waiting_egg->team, egg);
  print_log("Team %s has an hatched egg on %d %d\n", waiting_egg->team->name,
	    egg->pos_x, egg->pos_y);
  free(waiting_egg);
  return (0);
}
