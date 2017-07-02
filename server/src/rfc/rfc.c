/*
** rfc.c for rfc in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Fri Jun 30 19:35:57 2017 Pierre Monge
** Last update Sun Jul  2 22:35:57 2017 Pierre Monge
*/

#include <stdarg.h>

#include "list.h"
#include "packet.h"
#include "struct.h"
#include "h.h"

static void	print_log_list(t_list_head *head,
			       const char * restrict format, va_list va)
{
  t_list_head	*pos;
  va_list	va_cpy;

  pos = list_get_first(head);
  while (pos != head)
    {
      va_copy(va_cpy, va);
      queue_packet_va(list_entry(pos, t_client, list), SIMPLE_PACKET,
		      (char *)format, va_cpy);
      pos = pos->next;
    }
}

void		rfc(t_client *spectator, const char * restrict format, ...)
{
  va_list	va;
  va_list	va_cpy;

  va_start(va, format);
  va_copy(va_cpy, va);
  if (!game.sig_handled && spectator)
    queue_packet_va(spectator, SIMPLE_PACKET, (char *)format, va_cpy);
  else if (!game.sig_handled)
    print_log_list(&game.spectators, format, va);
  va_end(va);
}
