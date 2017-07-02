//
// player.hpp for player in /home/thomas/Rendu/Zappy/client/include
//
// Made by Thomas
// Login   <thomas@epitech.net>
//
// Started on  Fri Jun 30 13:54:26 2017 Thomas
// Last update Sun Jul  2 16:27:50 2017 Thomas
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

class Player : public LTexture
{

public:
  Player(int);
  Player(const Player &);
  ~Player();

  Player	operator=(const Player &);

private:
  int					_fd;
  int					_x;
  int					_y;
  int					_rendX;
  int					_rendY;
  int					_direction;
  int					_level;
  bool					_is_alive;
  std::map<InvType, int>		_inventory;
  std::string				_buf;
  bool					_print_buf;
  irr::scene::IAnimatedMeshSceneNode*	playerMesh;
  irr::core::vector3df			position;
  irr::core::vector3df			rotation;
  irr::core::vector3df			echelle;

public:
  void	setFd(const int &);
  void	setX(const int &);
  void	setY(const int &);
  void	setRendX(const int &);
  void	setRendY(const int &);
  void	setDirection(const int &);
  void	setLevel(const int &);
  void	updateInventory(std::string &);
  void	setBuf(const std::string &);
  void	setIsPrint(const bool &);
  void	setOneItem(const InvType &);
  void	makePlayer();
  int	removeOneItem(const InvType &);

  int				getFd() const;
  int				getX() const;
  int				getY() const;
  int				getRendX() const;
  int				getRendY() const;
  int				getDirection() const;
  int				getLevel() const;
  std::map<InvType, int>	getInventory() const;
  std::string			getBuf() const;
  bool				getIsPrint() const;
  // int				getOneItem(const InvType &type) const;
};

#endif
