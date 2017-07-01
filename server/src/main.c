/*
** main.c for main in /Users/pierre/Epitech/PSU/Zappy
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Tue Jun 13 05:20:34 2017 Pierre Monge
** Last update Sat Jul  1 02:46:01 2017 Pierre Monge
*/

#include <time.h>
#include <string.h>
#include <stdlib.h>

#include "debug.h"
#include "log.h"
#include "h.h"
#include "list.h"
#include "getopt.h"
#include "struct.h"
#include "chrono.h"

t_game	game;

static void	  close_game_server()
{
  sig_set(0);
  delete_game();
}

static void		loop_game_server()
{
  struct timespec	*next_chrono;

  next_chrono = NULL;
  while (!game.sig_handled)
    {
      process_chrono_event();
      next_chrono = NULL;
      if (game.chrono_queue.next != &game.chrono_queue)
	next_chrono = (struct timespec *)
	  (&((t_chrono_queue *)list_entry(game.chrono_queue.next,
					  t_chrono_queue, list))->duration);
      process_command();
      if (fd_select(next_chrono) == -1)
	break;
    }
}

static int	init_game_server(int argc, char *argv[])
{
  memset(&game, 0, sizeof(t_game));
  fdset.highest_fd = -1;
  list_init(&game.teams);
  list_init(&game.connection_queue);
  list_init(&game.chrono_queue);
  list_init(&game.admins);
  list_init(&game.spectators);
  sig_set(1);
  if (getopt(argc, argv) == -1)
    return (-1);
  if (generate_map() == -1)
    return (-1);
  if ((game.net_info.fd = inetport(game.net_info.port)) == -1)
    return (-1);
  PRINT_LOG("Plannet Trantor was created on sector %d\n", game.net_info.port);
  return (0);
}

int	main(int argc,
	     char *argv[])
{
  if (init_game_server(argc, argv) == -1)
    return (84);
  loop_game_server();
  close_game_server();
  return (0);
}
