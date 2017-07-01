/*
** r_11.c for rfc 11 in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Fri Jun 30 22:28:16 2017 Pierre Monge
** Last update Sat Jul  1 04:51:15 2017 guicha_t
*/

#include "struct.h"
#include "rfc.h"

void		rfc_11(t_client *spectator, t_client *client)
{
  rfc(spectator, RPL_RFC_11, client->net_info.fd);
}
