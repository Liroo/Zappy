//
// lobby.hpp for lobby in /home/lucas/rendu/reseau_psu/Zappy/client
//
// Made by Lucas
// Login   <lucas.onillon@epitech.eu>
//
// Started on  Wed Jun 28 00:16:38 2017 Lucas
// Last update Sat Jul  1 17:03:34 2017 Thomas
//

#ifndef LOBBY_HPP_
# define LOBBY_HPP_

/*
** Personnal header inclusions.
*/
# include "zappy.hpp"
# include "LTexture.hpp"
# include "eventGesture.hpp"
# include "gui.hpp"
# include "connectClient.hpp"

/*
** Macro definitions.
*/
# define	CONNECTL_PATH	"./media/img/connect_layer.png"

/*
** Lobby class, while handle the home Lobby
** that implies the Hostname/Port textfields
** and moreover the settings/credits support.
*/
class Lobby : public LTexture
{
public:
  Lobby(irr::scene::ISceneManager *, irr::video::IVideoDriver*, irr::IrrlichtDevice*);
  ~Lobby();
  int      	initLobby(t_sett *sett, int status);
  void		makeLobbySkybox();
  void		makeTextfields();
  void		lobbyRemove();
  bool		getQuit() const;
  int           launchGUI(t_sett *, int status);
  bool		isDigits(const std::string &str);
  int		getPort() const;
  std::string	getHost() const;

private:
  irr::scene::ISceneManager	*sm;
  irr::video::IVideoDriver      *driver;
  irr::IrrlichtDevice           *device;

  // LOBBY GUI //
  irr::gui::IGUIEnvironment     *lobbyGUI;
  irr::gui::IGUIEditBox		*hostTF;
  irr::gui::IGUIEditBox		*portTF;
  irr::gui::IGUIButton		*connectBtt;

  irr::gui::IGUIElement		*elem;

  irr::scene::ISceneNode        *skybox;
  bool				quit;
  Win				win;

  ConnectClient			*connect;
  int				save_port;
  std::string			save_host;
};

#endif	/* !LOBBY_HPP_*/
