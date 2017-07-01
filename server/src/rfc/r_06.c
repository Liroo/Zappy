/*
** r_06.c for rfc 07 in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Fri Jun 30 22:27:42 2017 Pierre Monge
** Last update Sat Jul  1 04:29:38 2017 guicha_t
*/

#include "struct.h"
#include "rfc.h"

void		rfc_06(t_client *spectator, t_client *client)
{
  t_player	*player;

  player = client->data;
  rfc(spectator, RPL_RFC_06, client->net_info.fd,
      player->direction);
}
