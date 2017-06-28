//
// core.cpp for core in /home/lucas/rendu/reseau_psu/Zappy/client/zappy_client
//
// Made by Lucas
// Login   <lucas.onillon@epitech.eu>
//
// Started on  Sun Jun 25 22:01:46 2017 Lucas
// Last update Wed Jun 28 01:57:08 2017 Thomas
//

#include "zappy.hpp"
#include "core.hpp"

int	Core::initConnectClient(int port, std::string host)
{
  coClient = new ConnectClient(port, host);
  if (coClient->myConnect() == GUI_ERR)
    return (GUI_ERR);
  while (1)
    {
      if (coClient->my_select() == GUI_ERR)
	return (GUI_ERR);
    }
  return (GUI_OK);
}

int    Core::initSplashScreen()
{
  ss = new Ss(smgr, driver, device);
  if (ss->setTexture(smgr, driver, lobbyGUI) == GUI_ERR)
    return (GUI_ERR);
  ss->splashScreen();
  if (ss)
    delete (ss);
  return (GUI_OK);
}

Core::Core()
{
  this->window = LOBBY;
  this->quit = false;
}

Core::~Core()
{
  this->device->drop();
}

int     Core::initDevice()
{
  if ((device = irr::createDevice(irr::video::EDT_OPENGL,
				  irr::core::dimension2d<irr::u32>(1280, 720),
			     16, false, false, false, 0)) == NULL)
    return (GUI_ERR);
  device->setWindowCaption(L"Welcome to this amazing Zappy GUI");
  device->setResizable(false);
  driver = device->getVideoDriver();
  smgr = device->getSceneManager();
  lobbyGUI = device->getGUIEnvironment();
  return (GUI_OK);
}

irr::gui::IGUIEnvironment*        Core::getLobbyGUI() const
{
  return (this->lobbyGUI);
}

irr::video::IVideoDriver*           Core::getDriver() const
{
  return (this->driver);
}

irr::scene::ISceneManager*          Core::getSceneManager() const
{
  return (this->smgr);
}
