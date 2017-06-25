#ifndef CONNECTCLIENT_H
# define CONNECTCLIENT_H

# include <sys/types.h>
# include <unistd.h>

class ConnectClient {
public:
  ConnectClient();
  ~ConnectClient();

private:
  int	port;
  char	*name;
  char	*machine;

private:
  int	check_param(int, char**);
  void	usagedisp();
  int	my_loop(fd_set, struct timeval, int);
  int	clienttoserv(int);
  int	servtoclient(int);
  int	add_server_to_client();


public:
  int	myConnect(int, char**);
};

#endif
