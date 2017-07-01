/*
** getopt.c for getopt in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sat Jul  1 01:20:27 2017 Pierre Monge
** Last update Sat Jul  1 06:07:37 2017 Pierre Monge
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "getopt.h"
#include "struct.h"
#include "list.h"
#include "h.h"

void	print_help()
{
  printf("USAGE: ./zappy_server -p port -x width -y height"		\
	 " -n name1 name2 ... -c clientsNb -f freq\n\n"			\
	 "\tport\t\tis the port number\n"				\
	 "\twidth\t\tis the width of the world\n"			\
	 "\theight\t\tis the height of the world\n"			\
	 "\tnameX\t\tis the name of the team X (default: Trantorian)\n" \
	 "\tclientsNb\tis the number of authorized clients per team\n"	\
	 "\tfreq\t\tis the reciprocal of"				\
	 " time unit for execution of actions\n\n");
}

static void	basic_option()
{
  game.nb_client_max = DFL_OPT_C;
  game.freq = DFL_OPT_F;
  game.net_info.port = DFL_OPT_P;
  game.map_size_x = DFL_OPT_X;
  game.map_size_y = DFL_OPT_Y;
}

static void	teamopt()
{
  t_list_head	*pos;
  t_team	*team;

  pos = list_get_first(&game.teams);
  if (pos == &game.teams)
    {
      if (!(team = malloc(sizeof(t_team))))
	return ((void)zappy_exit());
      memset(team, 0, sizeof(t_team));
      if (!(team->name = strdup(DFL_TEAM_NAME)))
	return (free(team), (void)zappy_exit());
      list_init(&team->players);
      list_init(&team->eggs);
      list_add_tail(&team->list, &game.teams);
    }
  pos = list_get_first(&game.teams);
  while (pos != &game.teams)
    {
      team = list_entry(pos, t_team, list);
      team->size = team->empty_slot = game.nb_client_max;
      pos = pos->next;
    }
}

static int	parseopt(char **argv[])
{
  t_option	*options;
  int		i;
  char		*option;

  options = getopt_list();
  option = **argv;
  i = 0;
  while (i < SHORT_OPT_SIZE)
    {
      if (option[0] && option[0] == '-' && strcmp(&option[1],
						  options[i].short_opt) == 0)
	return (options[i].exec(argv));
      i++;
    }
  return (printf("\nunknown option: %s\n\n", option), -1);
}

int	getopt(int argc, char *argv[])
{
  if (argc < 1)
    return (print_help(), -1);
  basic_option();
  argv++;
  while (*argv)
    {
      if (parseopt(&argv) == -1)
	return (print_help(), -1);
    }
  teamopt();
  return (0);
}
