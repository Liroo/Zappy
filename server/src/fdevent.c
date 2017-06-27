/*
** fdevent.c for fdevent in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Fri Jun 16 20:34:58 2017 Pierre Monge
** Last update Tue Jun 27 02:17:17 2017 Pierre Monge
*/

#include "h.h"
#include "event.h"
#include "debug.h"

EVENT	get_event_flags(int fd, fd_set read_fds, fd_set write_fds)
{
  EVENT		event_flags;

  event_flags = 0;
  if (FD_ISSET(fd, &read_fds))
    event_flags |= FD_SELECT_READ;
  if (FD_ISSET(fd, &write_fds))
    event_flags |= FD_SELECT_WRITE;
  return (event_flags);
}

void	read_event(t_client *client)
{
  int	ret;

  ret = 0;
  if (!client)
    return ;
  if ((ret = recv_packet(client)) != 0)
    {
      if (ret == -1)
	delete_client(client);
      else if (ret == -2)
	broken_pipe(client);
      return ;
    }
}

void	write_event(t_client *client)
{
  if (!client)
    return ;
  if (send_queued_packet(client) != 0 ||
      broken_pipe_empty_event(client))
    {
      delete_client(client);
      return ;
    }
}
