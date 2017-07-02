/*
** d_team.c for delete_team in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sun Jun 25 00:19:41 2017 Pierre Monge
** Last update Sun Jul  2 07:45:01 2017 Pierre Monge
*/

#include <stdlib.h>

#include "debug.h"
#include "struct.h"
#include "h.h"

void	delete_egg(t_egg *egg)
{
  list_del(egg->list.prev, egg->list.next);
  free(egg);
}

void		delete_team(t_team *team)
{
  t_list_head	*pos;
  t_list_head	*next;

  PRINT_DEBUG("Deleting team: %s...\n", team->name);
  if (team->name)
    free(team->name);
  pos = list_get_first(&team->players);
  while (pos != &team->players)
    {
      next = pos->next;
      delete_client(list_entry(pos, t_client, list));
      pos = next;
    }
  pos = list_get_first(&team->eggs);
  while (pos != &team->eggs)
    {
      next = pos->next;
      list_del(pos->prev, pos->next);
      free(list_entry(pos, t_egg, list));
      pos = next;
    }
  free(team);
}
