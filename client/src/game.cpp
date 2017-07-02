//
// game.cpp for zappy in /home/thomas/Rendu/Zappy/client/src
//
// Made by Thomas
// Login   <thomas@epitech.net>
//
// Started on  Fri Jun 30 02:42:24 2017 Thomas
// Last update Sun Jul  2 22:59:14 2017 Thomas
//

#include <iostream>
#include "game.hpp"

Game::Game(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver,
	   irr::IrrlichtDevice *device)
{
  _sm = smgr;
  _driver = driver;
  _device = device;
  _gameGUI = device->getGUIEnvironment();
  setTexture(_sm, _driver, _gameGUI);
  nbGround = 0;
  _mapInit = false;
  _map_x = DEFAULT;
  _map_y = DEFAULT;
  _allResp["01"] = &Game::size;
  _allResp["02"] = &Game::teamsDetails;
  _allResp["03"] = &Game::playerDetails;
  _allResp["04"] = &Game::initMap;
  _allResp["05"] = &Game::forward;
  _allResp["06"] = &Game::direction;
  _allResp["07"] = &Game::direction;
  _allResp["08"] = &Game::see;
  _allResp["09"] = &Game::inventoryPlayer;
  _allResp["10"] = &Game::broadcast;
  _allResp["11"] = &Game::eject;
  _allResp["12"] = &Game::dead;
  _allResp["13"] = &Game::takeObject;
  _allResp["14"] = &Game::setObject;
  _allResp["15"] = &Game::forkPlayer;
  _allResp["16"] = &Game::egg;
  _allResp["17"] = &Game::elevationAll;
  _allResp["18"] = &Game::elevationPlayer;
  _allResp["19"] = &Game::cast;
}

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

std::string  Game::invToStr(int i) const
{
  std::map<InvType, std::string>        toStr;

  toStr[LINEMATE] = "LINEMATE";
  toStr[DERAUMERE] = "DERAUMERE";
  toStr[SIBUR] = "SIBUR";
  toStr[MENDIANE] = "MENDIANE";
  toStr[PHIRAS] = "PHIRAS";
  toStr[THYSTAME] = "THYSTAME";
  toStr[FOOD] = "FOOD";
  return (toStr[(InvType)i]);
}

int	Game::initMap(std::string &resp)
{
  std::string	delim_before = " ";
  std::string	delim_after = ", ";
  std::string	params;
  size_t	pos = 0;
  int		i;
  int		posx;
  int		posy;
  std::string	gui;

  if ((pos = resp.find(delim_before)) != std::string::npos)
    {
      params = resp.substr(0, pos);
      resp.erase(0, pos + delim_before.length());
    }
  posx = std::stoi(params, nullptr, 10);;

  if ((pos = resp.find(delim_before)) != std::string::npos)
    {
      params = resp.substr(0, pos);
      resp.erase(0, pos + delim_before.length());
    }
  posy = std::stoi(params, nullptr, 10);

  gui = "Tiles " + std::to_string(posx) + " " + std::to_string(posy) + " contains: ";

  i = 0;
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
      _map[posx][posy].items[(InvType)i] = std::stoi(params, nullptr, 10);
      gui += invToStr(i) + " " + params;
      i++;
    }
  if ((pos = resp.find(delim_before)) != std::string::npos) {
    params = resp.substr(0, pos);
    resp.erase(0, pos + delim_before.length());
  }
  resp = resp.substr(0, resp.size() - 1);
  _map[posx][posy].items[(InvType)i] = std::stoi(resp, nullptr, 10);
  gui += invToStr(i) + " " + params;
  std::wstring ws(gui.begin(), gui.end());
  _guiResp = ws.c_str();
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
  tmp = new Player(std::stoi(resp, nullptr, 10), _sm, _driver, _device);

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
  std::string	delim = " ";
  std::string	params;
  size_t	pos = 0;
  int		find;
  bool		is_already;

  if ((pos = resp.find(delim)) != std::string::npos) {
    params = resp.substr(0, pos);
    resp.erase(0, pos + delim.length());
  }
  else
    return (1);

  find = 0;
  std::vector<Team>::iterator it_team = _teams.begin();
  while (it_team != _teams.end() && find == 0)
    {
      std::vector<Player> tmp = (*it_team).getAllPlayer();
      std::vector<Player>::iterator it_player = tmp.begin();
      while (it_player != tmp.end() && (*it_player).getFd() != std::stoi(params, nullptr, 10))
	it_player++;
      if (it_player == tmp.end())
	it_team++;
      else if ((*it_player).getFd() == std::stoi(params, nullptr, 10))
	{
	  find = 1;
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

	  is_already = false;
	  std::vector<Player>::iterator check = _map[(*it_player).getX()][(*it_player).getY()].players.begin();
	  while (check != _map[(*it_player).getX()][(*it_player).getY()].players.end())
	    {
	      if ((*check).getFd() == (*it_player).getFd())
		is_already = true;
	      check++;
	    }
	  if (is_already == false)
	    _map[(*it_player).getX()][(*it_player).getY()].players.push_back((*it_player));
	  else
	    (*check) = (*it_player);

	}
    }

  return (0);
}

