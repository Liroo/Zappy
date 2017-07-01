//
// main.cpp for main in /home/lucas/rendu/reseau_psu/Zappy/client/zappy_client
//
// Made by Lucas
// Login   <lucas.onillon@epitech.eu>
//
// Started on  Sun Jun 25 23:59:42 2017 Lucas
// Last update Sat Jul  1 16:28:25 2017 Thomas
//

#include "zappy.hpp"
#include "core.hpp"

int	main()
{
  Core *core = new Core();

  if (core->initDevice() == GUI_ERR)
    return (GUI_ERR);
  if (core->initSplashScreen() == GUI_ERR)
    return (GUI_ERR);
  if (core->loopGui() == GUI_ERR)
    return (GUI_ERR);
  delete (core);
  return (GUI_OK);
}
