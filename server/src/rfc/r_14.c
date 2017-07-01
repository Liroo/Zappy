/*
** r_14.c for rfc 14 in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Fri Jun 30 22:28:33 2017 Pierre Monge
** Last update Sat Jul  1 04:57:12 2017 guicha_t
*/

#include "struct.h"
#include "rfc.h"

void		rfc_14(t_client *spectator, t_client *client,
		       char *object)
{
  rfc(spectator, RPL_RFC_14, client->net_info.fd, object);
}
