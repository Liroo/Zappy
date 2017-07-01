//
// game.cpp for zappy in /home/thomas/Rendu/Zappy/client/src
//
// Made by Thomas
// Login   <thomas@epitech.net>
//
// Started on  Fri Jun 30 02:42:24 2017 Thomas
// Last update Sun Jul  2 01:30:58 2017 Thomas
//

#include <iostream>
#include "game.hpp"

void	Game::setMapInit(bool update)
{
  this->_mapInit = update;
}

bool	Game::getMapInit() const
{
  return (this->_mapInit);
}

int	Game::getMapX() const
{
  return (_map_x);
}

int	Game::getMapY() const
{
  return (_map_y);
}

int	Game::getFreq() const
{
  return (_freq);
}

int	Game::initMap(std::string &resp)
{
  std::string   delim_before = " ";
  std::string	delim_after = ", ";
  std::string   params;
  size_t        pos = 0;
  int		x;
  int		y;
  int		i;

  x = 0;
  y = 0;
  while (x < _map_x)
    {
      while (y < _map_y)
	{
	  t_tiles	tmp;

	  i = 0;
	  tmp.available = true;
	  if ((pos = resp.find(delim_before)) != std::string::npos) {
	    params = resp.substr(0, pos);
	    resp.erase(0, pos + delim_before.length());
	  }
	  else
	    return (1);
	  tmp.x = std::stoi(params, nullptr, 10);
	  if ((pos = resp.find(delim_before)) != std::string::npos) {
	    params = resp.substr(0, pos);
	    resp.erase(0, pos + delim_before.length());
	  }
	  else
	    return (1);
	  tmp.y = std::stoi(params, nullptr, 10);
	  while (i < 6)
	    {
	      if ((pos = resp.find(delim_before)) != std::string::npos) {
		params = resp.substr(0, pos);
		resp.erase(0, pos + delim_before.length());
	      }
	      if ((pos = resp.find(delim_after)) != std::string::npos) {
		params = resp.substr(0, pos);
		resp.erase(0, pos + delim_after.length());
	      }
	      tmp.items[(InvType)i] = std::stoi(params, nullptr, 10);
	      i++;
	    }
	  if ((pos = resp.find(delim_before)) != std::string::npos) {
	    params = resp.substr(0, pos);
	    resp.erase(0, pos + delim_before.length());
	  }
	  resp.substr(0, resp.size() - 1);
	  tmp.items[(InvType)i] = std::stoi(resp, nullptr, 10);
	  y++;
	}
      x++;
      y = 0;
    }
  return (0);
}

int	Game::teamsDetails(std::string &resp)
{
  std::string	delim = " ";
  std::string	params;
  std::string	team_name;
  size_t	pos = 0;
  Player	*tmp;
  Team		*tmp_t;

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
  tmp = new Player(std::stoi(resp, nullptr, 10));

  std::vector<Team>::iterator it_team = _teams.begin();
  while (it_team != _teams.end() && (*it_team).getName() != team_name)
    it_team++;
  if (it_team == _teams.end())
    {
      tmp_t = new Team(team_name);
      tmp_t->setNbPlayer(1);
      tmp_t->addPlayer(*tmp);
      _teams.push_back(*tmp_t);
    }
  else
    {
      (*it_team).setNbPlayer((*it_team).getNbPlayer() + 1);
      (*it_team).addPlayer(*tmp);
    }
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
      std::vector<Player>       tmp = (*it_team).getAllPlayer();
      std::vector<Player>::iterator it_player = tmp.begin();
      while (it_player != tmp.end() && (*it_player).getFd() != std::stoi(params, nullptr, 10))
	it_player++;
      if ((*it_player).getFd() == std::stoi(params, nullptr, 10))
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

int	Game::size(std::string &resp)
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
  _map_x = std::stoi(params, nullptr, 10);
  if ((pos = resp.find(delim)) != std::string::npos) {
    params = resp.substr(0, pos);
    resp.erase(0, pos + delim.length());
  }
  else
    return (1);
  _map_y = std::stoi(params, nullptr, 10);
  _freq = std::stoi(resp, nullptr, 10);
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

int	Game::updateGame(const std::string &old)
{
  std::string	resp;
  std::string	delim = " ";
  std::string	id;
  size_t	pos = 0;

  resp = old;
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

Game::Game(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver,
	   irr::IrrlichtDevice *device)
{
  sm = smgr;
  driver = driver;
  device = device;
  gameGUI = device->getGUIEnvironment();
  nbGround = 0;
  _mapInit = false;
  _map_x = DEFAULT;
  _map_y = DEFAULT;
  _allResp["01"] = &Game::size;
  _allResp["02"] = &Game::teamsDetails;
  _allResp["03"] = &Game::playerDetails;
  _allResp["04"] = &Game::initMap;
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
