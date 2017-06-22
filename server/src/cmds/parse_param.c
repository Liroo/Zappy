/*
** parse_param.c for Project-Master in /home/guicha/tek2/Zappy/server/src/cmds
** 
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
** 
** Started on  Thu Jun 22 00:36:24 2017 guicha_t
** Last update Thu Jun 22 00:42:51 2017 guicha_t
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
    perror("malloc");
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
