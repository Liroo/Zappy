/*
** r_20.c for rfc 20 in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sun Jul  2 06:50:43 2017 Pierre Monge
** Last update Sun Jul  2 06:51:09 2017 Pierre Monge
*/

#include "struct.h"
#include "rfc.h"

void		rfc_20(t_client *spectator, t_team *team)
{
  rfc(spectator, RPL_RFC_20, team->name);
}
