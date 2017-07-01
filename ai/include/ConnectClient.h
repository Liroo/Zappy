#ifndef CONNECTCLIENT_H
# define CONNECTCLIENT_H

# include <sys/types.h>
# include <unistd.h>

class ConnectClient {
public:
  ConnectClient();
  ~ConnectClient();

private:
  int						 _port;
  char					 *_name;
  char					 *_machine;
  fd_set				 _fd_read;
  int						 _fd;
  struct timeval _tv;

private:
  int	  check_param(int, char**);
  void	usagedisp();
  char	*servtoclient();
  int	  add_server_to_client();

public:
  char	*getResponse();
  int		sendToServ(char *);


public:
  int	myConnect(int, char**);
};

#endif
