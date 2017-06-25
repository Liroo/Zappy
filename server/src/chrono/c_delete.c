/*
** chrono_delete.c for chrono_delete in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Thu Jun 22 22:27:44 2017 Pierre Monge
** Last update Sat Jun 24 23:18:52 2017 Pierre Monge
*/

#include <stdlib.h>

#include "list.h"
#include "struct.h"
#include "chrono.h"

void			delete_chrono_client(t_client *client)
{
  t_list_head		*pos;
  t_list_head		*next;
  t_chrono_queue	*chrono;

  pos = list_get_first(&game.chrono_queue);
  while (pos != &game.chrono_queue)
    {
      next = pos->next;
      chrono = list_entry(pos, t_chrono_queue, list);
      if (chrono->data == (void *)client)
	{
	  list_del(pos->prev, pos->next);
	  free(chrono);
	}
      pos = next;
    }
}

void			delete_chrono(t_chrono_queue *chrono)
{
  list_del(chrono->list.prev, chrono->list.next);
  free(chrono);
}
