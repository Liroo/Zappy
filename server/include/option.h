/*
** option.c for zappy in /home/thomas/Rendu/PSU_2016_zappy/server/src
**
** Made by Thomas
** Login   <thomas@epitech.net>
**
** Started on  Tue Jun 13 22:46:11 2017 Thomas
** Last update Mon Jun 19 17:41:07 2017 Thomas
*/

#ifndef OPTION_H
# define OPTION_H

# include "struct.h"

typedef void	(*t_option)(t_game *game, int ac, char *av[]);

# define RAW_SHORT_OPTION "cfnpxy"
# define GETOPT_SHORT_OPTION "p:x:y:n:c:f:"

#endif /* !OPTION_H */
