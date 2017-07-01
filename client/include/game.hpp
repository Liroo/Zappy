//
// game.hpp for zappy in /home/thomas/Rendu/Zappy/client/include
//
// Made by Thomas
// Login   <thomas@epitech.net>
//
// Started on  Fri Jun 30 01:23:13 2017 Thomas
// Last update Sat Jul  1 17:06:27 2017 Thomas
//

#ifndef GAME_HPP
# define GAME_HPP

# include <map>
# include <vector>
# include <string>

# include "team.hpp"

typedef struct                          s_tiles
{
  int                                   x;
  int                                   y;
  std::map<InvType, int>                items;
  bool                                  available;
  std::vector<Player>                   players;
}					t_tiles;

class Game {

public:
  Game();
  ~Game();
  int	updateGame(const std::string &);

  typedef int   (Game::*pfunc)(std::string &);


private:
  int					_map_x;
  int					_map_y;
  std::vector<Team>			_teams;
  std::map<std::string, pfunc>		_allResp;
  std::vector<std::vector<t_tiles>>	_map;

private:
  int	size(std::string &);
  int	teamsDetails(std::string &);
  int	playerDetails(std::string &);
  int	initMap(std::string &);
  int	forward(std::string &);
  int	right(std::string &);
  int	left(std::string &);
  int	see(std::string &);
  int	inventoryPlayer(std::string &);
  int	broadcast(std::string &);
  int	eject(std::string &);
  int	dead(std::string &);
  int	takeObject(std::string &);
  int	setObject(std::string &);

public:
  int	getMapX() const;
  int	getMapY() const;

};

#endif
