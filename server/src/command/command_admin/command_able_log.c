/*
** command_able_log.c for Project-Master in /home/guicha/tek2/Zappy/server/src/command/command_admin
**
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
**
** Started on  Sun Jul  2 05:55:08 2017 guicha_t
** Last update Sun Jul  2 22:36:40 2017 Pierre Monge
*/

#include "command.h"
#include "struct.h"
#include "h.h"

int		cmd_able_log(t_client *client, char *token)
{
  t_admin	*admin;

  (void)token;
  admin = client->data;
  if (admin->disable_log == 1)
    {
      admin->disable_log = 0;
      queue_packet(client, SIMPLE_PACKET, "ok: Log able\n");
    }
  else
    queue_packet(client, SIMPLE_PACKET, "ko: Log already able\n");
  return (0);
}
