//
// gnl.cpp for zappy in /home/thomas/Rendu/Zappy/client
//
// Made by Thomas
// Login   <thomas@epitech.net>
//
// Started on  Sat Jul  1 18:01:47 2017 Thomas
// Last update Sat Jul  1 18:29:50 2017 Thomas
//

#include "gnl.hpp"

int     Gnl::my_strlen(char *str) const
{
  int   i;

  i = 0;
  while (str && str[i])
    i++;
  return (i);
}

char	*Gnl::my_gnl_realloc(char *old_str, int size) const
{
  char	*new_str;
  int	i;

  i = 0;
  if ((new_str = (char *)malloc(sizeof(char) * (size + 1))) == NULL)
    return (NULL);
  memset(new_str, 0, size + 1);
  while (old_str && old_str[i] && i != size)
    {
      new_str[i] = old_str[i];
      i++;
    }
  if (old_str)
    free(old_str);
  return (new_str);
}

int	Gnl::my_bufflen(char *buff, int opt) const
{
  int	i;

  i = 0;
  if (opt == 0)
    {
      while (buff && buff[i] && buff[i] != '\n' && buff[i] != '\0')
	i++;
      return (i);
    }
  else if (opt == 1)
    {
      while (buff && buff[i])
	{
	  if (buff[i] == '\n' || buff[i] == '\0')
	    return (1);
	  i++;
	}
      return (0);
    }
  return (0);
}

char	*Gnl::put_to_line(char *buff) const
{
  char	*str;
  int	i;

  i = 0;
  if (!buff || !buff[0] ||
      (str = (char *)malloc(sizeof(char) * (my_bufflen(buff, 0) + 1))) == NULL)
    return (NULL);
  while (buff && buff[i] && buff[i] && buff[i] != '\n' && buff[i] != '\0')
    {
      str[i] = buff[i];
      i++;
    }
  str[i] = '\0';
  return (str);
}

char	*Gnl::mod_buff(char *buff) const
{
  char	*new_buff;
  int	i;

  i = my_bufflen(buff, 0);
  if (buff[i] && (buff[i] == '\n' || buff[i] == '\0'))
    i++;
  new_buff = strdup(&buff[i]);
  free(buff);
  return (new_buff);
}

char		*Gnl::getnextline(const int &fd) const
{
  static char	*buff = NULL;
  char		tmp_string[100 + 1];
  char		*line;
  int		readed;
  int		check;

  check = 0;
  if (fd < 0)
    return (NULL);
  while (check == 0 && my_bufflen(buff, 1) == 0)
    {
      if ((readed = read(fd, tmp_string, 100)) != 0)
	{
	  tmp_string[readed] = '\0';
	  if ((buff = my_gnl_realloc(buff, my_strlen(buff) + readed)) == NULL)
	    return (NULL);
	  buff = strcat(buff, tmp_string);
	}
      check = (readed == 0 ? 1 : 0);
    }
  if ((line = put_to_line(buff)) == NULL)
    return (NULL);
  if ((buff = mod_buff(buff)) == NULL)
    return (NULL);
  return (line);
}

Gnl::Gnl() {}

Gnl::~Gnl() {}
