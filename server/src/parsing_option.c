/*
** parsing_opt.c for zaapy in /home/thomas/Rendu/PSU_2016_zappy/server/src
**
** Made by Thomas
** Login   <thomas@epitech.net>
**
** Started on  Fri Jun 16 14:59:23 2017 Thomas
** Last update Mon Jun 19 17:36:37 2017 Thomas
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "h.h"
#include "option.h"

static int	check_order_option(int ac, char *av[])
{
  int	c;

  optind = 0;
  while ((c = getopt(ac, av, "p:x:y:n:c:f:")) != -1)
    {
      if (c == 'c')
	return (0);
      else if (c == 'n')
	return (1);
    }
  return (1);
}

static int	choose_option(t_game *game, int c, int ac, char *av[])
{
  static t_option	option_list[6] = {
    c_opt, f_opt, n_opt, p_opt, x_opt, y_opt
  };
  if (optarg && optarg[0] != '-')
    option_list[c](game, ac, av);
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
  printf(" -n name1 name2 ... -c clientsNb -f freq\n");
  return (NULL);
}

t_game	*parse_option(int ac, char *av[], t_game *game)
{
  int	c;
  int	i;
  int	check;
  char	*cmp;

  cmp = strdup("cfnpxy");
  if (!av[1] || (av[1] && strcmp(av[1], "-help") == 0)
      || check_params(av, cmp) == 0)
    return (help_func());
  while ((c = getopt(ac, av, "p:x:y:n:c:f:")) != -1)
    {
      i = 0;
      check = 0;
      while (cmp && cmp[i])
	{
	  if (cmp[i] == c)
	    check = choose_option(game, i, ac, av);
	  i++;
	}
      if (check == 0)
	return (help_func());
    }
  if (game->nb_client_max != 0 && check_order_option(ac, av) == 0)
    c_opt(game, ac, av);
  return (free(cmp), game);
}
