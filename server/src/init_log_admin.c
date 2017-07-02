/*
** init_log_admin.c for Project-Master in /home/guicha/tek2/Zappy/server/src
** 
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
** 
** Started on  Sun Jul  2 05:32:09 2017 guicha_t
** Last update Sun Jul  2 05:33:34 2017 guicha_t
*/

#include "struct.h"
#include "debug.h"

void	init_disable_log(t_client *client)
{
  t_admin	*admin;

  admin = client->data;
  admin->disable_log = 0;
}
