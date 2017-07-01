/*
** getopt_list.c for getopt_list in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sat Jul  1 01:57:06 2017 Pierre Monge
** Last update Sat Jul  1 02:42:55 2017 Pierre Monge
*/

#include "getopt.h"

t_option		*getopt_list()
{
  static t_option	options[SHORT_OPT_SIZE] = {
    { SHORT_OPT_P, getopt_p },
    { SHORT_OPT_X, getopt_x },
    { SHORT_OPT_Y, getopt_y },
    { SHORT_OPT_N, getopt_n },
    { SHORT_OPT_C, getopt_c },
    { SHORT_OPT_F, getopt_f },
    { SHORT_OPT_HELP, getopt_help }
  };

  return (options);
}
