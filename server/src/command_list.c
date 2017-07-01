/*
** command_list.c for command_list in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sun Jun 25 00:41:14 2017 Pierre Monge
** Last update Sat Jul  1 04:54:11 2017 Pierre Monge
*/

#include "debug.h"
#include "command.h"
#include "struct.h"
#include "h.h"

t_command	*get_command_list_player()
{
  static t_command	command_list[MAX_COMMAND_SIZE_PLAYER + 1] =
    {
      { "Forward", 7, 7, &cmd_forward },
      { "Right", 5, 7, &cmd_right },
      { "Left", 4, 7, &cmd_left },
      { "Look", 4, 7, &cmd_look },
      { "Inventory", 9, 1, &cmd_inventory },
      { "Broadcast", 9, 7, &cmd_broadcast },
      { "Connect_nbr", 11, 0, &cmd_connect_nbr },
      { "Fork", 4, 42, cmd_fork },
      { "Eject", 5, 7, &cmd_eject },
      { "Take", 4, 7, &cmd_take },
      { "Set", 3, 7, &cmd_set },
      { "Incantation", 11, 300, NULL },
      { NULL, -1, 0, NULL }
    };

  return (command_list);
}

t_command	*get_command_list_admin()
{
  static t_command	command_list[MAX_COMMAND_SIZE_ADMIN + 1] =
    {
      { "getinfo", 7, 0, &cmd_getplayer },
      { NULL, -1, 0, NULL }
    };

  return (command_list);
}
