//
// player.cpp for zappy in /home/thomas/Rendu/Zappy/client/src
//
// Made by Thomas
// Login   <thomas@epitech.net>
//
// Started on  Fri Jun 30 13:54:32 2017 Thomas
// Last update Sun Jul  2 03:57:15 2017 Thomas
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
  std::string   delim_before = " ";
  std::string	delim_after = ", ";
  std::string   params;
  size_t        pos = 0;
  int		i;

  i = 0;
  while (i < 6)
    {
      if ((pos = inv.find(delim_before)) != std::string::npos) {
	params = inv.substr(0, pos);
	inv.erase(0, pos + delim_before.length());
      }
      if ((pos = inv.find(delim_after)) != std::string::npos) {
	params = inv.substr(0, pos);
	inv.erase(0, pos + delim_after.length());
      }
      _inventory[(InvType)i] = std::stoi(params, nullptr, 10);
      i++;
    }
  if ((pos = inv.find(delim_before)) != std::string::npos) {
    params = inv.substr(0, pos);
    inv.erase(0, pos + delim_before.length());
  }
  inv.substr(0, inv.size() - 1);
  _inventory[(InvType)i] = std::stoi(inv, nullptr, 10);
}

void	Player::setBuf(const std::string &text)
{
  _buf = text;
}

void	Player::setIsPrint(const bool &print)
{
  _print_buf = print;
}

void	Player::setOneItem(const InvType &type)
{
  _inventory[type] += 1;
}

int	Player::removeOneItem(const InvType &type)
{
  if (_inventory[type] > 0)
    {
      _inventory[type] -= 1;
      return (0);
    }
  else
    return (1);
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

std::map<InvType, int>	Player::getInventory() const
{
  return (_inventory);
}

std::string	Player::getBuf() const
{
  return (_buf);
}

bool	Player::getIsPrint() const
{
  return (_print_buf);
}

// int	Player::getOneItem(const InvType &type) const
// {
//   return (_inventory[type]);
// }

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
  _print_buf = false;
}

Player::Player(const Player &p)
{
  _fd = p.getFd();
  _x = p.getX();
  _y = p.getY();
  _direction = p.getDirection();
  _level = p.getLevel();
  _is_alive = true;
  _inventory = p.getInventory();
  _buf = p.getBuf();
  _print_buf = p.getIsPrint();
}

Player::~Player() {}
