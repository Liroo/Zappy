/*
** debug.c for debug in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Tue Jun 13 10:38:05 2017 Pierre Monge
** Last update Tue Jun 13 11:26:52 2017 Pierre Monge
*/

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "debug.h"

void		debug(const char * restrict format, ...)
{
  va_list	va;

  if (!DEBUG)
    return ;
  va_start(va, format);
  vfprintf(stderr, format, va);
  va_end(va);
}

void	debug_array(const char *fname, char * const *sarray, size_t len)
{
  if (!DEBUG)
    return ;
  fprintf(stderr, DEBUG_RED"%s:"DEBUG_CLEAR, fname);
  while (len)
    {
      fprintf(stderr, " %s", *sarray++);
      len--;
    }
  fprintf(stderr, "\n");
}
