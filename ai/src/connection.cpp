//
// connection.cpp for  in /home/andre/reseau/Zappy/client/src
//
// Made by andre
// Login   <andre@epitech.net>
//
// Started on  Sat Jun 17 03:26:14 2017 andre
// Last update Sun Jun 25 21:54:20 2017 andre
//

# include <stdio.h>
# include <sys/socket.h>
# include <stdlib.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <string.h>
# include "ConnectClient.h"

int	ConnectClient::add_server_to_client(ConnectClient::t_param param)
{
  int	fd;
  struct sockaddr_in	sin;

  if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
      printf("Server connection error\n");
      return (1);
    }
  sin.sin_addr.s_addr = inet_addr(param.machine);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(param.port);
  if (connect(fd, (struct sockaddr*)&sin, sizeof(sin)))
    {
      printf("Server connection error\n");
      return (1);
    }
  write(1, "Connected...\n", strlen("Connected...\n"));
  return (fd);
}

int	ConnectClient::servtoclient(int fd)
{
  char	repserv[2000];

  bzero(repserv, 2000);
  if (recv(fd, repserv, 2000, 0) < 0)
    {
      printf("Error message reception\n");
      return (1);
    }
  printf("%s", repserv);
  return (0);
}

int	ConnectClient::clienttoserv(int fd)
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
  if (send(fd, final, strlen(final), 0) < 0)
    return (printf("Message sending error\n"), 1);
  return (0);
}

int	ConnectClient::my_loop(fd_set fd_read, struct timeval tv, int fd)
{
  int	rd;

  while (1)
    {
      FD_ZERO(&fd_read);
      if (fd != 0)
      	FD_SET(fd, &fd_read);
      FD_SET(0, &fd_read);
      if (select(fd + 1, &fd_read, NULL, NULL, &tv) < 0)
	{
	  printf("Select error\n");
	  return (1);
	}
      else if (fd != 0 && FD_ISSET(fd, &fd_read))
      	{
	  if ((rd = servtoclient(fd)) != 0)
	    return (rd);
      	}
      else if (FD_ISSET(0, &fd_read))
      	{
	  if (clienttoserv(fd) == 1)
	    return (1);
      	}
    }
  return (0);
}

void	ConnectClient::usagedisp()
{
  printf("USAGE: ./zappy_client -p port -n name -h machine\n");
  printf("\tport\tis the port number\n");
  printf("\tname\tis the name of the team\n");
  printf("\tmachine\tis the name of the machine; localhost by default\n");
}

int	ConnectClient::check_param(int ac, char **av, t_param *param)
{
  if ((ac != 5 && ac != 7) || strcmp(av[1], "-p") != 0
      || strcmp(av[3], "-n") != 0)
    return (usagedisp(), 1);
  if (ac == 7)
    if (strcmp(av[5], "-h") != 0)
      return(usagedisp(), 1);
  param->port = atoi(av[2]);
  if ((param->name = (char*)malloc(strlen(av[4]))) == NULL)
    return (1);
  strcpy(param->name, av[4]);
  if ((param->machine = (char*)malloc(10 + strlen(av[6]))) == NULL)
    return (1);
  if (ac == 5)
    strcpy(param->machine, "127.0.0.1");
  else
    strcpy(param->machine, av[6]);
  return (0);
}

int			ConnectClient::myConnect(int ac, char **av)
{
  fd_set		fd_read;
  struct timeval	tv;
  int			fd;
  t_param		param;

  if (check_param(ac, av, &param) == 1)
    return (0);
  if ((fd = add_server_to_client(param)) == 1)
    return (1);
  tv.tv_sec = 1;
  tv.tv_usec = 0;
  if (my_loop(fd_read, tv, fd) == 1)
    return (1);
  close(fd);
  return (0);
}

ConnectClient::ConnectClient() {}

ConnectClient::~ConnectClient() {}
