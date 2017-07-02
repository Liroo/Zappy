//
// player.hpp for player in /home/thomas/Rendu/Zappy/client/include
//
// Made by Thomas
// Login   <thomas@epitech.net>
//
// Started on  Fri Jun 30 13:54:26 2017 Thomas
// Last update Sun Jul  2 22:07:00 2017 Thomas
//

#ifndef PLAYER_HPP
# define PLAYER_HPP

# define RED            "\033[1;31m"
# define GREEN           "\033[1;32m"
# define BLUE            "\033[1;34m"
# define YELLOW          "\033[1;33m"
# define BLANK          "\033[0m"

/*
** Standard header inclusions.
*/
# include <irrlicht.h>
# include <iostream>
# include <fstream>
# include <chrono>
# include <ctime>
# include <vector>
# include <thread>
# include <string>
# include <mutex>
# include <limits>
# include <time.h>
# include <irrKlang.h>
# include <sstream>
# include <map>
# include <iostream>

/*
** Personnal header inclusions.
*/
# include "LTexture.hpp"

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
  Player(int, irr::scene::ISceneManager *, irr::video::IVideoDriver*, irr::IrrlichtDevice*);
  Player(const Player &);
  ~Player();

  Player	operator=(const Player &);

private:
  irr::scene::ISceneManager     *_sm;
  irr::video::IVideoDriver      *_driver;
  irr::IrrlichtDevice           *_device;

  irr::gui::IGUIEnvironment		*_playerGUI;
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
  irr::scene::IAnimatedMesh*	getBricksObj() const;
  // int				getOneItem(const InvType &type) const;
};

#endif
