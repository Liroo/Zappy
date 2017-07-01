/*
** countword.c for Project-Master in /home/guicha/tek2/Zappy/server/src/command/command_admin
** 
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
** 
** Started on  Sat Jul  1 21:35:24 2017 guicha_t
** Last update Sat Jul  1 21:39:55 2017 guicha_t
*/

#include "h.h"

int	my_count_word(char *str, char d)
{
  int	i;
  int	c;

  c = 0;
  i = 0;
  while (str[i] != '\0')
    {
      if (str[i] == d)
	c = c + 1;
      i = i + 1;
    }
  c = c + 1;
  return (c);
}
