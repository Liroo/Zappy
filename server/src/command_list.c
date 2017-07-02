/*
** command_list.c for command_list in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sun Jun 25 00:41:14 2017 Pierre Monge
** Last update Sun Jul  2 07:18:36 2017 guicha_t
*/

#include "debug.h"
#include "command.h"
#include "struct.h"
#include "h.h"

t_command	*get_command_list_player()
{
  static t_command	command_list[MAX_COMMAND_SIZE_PLAYER + 1] =
    {
      { "Forward", 7, 7, cmd_forward, 0 },
      { "Right", 5, 7, cmd_right, 0 },
      { "Left", 4, 7, cmd_left, 0 },
      { "Look", 4, 7, cmd_look, 0 },
      { "Inventory", 9, 1, cmd_inventory, 0 },
      { "Broadcast", 9, 7, cmd_broadcast, 0 },
      { "Connect_nbr", 11, 0, cmd_connect_nbr, 0 },
      { "Fork", 4, 42, cmd_fork, 0 },
      { "Eject", 5, 7, cmd_eject, 0 },
      { "Take", 4, 7, cmd_take, 0 },
      { "Set", 3, 7, cmd_set, 0 },
      { "Incantation", 11, 300, cmd_elevation, cmd_pre_elevation },
      { NULL, -1, 0, NULL, 0 }
    };

  return (command_list);
}

t_command	*get_command_list_admin()
{
  static t_command	command_list[MAX_COMMAND_SIZE_ADMIN + 1] =
    {
      { "getinfo", 7, 0, cmd_getplayer, 0 },
      { "mvplayer", 8, 0, cmd_mvplayer, 0 },
      { "logoff", 6, 0, cmd_disable_log, 0 },
      { "logon", 5, 0, cmd_able_log, 0 },
      { "setlevel", 8, 0, cmd_set_level, 0 },
      { NULL, -1, 0, NULL, 0 }
    };

  return (command_list);
}
