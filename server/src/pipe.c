/*
** pipe.c for pipe in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Tue Jun 27 02:14:23 2017 Pierre Monge
** Last update Tue Jun 27 02:27:34 2017 Pierre Monge
*/

#include "h.h"
#include "struct.h"
#include "event.h"

int	broken_pipe_empty_event(t_client *client)
{
  if (!client->r_pipe_broken)
    return (0);
  if (client->client_type == PLAYER &&
      ((t_player *)(client->data))->command_in_queue == 0
      && list_empty(&client->w_packet))
    return (1);
  if (client->client_type == SPECTATOR)
    return (1);
  if (client->client_type == ADMIN &&
      ((t_admin *)(client->data))->command_in_queue == 0
      && list_empty(&client->w_packet))
    return (1);
  return (0);
}

void	broken_pipe(t_client *client)
{
  client->r_pipe_broken = 1;
  if (FD_ISSET(client->net_info.fd, &fdset.write_fds))
    fd_set_select(client->net_info.fd, FD_SELECT_WRITE, client);
  else
    fd_set_select(client->net_info.fd, FD_SELECT_NO_EVENT, client);
}
