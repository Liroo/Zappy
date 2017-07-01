//
// ConnectClient.cpp for  in /home/andre/reseau/Zappy/ai/src
//
// Made by andre
// Login   <andre@epitech.net>
//
// Started on  Tue Jun 27 03:02:21 2017 andre
// Last update Sat Jul  1 03:14:33 2017 Thomas
//

# include <stdio.h>
# include <sys/socket.h>
# include <stdlib.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <string.h>
# include <iostream>
# include "connectClient.hpp"

int	ConnectClient::add_server_to_client()
{
  struct sockaddr_in	sin;

  if ((_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
      std::cout << "Server connection error" << std::endl;
      return (1);
    }
  sin.sin_addr.s_addr = inet_addr(_host.c_str());
  sin.sin_family = AF_INET;
  sin.sin_port = htons(_port);
  if (connect(_fd, (struct sockaddr*)&sin, sizeof(sin)))
    {
      std::cout << "Server connection error" << std::endl;
      return (1);
    }
  std::cout << "Connected..." << std::endl;
  if (this->_checkParam == true)
    return (PARAM_OK);
  return (0);
}

int	ConnectClient::servtoclient()
{
  char	repserv[2000];

  bzero(repserv, 2000);
  if (recv(_fd, repserv, 2000, 0) < 0)
    {
      std::cout << "Error message reception" << std::endl;
      return (1);
    }
  printf("%s", repserv); // Pour debug, a enlever sinon
  _buf = repserv;
  return (0);
}

int	ConnectClient::clienttoserv()
{
  char	message[1000];
  char	final[1000];
  int	i;
  int	y;

  i = 0;
  y = 0;
  bzero(message, 1000);
  if (read(0, (char *)message, 998) < 0)
    return (1);
  if (message[0] == '\n')
    return (0);
  message[strlen(message) - 1] = '\0';
  sprintf(message, "%s\r\n", message);
  if (message[0] == '/')
    i++;
  while (message[i] != '\0')
    final[y++] = message[i++];
  final[y] = message[i];
  if (send(_fd, final, strlen(final), 0) < 0)
    return (std::cout << "Message sending error" << std::endl, 1);
  return (0);
}

int	ConnectClient::my_select()
{
  int	rd;

  FD_ZERO(&_fd_read);
  if (_fd != 0)
    FD_SET(_fd, &_fd_read);
  FD_SET(0, &_fd_read);
  if (select(_fd + 1, &_fd_read, NULL, NULL, &_tv) < 0)
    {
      std::cout << "Select error" << std::endl;
      return (1);
    }
  else if (_fd != 0 && FD_ISSET(_fd, &_fd_read))
    {
      if ((rd = servtoclient()) != 0)
	return (rd);
    }
  else if (FD_ISSET(0, &_fd_read))
    {
      if (clienttoserv() == 1)
	return (1);
    }
  return (0);
}

int			ConnectClient::firstConnect()
{
  std::string	msg;

  msg = "spectator\nspectator\n";
  if (send(_fd, msg.c_str(), msg.size(), 0) < 0)
    return (std::cout << "Message sending error" << std::endl, 1);
  return (0);
}

int			ConnectClient::myConnect()
{
  int	ret;
  int	i;

  i = 0;
  ret = 0;
  if ((ret = add_server_to_client()) == 1)
    return (-1);
  else if (ret == PARAM_OK)
    return (0);
  while (firstConnect() == 1 && i < 20)
    i++;
  if (i >= 20)
    return (-1);
  return (0);
}

ConnectClient::ConnectClient(int port, std::string host, bool param) {
  _port = port;
  _host = host;
  _tv.tv_sec = 5;
  _tv.tv_usec = 0;
  _checkParam = param;
}

ConnectClient::~ConnectClient() {
  close(_fd);
}
