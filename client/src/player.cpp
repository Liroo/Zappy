//
// player.cpp for zappy in /home/thomas/Rendu/Zappy/client/src
//
// Made by Thomas
// Login   <thomas@epitech.net>
//
// Started on  Fri Jun 30 13:54:32 2017 Thomas
// Last update Fri Jun 30 20:09:56 2017 Thomas
//

#include "player.hpp"

void	Player::setFd(const int &fd)
{
  _fd = fd;
}

void	Player::setX(const int &x)
{
  _x = x;
}

void    Player::setY(const int &y)
{
  _y = y;
}

void    Player::setDirection(const int &direction)
{
  _direction = direction;
}

void    Player::setLevel(const int &level)
{
  _level = level;
}

void    Player::updateInventory(std::string &inv)
{
  std::string   delim = " ";
  std::string   params;
  size_t        pos = 0;
  int		i;

  i = 0;
  while ((pos = inv.find(delim)) != std::string::npos) {
    params = inv.substr(0, pos);
    inv.erase(0, pos + delim.length());
    _inventory[(InvType)i] = std::stoi(params, nullptr, 10);
    i++;
  }
  _inventory[(InvType)i] = std::stoi(inv, nullptr, 10);
}

int	Player::getFd() const
{
  return (_fd);
}

int	Player::getX() const
{
  return (_x);
}

int	Player::getY() const
{
  return (_y);
}

int	Player::getDirection() const
{
  return (_direction);
}

int	Player::getLevel() const
{
  return (_level);
}

Player::Player(int fd)
{
  _fd = fd;
  _x = 0;
  _y = 0;
  _direction = 0;
  _level = 1;
  _is_alive = true;
  _inventory[LINEMATE] = 0;
  _inventory[DERAUMERE] = 0;
  _inventory[SIBUR] = 0;
  _inventory[MENDIANE] = 0;
  _inventory[PHIRAS] = 0;
  _inventory[THYSTAME] = 0;
  _inventory[FOOD] = 0;
}

Player::~Player() {}
