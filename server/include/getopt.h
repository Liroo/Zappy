/*
** getopt.c for zappy in /home/thomas/Rendu/PSU_2016_zappy/server/src
**
** Made by Thomas
** Login   <thomas@epitech.net>
**
** Started on  Tue Jun 13 22:46:11 2017 Thomas
** Last update Sat Jul  1 02:45:45 2017 Pierre Monge
*/

#ifndef OPTION_H
# define OPTION_H

# include "struct.h"

typedef int	(*t_option_func)(char **av[]);
typedef struct	s_option
{
  char		*short_opt;
  t_option_func	exec;
}		t_option;

extern int		getopt(int argc, char *argv[]);
void			print_help();
t_option		*getopt_list();

int	getopt_p(char **argv[]);
int	getopt_x(char **argv[]);
int	getopt_y(char **argv[]);
int	getopt_n(char **argv[]);
int	getopt_c(char **argv[]);
int	getopt_f(char **argv[]);
int	getopt_help(char **argv[]);

# define SHORT_OPT_P "p"
# define SHORT_OPT_X "x"
# define SHORT_OPT_Y "y"
# define SHORT_OPT_N "n"
# define SHORT_OPT_C "c"
# define SHORT_OPT_F "f"
# define SHORT_OPT_HELP "help"
# define SHORT_OPT_SIZE 7

# define DFL_TEAM_NAME "Trantorian"
# define DFL_OPT_C 6
# define DFL_OPT_F 100
# define DFL_OPT_P 1024
# define DFL_OPT_X 10
# define DFL_OPT_Y 10

#endif /* !OPTION_H */
