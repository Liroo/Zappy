/*
** r_12.c for rfc 12 in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Fri Jun 30 22:28:22 2017 Pierre Monge
** Last update Sat Jul  1 04:52:38 2017 guicha_t
*/

#include "struct.h"
#include "rfc.h"

void		rfc_12(t_client *spectator, t_client *client)
{
  rfc(spectator, RPL_RFC_12, client->net_info.fd);
}
