//
// main.cpp for  in /home/andre/reseau/Zappy/client/src
//
// Made by andre
// Login   <andre@epitech.net>
//
// Started on  Sat Jun 17 03:17:19 2017 andre
// Last update Sun Jun 25 21:54:41 2017 andre
//

# include "Ai.h"

int	main(int ac, char **av)
{
  Ai ai;

  if (ai.connect.myConnect(ac, av) == 1)
    return (1);
  ai.aiBrain();
}
