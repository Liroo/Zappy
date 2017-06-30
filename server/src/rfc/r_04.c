/*
** r_04.c for rfc 04 in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Fri Jun 30 22:27:26 2017 Pierre Monge
** Last update Fri Jun 30 23:13:24 2017 Pierre Monge
*/

#include "struct.h"
#include "rfc.h"

void		rfc_04(t_client *spectator, int x, int y)
{
  t_inventory	tile;

  tile = game.map[x][y];
  rfc(spectator, RPL_RFC_04,
      x, y,
      tile.linemate, tile.deraumere,
      tile.sibur, tile.mendiane,
      tile.phiras, tile.thystame,
      tile.food);
}
