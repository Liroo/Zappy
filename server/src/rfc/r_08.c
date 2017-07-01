/*
** r_08.c for rfc 08 in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Fri Jun 30 22:27:49 2017 Pierre Monge
** Last update Sat Jul  1 04:41:44 2017 guicha_t
*/

#include "struct.h"
#include "rfc.h"

void		rfc_08(t_client *spectator, t_client *client)
{
  rfc(spectator, RPL_RFC_08, client->net_info.fd);
}
