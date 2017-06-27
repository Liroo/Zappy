/*
** command_list.c for command_list in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sun Jun 25 00:41:14 2017 Pierre Monge
** Last update Mon Jun 26 20:50:13 2017 guicha_t
*/

#include "command.h"
#include "struct.h"
#include "h.h"

t_command	*get_command_list_player()
{
  static t_command	command_list[MAX_COMMAND_SIZE_PLAYER + 1] =
    {
      { "Forward", 7, &cmd_forward },
      { "Right", 5, &cmd_right },
      { "Left", 4, &cmd_left },
      { "Look", 4, &cmd_look },
      { "Inventory", 9, &cmd_inventory },
      { "Broadcast", 9, &cmd_broadcast },
      { "Connect_nbr", 11, &cmd_connect_nbr },
      { "Fork", 4, NULL },
      { "Eject", 5, &cmd_eject },
      { "Take", 4, &cmd_take },
      { "Set", 3, &cmd_set },
      { "Incantation", 11, NULL },
      { NULL, -1, NULL }
    };

  return (command_list);
}

t_command	*get_command_list_admin()
{
  static t_command	command_list[MAX_COMMAND_SIZE_ADMIN + 1] =
    {
      { NULL, -1, NULL }
    };

  return (command_list);
}
