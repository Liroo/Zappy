/*
** parse_param.c for Project-Master in /home/guicha/tek2/Zappy/server/src/cmds
**
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
**
** Started on  Thu Jun 22 00:36:24 2017 guicha_t
** Last update Sat Jul  1 17:01:06 2017 Pierre Monge
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "debug.h"
#include "h.h"
#include "struct.h"

char	*parse_param(char *token)
{
  char	*param;
  int	i;
  int	i_p;

  if ((param = malloc(sizeof(char) * strlen(token))) == NULL)
    return (zappy_exit(), NULL);
  memset(param, '\0', strlen(token));
  i = 0;
  i_p = 0;
  while (token[i] != ' ')
    i++;
  i++;
  while (token[i] != ' ' && token[i] != '\0')
    {
      param[i_p] = token[i];
      i_p++;
      i++;
    }
  return (param);
}
