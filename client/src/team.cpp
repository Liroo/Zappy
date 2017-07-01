//
// team.cpp for zappy in /home/thomas/Rendu/Zappy/client/src
//
// Made by Thomas
// Login   <thomas@epitech.net>
//
// Started on  Fri Jun 30 15:37:59 2017 Thomas
// Last update Sun Jul  2 00:12:03 2017 Thomas
//

#include "team.hpp"

void	Team::setName(const std::string &name)
{
  _name = name;
}

void	Team::setNbPlayer(const int &nb)
{
  _nbPlayers = nb;
}

void	Team::addPlayer(const Player &p)
{
  _players.push_back(p);
}

std::string	Team::getName() const
{
  return (_name);
}

int	Team::getNbPlayer() const
{
  return (_nbPlayers);
}

Player	Team::getPlayer(const int &index) const
{
  return (_players.at(index));
}

std::vector<Player>	Team::getAllPlayer() const
{
  return (_players);
}

Team::Team(const std::string &name)
{
  _name = name;
  _nbPlayers = 0;
}

Team::~Team() {}
