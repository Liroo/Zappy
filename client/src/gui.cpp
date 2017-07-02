//
// gui.cpp for gui in /home/lucas/Zappy/client
//
// Made by Lucas
// Login   <lucas.onillon@epitech.eu>
//
// Started on  Fri Jun 30 05:14:07 2017 Lucas
// Last update Sun Jul  2 14:59:47 2017 Thomas
//

#include "gui.hpp"

void		Gui::makeGuiSkybox()
{
  driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, false);
  skybox = smgr->addSkyBoxSceneNode(getSbMountUp(),
				  getSbMountDown(),
				  getSbMountRight(),
				  getSbMountLeft(),
				  getSbMountFront(),
				  getSbMountBack());
  driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, true);
}

void		Gui::guiRemove()
{
  envGUI->clear();
}

void		Gui::makeCamera(int type)
{
  guiCamera = smgr->addCameraSceneNode(0, irr::core::vector3df(0,0,1200),
				       irr::core::vector3df(0,60,-400));
  device->getCursorControl()->setVisible(true);
}

int		Gui::initGui(const int &port, const std::string &host)
{
  Event		event;

  game = new Game(smgr, driver, device);
  makeCamera(STATIC);
  makeGuiSkybox();
  coClient = new ConnectClient(port, host, false);
  if (coClient->myConnect() == GUI_ERR)
    return (GUI_ERR);
  device->setEventReceiver(&event);
  while (device->run() && win == GUI && quit == false)
    {
      if (game->getMapInit() == false && game->getMapX() != DEFAULT && game->getMapY() != DEFAULT)
	{
	  game->makeMap();
	  game->setMapInit(true);
	}
      driver->beginScene(true, true, irr::video::SColor(255, 38, 196, 236));
      quit = event.getQuit();
      smgr->drawAll();
      envGUI->drawAll();
      driver->endScene();
      coClient->my_select();
      if (coClient->getResponse().size() > 0) {
	game->updateGame(coClient->getResponse());
	if (game->getMapInit() == true)
	  game->updateDisplay();
	coClient->clearResponse();
      }
    }
  guiRemove();
  return (GUI_OK);
}

Gui::Gui(irr::scene::ISceneManager *smgr_, irr::video::IVideoDriver *driver_, irr::IrrlichtDevice *device_)
{
  this->smgr = smgr_;
  this->driver = driver_;
  this->device = device_;
  this->quit = false;
  this->envGUI = device->getGUIEnvironment();
  win = GUI;
}

Gui::~Gui()
{}

bool				Gui::getQuit() const
{
  return (this->quit);
}
