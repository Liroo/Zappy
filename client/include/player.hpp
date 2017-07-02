//
// player.hpp for player in /home/thomas/Rendu/Zappy/client/include
//
// Made by Thomas
// Login   <thomas@epitech.net>
//
// Started on  Fri Jun 30 13:54:26 2017 Thomas
// Last update Sun Jul  2 03:57:48 2017 Thomas
//

#ifndef PLAYER_HPP
# define PLAYER_HPP

# include <map>
# include <iostream>

enum    Inv
  {
    LINEMATE = 0,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    FOOD
  };
typedef Inv InvType;

class Player {

public:
  Player(int);
  Player(const Player &);
  ~Player();

private:
  int				_fd;
  int				_x;
  int				_y;
  int				_direction;
  int				_level;
  bool				_is_alive;
  std::map<InvType, int>	_inventory;
  std::string			_buf;
  bool				_print_buf;

public:
  void	setFd(const int &);
  void	setX(const int &);
  void	setY(const int &);
  void	setDirection(const int &);
  void	setLevel(const int &);
  void	updateInventory(std::string &);
  void	setBuf(const std::string &);
  void	setIsPrint(const bool &);
  void	setOneItem(const InvType &);
  int	removeOneItem(const InvType &);

  int				getFd() const;
  int				getX() const;
  int				getY() const;
  int				getDirection() const;
  int				getLevel() const;
  std::map<InvType, int>	getInventory() const;
  std::string			getBuf() const;
  bool				getIsPrint() const;
  // int				getOneItem(const InvType &type) const;
};

#endif
