//
// core.hpp for core in /home/lucas/rendu/reseau_psu/Zappy/client/zappy_client
//
// Made by Lucas
// Login   <lucas.onillon@epitech.eu>
//
// Started on  Sat Jun 25 22:00:09 2017 Lucas
// Last update Sun Jul  2 23:14:53 2017 Lucas
//

#ifndef CORE_HPP_
# define CORE_HPP_

/*
** Personnal header inclusions.
*/
# include "connectClient.hpp"
# include "zappy.hpp"
# include "splashScreen.hpp"
# include "lobby.hpp"
# include "gui.hpp"

/*
** Core class definition.
** Handle the whole process (GFX & server connections).
*/
class Core
{
public:
  Core();
  ~Core();
  int				initSplashScreen();
  int				initDevice();
  int				initConnectClient(int port, std::string host);
  int                           launchLobby(t_sett *settings, int status);
  int                           loopGui();
  int				launchGUI(t_sett *);

  irr::video::IVideoDriver*	getDriver() const;
  irr::scene::ISceneManager*    getSceneManager() const;
  irr::IrrlichtDevice*          getDevice() const;
  irr::gui::IGUIEnvironment*	getLobbyGUI() const;

private:
  irr::video::IVideoDriver*	driver;
  irr::scene::ISceneManager*	smgr;
  irr::IrrlichtDevice*		device;
  irr::gui::IGUIEnvironment*	lobbyGUI;

  Gui				*gui;
  Lobby                         *lobby;
  Win				win;
  bool				quit;
  bool				inLobby;
  bool				inGui;
  Ss				*ss;

  int				port;
  std::string			host;
};

#endif /* CORE_HPP_ */