int	Game::size(std::string &resp)
{
  std::string	delim = " ";
  std::string	params;
  size_t	pos = 0;

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
  std::string	delim = " ";
  std::string	params;
  size_t	pos = 0;
  int		find;
  int		x;
  int		y;
  int		del_check;

  if ((pos = resp.find(delim)) != std::string::npos) {
    params = resp.substr(0, pos);
    resp.erase(0, pos + delim.length());
  }
  else
    return (1);

  del_check = 0;
  find = 0;
  std::vector<Team>::iterator it_team = _teams.begin();
  while (it_team != _teams.end() && find == 0)
    {
      std::vector<Player> tmp = (*it_team).getAllPlayer();
      std::vector<Player>::iterator it_player = tmp.begin();
      while (it_player != tmp.end() && (*it_player).getFd() != std::stoi(params, nullptr, 10))
	it_player++;
      if (it_player == tmp.end())
	it_team++;
      else if ((*it_player).getFd() == std::stoi(params, nullptr, 10))
	{
	  find = 1;
	  if ((pos = resp.find(delim)) != std::string::npos) {
	    params = resp.substr(0, pos);
	    resp.erase(0, pos + delim.length());
	  }
	  else
	    return (1);
	  x = std::stoi(params, nullptr, 10);
	  y = std::stoi(resp, nullptr, 10);
	  (*it_player).setX(x);
	  (*it_player).setY(y);
	  std::vector<Player>::iterator check = _map[x][y].players.begin();
	  while (check != _map[x][y].players.end() && del_check == 0)
	    {
	      if ((*check).getFd() == (*it_player).getFd())
		del_check = 1;
	      check++;
	    }
	  if (del_check == 1)
	    _map[x][y].players.erase(check);
	  _map[x][y].players.push_back((*it_player));
	}
    }

  return (0);
}

int	Game::direction(std::string &resp)
{
  std::string	delim = " ";
  std::string	params;
  size_t	pos = 0;
  int		find;
  bool		is_already;

  if ((pos = resp.find(delim)) != std::string::npos) {
    params = resp.substr(0, pos);
    resp.erase(0, pos + delim.length());
  }
  else
    return (1);

  find = 0;
  std::vector<Team>::iterator it_team = _teams.begin();
  while (it_team != _teams.end() && find == 0)
    {
      std::vector<Player> tmp = (*it_team).getAllPlayer();
      std::vector<Player>::iterator it_player = tmp.begin();
      while (it_player != tmp.end() && (*it_player).getFd() != std::stoi(params, nullptr, 10))
	it_player++;
      if (it_player == tmp.end())
	it_team++;
      else if ((*it_player).getFd() == std::stoi(params, nullptr, 10))
	{
	  find = 1;
	  (*it_player).setDirection(std::stoi(resp, nullptr, 10));

	  is_already = false;
	  std::vector<Player>::iterator check = _map[(*it_player).getX()][(*it_player).getY()].players.begin();
	  while (check != _map[(*it_player).getX()][(*it_player).getY()].players.end())
	    {
	      if ((*check).getFd() == (*it_player).getFd())
		is_already = true;
	      check++;
	    }
	  if (is_already == false)
	    _map[(*it_player).getX()][(*it_player).getY()].players.push_back((*it_player));
	  else
	    (*check) = (*it_player);
	}
    }

  return (0);
}

int	Game::see(std::string &resp)
{
  int	find;

  find = 0;
  std::vector<Team>::iterator it_team = _teams.begin();
  while (it_team != _teams.end() && find == 0)
    {
      std::vector<Player> tmp = (*it_team).getAllPlayer();
      std::vector<Player>::iterator it_player = tmp.begin();
      while (it_player != tmp.end() && (*it_player).getFd() != std::stoi(resp, nullptr, 10))
	it_player++;
      if (it_player == tmp.end())
	it_team++;
      else if ((*it_player).getFd() == std::stoi(resp, nullptr, 10))
	find = 1;
    }

  return (0);
}

