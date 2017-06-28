/*
** ConnectClient.h for zappy in /home/thomas/Rendu/Zappy/client/include
**
** Made by Thomas
** Login   <thomas@epitech.net>
**
** Started on  Wed Jun 28 00:50:35 2017 Thomas
// Last update Wed Jun 28 03:14:56 2017 Thomas
*/

#ifndef CONNECTCLIENT_H
# define CONNECTCLIENT_H

# include <sys/types.h>
# include <unistd.h>

class ConnectClient {

public:
  ConnectClient(int, std::string);
  ~ConnectClient();

private:
  int			_port;
  std::string		_host;
  int			_fd;
  fd_set		_fd_read;
  struct timeval	_tv;

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
