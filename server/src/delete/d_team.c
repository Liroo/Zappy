/*
** d_team.c for delete_team in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sun Jun 25 00:19:41 2017 Pierre Monge
** Last update Sun Jun 25 00:26:27 2017 Pierre Monge
*/

#include <stdlib.h>

#include "debug.h"
#include "struct.h"
#include "h.h"

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
  free(team);
}
