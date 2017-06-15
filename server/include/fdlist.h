/*
** fdlist.h for fdlist in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Thu Jun 15 03:44:07 2017 Pierre Monge
** Last update Thu Jun 15 04:25:17 2017 Pierre Monge
*/

#ifndef FDLIST_H
# define FDLIST_H

# include "h.h"

typedef struct	s_fd_entry
{
  int		fd;
  char		is_open;
  int		flags;
  void     	*data;
}		t_fd_entry;

extern t_fd_entry	fd_entry[MAX_CONNECTIONS + 1];

#endif /* !FDLIST_H */
