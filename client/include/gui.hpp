//
// gui.hpp for gui in /home/lucas/Zappy/client
//
// Made by Lucas
// Login   <lucas.onillon@epitech.eu>
//
// Started on  Fri Jun 30 05:00:17 2017 Lucas
// Last update Sun Jul  2 23:23:46 2017 Lucas
//

#ifndef GUI_HPP_
# define GUI_HPP_

/*
** Personnal header inclusions.
*/
# include "zappy.hpp"
# include "LTexture.hpp"
# include "eventGesture.hpp"
# include "connectClient.hpp"
# include "game.hpp"

/*
** Gui class, will handle the main graphic render
** including the map, chat, inventory and trivias.
*/
class Gui : public LTexture
{
public:
  Gui(irr::scene::ISceneManager*, irr::video::IVideoDriver*, irr::IrrlichtDevice*);
  ~Gui();
  int				initGui(const int &, const std::string &);
  void				makeGuiSkybox();
  void				guiRemove();
  bool				getQuit() const;
  void				initChatBox();
  int				getPort() const;
  std::string			getHost() const;
  void				makeCamera(int);
  void				makeChatBox();
  
private:
  irr::scene::ICameraSceneNode	*guiCamera;
  irr::video::IVideoDriver	*driver;
  irr::scene::ISceneManager	*smgr;
  irr::IrrlichtDevice		*device;
  irr::gui::IGUIEnvironment	*envGUI;

  Win				win;
  bool				quit;
  irr::scene::ISceneNode	*skybox;

  ConnectClient			*coClient;
  Game				*game;
};

#endif	/* !GUI_HPP_ */
