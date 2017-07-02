/*
** packet.h for packet in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Thu Jun 15 22:17:36 2017 Pierre Monge
** Last update Sun Jul  2 22:30:55 2017 Pierre Monge
*/

#ifndef PACKET_H
# define PACKET_H

# include "list.h"

# define PACKET_SIZE_DFL 4096

# define SIMPLE_PACKET 0x0
# define DEAD_PACKET 0x1

# include <sys/socket.h>
# ifndef MSG_NOSIGNAL
#  define MSG_NOSIGNAL 0
# endif

typedef struct	s_packet
{
  char		*block;
  int		offset;
  int		size;

  char		type;

  t_list_head	list;
}		t_packet;

#endif /* !PACKET_H */
