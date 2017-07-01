//
// gui.cpp for gui in /home/lucas/Zappy/client
// 
// Made by Lucas
// Login   <lucas.onillon@epitech.eu>
// 
// Started on  Fri Jun 30 05:14:07 2017 Lucas
// Last update Sat Jul  1 01:20:56 2017 Lucas
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

void		Gui::initChatBox()
{
  wchar_t	data[100];

  swprintf(data, 100, L"Za'piqueBox", 244);
  device->setWindowCaption(data);

  chatBox = envGUI->addComboBox(irr::core::rect
		     <irr::s32>(20,525,320,575));

  chatBox->addItem(L"Ultra hardcore programming");
  swprintf(data, 100, L"Compliqu%c", 233);
  chatBox->addItem(data);
  swprintf(data, 100, L"Ca va %c peu pr%cs", 224, 232);
  chatBox->addItem(data);
  chatBox->addItem(L"Facile");
}

int		Gui::initGui()
{
  Event		event;

  makeGuiSkybox();
  //  initChatBox();
  device->setEventReceiver(&event);
  while (device->run() && win == GUI && quit == false)
    {
      driver->beginScene(true, true, irr::video::SColor(255, 38, 196, 236));
      quit = event.getQuit();
      smgr->drawAll();
      envGUI->drawAll();
      driver->endScene();
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
