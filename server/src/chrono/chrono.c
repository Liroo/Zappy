/*
** chrono.c for chrono in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Wed Jun 21 00:04:42 2017 Pierre Monge
** Last update Sat Jul  1 06:12:07 2017 Pierre Monge
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "chrono.h"
#include "struct.h"
#include "debug.h"
#include "h.h"

t_chrono_event_func		*get_chrono_event_func_list()
{
  static t_chrono_event_func	chrono_event_func_list[MAX_C_EVENT_SIZE] = {
    event_timeout, event_lifetime, event_command, event_fork
  };

  return (chrono_event_func_list);
}

void	create_chrono(t_chrono_queue *chrono, int duration_s,
		      void *data, char event_type)
{
  chrono->event_type = event_type;
  chrono->data = data;
  if (clock_gettime(CLOCK_REALTIME, &chrono->start) == -1)
    perror("clock_gettime");
  chrono->duration.tv_sec = duration_s / game.freq;
  chrono->duration.tv_nsec = (((double)duration_s / (double)game.freq) -
		      (double)(duration_s / game.freq)) * BILLION;
  chrono->end = add_time(chrono->start, chrono->duration);
}

void		insert_chrono_queue(t_chrono_queue *chrono)
{
  t_list_head	*head;
  t_list_head	*pos;

  head = &game.chrono_queue;
  pos = list_get_first(head);
  while (pos != head)
    {
      if (compare_time(((t_chrono_queue *)list_entry(pos, t_chrono_queue,
						   list))->end,
		       chrono->end) == 1)
	break;
      pos = pos->next;
    }
  list_add(&(chrono->list), pos->prev, pos);
}

void			queue_chrono(int duration_s, void *data, char event_type)
{
  t_chrono_queue	*chrono;

  if (!(chrono = malloc(sizeof(t_chrono_queue))))
    return (void)zappy_exit();
  memset(chrono, 0, sizeof(t_chrono_queue));
  create_chrono(chrono, duration_s, data, event_type);
  insert_chrono_queue(chrono);
}
