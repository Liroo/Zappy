/*
** main.c for main in /Users/pierre/Epitech/PSU/Zappy
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Tue Jun 13 05:20:34 2017 Pierre Monge
** Last update Tue Jun 13 21:35:34 2017 Pierre Monge
*/

#include "debug.h"

/*
** Note: This is to remove, this is an introduction to struct.h
** and to be sure it will compile, I let this here -- Pierre
*/
#include "struct.h"

int	main(int argc,
	     char *argv[])
{
  PRINT_DEBUG("%d\n", argc);
  PRINT_DEBUG_ARRAY(argv, argc);
  return (0);
}
