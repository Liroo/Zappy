/*
** Connect.h for Project-Master in /home/guicha/tek2/Zappy/admin/inc
** 
** Made by guicha_t
** Login   <thomas.guichard@epitech.eu>
** 
** Started on  Fri Jun 30 19:49:40 2017 guicha_t
** Last update Fri Jun 30 20:32:06 2017 guicha_t
*/

#ifndef _CONNECT_H
# define _CONNECT_H

#include <sys/types.h>
#include <unistd.h>

class	Connect
{
 public:
  Connect();
  ~Connect();

 private:
  int	port;
  char	*machine;

 private:
  int	check_param(int, char **);
  void	usagedisp();
  int	my_loop(fd_set, struct timeval, int);
  int	clienttoserv(int);
  int	servtoclient(int);
  int	add_server_to_client();

 public:
  int	myConnect(int, char **);
};

#endif
