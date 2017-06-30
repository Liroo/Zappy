/*
** r_02.c for rfc 02 in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Fri Jun 30 22:27:09 2017 Pierre Monge
** Last update Fri Jun 30 23:09:26 2017 Pierre Monge
*/

#include <stdio.h>
#include <string.h>

#include "struct.h"
#include "rfc.h"
#include "packet.h"

void		rfc_02(t_client *spectator, t_team *team)
{
  char		buffer[PACKET_SIZE_DFL];
  t_list_head	*pos;
  t_client	*client;

  pos = list_get_first(&team->players);
  memset((char *)buffer, 0, sizeof(buffer));
  sprintf(buffer, RPL_RFC_02, team->name);
  while (pos != &team->players)
    {
      client = list_entry(pos, t_client, list);
      sprintf(&buffer[strlen(buffer)], RPL_RFC_02_FD, client->net_info.fd);
      pos = pos->next;
    }
  strcat(buffer, RPL_RFC_02_END);
  rfc(spectator, buffer);
}