int	Game::inventoryPlayer(std::string &resp)
{
  int	find;

  find = 0;
  std::vector<Team>::iterator it_team = _teams.begin();
  while (it_team != _teams.end() && find == 0)
    {
      std::vector<Player> tmp = (*it_team).getAllPlayer();
      std::vector<Player>::iterator it_player = tmp.begin();
      while (it_player != tmp.end() && (*it_player).getFd() != std::stoi(resp, nullptr, 10))
	it_player++;
      if (it_player == tmp.end())
	it_team++;
      else if ((*it_player).getFd() == std::stoi(resp, nullptr, 10))
	find = 1;
    }

  return (0);
}

int	Game::broadcast(std::string &resp)
{
  std::string	delim = " ";
  std::string	params;
  size_t	pos = 0;
  int		find;
  bool		is_already;

  if ((pos = resp.find(delim)) != std::string::npos) {
    params = resp.substr(0, pos);
    resp.erase(0, pos + delim.length());
  }
  else
    return (1);

  find = 0;
  std::vector<Team>::iterator it_team = _teams.begin();
  while (it_team != _teams.end() && find == 0)
    {
      std::vector<Player> tmp = (*it_team).getAllPlayer();
      std::vector<Player>::iterator it_player = tmp.begin();
      while (it_player != tmp.end() && (*it_player).getFd() != std::stoi(params, nullptr, 10))
	it_player++;
      if (it_player == tmp.end())
	it_team++;
      else if ((*it_player).getFd() == std::stoi(params, nullptr, 10))
	{
	  find = 1;
	  (*it_player).setBuf(resp);
	  (*it_player).setIsPrint(true);

	  is_already = false;
	  std::vector<Player>::iterator check = _map[(*it_player).getX()][(*it_player).getY()].players.begin();
	  while (check != _map[(*it_player).getX()][(*it_player).getY()].players.end())
	    {
	      if ((*check).getFd() == (*it_player).getFd())
		is_already = true;
	      check++;
	    }
	  if (is_already == false)
	    _map[(*it_player).getX()][(*it_player).getY()].players.push_back((*it_player));
	  else
	    (*check) = (*it_player);
	}
    }

  return (0);
}

int	Game::eject(std::string &resp)
{
  int	find;

  find = 0;
  std::vector<Team>::iterator it_team = _teams.begin();
  while (it_team != _teams.end() && find == 0)
    {
      std::vector<Player> tmp = (*it_team).getAllPlayer();
      std::vector<Player>::iterator it_player = tmp.begin();
      while (it_player != tmp.end() && (*it_player).getFd() != std::stoi(resp, nullptr, 10))
	it_player++;
      if (it_player == tmp.end())
	it_team++;
      else if ((*it_player).getFd() == std::stoi(resp, nullptr, 10))
	find = 1;
    }
  return (0);
}

int	Game::dead(std::string &resp)
{
  int				i;
  int				find;
  std::map<InvType, int>	invP;
  bool				is_already;

  i = 0;
  find = 0;
  std::vector<Team>::iterator it_team = _teams.begin();
  while (it_team != _teams.end() && find == 0)
    {
      std::vector<Player>       tmp = (*it_team).getAllPlayer();
      std::vector<Player>::iterator it_player = tmp.begin();
      while (it_player != tmp.end() && (*it_player).getFd() != std::stoi(resp, nullptr, 10))
	it_player++;

      if (it_player == tmp.end())
	it_team++;
      else if ((*it_player).getFd() == std::stoi(resp, nullptr, 10))
	{
	  if ((*it_player).getFd() == std::stoi(resp, nullptr, 10))
	    {
	      invP = (*it_player).getInventory();
	      while (i < 7)
		{
		  _map[(*it_player).getX()][(*it_player).getY()].items[(InvType)i] += invP[(InvType)i];
		  i++;
		}

	      is_already = false;
	      std::vector<Player>::iterator check = _map[(*it_player).getX()][(*it_player).getY()].players.begin();
	      while (check != _map[(*it_player).getX()][(*it_player).getY()].players.end())
		{
		  if ((*check).getFd() == (*it_player).getFd())
		    is_already = true;
		  check++;
		}
	      if (is_already == true)
		_map[(*it_player).getX()][(*it_player).getY()].players.erase(check);

	      (*it_team).setNbPlayer((*it_team).getNbPlayer() - 1);
	      (*it_team).erasePlayer(it_player);
	    }
	}
    }
  return (0);
}

