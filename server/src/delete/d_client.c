/*
** d_client.c for delete_client in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sun Jun 25 00:09:45 2017 Pierre Monge
** Last update Sat Jul  1 06:57:19 2017 Pierre Monge
*/

#include <stdlib.h>

#include "debug.h"
#include "h.h"
#include "struct.h"
#include "list.h"
#include "fdlist.h"

static void	delete_player(t_player *player)
{
  int		i;

  i = 0;
  if (!player->is_from_egg)
    player->team->empty_slot++;
  while (player->command_queue[i].command && (i < COMMAND_QUEUE_SIZE))
    free(player->command_queue[i++].command);
  free(player);
}

static void	delete_admin(t_admin *admin)
{
  int		i;

  i = 0;
  while (admin->command_queue[i].command && (i < COMMAND_QUEUE_SIZE))
    free(admin->command_queue[i++].command);
  free(admin);
}

static void	delete_registered_client(t_client *client)
{
  if (client->auth_status != AUTH)
    return ;
  if (client->client_type == ADMIN)
    delete_admin(client->data);
  if (client->client_type == PLAYER)
    delete_player(client->data);
}

void		delete_client(t_client *client)
{
  t_list_head	*pos;
  t_list_head	*next;

  PRINT_DEBUG("Deletting client: %d...\n", client->net_info.fd);
  list_del(client->list.prev, client->list.next);
  fd_set_select(client->net_info.fd, FD_SELECT_NO_EVENT, NULL);
  fd_close(client->net_info.fd);
  free(client->r_packet.block);
  pos = list_get_first(&client->w_packet);
  while (pos != &client->w_packet)
    {
      next = pos->next;
      list_del(pos->prev, next);
      clear_packet(container_of(pos, t_packet, list));
      pos = next;
     }
  delete_registered_client(client);
  delete_chrono_client(client);
  free(client);
}
