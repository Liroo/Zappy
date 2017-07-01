/*
** r_13.c for rfc 13 in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Fri Jun 30 22:28:28 2017 Pierre Monge
** Last update Sat Jul  1 04:55:45 2017 guicha_t
*/

#include "struct.h"
#include "rfc.h"

void		rfc_13(t_client *spectator, t_client *client,
		       char *object)
{
  rfc(spectator, RPL_RFC_13, client->net_info.fd, object);
}
