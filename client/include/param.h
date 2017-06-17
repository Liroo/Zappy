//
// param.h for  in /home/andre/reseau/Zappy/client/include
//
// Made by andre
// Login   <andre@epitech.net>
//
// Started on  Fri Jun 16 20:55:43 2017 andre
// Last update Sat Jun 17 03:31:24 2017 andre
//

#ifndef PARAM_H
# define PARAM_H

# include <sys/types.h>
# include <unistd.h>

typedef struct	s_param
{
  int	port;
  char	*name;
  char	*machine;
}		t_param;

extern "C" {
  int	connectClient(int, char**);
  int	check_param(int, char**, t_param*);
  void	usagedisp();
  int	my_loop(fd_set, struct timeval, int);
  int	clienttoserv(int);
  int	servtoclient(int);
  int	add_server_to_client(t_param);
}

#endif /* !PARAM_H */
