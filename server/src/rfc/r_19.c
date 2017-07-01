/*
** r_19.c for rfc 19 in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sat Jul  1 16:15:54 2017 Pierre Monge
** Last update Sat Jul  1 16:16:28 2017 Pierre Monge
*/

#include "struct.h"
#include "rfc.h"

void		rfc_19(t_client *spectator, t_client *client, int duration)
{
  t_player	*player;

  player = client->data;
  rfc(spectator, RPL_RFC_19, client->net_info.fd, duration);
}
