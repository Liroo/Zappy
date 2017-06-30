/*
** r_03.c for rfc 03 in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Fri Jun 30 22:27:16 2017 Pierre Monge
** Last update Fri Jun 30 23:11:16 2017 Pierre Monge
*/

#include "struct.h"
#include "rfc.h"

void		rfc_03(t_client *spectator, t_client *client)
{
  t_player	*player;

  player = client->data;
  rfc(spectator, RPL_RFC_03, client->net_info.fd,
      player->pos_x, player->pos_y,
      player->direction, player->elevation,
      player->inventory.linemate, player->inventory.deraumere,
      player->inventory.sibur, player->inventory.mendiane,
      player->inventory.phiras, player->inventory.thystame,
      player->inventory.food);
}
