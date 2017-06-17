/*
** main.c for main in /Users/pierre/Epitech/PSU/Zappy
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Tue Jun 13 05:20:34 2017 Pierre Monge
** Last update Fri Jun 16 03:48:07 2017 Pierre Monge
*/

#include <string.h>

#include "debug.h"
#include "h.h"
#include "list.h"

/*
** Note: This is to remove, this is an introduction to struct.h
** and to be sure it will compile, I let this here -- Pierre
*/
#include "struct.h"

t_game	game;

static void	  close_game_server()
{
  sig_set(0);
}

static void	loop_game_server()
{
  while (!game.sig_handled)
    {
      // time pass to fd_select is to determine depends on binary option -t
      if (fd_select(10000) == -1)
	break;
      // here we should process client (execute commands depends on time etc..)
    }
}

static int	init_game_server(int argc, char *argv[])
{
  memset(&game, 0, sizeof(t_game));
  fdset.highest_fd = -1;
  list_init(&game.teams);
  list_init(&game.connection_queue);
  sig_set(1);

  // hard encoded port
  // we need to parse option to know things like this
  (&game)->net_info.port = 1024;
  (void)argc;
  (void)argv;

  if ((game.net_info.fd = inetport(game.net_info.port)) == -1)
    return (-1);
  return (0);
}

int	main(int argc,
	     char *argv[])
{
  PRINT_DEBUG("%d\n", argc);
  PRINT_DEBUG_ARRAY(argv, argc);
  if (init_game_server(argc, argv) == -1)
    return (84);
  loop_game_server();
  close_game_server();
  return (0);
}
