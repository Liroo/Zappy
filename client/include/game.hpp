//
// game.hpp for zappy in /home/thomas/Rendu/Zappy/client/include
//
// Made by Thomas
// Login   <thomas@epitech.net>
//
// Started on  Fri Jun 30 01:23:13 2017 Thomas
// Last update Sun Jul  2 23:09:03 2017 Lucas
//

#ifndef GAME_HPP
# define GAME_HPP

/*
** Standard header inclusions.
*/
# include <map>
# include <vector>
# include <string>
# include <algorithm>

/*
** Personnal header inclusions.
*/
# include "team.hpp"
# include "zappy.hpp"
# include "LTexture.hpp"

/*
** Macro definitions.
*/
# define	DEFAULT (0)

/*
** Game class definitions.
** Handle the map process.
*/
class Game : public LTexture
{
public:
  Game(irr::scene::ISceneManager *, irr::video::IVideoDriver*, irr::IrrlichtDevice*);
  ~Game();
  int	updateGame(const std::string &);

  typedef int   (Game::*pfunc)(std::string &);

  int					getMapX() const;
  int					getMapY() const;
  int					getFreq() const;
  bool					getMapInit() const;
  std::vector< std::vector< t_tiles > >	getMap() const;
  void					setMapInit(bool update);
  void					makeMap();
  void					makeGround(int x, int y);
  std::map<std::string, InvType>	initConvert() const;
  std::string				invToStr(int i) const;
  const wchar_t *			getChatData() const;

private:
  irr::video::IVideoDriver	*_driver;
  irr::scene::ISceneManager	*_sm;
  irr::IrrlichtDevice		*_device;
  irr::gui::IGUIEnvironment	*_gameGUI;
  irr::scene::ISceneNode	*gameBrick[1024];

  const wchar_t				*_guiResp;
  int					nbGround;
  int					_freq;
  int					_map_x;
  int					_map_y;
  std::vector<Team>			_teams;
  std::map<std::string, pfunc>		_allResp;
  bool					_mapInit;
  std::vector< std::vector< t_tiles > >	_map;
  irr::scene::ISceneNode*		gameTiles[400];

  // PTR FUNC //
  int	size(std::string &);
  int	teamsDetails(std::string &);
  int	playerDetails(std::string &);
  int	initMap(std::string &);
  int	forward(std::string &);
  int	direction(std::string &);
  int	see(std::string &);
  int	inventoryPlayer(std::string &);
  int	broadcast(std::string &);
  int	eject(std::string &);
  int	dead(std::string &);
  int	takeObject(std::string &);
  int	setObject(std::string &);
  int	forkPlayer(std::string &);
  int	egg(std::string &);
  int	elevationAll(std::string &);
  int	elevationPlayer(std::string &);
  int	cast(std::string &);
};

#endif