std::map<std::string, InvType>	Game::initConvert() const
{
  std::map<std::string, InvType>	convertType;

  convertType["LINEMATE"] = LINEMATE;
  convertType["DERAUMERE"] = DERAUMERE;
  convertType["SIBUR"] = SIBUR;
  convertType["MENDIANE"] = MENDIANE;
  convertType["PHIRAS"] = PHIRAS;
  convertType["THYSTAME"] = THYSTAME;
  convertType["FOOD"] = FOOD;
  return (convertType);
}

int	Game::takeObject(std::string &resp)
{
  std::string				delim = " ";
  std::string				params;
  size_t				pos = 0;
  std::map<std::string, InvType>	convertType;
  InvType				type;
  int					find;
  bool					is_already;

  convertType = initConvert();
  if ((pos = resp.find(delim)) != std::string::npos) {
    params = resp.substr(0, pos);
    resp.erase(0, pos + delim.length());
  }
  else
    return (1);

  find = 0;
  std::vector<Team>::iterator it_team = _teams.begin();
  while (it_team != _teams.end() && find == 0)
    {
      std::vector<Player> tmp = (*it_team).getAllPlayer();
      std::vector<Player>::iterator it_player = tmp.begin();
      while (it_player != tmp.end() && (*it_player).getFd() != std::stoi(params, nullptr, 10))
	it_player++;
      if (it_player == tmp.end())
	it_team++;
      else if ((*it_player).getFd() == std::stoi(params, nullptr, 10))
	{
	  find = 1;
	  std::transform(resp.begin(), resp.end(), resp.begin(), ::toupper);
	  type = convertType[resp];
	  (*it_player).setOneItem(type);
	  if (_map[(*it_player).getX()][(*it_player).getY()].items[type] > 0)
	    _map[(*it_player).getX()][(*it_player).getY()].items[type] -= 1;

	  is_already = false;
	  std::vector<Player>::iterator check = _map[(*it_player).getX()][(*it_player).getY()].players.begin();
	  while (check != _map[(*it_player).getX()][(*it_player).getY()].players.end())
	    {
	      if ((*check).getFd() == (*it_player).getFd())
		is_already = true;
	      check++;
	    }
	  if (is_already == false)
	    _map[(*it_player).getX()][(*it_player).getY()].players.push_back((*it_player));
	  else
	    (*check) = (*it_player);

	}
    }

  return (0);
}

int	Game::setObject(std::string &resp)
{
  std::string				delim = " ";
  std::string				params;
  size_t				pos = 0;
  std::map<std::string, InvType>	convertType;
  InvType				type;
  int					find;
  bool					is_already;

  convertType = initConvert();
  if ((pos = resp.find(delim)) != std::string::npos) {
    params = resp.substr(0, pos);
    resp.erase(0, pos + delim.length());
  }
  else
    return (1);

  find = 0;
  std::vector<Team>::iterator it_team = _teams.begin();
  while (it_team != _teams.end() && find == 0)
    {
      std::vector<Player> tmp = (*it_team).getAllPlayer();
      std::vector<Player>::iterator it_player = tmp.begin();
      while (it_player != tmp.end() && (*it_player).getFd() != std::stoi(params, nullptr, 10))
	it_player++;
      if (it_player == tmp.end())
	it_team++;
      else if ((*it_player).getFd() == std::stoi(params, nullptr, 10))
	{
	  find = 1;
	  std::transform(resp.begin(), resp.end(), resp.begin(), ::toupper);
	  type = convertType[resp];
	  if ((*it_player).removeOneItem(type) == 0)
	    _map[(*it_player).getX()][(*it_player).getY()].items[type] += 1;

	  is_already = false;
	  std::vector<Player>::iterator check = _map[(*it_player).getX()][(*it_player).getY()].players.begin();
	  while (check != _map[(*it_player).getX()][(*it_player).getY()].players.end())
	    {
	      if ((*check).getFd() == (*it_player).getFd())
		is_already = true;
	      check++;
	    }
	  if (is_already == false)
	    _map[(*it_player).getX()][(*it_player).getY()].players.push_back((*it_player));
	  else
	    (*check) = (*it_player);

	}
    }

  return (0);
}

