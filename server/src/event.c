/*
** event.c for event in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Fri Jun 16 20:34:58 2017 Pierre Monge
** Last update Mon Jun 19 22:10:40 2017 Pierre Monge
*/

#include "h.h"
#include "event.h"

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

void	read_event(t_player *player)
{
  if (recv_packet(player) != 0)
    {
      delete_player(player);
      return ;
    }
}

void	write_event(t_player *player)
{
  send_queued_packet(player);
}
