/*
** bsd.c for bsd in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Thu Jun 15 01:26:48 2017 Pierre Monge
** Last update Sun Jun 25 02:13:28 2017 Pierre Monge
*/

#include <stdlib.h>
#include <string.h>

#include "h.h"
#include "struct.h"
#include "event.h"
#include "debug.h"
#include "fdlist.h"
#include "packet.h"

#include <stdio.h>

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
    return ;
  add_connection(fd);
}

void		add_connection(int fd)
{
  t_client	*client;

  PRINT_DEBUG("incoming connection on fd: %d\n", fd);
  if (!(client = malloc(sizeof(t_client))))
    {
      socket_close(fd);
      return (void)zappy_exit();
    }
  memset(client, 0, sizeof(t_client));
  if (!(client->r_packet.block = malloc(PACKET_SIZE_DFL + 1)))
    {
      free(client);
      socket_close(fd);
      return (void)zappy_exit();
    }
  client->net_info.fd = fd;
  list_add_tail(&client->list, &game.connection_queue);
  list_init(&client->w_packet);
  client->process_r_packet = auth_client;
  fd_set_select(fd, FD_SELECT_READ, client);
  queue_packet(client, SIMPLE_PACKET, RPL_WELCOME);
  queue_chrono(AUTH_TIMEOUT(game.freq), client, C_EVENT_TIMEOUT);
}