int	Game::forkPlayer(std::string &resp)
{
  std::string	delim = " ";
  std::string	params;
  size_t	pos = 0;
  int		find;

  if ((pos = resp.find(delim)) != std::string::npos) {
    params = resp.substr(0, pos);
    resp.erase(0, pos + delim.length());
  }
  else
    return (1);

  find = 0;
  std::vector<Team>::iterator it_team = _teams.begin();
  while (it_team != _teams.end() && find == 0)
    {
      std::vector<Player> tmp = (*it_team).getAllPlayer();
      std::vector<Player>::iterator it_player = tmp.begin();
      while (it_player != tmp.end() && (*it_player).getFd() != std::stoi(params, nullptr, 10))
	it_player++;
      if (it_player == tmp.end())
	it_team++;
      else if ((*it_player).getFd() == std::stoi(params, nullptr, 10))
	{
	  find = 1;
	  if ((pos = resp.find(delim)) != std::string::npos) {
	    params = resp.substr(0, pos);
	    resp.erase(0, pos + delim.length());
	  }
	  else
	    return (1);
	}
    }

  return (0);
}

int	Game::egg(std::string &resp)
{
  std::string	delim = " ";
  std::string	params;
  size_t	pos = 0;

  if ((pos = resp.find(delim)) != std::string::npos) {
    params = resp.substr(0, pos);
    resp.erase(0, pos + delim.length());
  }
  else
    return (1);

  std::vector<Team>::iterator it_team = _teams.begin();
  while (it_team != _teams.end() && (*it_team).getName() != params)
    it_team++;

  if ((pos = resp.find(delim)) != std::string::npos) {
    params = resp.substr(0, pos);
    resp.erase(0, pos + delim.length());
  }
  else
    return (1);
  return (0);
}

int	Game::elevationAll(std::string &resp)
{
  std::string	delim = " ";
  std::string	params;
  size_t	pos = 0;
  int	find;

  if ((pos = resp.find(delim)) != std::string::npos) {
    params = resp.substr(0, pos);
    resp.erase(0, pos + delim.length());
  }
  else
    return (1);

  find = 0;
  std::vector<Team>::iterator it_team = _teams.begin();
  while (it_team != _teams.end() && find == 0)
    {
      std::vector<Player> tmp = (*it_team).getAllPlayer();
      std::vector<Player>::iterator it_player = tmp.begin();
      while (it_player != tmp.end() && (*it_player).getFd() != std::stoi(params, nullptr, 10))
	it_player++;
      if (it_player == tmp.end())
	it_team++;
      else if ((*it_player).getFd() == std::stoi(params, nullptr, 10))
	{
	  find = 1;
	  if ((pos = resp.find(delim)) != std::string::npos) {
	    params = resp.substr(0, pos);
	    resp.erase(0, pos + delim.length());
	  }
	  else
	    return (1);
	}
    }

  return (0);
}

int	Game::elevationPlayer(std::string &resp)
{
  std::string	delim = " ";
  std::string	params;
  size_t	pos = 0;
  int		find;

  if ((pos = resp.find(delim)) != std::string::npos) {
    params = resp.substr(0, pos);
    resp.erase(0, pos + delim.length());
  }
  else
    return (1);

  find = 0;
  std::vector<Team>::iterator it_team = _teams.begin();
  while (it_team != _teams.end() && find == 0)
    {
      std::vector<Player> tmp = (*it_team).getAllPlayer();
      std::vector<Player>::iterator it_player = tmp.begin();
      while (it_player != tmp.end() && (*it_player).getFd() != std::stoi(params, nullptr, 10))
	it_player++;
      if (it_player == tmp.end())
	it_team++;
      else if ((*it_player).getFd() == std::stoi(params, nullptr, 10))
	find = 1;
    }

  return (0);
}

int	Game::cast(std::string &resp)
{
  std::string	delim = " ";
  std::string	params;
  size_t	pos = 0;
  int		find;

  if ((pos = resp.find(delim)) != std::string::npos) {
    params = resp.substr(0, pos);
    resp.erase(0, pos + delim.length());
  }
  else
    return (1);

  find = 0;
  std::vector<Team>::iterator it_team = _teams.begin();
  while (it_team != _teams.end() && find == 0)
    {
      std::vector<Player> tmp = (*it_team).getAllPlayer();
      std::vector<Player>::iterator it_player = tmp.begin();
      while (it_player != tmp.end() && (*it_player).getFd() != std::stoi(params, nullptr, 10))
	it_player++;
      if (it_player == tmp.end())
	it_team++;
      else if ((*it_player).getFd() == std::stoi(params, nullptr, 10))
	find = 1;
    }

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

Game::~Game() {}
