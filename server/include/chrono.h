/*
** chrono.h for chrono in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Wed Jun 21 00:47:44 2017 Pierre Monge
** Last update Wed Jun 21 05:51:19 2017 Pierre Monge
*/

#ifndef CHRONO_H
# define CHRONO_H

# include <time.h>

# include "list.h"

# define BILLION 1000000000

# define EVENT_LIFETIME 0x1
# define COMMAND_LIFETIME 0x2

typedef struct		s_chono_queue
{
  t_list_head		list;
  struct timespec	start;
  struct timespec	duration;
  struct timespec	end;
  void			*data;
  char			event_type;
}			t_chrono_queue;

#endif /* !CHRONO_H */
