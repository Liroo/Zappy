/*
** bsd.c for bsd in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Thu Jun 15 01:26:48 2017 Pierre Monge
** Last update Thu Jun 15 06:19:42 2017 Pierre Monge
*/

#include <stdlib.h>
#include <string.h>

#include "h.h"
#include "struct.h"
#include "event.h"
#include "debug.h"
#include "fdlist.h"

int	inetport(int port)
{
  int	fd;

  PRINT_DEBUG("oppening new socket in port: %d\n", port);
  if ((fd = zappy_socket(port)) < 0)
    return (-1);
  if (socket_setopt(fd, 1) == -1)
    {
      socket_close(fd);
      return (-1);
    }
  if (zappy_bind(fd, port) == -1)
    {
      socket_close(fd);
      return (-1);
    }
  if (listen(fd, MAX_CONNECTIONS) < 0)
    {
      socket_close(fd);
      return (-1);
    }
  fd_set_select(fd, FD_SELECT_READ, NULL);
  return (fd);
}

void	accept_connection(int sock_fd)
{
  int	fd;

  if ((fd = fd_accept(sock_fd)) == -1)
    return;
  add_connection(fd);
}

void		add_connection(int fd)
{
  t_player	*pl;

  PRINT_DEBUG("incoming connection on fd: %d\n", fd);
  if (!(pl = malloc(sizeof(t_player))))
    {
      socket_close(fd);
      return ;
    }
  memset(pl, 0, sizeof(t_player));
  pl->net_info.fd = fd;
  list_add_tail(&pl->list, &game.connection_queue);
  fd_set_select(fd, FD_SELECT_READ, pl);
}
