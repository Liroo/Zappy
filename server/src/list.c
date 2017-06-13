/*
** list.c for list in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Tue Jun 13 21:39:03 2017 Pierre Monge
** Last update Tue Jun 13 21:39:13 2017 Pierre Monge
*/

#include "list.h"

t_list_head	*list_init(t_list_head *list)
{
  list->next = list;
  list->prev = list;
  return (list);
}

t_list_head	*list_add(t_list_head *new,
			  t_list_head *prev,
			  t_list_head *next)
{
  next->prev = new;
  new->next = next;
  new->prev = prev;
  prev->next = new;
  return (new);
}

t_list_head	*list_del(t_list_head *prev,
			  t_list_head *next)
{
  next->prev = prev;
  prev->next = next;
  return (prev);
}
