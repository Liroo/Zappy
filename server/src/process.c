/*
** process.c for process in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Wed Jun 21 04:30:29 2017 Pierre Monge
** Last update Wed Jun 21 06:08:33 2017 Pierre Monge
*/

#include "struct.h"
#include "list.h"

void		process_chrono_event()
{
  t_list_head	*pos;
  t_list_head	*next;

  pos = list_get_first(&game.chrono_queue);
  while (pos != &game.chrono_queue)
    {
      next = pos->next;
      // get actual time
      // all packet that are in the past should be handle
      // the future packet should refresh
      pos = next;
    }
}
