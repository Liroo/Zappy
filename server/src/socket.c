/*
** socket.c for socket in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Tue Jun 13 21:50:17 2017 Pierre Monge
** Last update Tue Jun 20 23:04:12 2017 Pierre Monge
*/

#include <netdb.h>
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>

#include "h.h"

int			zappy_bind(int fd, int port)
{
  struct sockaddr_in	server;

  memset(&server, 0, sizeof(server));
  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  server.sin_addr.s_addr = INADDR_ANY;
  if (bind(fd, (struct sockaddr *)&server, sizeof(server)))
    {
      perror("bind");
      socket_close(fd);
      return (-1);
    }
  return (0);
}

int	socket_setopt(int fd, int socket_opt)
{
  if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &socket_opt, sizeof(int)))
    return (perror("setsockopt"), -1);
  return (0);
}

int			zappy_socket()
{
  struct protoent	*pe;
  int			fd;

  if (!(pe = getprotobyname("TCP")))
    return (fprintf(stderr, "getprotobyname"), -1);
  if ((fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) < 0)
    perror("socket");
  return (fd);
}

int	socket_close(int fd)
{
  if (close(fd) == -1)
    {
      perror("socket_close");
      return (-1);
    }
  return (0);
}
