/*
** d_game.c for delete_game in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sun Jun 25 00:22:07 2017 Pierre Monge
** Last update Sun Jun 25 00:26:46 2017 Pierre Monge
*/

#include <stdlib.h>

#include "debug.h"
#include "struct.h"
#include "h.h"

static void	delete_client_list(t_list_head *head)
{
  t_list_head	*pos;
  t_list_head	*next;

  pos = list_get_first(head);
  while (pos != head)
    {
      next = pos->next;
      delete_client(list_entry(pos, t_client, list));
      pos = next;
    }
}

static void	delete_teams()
{
  t_list_head	*pos;
  t_list_head	*next;

  pos = list_get_first(&game.teams);
  while (pos != &game.teams)
    {
      next = pos->next;
      delete_team(list_entry(pos, t_team, list));
      pos = next;
    }
}

void	delete_game()
{
  t_list_head	*pos;
  t_list_head	*next;
  int		i;

  PRINT_DEBUG("Deleting game...\n");
  delete_teams();
  delete_client_list(&game.connection_queue);
  delete_client_list(&game.admins);
  delete_client_list(&game.spectators);
  pos = list_get_first(&game.chrono_queue);
  while (pos != &game.chrono_queue)
    {
      next = pos->next;
      free(list_entry(pos, t_chrono_queue, list));
      pos = next;
    }
  i = 0;
  while (i < (int)game.map_size_y)
    free(game.map[i++]);
  free(game.map);
}
