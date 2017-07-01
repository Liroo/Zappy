/*
** r_05.c for rfc 05 in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Fri Jun 30 22:27:36 2017 Pierre Monge
** Last update Sat Jul  1 04:24:41 2017 guicha_t
*/

#include "struct.h"
#include "rfc.h"

void		rfc_05(t_client *spectator, t_client *client)
{
  t_player	*player;

  player = client->data;
  rfc(spectator, RPL_RFC_05, client->net_info.fd,
      player->pos_x, player->pos_y);
}
