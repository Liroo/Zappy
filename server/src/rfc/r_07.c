/*
** r_07.c for Project-Master in /home/guicha/tek2/Zappy/server/src/rfc
** 
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
** 
** Started on  Sat Jul  1 04:30:03 2017 guicha_t
** Last update Sat Jul  1 04:38:40 2017 guicha_t
*/

#include "struct.h"
#include "rfc.h"

void		rfc_07(t_client *spectator, t_client *client)
{
  t_player	*player;

  player = client->data;
  rfc(spectator, RPL_RFC_07, client->net_info.fd,
      player->direction);
}
