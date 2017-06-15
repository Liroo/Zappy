/*
** event.h for event in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Thu Jun 15 03:40:33 2017 Pierre Monge
** Last update Thu Jun 15 05:56:23 2017 Pierre Monge
*/

#ifndef EVENT_H
# define EVENT_H

# define EVENT char
# define FD_SELECT_READ 0x1
# define FD_SELECT_WRITE 0x2

# include <sys/socket.h>

typedef struct	s_fdset
{
  int		highest_fd;
  fd_set	read_fds;
  fd_set	write_fds;
}		t_fdset;

extern t_fdset	fdset;

#endif /* !EVENT_H */
