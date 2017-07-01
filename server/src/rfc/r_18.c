/*
** r_18.c for rfc 18 in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sat Jul  1 16:12:17 2017 Pierre Monge
** Last update Sat Jul  1 16:16:03 2017 Pierre Monge
*/

#include "struct.h"
#include "rfc.h"

void		rfc_18(t_client *spectator, t_client *client)
{
  t_player	*player;

  player = client->data;
  rfc(spectator, RPL_RFC_18, client->net_info.fd, player->elevation);
}
