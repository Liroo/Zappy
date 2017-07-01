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
  sin.sin_addr.s_addr = inet_addr(machine);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
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
  if (recv(fd, repserv, 2000, 0) < 0)
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
      FD_ZERO(&fd_read);
      if (fd != 0)
      	FD_SET(fd, &fd_read);
      FD_SET(0, &fd_read);
      if (select(fd + 1, &fd_read, NULL, NULL, &tv) < 0)
      	{
      	  std::cout << "Select error" << std::endl;
      	  return (NULL);
      	}
      else if (fd != 0 && FD_ISSET(fd, &fd_read))
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
  port = atoi(av[2]);
  if ((name = (char*)malloc(strlen(av[4]))) == NULL)
    return (1);
  strcpy(name, av[4]);
  if ((machine = (char*)malloc(10 + strlen(av[6]))) == NULL)
    return (1);
  if (ac == 5)
    strcpy(machine, "127.0.0.1");
  else
    strcpy(machine, av[6]);
  return (0);
}

int     ConnectClient::sendToServ(char *message)
{
  sprintf(message, "%s\r\n", message);
  if (send(fd, message, strlen(message), 0) < 0) {
    std::cout << "Message sending error" << std::endl;
    return (1);
  }
  return (0);
}

int			ConnectClient::myConnect(int ac, char **av)
{
  if (check_param(ac, av) == 1)
    return (0);
  if ((fd = add_server_to_client()) == 1)
    return (1);
  tv.tv_sec = 1;
  tv.tv_usec = 0;
  std::cout << "-----------" << getResponse() << '\n';
  sendToServ(strdup("toto"));
  std::cout << "-----------" << getResponse() << '\n';
  std::cout << "-----------" << getResponse() << '\n';
  return (0);
}

ConnectClient::ConnectClient() {}

ConnectClient::~ConnectClient() {}
