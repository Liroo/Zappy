/*
** r_14.c for rfc 14 in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Fri Jun 30 22:28:33 2017 Pierre Monge
** Last update Sat Jul  1 07:03:45 2017 Pierre Monge
*/

#include "struct.h"
#include "rfc.h"

void		rfc_15(t_client *spectator, t_client *client)
{
  t_player	*player;

  player = client->data;
  rfc(spectator, RPL_RFC_15, client->net_info.fd, player->pos_x, player->pos_y);
}
