/*
** exit.c for exit in /Users/pierre/Epitech/PSU/Zappy/server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sun Jun 25 02:07:21 2017 Pierre Monge
** Last update Sun Jul  2 06:36:21 2017 Pierre Monge
*/

#include <stdlib.h>

#include "debug.h"
#include "log.h"
#include "h.h"

int	zappy_exit()
{
  PRINT_DEBUG("Server out of memory\n");
  PRINT_LOG("Trantor suffered an alien attack and exploded...\n");
  delete_game();
  exit(84);
  return (-1);
}
