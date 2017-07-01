//
// team.hpp for zappy in /home/thomas/Rendu/Zappy/client/include
//
// Made by Thomas
// Login   <thomas@epitech.net>
//
// Started on  Fri Jun 30 15:37:29 2017 Thomas
// Last update Sat Jul  1 00:43:52 2017 Thomas
//

#ifndef TEAM_HPP
# define TEAM_HPP

# include <string>
# include <vector>

# include "player.hpp"

class Team {

public:
  Team(const std::string &);
  ~Team();

private:
  std::string		_name;
  int			_nbPlayers;
  std::vector<Player>	_players;

public:
  void	setName(const std::string &);
  void	setNbPlayer(const int &);
  void	addPlayer(const Player &);

  std::string		getName() const;
  int			getNbPlayer() const;
  Player		getPlayer(const int &) const;
  std::vector<Player>	getAllPlayer() const;

};

#endif