/*
** option.c for zappy in /home/thomas/Rendu/PSU_2016_zappy/server/src
**
** Made by Thomas
** Login   <thomas@epitech.net>
**
** Started on  Tue Jun 13 22:53:02 2017 Thomas
** Last update Thu Jun 22 22:42:32 2017 Thomas
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "list.h"
#include "struct.h"
#include "option.h"

int	f_opt(t_game *game, int ac, char *av[])
{
  (void)ac;
  (void)av;
  game->freq = atoi(optarg);
  if (game->freq < 2 || game->freq > 10000)
    {
      printf("\n-f option only accepts integer values");
      printf(" between 2 and 10000\n\n");
      return (0);
    }
  return (1);
}

int	p_opt(t_game *game, int ac, char *av[])
{
  (void)ac;
  (void)av;
  game->net_info.port = atoi(optarg);
  return (1);
}

int	x_opt(t_game *game, int ac, char *av[])
{
  (void)ac;
  (void)av;
  game->map_size_x = atoi(optarg);
  if (game->map_size_x < 10 || game->map_size_x > 30)
    {
      printf("\n-x option only accepts integer values");
      printf(" between 10 and 30\n\n");
      return (0);
    }
  return (1);
}

int	y_opt(t_game *game, int ac, char *av[])
{
  (void)ac;
  (void)av;
  game->map_size_y = atoi(optarg);
  if (game->map_size_y < 10 || game->map_size_y > 30)
    {
      printf("\n-y option only accepts integer values");
      printf(" between 10 and 30\n\n");
      return (0);
    }
  return (1);
}
