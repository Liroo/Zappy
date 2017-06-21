/*
** chrono.c for chrono in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Wed Jun 21 00:04:42 2017 Pierre Monge
** Last update Wed Jun 21 06:04:53 2017 Pierre Monge
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "chrono.h"
#include "struct.h"
#include "debug.h"

int	diff_time(t_chrono_queue *c1, t_chrono_queue *c2)
{
  if (c1->end.tv_sec > c2->end.tv_sec)
    return (1);
  else if (c1->end.tv_sec < c2->end.tv_sec)
    return (-1);
  if (c1->end.tv_nsec > c2->end.tv_nsec)
    return (1);
  else if (c1->end.tv_nsec < c2->end.tv_nsec)
    return (1);
  return (0);
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
  if (chrono->start.tv_nsec + chrono->duration.tv_nsec >= BILLION)
    {
      chrono->end.tv_sec = chrono->start.tv_sec + chrono->duration.tv_sec + 1;
      chrono->end.tv_nsec = chrono->start.tv_nsec +
	chrono->duration.tv_nsec - BILLION;
    }
  else
    {
      chrono->end.tv_sec = chrono->start.tv_sec + chrono->duration.tv_sec;
      chrono->end.tv_nsec = chrono->start.tv_nsec + chrono->duration.tv_nsec;
    }
}

void		insert_chrono_queue(t_chrono_queue *chrono)
{
  t_list_head	*head;
  t_list_head	*pos;

  head = &game.chrono_queue;
  pos = list_get_first(head);
  while (pos != head)
    {
      if (diff_time(list_entry(pos, t_chrono_queue, list), chrono) == 1)
	break;
      pos = pos->next;
    }
  list_add(&(chrono->list), pos->prev, pos);
}

void			queue_chrono(int duration_s, void *data, char event_type)
{
  t_chrono_queue	*chrono;

  if (!(chrono = malloc(sizeof(t_chrono_queue))))
    return ;
  memset(chrono, 0, sizeof(t_chrono_queue));
  create_chrono(chrono, duration_s, data, event_type);
  insert_chrono_queue(chrono);
}
