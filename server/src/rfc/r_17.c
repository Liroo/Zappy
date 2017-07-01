/*
** r_17.c for rfc 17 in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sat Jul  1 16:10:34 2017 Pierre Monge
** Last update Sat Jul  1 16:16:07 2017 Pierre Monge
*/

#include "struct.h"
#include "rfc.h"

void		rfc_17(t_client *spectator, t_client *client)
{
  t_player	*player;

  player = client->data;
  rfc(spectator, RPL_RFC_17, client->net_info.fd, player->pos_x, player->pos_y);
}
