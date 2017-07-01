//
// lobby.cpp for lobby in /home/lucas/rendu/reseau_psu/Zappy/client
//
// Made by Lucas
// Login   <lucas.onillon@epitech.eu>
//
// Started on  Wed Jun 28 00:39:03 2017 Lucas
// Last update Sat Jul  1 03:25:13 2017 Thomas
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
	  checkConnect = new ConnectClient(std::stoi(check_port, nullptr, 10), check_host, true);
	  if (checkConnect->myConnect() == 0)
	    std::cout << "$OK$\n" << std::endl;
	  else
	    std::cout << "$KO$\n" << std::endl;
	  delete (checkConnect);
	  status = GUI;
	}
    }
  lobbyRemove();
  return (status);
}

bool	Lobby::getQuit() const
{
  return (this->quit);
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
