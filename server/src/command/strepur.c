/*
** epur_str.c for Project-Master in /home/guicha/tek2/Zappy/server/src/cmds
**
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
**
** Started on  Wed Jun 21 23:18:03 2017 guicha_t
** Last update Sat Jul  1 16:59:41 2017 Pierre Monge
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "h.h"

char	*strepur(char *str)
{
  char  *epur;
  int   i;
  int   j;

  i = 0;
  j = 0;
  if ((epur = malloc(strlen(str) + 1)) == NULL)
    return (zappy_exit(), NULL);
  while ((str[i] == '\t') || (str[i] == ' '))
    i = i + 1;
  while (str[i] != '\0')
    {
      epur[j++] = str[i++];
      while ((str[i] == '\t') || (str[i] == ' '))
	i = i + 1;
      if (((str[i - 1] == '\t') ||
	   (str[i - 1] == ' ')) &&
	  (str[i] != '\0'))
	{
	  epur[j] = ' ';
	  j = j + 1;
	}
    }
  epur[j] = '\0';
  return (epur);
}
