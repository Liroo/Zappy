/*
** main.c for main in /Users/pierre/Epitech/PSU/Zappy
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Tue Jun 13 05:20:34 2017 Pierre Monge
** Last update Tue Jun 13 11:22:47 2017 Pierre Monge
*/

#include "debug.h"

int	main(int argc,
	     char *argv[])
{
  PRINT_DEBUG("%d\n", argc);
  PRINT_DEBUG_ARRAY(argv, argc);
  return (0);
}
