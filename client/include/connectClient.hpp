/*
** ConnectClient.h for zappy in /home/thomas/Rendu/Zappy/client/include
**
** Made by Thomas
** Login   <thomas@epitech.net>
**
** Started on  Wed Jun 28 00:50:35 2017 Thomas
// Last update Sat Jul  1 18:11:03 2017 Thomas
*/

#ifndef CONNECTCLIENT_H
# define CONNECTCLIENT_H

# include <sys/types.h>
# include <unistd.h>

# include "gnl.hpp"

# define	PARAM_OK	(2)

class ConnectClient {

public:
  ConnectClient(int, std::string, bool param);
  ~ConnectClient();

private:
  int			_port;
  int			_save_port;
  std::string		_host;
  std::string		_save_host;
  int			_fd;
  fd_set		_fd_read;
  struct timeval	_tv;
  bool			_checkParam;
  std::string		_buf;
  Gnl			*_gnl;

private:
  int	clienttoserv();
  int	servtoclient();
  int	add_server_to_client();
  int	firstConnect();

public:
  int		myConnect();
  int		my_select();
  std::string	getResponse() const;
  void		clearResponse();

};

#endif
