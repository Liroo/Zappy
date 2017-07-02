/*
** log.c for log in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Fri Jun 23 23:09:22 2017 Pierre Monge
** Last update Sun Jul  2 05:52:44 2017 guicha_t
*/

#include <stdio.h>
#include <time.h>

#include "debug.h"
#include "log.h"
#include "list.h"
#include "packet.h"
#include "struct.h"
#include "h.h"

static void	print_log_list(t_list_head *head,
			       const char * restrict format, va_list va)
{
  t_list_head	*pos;
  va_list	va_cpy;
  t_client	*c_admin;
  t_admin	*admin;

  pos = list_get_first(head);
  while (pos != head)
    {
      va_copy(va_cpy, va);
      c_admin = list_entry(pos, t_client, list);
      admin = c_admin->data;
      if (admin->disable_log == 0)
	queue_packet_va(list_entry(pos, t_client, list),
			SIMPLE_PACKET, (char *)format, va_cpy);
      pos = pos->next;
    }
}

void	print_log(const char * restrict format, ...)
{
  va_list	va;
  va_list	va_cpy;
  time_t	now;
  char		f_time[32];
  struct tm	*tm_info;

  time(&now);
  tm_info = localtime(&now);
  strftime(f_time, 26, LOG_GREEN"%H:%M.%S"LOG_CLEAR, tm_info);
  va_start(va, format);
  va_copy(va_cpy, va);
  fprintf(stderr, "[%s]: ", f_time);
  vfprintf(stderr, format, va_cpy);
  if (!game.sig_handled)
    print_log_list(&game.admins, format, va);
  va_end(va);
}
