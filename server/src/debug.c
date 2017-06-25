/*
** debug.c for debug in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Tue Jun 13 10:38:05 2017 Pierre Monge
** Last update Sat Jun 24 23:57:11 2017 Pierre Monge
*/

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "debug.h"
#include "list.h"
#include "struct.h"
#include "h.h"

void		debug(const char * restrict format, ...)
{
  va_list	va;
  va_list	va_cpy;
  t_list_head	*pos;

  if (!DEBUG)
    return ;
  pos = list_get_first(&game.admins);
  va_start(va, format);
  va_copy(va_cpy, va);
  vfprintf(stderr, format, va_cpy);
  if (!game.sig_handled)
    {
      while (pos != &game.admins)
	{
	  va_copy(va_cpy, va);
	  queue_packet_va(list_entry(pos, t_client, list), SIMPLE_PACKET,
			  (char *)format, va_cpy);
	  pos = pos->next;
	}
    }
  va_end(va);
}
