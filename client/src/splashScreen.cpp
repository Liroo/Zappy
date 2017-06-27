//
// splashScreen.cpp for splashscreen in /home/lucas/rendu/reseau_psu/Zappy/client/zappy_client
// 
// Made by Lucas
// Login   <lucas.onillon@epitech.eu>
// 
// Started on  Mon Jun 26 01:23:51 2017 Lucas
// Last update Tue Jun 27 01:19:27 2017 Lucas
//

#include "splashScreen.hpp"

Ss::Ss(irr::scene::ISceneManager* sm_, irr::video::IVideoDriver* driver_,
       irr::IrrlichtDevice* device_)
{
  this->sm = sm_;
  this->driver = driver_;
  this->device = device_;
  this->ssGUI = device->getGUIEnvironment();
}

Ss::~Ss()
{}

void    Ss::makeCamera(int type)
{
  if (type == FPS)
    {
      ssCamera =
	sm->addCameraSceneNodeFPS(0, 100.0f, //speed rotation
				  10.0f, -1, keyMap, 6); // speed deplacement
      ssCamera->setPosition(irr::core::vector3df(1000,30,100));
      // camera->setTarget(vector3df(-100,-300,-60));
      device->getCursorControl()->setVisible(false);
    }
  else
    {
      ssCamera = sm->addCameraSceneNode(0, irr::core::vector3df(0,30,100),
					irr::core::vector3df(0,60,0));
      device->getCursorControl()->setVisible(true);
    }
}


void    Ss::makeSkybox()
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

void		Ss::ss_remove()
{
  ssGUI->clear();
}

void		Ss::makeLogo()
{
  ssGUI->addImage(getLogo(), irr::core::vector2d<irr::s32>(400,450));
}

int		Ss::splashScreen()
{
  int		timer;
  std::chrono::time_point<std::chrono::system_clock> end;

  makeLogo();
  makeCamera(STATIC);
  makeSkybox();
  zappyLogo = driver->getTexture(LOGO_PATH);
  start = std::chrono::system_clock::now();
  while (device->run())
    {
      end = std::chrono::system_clock::now();
      timer = std::chrono::duration_cast<std::chrono::seconds> (end - start).count();
      if (timer >= TIMER)
	break;
      driver->beginScene(true, true, irr::video::SColor(255, 38, 196, 236));
      sm->drawAll();
      ssGUI->drawAll();
      driver->endScene();
    }
  ss_remove();
  return (GUI_OK);
}
