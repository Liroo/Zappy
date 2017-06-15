/*
** fdlist.c for fdlist in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Thu Jun 15 03:47:25 2017 Pierre Monge
** Last update Thu Jun 15 06:19:25 2017 Pierre Monge
*/

#include <string.h>
#include <sys/socket.h>

#include "fdlist.h"

t_fd_entry	fd_entry[MAX_CONNECTIONS + 1];

int		fd_open(int fd)
{
  t_fd_entry	*fde;

  if ((fd < 0) || (fd >= MAX_CONNECTIONS))
    return (-1);
  fde = &fd_entry[fd];
  memset(fde, 0, sizeof(t_fd_entry));
  fde->fd = fd;
  fde->is_open = 1;
  return (fd);
}

int		fd_unmap(int fd)
{
  t_fd_entry	*fde;

  if ((fd < 0) || (fd >= MAX_CONNECTIONS))
    return (-1);
  fde = &fd_entry[fd];
  if (!fde->is_open)
    return (-1);
  memset(fde, 0, sizeof(t_fd_entry));
  fde->fd = fd;
  return (fd);
}

int		fd_close(int fd)
{
  if (!fd_unmap(fd))
    return (-1);
  return (socket_close(fd));
}

int	fd_accept(int sockfd)
{
  int	fd;

  if ((fd = accept(sockfd, NULL, NULL)) < 0)
    return (-1);
  return (fd_open(fd));
}
