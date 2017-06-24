/*
** parsing_opt.c for zaapy in /home/thomas/Rendu/PSU_2016_zappy/server/src
**
** Made by Thomas
** Login   <thomas@epitech.net>
**
** Started on  Fri Jun 16 14:59:23 2017 Thomas
** Last update Sat Jun 24 02:41:42 2017 Thomas
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "h.h"
#include "option.h"

static int	choose_option(t_game *game, int c, int ac, char *av[])
{
  static t_option	option_list[6] = {
    c_opt, f_opt, n_opt, p_opt, x_opt, y_opt
  };
  if (optarg && optarg[0] != '-')
    {
      if (option_list[c](game, ac, av) == 0)
	return (0);
    }
  else
    optind--;
  return (1);
}

static int	check_params(char *av[], char *cmp)
{
  int	i;
  int	j;
  int	check;

  i = 1;
  check = 0;
  while (av[i])
    {
      if (av[i][0] && av[i][0] == '-' && av[i][1])
	{
	  j = 0;
	  while (cmp && cmp[j])
	    {
	      if (cmp[j] == av[i][1])
		check = cmp[j];
	      j++;
	    }
	}
      else if (av[i][0] && av[i][0] != '-' && check == 0 && check != 'n')
	return (0);
      else
	check = (check == 'n') ? check : 0;
      i++;
    }
  return (1);
}

static void	*help_func()
{
  printf("USAGE: ./zappy_server -p port -x width -y height");
  printf(" -n name1 name2 ... -c clientsNb -f freq\n\n");
  printf("\tport\t\tis the port number\n");
  printf("\twidth\t\tis the width of the world\n");
  printf("\theight\t\tis the height of the world\n");
  printf("\tnameX\t\tis the name of the team X (default: Trantorian)\n");
  printf("\tclientsNb\tis the number of authorized clients per team\n");
  printf("\tfreq\t\tis the reciprocal of");
  printf(" time unit for execution of actions\n\n");
  return (NULL);
}

t_game	*parse_option(int ac, char *av[], t_game *game)
{
  int	c;
  int	i;
  int	check;

  init_opt(game);
  if ((av[1] && strcmp(av[1], "-help") == 0)
      || check_params(av, RAW_SHORT_OPTION) == 0)
    return (help_func());
  while ((c = getopt(ac, av, GETOPT_SHORT_OPTION)) != -1)
    {
      i = 0;
      check = 0;
      while (RAW_SHORT_OPTION[i])
	{
	  if (RAW_SHORT_OPTION[i] == c)
	    check = choose_option(game, i, ac, av);
	  i++;
	}
      if (check == 0)
	return (help_func());
    }
  check = -1;
  if (game->nb_client_max != 0)
    c_opt(game, check, av);
  return (game);
}
