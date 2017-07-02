//
// core.cpp for core in /home/lucas/rendu/reseau_psu/Zappy/client/zappy_client
//
// Made by Lucas
// Login   <lucas.onillon@epitech.eu>
//
// Started on  Sun Jun 25 22:01:46 2017 Lucas
// Last update Sun Jul  2 23:11:51 2017 Lucas
//

#include "zappy.hpp"
#include "core.hpp"

int     Core::launchLobby(t_sett *sett, int status)
{
  (void)sett;
  lobby = new Lobby(smgr, driver, device);
  if (lobby->setTexture(smgr, driver, lobbyGUI) == GUI_ERR)
    return (GUI_ERR);
  inLobby = true;
  while (device->run() && inLobby == true && quit == false)
    {
      switch (status)
	{
	case (LOBBY):
	  status = lobby->initLobby(sett, LOBBY);
	  break;
	case (GUI):
	  inGui = true;
	  inLobby = false;
	  port = lobby->getPort();
	  host = lobby->getHost();
	default:
	  break;
	}
      quit = lobby->getQuit();
    }
  win = (WinType)status;
  std::cout << RED << "Entering GUI..." << BLANK << std::endl;
  delete (lobby);
  return (GUI_OK);
}

int		Core::launchGUI(t_sett *s)
{
  int		winTmp;

  winTmp = win;
  gui = new Gui(smgr, driver, device);
  if (gui->setTexture(smgr, driver, lobbyGUI) == GUI_ERR)
    return (GUI_ERR);
  inGui = true;
  quit = false;
  while (device->run() && quit == false && inGui == true)
    {
      switch (winTmp)
	{
	case (GUI):
	  winTmp = (WinType)gui->initGui(port, host);
	  break;
	case (GUI_ERR):
	  return (GUI_ERR);
	default:
	  break;
	}
      quit = gui->getQuit();
    }
  win = (WinType)winTmp;
  delete (gui);
  return (GUI_OK);
}

int             Core::loopGui()
{
  t_sett        *sett = new t_sett;

  while (device->run() && quit == false)
    {
      switch (win)
	{
	case (LOBBY):
	  if (launchLobby(sett, LOBBY) == GUI_ERR)
	    return (GUI_ERR);
	  break;
	case (GUI):
	  if (launchGUI(sett) == GUI_ERR)
	    return (GUI_ERR);
	  break;
	default:
	  break;
	}

      //loopGui
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
  this->inGui = false;
  this->win = LOBBY;
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
