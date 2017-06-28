//
// main.cpp for main in /home/lucas/rendu/reseau_psu/Zappy/client/zappy_client
//
// Made by Lucas
// Login   <lucas.onillon@epitech.eu>
//
// Started on  Sun Jun 25 23:59:42 2017 Lucas
// Last update Wed Jun 28 03:45:34 2017 Thomas
//

#include "zappy.hpp"
#include "core.hpp"

int	main()
{
  Core *core = new Core();
  int port = 1024;
  std::string host = "127.0.0.1";

  if (core->initDevice() == GUI_ERR)
    return (GUI_ERR);
  if (core->initSplashScreen() == GUI_ERR)
    return (GUI_ERR);
  if (core->initConnectClient(port, host) == GUI_ERR)
    return (GUI_ERR);
  delete (core);
  return (GUI_OK);
}
