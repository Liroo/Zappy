/*
** r_16.c for rfc 16 in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sat Jul  1 06:22:01 2017 Pierre Monge
** Last update Sat Jul  1 06:22:45 2017 Pierre Monge
*/

#include "struct.h"
#include "rfc.h"

void	rfc_16(t_client *spectator, t_team *team, t_egg *egg)
{
  rfc(spectator, RPL_RFC_16, team->name, egg->pos_x, egg->pos_y);
}
