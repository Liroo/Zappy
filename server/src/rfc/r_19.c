/*
** r_19.c for rfc 19 in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sat Jul  1 16:15:54 2017 Pierre Monge
** Last update Sun Jul  2 07:45:02 2017 Pierre Monge
*/

#include "struct.h"
#include "rfc.h"

void		rfc_19(t_client *spectator, t_client *client, int duration)
{
  rfc(spectator, RPL_RFC_19, client->net_info.fd, duration);
}
