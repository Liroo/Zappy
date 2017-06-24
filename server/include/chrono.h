/*
** chrono.h for chrono in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Wed Jun 21 00:47:44 2017 Pierre Monge
** Last update Thu Jun 22 22:50:01 2017 Pierre Monge
*/

#ifndef CHRONO_H
# define CHRONO_H

# include <time.h>

# include "list.h"

# define BILLION 1000000000

typedef struct		s_chono_queue
{
  t_list_head		list;
  struct timespec	start;
  struct timespec	duration;
  struct timespec	end;
  void			*data;
  int			event_type;
}			t_chrono_queue;

# include "struct.h"
typedef void	(*t_chrono_event_func)(void *data);

# define C_EVENT_TIMEOUT 0
# define C_EVENT_LIFETIME 1
# define C_EVENT_COMMAND 2

# define MAX_C_EVENT_SIZE 3

#endif /* !CHRONO_H */
