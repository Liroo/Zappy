//
// ConnectClient.cpp for  in /home/andre/reseau/Zappy/ai/src
//
// Made by andre
// Login   <andre@epitech.net>
//
// Started on  Tue Jun 27 03:02:21 2017 andre
// Last update Tue Jun 27 03:02:22 2017 andre
//

# include <stdio.h>
# include <sys/socket.h>
# include <stdlib.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <string.h>
# include <iostream>
# include "ConnectClient.h"

int	ConnectClient::add_server_to_client()
{
  int	fd;
  struct sockaddr_in	sin;

  if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
      std::cout << "Server connection error" << std::endl;
      return (1);
    }
  sin.sin_addr.s_addr = inet_addr(_machine);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(_port);
  if (connect(fd, (struct sockaddr*)&sin, sizeof(sin)))
    {
      std::cout << "Server connection error" << std::endl;
      return (1);
    }
  std::cout << "Connected..." << std::endl;
  return (fd);
}

char	*ConnectClient::servtoclient()
{
  char	repserv[2000];

  bzero(repserv, 2000);
  if (recv(_fd, repserv, 2000, 0) < 0)
    {
      std::cout << "Error message reception" << std::endl;
      return (NULL);
    }
  return (strdup(repserv));
}

char	*ConnectClient::getResponse()
{
  while (1)
    {
      FD_ZERO(&_fd_read);
      if (_fd != 0)
      	FD_SET(_fd, &_fd_read);
      FD_SET(0, &_fd_read);
      if (select(_fd + 1, &_fd_read, NULL, NULL, &_tv) < 0)
      	{
      	  std::cout << "Select error" << std::endl;
      	  return (NULL);
      	}
      else if (_fd != 0 && FD_ISSET(_fd, &_fd_read))
        return(servtoclient());
    }
  return (NULL);
}

void	ConnectClient::usagedisp()
{
  std::cout << "USAGE: ./zappy_client -p port -n name -h machine" << std::endl <<
    "\tport\tis the port number" << std::endl << "\tname\tis the name of the team" <<
    std::endl << "\tmachine\tis the name of the machine; localhost by default"
	    << std::endl;
}

int	ConnectClient::check_param(int ac, char **av)
{
  if ((ac != 5 && ac != 7) || strcmp(av[1], "-p") != 0
      || strcmp(av[3], "-n") != 0)
    return (usagedisp(), 1);
  if (ac == 7)
    if (strcmp(av[5], "-h") != 0)
      return(usagedisp(), 1);
  _port = atoi(av[2]);
  if ((_name = (char *)malloc(strlen(av[4]))) == NULL)
    return (1);
  _name = av[4];
  if ((_machine = (char *)malloc(10 + strlen(av[6]))) == NULL)
    return (1);
  if (ac == 5)
    {
      if ((_machine = (char *)malloc(10)) == NULL)
        return (1);
      _machine = (char *)"127.0.0.1";
    }
  else
    {
      if ((_machine = (char *)malloc(strlen(av[6]))) == NULL)
        return (1);
      _machine = av[6];
    }
  return (0);
}

int     ConnectClient::sendToServ(char *message)
{
  if (send(_fd, message, strlen(message), 0) < 0) {
    std::cout << "Message sending error" << std::endl;
    return (1);
  }
  return (0);
}

int			ConnectClient::myConnect(int ac, char **av)
{
  std::size_t found_ko;
  std::string resp;
  if (check_param(ac, av) == 1)
    return (0);
  if ((_fd = add_server_to_client()) == 1)
    return (1);
  _tv.tv_sec = 1;
  _tv.tv_usec = 0;
  std::cout << getResponse();
  sendToServ(strcat(_name, "\n"));
  resp = getResponse();
  found_ko = resp.find("ko");
  std::size_t found_enter = resp.find("\n");
  std::cout << resp;
  if (found_ko != std::string::npos)
    return (1);
  if (found_enter == std::string::npos)
    std::cout << getResponse();
  return (0);
}

ConnectClient::ConnectClient() {}

ConnectClient::~ConnectClient() {}
