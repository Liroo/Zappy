//
// LTexture.cpp for loadtexture in /home/lucas/rendu/reseau_psu/Zappy/client/zappy_client
//
// Made by Lucas
// Login   <lucas.onillon@epitech.eu>
//
// Started on  Mon Jun 26 00:55:18 2017 Lucas
// Last update Sun Jul  2 23:36:19 2017 Thomas
//

#include "LTexture.hpp"

LTexture::LTexture()
{}

LTexture::~LTexture()
{}

int	LTexture::setTexture(irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver,
			     irr::gui::IGUIEnvironment* lobbyGUI)
{
  if ((LogoPNG = driver->getTexture("./client/media/img/layer1.png")) == 0
      || (SKYBOX_MOUNT_UP = driver->getTexture("./client/media/skybox/velcor_up.tga")) == 0
      || (SKYBOX_MOUNT_DOWN = driver->getTexture("./client/media/skybox/velcor_dn.tga")) == 0
      || (SKYBOX_MOUNT_LEFT = driver->getTexture("./client/media/skybox/velcor_lf.tga")) == 0
      || (SKYBOX_MOUNT_RIGHT = driver->getTexture("./client/media/skybox/velcor_rt.tga")) == 0
      || (SKYBOX_MOUNT_FRONT = driver->getTexture("./client/media/skybox/velcor_ft.tga")) == 0
      || (SKYBOX_MOUNT_BACK = driver->getTexture("./client/media/skybox/velcor_bk.tga")) == 0
      || (hostLogo = driver->getTexture("./client/media/img/host_layer.png")) == 0
      || (portLogo = driver->getTexture("./client/media/img/port_layer.png")) == 0
      || (connectLogo = driver->getTexture("./client/media/img/connect_layer.png")) == 0
      || (GROUND_PNG = driver->getTexture("./client/media/img/materials/floor.png")) == 0
      || (BRICKS_MENU_OBJ = smgr->getMesh("./client/media/models/brick_menu.dae")) == NULL
      || (BRICKS_MENU_PNG = driver->getTexture("./client/media/Texture/brick_menu.png")) == 0
      || (PLAYER_PNG = driver->getTexture("./client/media/models/sprites/trantorian.png")) == 0
      )
    return (GUI_ERR);
  return (GUI_OK);
}

irr::video::ITexture*  LTexture::getPlayerPng() const
{
  return (this->PLAYER_PNG);
}

irr::video::ITexture*       LTexture::getGroundPng() const
{
  return (this->GROUND_PNG);
}

irr::scene::IAnimatedMesh*  LTexture::getBricksObj() const
{
  return (this->BRICKS_MENU_OBJ);
}

irr::video::ITexture*       LTexture::getConnectL() const
{
  return (this->connectLogo);
}

irr::video::ITexture*       LTexture::getPortL() const
{
  return (this->portLogo);
}

irr::video::ITexture*       LTexture::getHostL() const
{
  return (this->hostLogo);
}

irr::video::ITexture*       LTexture::getLogo() const
{
  return (this->LogoPNG);
}

irr::video::ITexture*       LTexture::getSbMountUp() const
{
  return (this->SKYBOX_MOUNT_UP);
}

irr::video::ITexture*       LTexture::getSbMountDown() const
{
  return (this->SKYBOX_MOUNT_DOWN);
}

irr::video::ITexture*       LTexture::getSbMountRight() const
{
  return (this->SKYBOX_MOUNT_RIGHT);
}

irr::video::ITexture*       LTexture::getSbMountLeft() const
{
  return (this->SKYBOX_MOUNT_LEFT);
}

irr::video::ITexture*       LTexture::getSbMountFront() const
{
  return (this->SKYBOX_MOUNT_FRONT);
}

irr::video::ITexture*       LTexture::getSbMountBack() const
{
  return (this->SKYBOX_MOUNT_BACK);
}
