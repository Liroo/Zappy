/*
** option.c for zappy in /home/thomas/Rendu/PSU_2016_zappy/server/src
**
** Made by Thomas
** Login   <thomas@epitech.net>
**
** Started on  Tue Jun 13 22:46:11 2017 Thomas
** Last update Sun Jun 18 04:24:25 2017 Thomas
*/

#ifndef OPTION_H
# define OPTION_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "struct.h"

t_game	*parse_option(int ac, char *av[], t_game *game);
void	c_opt(t_game *game, int ac, char *av[]);
void	f_opt(t_game *game, int ac, char *av[]);
void	n_opt(t_game *game, int ac, char *av[]);
void	x_opt(t_game *game, int ac, char *av[]);
void	y_opt(t_game *game, int ac, char *av[]);

#endif /* !OPTION_H */
