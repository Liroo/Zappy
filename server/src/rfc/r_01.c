/*
** r_01.c for rfc 01 in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Fri Jun 30 20:01:10 2017 Pierre Monge
** Last update Sun Jul  2 14:26:15 2017 Pierre Monge
*/

#include "struct.h"
#include "rfc.h"

void	rfc_01(t_client *spectator)
{
  rfc(spectator, RPL_RFC_01, game.map_size_x, game.map_size_y, game.freq);
}
