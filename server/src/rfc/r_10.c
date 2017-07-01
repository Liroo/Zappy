/*
** r_10.c for rfc 10 in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Fri Jun 30 22:28:11 2017 Pierre Monge
** Last update Sat Jul  1 04:48:22 2017 guicha_t
*/

#include "struct.h"
#include "rfc.h"

void		rfc_10(t_client *spectator, t_client *client,
		       char *text)
{
  rfc(spectator, RPL_RFC_10, client->net_info.fd, text);
}
