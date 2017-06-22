/*
** process.c for process in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Wed Jun 21 04:30:29 2017 Pierre Monge
** Last update Thu Jun 22 23:17:33 2017 Pierre Monge
*/

#include <time.h>
#include <stdio.h>
#include <string.h>

#include "struct.h"
#include "list.h"
#include "chrono.h"
#include "h.h"
#include "debug.h"

void			process_chrono_event()
{
  t_list_head		*pos;
  t_list_head		*next;
  t_chrono_queue	now;
  t_chrono_queue	*container;
  t_chrono_event_func	*chrono_event_func_list;

  pos = list_get_first(&game.chrono_queue);
  memset(&now, 0, sizeof(t_chrono_queue));
  if (clock_gettime(CLOCK_REALTIME, &now.end) == -1)
    perror("clock_gettime");
  chrono_event_func_list = get_chrono_event_func_list();
  while (pos != &game.chrono_queue)
    {
      next = pos->next;
      container = list_entry(pos, t_chrono_queue, list);
      if (compare_time(container->end, now.end) <= 0)
	{
	  chrono_event_func_list[container->event_type](container->data);
	  delete_chrono(container);
	}
      else
	container->duration = sub_time(container->end, now.end);
      pos = next;
    }
}
