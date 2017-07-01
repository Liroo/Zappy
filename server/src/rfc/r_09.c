/*
** r_09.c for rfc 09 in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Fri Jun 30 22:27:58 2017 Pierre Monge
** Last update Sat Jul  1 05:02:15 2017 guicha_t
*/

#include "struct.h"
#include "rfc.h"

void		rfc_09(t_client *spectator, t_client *client)
{
  rfc(spectator, RPL_RFC_09, client->net_info.fd);
}
