/*
** ConnectClient.h for zappy in /home/thomas/Rendu/Zappy/client/include
**
** Made by Thomas
** Login   <thomas@epitech.net>
**
** Started on  Wed Jun 28 00:50:35 2017 Thomas
// Last update Sat Jul  1 02:10:59 2017 Lucas
*/

#ifndef CONNECTCLIENT_H
# define CONNECTCLIENT_H

# include <sys/types.h>
# include <unistd.h>

# define	PARAM_OK	(2)

class ConnectClient {

public:
  ConnectClient(int, std::string, bool param);
  ~ConnectClient();

private:
  int			_port;
  std::string		_host;
  int			_fd;
  fd_set		_fd_read;
  struct timeval	_tv;
  bool			_checkParam;

private:
  int	clienttoserv();
  int	servtoclient();
  int	add_server_to_client();
  int	firstConnect();

public:
  int	myConnect();
  int	my_select();

};

#endif
