/*
** cmd_left.c for Project-Master in /home/guicha/tek2/Zappy/server/src/cmds
** 
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
** 
** Started on  Wed Jun 21 01:01:36 2017 guicha_t
** Last update Fri Jun 23 03:50:16 2017 guicha_t
*/

#include "debug.h"
#include "struct.h"

int	cmd_left(t_player *p, char *token)
{
  (void)token;
  --p->direction;
  if (p->direction < 0)
    p->direction = 3;
  p->command_is_running = 1;
  return (0);
}
