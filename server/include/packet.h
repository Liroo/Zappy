/*
** packet.h for packet in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Thu Jun 15 22:17:36 2017 Pierre Monge
** Last update Fri Jun 16 17:04:09 2017 Pierre Monge
*/

#ifndef PACKET_H
# define PACKET_H

#include "list.h"

# define PACKET_SIZE_DFL 4096

typedef struct	s_packet
{
  char		*block;
  int		offset;
  int		size;
  t_list_head	list;
}		t_packet;

#endif /* !PACKET_H */
