//
// game.cpp for zappy in /home/thomas/Rendu/Zappy/client/src
//
// Made by Thomas
// Login   <thomas@epitech.net>
//
// Started on  Fri Jun 30 02:42:24 2017 Thomas
// Last update Sat Jul  1 04:07:53 2017 Thomas
//

#include <iostream>

#include "game.hpp"

int	Game::initMap(std::string &resp)
{
  std::string   delim = " ";
  std::string   params;
  size_t        pos = 0;
  t_tiles	tmp;

  if ((pos = resp.find(delim)) != std::string::npos) {
    params = resp.substr(0, pos);
    resp.erase(0, pos + delim.length());
  }
  else
    return (1);
  tmp.x = std::stoi(params, nullptr, 10);

  if ((pos = resp.find(delim)) != std::string::npos) {
    params = resp.substr(0, pos);
    resp.erase(0, pos + delim.length());
  }
  else
    return (1);
  tmp.y = std::stoi(params, nullptr, 10);

  if ((pos = resp.find(delim)) != std::string::npos) {
    params = resp.substr(0, pos);
    resp.erase(0, pos + delim.length());
  }
  else
    return (1);

  delim = ",";

  if ((pos = resp.find(delim)) != std::string::npos) {
    params = resp.substr(0, pos);
    resp.erase(0, pos + delim.length());
  }
  else
    return (1);
  tmp.items[LINEMATE] = std::stoi(params, nullptr, 10);

  return (0);
}

int	Game::teamsDetails(std::string &resp)
{
  std::string   delim = " ";
  std::string   params;
  std::string	team_name;
  size_t        pos = 0;
  Team		*tmp;
  Player	*tmp_p;

  if ((pos = resp.find(delim)) != std::string::npos) {
    team_name = resp.substr(0, pos);
    resp.erase(0, pos + delim.length());
  }
  else
    return (1);

  while ((pos = resp.find(delim)) != std::string::npos) {
    params = resp.substr(0, pos);
    resp.erase(0, pos + delim.length());
  }

  tmp_p = new Player(std::stoi(resp, nullptr, 10));

  std::vector<Team>::iterator it_team = _teams.begin();
  while (it_team != _teams.end() && (*it_team).getName() != team_name)
    it_team++;
  if (it_team == _teams.end())
    {
      tmp = new Team(team_name);
      tmp->getAllPlayer().push_back(*tmp_p);
    }
  else
    (*it_team).getAllPlayer().push_back(*tmp_p);

  return (0);
}

int	Game::playerDetails(std::string &resp)
{
  std::string   delim = " ";
  std::string   params;
  size_t        pos = 0;

  if ((pos = resp.find(delim)) != std::string::npos) {
    params = resp.substr(0, pos);
    resp.erase(0, pos + delim.length());
  }
  else
    return (1);

  std::vector<Team>::iterator it_team = _teams.begin();
  while (it_team != _teams.end())
    {
      std::vector<Player>::iterator it_player = (*it_team).getAllPlayer().begin();
      while (it_player != (*it_team).getAllPlayer().end() && (*it_player).getFd()
	     != std::stoi(params, nullptr, 10))
	it_player++;
      if (it_player != (*it_team).getAllPlayer().end() && (*it_player).getFd()
	  == std::stoi(params, nullptr, 10))
	{
	  if ((pos = resp.find(delim)) != std::string::npos) {
	    params = resp.substr(0, pos);
	    resp.erase(0, pos + delim.length());
	  }
	  else
	    return (1);
	  (*it_player).setX(std::stoi(params, nullptr, 10));

	  if ((pos = resp.find(delim)) != std::string::npos) {
	    params = resp.substr(0, pos);
	    resp.erase(0, pos + delim.length());
	  }
	  else
	    return (1);
	  (*it_player).setY(std::stoi(params, nullptr, 10));

	  if ((pos = resp.find(delim)) != std::string::npos) {
	    params = resp.substr(0, pos);
	    resp.erase(0, pos + delim.length());
	  }
	  else
	    return (1);
	  (*it_player).setDirection(std::stoi(params, nullptr, 10));

	  if ((pos = resp.find(delim)) != std::string::npos) {
	    params = resp.substr(0, pos);
	    resp.erase(0, pos + delim.length());
	  }
	  else
	    return (1);
	  (*it_player).setLevel(std::stoi(params, nullptr, 10));

	  (*it_player).updateInventory(resp);
	}
      it_team++;
    }
  return (0);
}

int	Game::tileInventory(std::string &resp)
{
  return (0);
}

int	Game::forward(std::string &resp)
{
  return (0);
}

int	Game::right(std::string &resp)
{
  return (0);
}

int	Game::left(std::string &resp)
{
  return (0);
}

int	Game::see(std::string &resp)
{
  return (0);
}

int	Game::inventoryPlayer(std::string &resp)
{
  return (0);
}

int	Game::broadcast(std::string &resp)
{
  return (0);
}

int	Game::eject(std::string &resp)
{
  return (0);
}

int	Game::dead(std::string &resp)
{
  return (0);
}

int	Game::takeObject(std::string &resp)
{
  return (0);
}

int	Game::setObject(std::string &resp)
{
  return (0);
}

int	Game::updateGame(std::string &resp)
{
  std::string	delim = " ";
  std::string	id;
  size_t	pos = 0;

  if ((pos = resp.find(delim)) != std::string::npos) {
    id = resp.substr(0, pos);
    resp.erase(0, pos + delim.length());
  }
  else
    return (1);
  std::map<std::string, pfunc>::iterator it = _allResp.find(id);
  if (it != _allResp.end())
    return (this->*(it->second))(resp);
  else
    return (1);
}

Game::Game()
{
  _allResp["01"] = &Game::initMap;
  _allResp["02"] = &Game::teamsDetails;
  _allResp["03"] = &Game::playerDetails;
  _allResp["04"] = &Game::tileInventory;
  _allResp["05"] = &Game::forward;
  _allResp["06"] = &Game::right;
  _allResp["07"] = &Game::left;
  _allResp["08"] = &Game::see;
  _allResp["09"] = &Game::inventoryPlayer;
  _allResp["10"] = &Game::broadcast;
  _allResp["11"] = &Game::eject;
  _allResp["12"] = &Game::dead;
  _allResp["13"] = &Game::takeObject;
  _allResp["14"] = &Game::setObject;
}

Game::~Game() {}
