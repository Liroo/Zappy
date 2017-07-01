//
// gnl.hpp for zappy in /home/thomas/Rendu/Zappy/client/include
//
// Made by Thomas
// Login   <thomas@epitech.net>
//
// Started on  Sat Jul  1 17:58:33 2017 Thomas
// Last update Sat Jul  1 18:30:13 2017 Thomas
//

#ifndef GNL_HPP
# define GNL_HPP

# include <stdlib.h>
# include <string.h>
# include <unistd.h>

class Gnl {

public:
  Gnl();
  ~Gnl();

  char	*getnextline(const int &) const;

private:
  int	my_strlen(char *str) const;
  char	*my_gnl_realloc(char *old_str, int size) const;
  int	my_bufflen(char *buff, int opt) const;
  char	*put_to_line(char *buff) const;
  char	*mod_buff(char *buff) const;

};

#endif
