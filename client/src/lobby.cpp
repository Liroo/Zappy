//
// lobby.cpp for lobby in /home/lucas/rendu/reseau_psu/Zappy/client
//
// Made by Lucas
// Login   <lucas.onillon@epitech.eu>
//
// Started on  Wed Jun 28 00:39:03 2017 Lucas
// Last update Sat Jul  1 04:14:01 2017 Lucas
//

#include "lobby.hpp"
#include "eventGesture.hpp"

void	Lobby::makeTextfields()
{
  lobbyGUI->addImage(getHostL(), irr::core::vector2d<irr::s32>(100,250));
  lobbyGUI->addImage(getPortL(), irr::core::vector2d<irr::s32>(700,250));
  hostTF = lobbyGUI->addEditBox(
				L"", irr::core::rect<irr::s32>(225,360,425,400), true,
				NULL, GUI_ID_HOST_TF);
  portTF = lobbyGUI->addEditBox(
  				L"", irr::core::rect<irr::s32>(825,360,1025,400), true,
				NULL, GUI_ID_PORT_TF);
  connectBtt = lobbyGUI->addButton(
				   irr::core::rect<irr::s32>(475, 500, 750, 600),
				   0, GUI_ID_CONNECT_BUTTON, L"");
  connectBtt->setImage(driver->getTexture(CONNECTL_PATH));
}

void	Lobby::makeLobbySkybox()
{
  driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, false);
  skybox = sm->addSkyBoxSceneNode(getSbMountUp(),
				  getSbMountDown(),
				  getSbMountRight(),
				  getSbMountLeft(),
				  getSbMountFront(),
				  getSbMountBack());
  driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, true);
}

void	Lobby::lobbyRemove()
{
  lobbyGUI->clear();
}

int	Lobby::initLobby(t_sett *sett, int status)
{
  Event	event;
  const wchar_t	*host;
  const wchar_t	*port;
  std::wstring	ws;

  makeLobbySkybox();
  makeTextfields();
  device->setEventReceiver(&event);
  while (device->run() && status == LOBBY && quit == false)
    {
      driver->beginScene(true, true, irr::video::SColor(255, 38, 196, 236));
      quit = event.getQuit();
      sm->drawAll();
      lobbyGUI->drawAll();
      driver->endScene();
      if (event.getPressConnect() == true)
	{
	  host = hostTF->getText();
	  port = portTF->getText();
	  ws = host;
	  std::string check_host(ws.begin(), ws.end());
	  ws = port;
	  std::string check_port(ws.begin(), ws.end());
	  if (!isDigits(check_port) || check_port.empty() == true || check_host.empty() == true)
	    lobbyGUI->addMessageBox(L"Syntax error", L"Wrong connection informations !", true);
	  else
	    {
	      checkConnect = new ConnectClient(std::stoi(check_port, nullptr, 10), check_host, true);
	      if (checkConnect->myConnect() == 0)
		status = GUI;
	      else
		lobbyGUI->addMessageBox(L"Internal error", L"Connection failed !", true);
	      delete (checkConnect);
	    }
	  check_port.clear();
	  check_host.clear();
	  event.setPressConnect(false);
	}
    }
  lobbyRemove();
  return (status);
}

bool	Lobby::getQuit() const
{
  return (this->quit);
}

bool	Lobby::isDigits(const std::string &str)
{
  return str.find_first_not_of("0123456789") == std::string::npos;
}

Lobby::Lobby(irr::scene::ISceneManager* sm_, irr::video::IVideoDriver* driver_,
	     irr::IrrlichtDevice* device_)
{
  this->sm = sm_;
  this->driver = driver_;
  this->device = device_;
  this->lobbyGUI = device->getGUIEnvironment();
  this->quit = false;
  win = LOBBY;
}

Lobby::~Lobby()
{}
