//
// core.hpp for core in /home/lucas/rendu/reseau_psu/Zappy/client/zappy_client
// 
// Made by Lucas
// Login   <lucas.onillon@epitech.eu>
// 
// Started on  Sat Jun 25 22:00:09 2017 Lucas
// Last update Tue Jun 27 01:26:49 2017 Lucas
//

#ifndef CORE_HPP_
# define CORE_HPP_

# include "zappy.hpp"
# include "splashScreen.hpp"

class Core
{
public:
  Core();
  ~Core();
  int				initSplashScreen();
  int				initDevice();

  irr::video::IVideoDriver*	getDriver() const;
  irr::scene::ISceneManager*    getSceneManager() const;
  irr::IrrlichtDevice*          getDevice() const;
  irr::gui::IGUIEnvironment*	getLobbyGUI() const;

private:
  irr::video::IVideoDriver*	driver;
  irr::scene::ISceneManager*	smgr;
  irr::IrrlichtDevice*		device;
  irr::gui::IGUIEnvironment*	lobbyGUI;

  Win				window;
  bool				quit;
  bool				inLobby;
  bool				inPlay;
  Ss				*ss;
};

#endif /* CORE_HPP_ */
