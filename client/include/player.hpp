//
// player.hpp for player in /home/thomas/Rendu/Zappy/client/include
//
// Made by Thomas
// Login   <thomas@epitech.net>
//
// Started on  Fri Jun 30 13:54:26 2017 Thomas
// Last update Sat Jul  1 00:44:01 2017 Thomas
//

#ifndef PLAYER_HPP
# define PLAYER_HPP

# include <map>

# include "zappy.hpp"

class Player {

public:
  Player(int);
  ~Player();

private:
  int				_fd;
  int				_x;
  int				_y;
  int				_direction;
  int				_level;
  bool				_is_alive;
  std::map<InvType, int>	_inventory;

public:
  void	setFd(const int &);
  void	setX(const int &);
  void	setY(const int &);
  void	setDirection(const int &);
  void	setLevel(const int &);
  void	updateInventory(std::string &);

  int	getFd() const;
  int	getX() const;
  int	getY() const;
  int	getDirection() const;
  int	getLevel() const;
};

#endif
