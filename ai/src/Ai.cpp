//
// Ai.cpp for  in /home/andre/reseau/Zappy/ai/src
//
// Made by andre
// Login   <andre@epitech.net>
//
// Started on  Tue Jun 27 03:01:54 2017 andre
// Last update Tue Jun 27 03:02:16 2017 andre
//

# include <sstream>
# include <stdio.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <string.h>
# include "Ai.h"

Ai::Ai() : _level(1), _life(1260), _action({Ai::ActionType::UNKNOWN, ""}), _dir(Ai::Direction::UNKNOWN), _nbResponse(0), _isRunning(true), _materialObj("food"), _isCalled(false), _CalledSomeone(false), _isDead(false) {
  _TabAdd["food"] = &Inventory::addFood;
  _TabAdd["linemate"] = &Inventory::addLinemate;
  _TabAdd["deraumere"] = &Inventory::addDeraumere;
  _TabAdd["sibur"] = &Inventory::addSibur;
  _TabAdd["mendiane"] = &Inventory::addMendiane;
  _TabAdd["phiras"] = &Inventory::addPhiras;
  _TabAdd["thystame"] = &Inventory::addThystame;
  _TabAdd["player"] = &Inventory::addPlayer;

  _TabMaterial["food"] = &Inventory::getFood;
  _TabMaterial["linemate"] = &Inventory::getLinemate;
  _TabMaterial["deraumere"] = &Inventory::getDeraumere;
  _TabMaterial["sibur"] = &Inventory::getSibur;
  _TabMaterial["mendiane"] = &Inventory::getMendiane;
  _TabMaterial["phiras"] = &Inventory::getPhiras;
  _TabMaterial["thystame"] = &Inventory::getThystame;

  _TabAction[ActionType::FORWARD] = &Ai::forward;
  _TabAction[ActionType::RIGHT] = &Ai::right;
  _TabAction[ActionType::LEFT] = &Ai::left;
  _TabAction[ActionType::TAKE] = &Ai::take;
  _TabAction[ActionType::INVENTORY] = &Ai::inventory;

  _closeAction.push_back({ActionType::LOOK});
  _closeAction.push_back({ActionType::FORWARD});
  _closeAction.push_back({ActionType::FORWARD, ActionType::LEFT, ActionType::FORWARD, ActionType::RIGHT});
  _closeAction.push_back({ActionType::LEFT, ActionType::FORWARD});
  _closeAction.push_back({ActionType::LEFT, ActionType::LEFT, ActionType::FORWARD, ActionType::RIGHT, ActionType::FORWARD, ActionType::LEFT});
  _closeAction.push_back({ActionType::LEFT, ActionType::LEFT, ActionType::FORWARD});
  _closeAction.push_back({{ActionType::RIGHT, ActionType::FORWARD, ActionType::RIGHT, ActionType::FORWARD}});
  _closeAction.push_back({ActionType::RIGHT, ActionType::FORWARD});
  _closeAction.push_back({{ActionType::RIGHT, ActionType::FORWARD, ActionType::LEFT, ActionType::FORWARD}});

  _invToInc.push_back(new Inventory(1, 1, 0, 0, 0, 0, 0));
  _invToInc.push_back(new Inventory(2, 1, 1, 1, 0, 0, 0));
  _invToInc.push_back(new Inventory(2, 2, 0, 1, 0, 2, 0));
  _invToInc.push_back(new Inventory(4, 1, 1, 2, 0, 1, 0));
  _invToInc.push_back(new Inventory(4, 1, 2, 1, 3, 0, 0));
  _invToInc.push_back(new Inventory(6, 1, 2, 3, 0, 1, 0));
  _invToInc.push_back(new Inventory(6, 2, 2, 2, 2, 2, 1));
}

Ai::~Ai() {}

const int &Ai::getLevel() const {
  return _level;
}

void Ai::setLevel(const int &var) {
  _level = var;
}

const Inventory &Ai::getBag() const {
  return _bag;
}

void Ai::setBag(const Inventory &var) {
  _bag = var;
}

const std::vector<Inventory> &Ai::getViewMaterial() const {
  return _viewMaterial;
}

void Ai::setViewMaterial(const std::vector<Inventory> &var) {
  _viewMaterial = var;
}

const int &Ai::getLife() const {
  return _life;
}

void Ai::setLife(const int &var) {
  _life = var;
}

const int &Ai::getFd() const {
  return _fd;
}

void Ai::setFd(const int &var) {
  _fd = var;
}

const std::pair<Ai::ActionType, std::string> &Ai::getAction() const {
  return _action;
}

void Ai::setAction(const std::pair<Ai::ActionType, std::string> &var) {
  _action = var;
}

const std::string &Ai::getResponse() const {
  return _response;
}

void Ai::printResponse()
{
  std::cout << _response;
}

void Ai::setResponse(const std::string &var) {
  _response = var;
}

int Ai::forward(const std::string &var) {
  (void)var;

  if (_isDead == true)
    return (-1);
  connect.sendToServ(strdup("forward\n"));
  std::cout << "forward" << std::endl;
  _response = connect.getResponse();
  if (_response.size() == 0)
    return (-1);
  _action.first = Ai::ActionType::FORWARD;
  _life--;
  _goToPlayer = -1;
  std::size_t found_ok = _response.find("ok");
  std::size_t found_ko = _response.find("ko");
  while (found_ok == std::string::npos && found_ko == std::string::npos)
    {
      if (checkServerMessage(_response) == -1) {
        std::cout << "C EST PASSE" << std::endl;
        return (-1);
      }
      _response = connect.getResponse();
      if (_response.size() == 0)
        return (-1);
      found_ok = _response.find("ok");
      found_ko = _response.find("ko");
    }
  printResponse();
  if (_goToPlayer != -1)
    {
      for (int i = 0; i < static_cast<int>(_closeAction[_goToPlayer].size()); i++)
        {
          std::map<Ai::ActionType, action_pointer>::iterator it;
          it = _TabAction.find(_closeAction[_goToPlayer][i]);
          if (it != _TabAction.end())
            ((*this).*(*it).second)("food");
        }
    }
  return (0);
}

int Ai::right(const std::string &var) {
  (void)var;

  if (_isDead == true)
    return (-1);
  connect.sendToServ(strdup("right\n"));
  std::cout << "right" << std::endl;
  _response = connect.getResponse();
  if (_response.size() == 0)
    return (-1);
  _action.first = Ai::ActionType::RIGHT;
  _life--;
  _goToPlayer = -1;
  std::size_t found_ok = _response.find("ok");
  std::size_t found_ko = _response.find("ko");
  while (found_ok == std::string::npos && found_ko == std::string::npos)
    {
      if (checkServerMessage(_response) == -1) {
        std::cout << "C EST PASSE" << std::endl;
        return (-1);
      }
      _response = connect.getResponse();
      if (_response.size() == 0)
        return (-1);
      found_ok = _response.find("ok");
      found_ko = _response.find("ko");
    }
  printResponse();
  if (_goToPlayer != -1)
    {
      for (int i = 0; i < static_cast<int>(_closeAction[_goToPlayer].size()); i++)
        {
          std::map<Ai::ActionType, action_pointer>::iterator it;
          it = _TabAction.find(_closeAction[_goToPlayer][i]);
          if (it != _TabAction.end())
            ((*this).*(*it).second)("food");
        }
    }
  return (0);
}

int Ai::left(const std::string &var) {
  (void)var;

  if (_isDead == true)
    return (-1);
  connect.sendToServ(strdup("left\n"));
  std::cout << "left" << std::endl;
  _response = connect.getResponse();
  if (_response.size() == 0)
    return (-1);
  _action.first = Ai::ActionType::LEFT;
  _life--;
  _goToPlayer = -1;
  std::size_t found_ok = _response.find("ok");
  std::size_t found_ko = _response.find("ko");
  while (found_ok == std::string::npos && found_ko == std::string::npos)
    {
      if (checkServerMessage(_response) == -1) {
        std::cout << "C EST PASSE" << std::endl;
        return (-1);
      }
      _response = connect.getResponse();
      if (_response.size() == 0)
        return (-1);
      found_ok = _response.find("ok");
      found_ko = _response.find("ko");
    }
  printResponse();
  if (_goToPlayer != -1)
    {
      for (int i = 0; i < static_cast<int>(_closeAction[_goToPlayer].size()); i++)
        {
          std::map<Ai::ActionType, action_pointer>::iterator it;
          it = _TabAction.find(_closeAction[_goToPlayer][i]);
          if (it != _TabAction.end())
            ((*this).*(*it).second)("food");
        }
    }
  return (0);
}

int Ai::look(const std::string &var)
{
  (void)var;
  std::string tmp;

  if (_isDead == true)
    return (-1);
  connect.sendToServ(strdup("look\n"));
  std::cout << "look" << std::endl;
  _response = connect.getResponse();
  if (_response.size() == 0)
    return (-1);
  _action.first = Ai::ActionType::LOOK;
  _life--;
  _goToPlayer = -1;
  std::size_t found_hook = _response.find("[");
  while (found_hook == std::string::npos)
    {
      if (_isDead == true)
        return (-1);
      if (checkServerMessage(_response) == -1) {
        std::cout << "C EST PASSE" << std::endl;
        return (-1);
      }
      _response = connect.getResponse();
      if (_response.size() == 0)
        return (-1);
      found_hook = _response.find("[");
    }
    if (_isDead == false)
      {
        while (checkHook(_response) == false) {
          tmp.clear();
          tmp = connect.getResponse();
          if (tmp.size() == 0)
            return (-1);
          _response += tmp;
        }
        std::size_t found_death = _response.find("dead");
        if (found_death != std::string::npos)
          {
            _isDead = true;
            printResponse();
            return (-1);
          }
        else
          {
            printResponse();
            fillView();
            if (_goToPlayer != -1)
              {
                for (int i = 0; i < static_cast<int>(_closeAction[_goToPlayer].size()); i++)
                  {
                    std::map<Ai::ActionType, action_pointer>::iterator it;
                    it = _TabAction.find(_closeAction[_goToPlayer][i]);
                    if (it != _TabAction.end())
                      ((*this).*(*it).second)("food");
                  }
              }
          }
    }
  return (0);
}

int Ai::inventory(const std::string &var)
{
  (void)var;

  if (_isDead == true)
    return (-1);
  connect.sendToServ(strdup("inventory\n"));
  std::cout << "inventory" << std::endl;
  _response = connect.getResponse();
  if (_response.size() == 0)
    return (-1);
  _action.first = Ai::ActionType::INVENTORY;
  _life--;
  _goToPlayer = -1;
  std::size_t found_hook = _response.find("[");
  while (found_hook == std::string::npos)
    {
      if (checkServerMessage(_response) == -1) {
        std::cout << "C EST PASSE" << std::endl;
        return (-1);
      }
      _response = connect.getResponse();
      if (_response.size() == 0)
        return (-1);
      found_hook = _response.find("[");
    }
  printResponse();
  fillBag();
  if (_goToPlayer != -1)
    {
      for (int i = 0; i < static_cast<int>(_closeAction[_goToPlayer].size()); i++)
        {
          std::map<Ai::ActionType, action_pointer>::iterator it;
          it = _TabAction.find(_closeAction[_goToPlayer][i]);
          if (it != _TabAction.end())
            ((*this).*(*it).second)("food");
        }
    }
  return (0);
}

int Ai::broadcast(const std::string &var)
{
  std::stringstream resp;

  if (_isDead == true)
    return (-1);
  resp << "broadcast " << var << "\n";
  connect.sendToServ((char *)resp.str().c_str());
  std::cout << resp.str();
  _response = connect.getResponse();
  if (_response.size() == 0)
    return (-1);
  _action.first = Ai::ActionType::BROADCAST;
  _life--;
  _goToPlayer = -1;
  std::size_t found_ok = _response.find("ok");
  std::size_t found_ko = _response.find("ko");
  while (found_ok == std::string::npos && found_ko == std::string::npos)
    {
      if (checkServerMessage(_response) == -1) {
        std::cout << "C EST PASSE" << std::endl;
        return (-1);
      }
      _response = connect.getResponse();
      if (_response.size() == 0)
        return (-1);
      found_ok = _response.find("ok");
      found_ko = _response.find("ko");
    }
  printResponse();
  if (_goToPlayer != -1)
    {
      for (int i = 0; i < static_cast<int>(_closeAction[_goToPlayer].size()); i++)
        {
          std::map<Ai::ActionType, action_pointer>::iterator it;
          it = _TabAction.find(_closeAction[_goToPlayer][i]);
          if (it != _TabAction.end())
            ((*this).*(*it).second)("food");
        }
    }
  return (-1);
}

int Ai::fork(const std::string &var)
{
  (void)var;

  if (_isDead == true)
    return (-1);
  connect.sendToServ(strdup("fork\n"));
  std::cout << "fork" << std::endl;
  _response = connect.getResponse();
  if (_response.size() == 0)
    return (-1);
  _action.first = Ai::ActionType::FORK;
  _life--;
  _goToPlayer = -1;
  std::size_t found_ok = _response.find("ok");
  std::size_t found_ko = _response.find("ko");
  while (found_ok == std::string::npos && found_ko == std::string::npos)
    {
      if (checkServerMessage(_response) == -1) {
        std::cout << "C EST PASSE" << std::endl;
        return (-1);
      }
      _response = connect.getResponse();
      if (_response.size() == 0)
        return (-1);
      found_ok = _response.find("ok");
      found_ko = _response.find("ko");
    }
  printResponse();
  if (_goToPlayer != -1)
    {
      for (int i = 0; i < static_cast<int>(_closeAction[_goToPlayer].size()); i++)
        {
          std::map<Ai::ActionType, action_pointer>::iterator it;
          it = _TabAction.find(_closeAction[_goToPlayer][i]);
          if (it != _TabAction.end())
            ((*this).*(*it).second)("food");
        }
    }
  return (0);
}

int Ai::eject(const std::string &var)
{
  (void)var;

  if (_isDead == true)
    return (-1);
  connect.sendToServ(strdup("eject\n"));
  std::cout << "eject" << std::endl;
  _response = connect.getResponse();
  if (_response.size() == 0)
    return (-1);
  _action.first = Ai::ActionType::EJECT;
  _life--;
  _goToPlayer = -1;
  std::size_t found_ok = _response.find("ok");
  std::size_t found_ko = _response.find("ko");
  while (found_ok == std::string::npos && found_ko == std::string::npos)
    {
      if (checkServerMessage(_response) == -1) {
        std::cout << "C EST PASSE" << std::endl;
        return (-1);
      }
      _response = connect.getResponse();
      if (_response.size() == 0)
        return (-1);
      found_ok = _response.find("ok");
      found_ko = _response.find("ko");
    }
  printResponse();
  if (_goToPlayer != -1)
    {
      for (int i = 0; i < static_cast<int>(_closeAction[_goToPlayer].size()); i++)
        {
          std::map<Ai::ActionType, action_pointer>::iterator it;
          it = _TabAction.find(_closeAction[_goToPlayer][i]);
          if (it != _TabAction.end())
            ((*this).*(*it).second)("food");
        }
    }
  return (0);
}

int Ai::take(const std::string &var)
{
  std::stringstream resp;

  if (_isDead == true)
    return (-1);
  resp << "take " << var << "\n";
  connect.sendToServ((char *)resp.str().c_str());
  std::cout << resp.str();
  _response = connect.getResponse();
  if (_response.size() == 0)
    return (-1);
  _action.first = Ai::ActionType::TAKE;
  _life--;
  _goToPlayer = -1;
  std::size_t found_ok = _response.find("ok");
  std::size_t found_ko = _response.find("ko");
  while (found_ok == std::string::npos && found_ko == std::string::npos)
    {
      if (checkServerMessage(_response) == -1) {
        std::cout << "C EST PASSE" << std::endl;
        return (-1);
      }
      _response = connect.getResponse();
      if (_response.size() == 0)
        return (-1);
      found_ok = _response.find("ok");
      found_ko = _response.find("ko");
    }
  printResponse();
  if (_goToPlayer != -1)
    {
      for (int i = 0; i < static_cast<int>(_closeAction[_goToPlayer].size()); i++)
        {
          std::map<Ai::ActionType, action_pointer>::iterator it;
          it = _TabAction.find(_closeAction[_goToPlayer][i]);
          if (it != _TabAction.end())
            ((*this).*(*it).second)("food");
        }
    }
  return (0);
}

int Ai::set(std::string const &var)
{
  std::stringstream resp;

  if (_isDead == true)
    return (-1);
  resp << "set " << var << "\n";
  connect.sendToServ((char *)resp.str().c_str());
  std::cout << resp.str();
  _response = connect.getResponse();
  if (_response.size() == 0)
    return (-1);
  _action.first = Ai::ActionType::SET;
  _life--;
  _goToPlayer = -1;
  std::size_t found_ok = _response.find("ok");
  std::size_t found_ko = _response.find("ko");
  while (found_ok == std::string::npos && found_ko == std::string::npos)
    {
        if (checkServerMessage(_response) == -1) {
          std::cout << "C EST PASSE" << std::endl;
          return (-1);
        }
        _response = connect.getResponse();
        if (_response.size() == 0)
          return (-1);
      found_ok = _response.find("ok");
      found_ko = _response.find("ko");
    }
  printResponse();
  if (_goToPlayer != -1)
    {
      for (int i = 0; i < static_cast<int>(_closeAction[_goToPlayer].size()); i++)
        {
          std::map<Ai::ActionType, action_pointer>::iterator it;
          it = _TabAction.find(_closeAction[_goToPlayer][i]);
          if (it != _TabAction.end())
            ((*this).*(*it).second)("food");
        }
    }
  return (0);
}

int Ai::incantation(std::string const &var)
{
  (void)var;

  if (_isDead == true)
    return (-1);
  connect.sendToServ(strdup("incantation\n"));
  std::cout << "incantation" << std::endl;
  _response = connect.getResponse();
  if (_response.size() == 0)
    return (-1);
  _action.first = Ai::ActionType::INCANTATION;
  _life--;
  _goToPlayer = -1;
  std::size_t found_level = _response.find("level");
  std::size_t found_ko = _response.find("ko");;
  while (found_level == std::string::npos
          && found_ko == std::string::npos)
    {
      if (checkServerMessage(_response) == -1) {
        std::cout << "C EST PASSE" << std::endl;
        return (-1);
      }
      _response = connect.getResponse();
      if (_response.size() == 0)
        return (-1);
      found_level = _response.find("level");
      found_ko = _response.find("ko");
    }
  found_ko = _response.find("ko");
  if (found_ko != std::string::npos)
  {
    _isCalled = false;
    _CalledSomeone = false;
    inventory("incantation");
    look("incantation");
    left("incantation");
    forward("incantation");
  }
  else if (found_level != std::string::npos)
    _level++;
  printResponse();
  if (_goToPlayer != -1)
    {
      for (int i = 0; i < static_cast<int>(_closeAction[_goToPlayer].size()); i++)
        {
          std::map<Ai::ActionType, action_pointer>::iterator it;
          it = _TabAction.find(_closeAction[_goToPlayer][i]);
          if (it != _TabAction.end())
            ((*this).*(*it).second)("food");
        }
    }
  _CalledSomeone = false;
  return (0);
}

void Ai::fillBag() {
  std::stringstream ss(_response);
  std::vector<std::string> sepFirst;
  std::string tmp;
  std::vector<std::pair<std::string, int>> inv;
  std::pair<std::string, int> temp;
  std::vector<std::string>::const_iterator it;
  size_t  found = _response.find('[');
  int inc = 0;

  if (found >= 1)
    _response.erase(0, (found - 1));
  if (checkHook(_response) == false)
    return ;
  std::cout << "AA" << _response << "BB" << std::endl;
  while (ss >> tmp) {
    for(unsigned int i=0; i< tmp.size(); ++i) {
      if(tmp[i] == ',' || tmp[i] == '[' || tmp[i] == ']')
        tmp.erase(i,1);
      }
    sepFirst.push_back(tmp);
  }
  std::cout << "BONJOUR" << std::endl;
  for (it = sepFirst.begin();it!=sepFirst.end();it++){
    if ((inc % 2) == 0)
      temp.first = sepFirst[inc];
    else {
      temp.second = std::stoi(sepFirst[inc]);
       inv.push_back(temp);
    }
    inc++;
  }
  std::cout << "COUCOU" << std::endl;
  _bag.setFood(inv[0].second);
  _bag.setLinemate(inv[1].second);
  _bag.setDeraumere(inv[2].second);
  _bag.setSibur(inv[3].second);
  _bag.setMendiane(inv[4].second);
  _bag.setPhiras(inv[5].second);
  _bag.setThystame(inv[6].second);
  _response = "";
  std::cout << "SALUT" << std::endl;
}

void Ai::ReplaceStringInPlace(std::string& subject, const std::string& search,
                          const std::string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
}

void Ai::fillView() {
  std::string comma = ",";
  std::string space = " ";
  std::string case_string;
  std::string word_string;
  size_t case_pos = 0;
  size_t word_pos = 0;
  size_t  found = _response.find('[');

  _viewMaterial.clear();
  if (found >= 1)
    _response.erase(0, (found - 1));
  _response.erase(0, 1);
  _response.erase(_response.size() - 1, _response.size());
  _response.push_back(',');
  ReplaceStringInPlace(_response, ", ", ",");
  ReplaceStringInPlace(_response, ",", " ,");
  while ((case_pos = _response.find(comma)) != std::string::npos)
    {
      Inventory fill;
      case_string = _response.substr(0, case_pos);
      while ((word_pos = case_string.find(space)) != std::string::npos) {
        word_string = case_string.substr(0, word_pos);
        std::map<std::string, add_pointer>::iterator it;
        it = _TabAdd.find(word_string);
        if (it != _TabAdd.end())
          {
            (fill.*(*it).second)();
          }
        case_string.erase(0, word_pos + 1);
      }
      _viewMaterial.push_back(fill);
      _response.erase(0, case_pos + 1);
    }
  _bag.setPlayer(_viewMaterial[0].getPlayer());
  _response = "";
}

void Ai::fillPath(const std::string &material) {
  int nb;
  int pos_y = 0;
  int pos_x = 0;
  int check = 0;
  int save;

  nb = -1;
  _path.clear();
  for (int i = 0; i < static_cast<int>(_viewMaterial.size()); i++)
    {
      std::map<std::string, material_pointer>::iterator it;
      it = _TabMaterial.find(material);
      if (it != _TabMaterial.end())
        {
          if ((_viewMaterial[i].*(*it).second)() > 0)
            {
              nb = i;
              i = static_cast<int>(_viewMaterial.size());
            }
        }
    }
  if (nb != -1)
    {
    for (int i = 1; i < static_cast<int>(_viewMaterial.size()); i = i + 2)
      {
        save = check;
        check += i;
        if (nb < check)
          {
            save += pos_y;
            pos_x = nb - save;
            i = static_cast<int>(_viewMaterial.size());
          }
        else
          pos_y++;
      }
    while (pos_y > 0)
      {
        _path.push_back(ActionType::FORWARD);
        pos_y--;
      }
    if (pos_x > 0)
      _path.push_back(ActionType::RIGHT);
    if (pos_x < 0)
      {
        _path.push_back(ActionType::LEFT);
        pos_x *= -1;
      }
    while (pos_x > 0)
      {
        _path.push_back(ActionType::FORWARD);
        pos_x--;
      }
    _path.push_back(ActionType::TAKE);
    _path.push_back(ActionType::INVENTORY);
    }
  else
    {
      _path.push_back((rand()%2 == 1) ? ActionType::RIGHT : ActionType::LEFT);
      _path.push_back(ActionType::FORWARD);
    }
}

bool  Ai::checkHook(const std::string &response) {
  std::size_t found = response.find(']');

  if (found != std::string::npos)
    return true;
  return false;
}

int  Ai::checkServerMessage(const std::string &response) {
  std::string save = response;
  std::size_t found_msg = _response.find("message");
  std::size_t found_start = save.find("start");
  std::size_t found_stop = save.find("stop");
  std::size_t found_level = save.find("level");
  std::size_t found_death = save.find("dead");

  if (found_msg != std::string::npos)
    {
      std::cout << save;
      save.erase(0, 8);
      _goToPlayer = std::stoi(save.substr(0, 1));
      std::size_t comma = save.find(", ");
      if (comma != std::string::npos)
        {
          if (save.size() >= 4)
            {
              save.erase(0, 3);
              if (save.size() >= 1)
                {
                  try
                    {
                        if (std::stoi(save.substr(0, 1)) == _level && found_start != std::string::npos)
                          _isCalled = true;
                        else if (std::stoi(save.substr(0, 1)) == _level && found_stop != std::string::npos) {
                          if (!checkIfPerson(*_invToInc[_level - 1]))
                            _isCalled = false;
                          _goToPlayer = -1;
                        }
                        else
                          {
                            _goToPlayer = -1;
                            _isCalled = false;
                          }
                    }
                  catch (std::invalid_argument&)
                    {
                      _goToPlayer = -1;
                      _isCalled = false;
                    }
                }
            }
          else
            {
              _goToPlayer = -1;
              _isCalled = false;
            }
        }
      else
        {
          _goToPlayer = -1;
          _isCalled = false;
        }
    }
  else if (found_level != std::string::npos)
    {
      std::cout << std::endl << std::endl << std::endl << save << std::endl << std::endl;
      _isCalled = false;
      _level++;
    }
  else if (found_death != std::string::npos)
    {
      _isDead = true;
      return (-1);
    }
  else
    std::cout << save;
  return (0);
}

void  Ai::randInventory() {
  if ((_nbResponse % 5) == 0) {
    inventory("rand");
    _nbResponse = 0;
  }
}

bool  Ai::inventoryCompare(const Inventory &us, const Inventory &obj) {

  if (us.getLinemate() >= obj.getLinemate() && us.getDeraumere() >= obj.getDeraumere() &&
      us.getSibur() >= obj.getSibur() && us.getMendiane() >= obj.getMendiane() && us.getPhiras() >= obj.getPhiras() &&
      us.getThystame() >= obj.getThystame() && _isCalled == false)
    {
      if (us.getPlayer() < obj.getPlayer()) {
        broadcast(std::to_string(_level) + "start");
        _CalledSomeone = true;
        return true;
      }
      else if (us.getPlayer() == obj.getPlayer())
          {
            broadcast(std::to_string(_level) + "stop");
            return (true);
          }
      else
        eject("incantation");
    }
  return false;
}

void  Ai::setMaterials(const Inventory &inv) {
  int inc = 0;
  std::map<std::string, int>  tabInv;

  tabInv = returnTabInv(inv);
  for(std::map<std::string, int>::iterator i = tabInv.begin(); i != tabInv.end(); i++){
    while (inc < i->second) {
      set(i->first);
      inc++;
    }
    inc = 0;
  }
}

std::map<std::string, int>  Ai::returnTabInv(const Inventory &inv) const{
  std::map<std::string, int>  tabInv;

  tabInv["linemate"] = inv.getLinemate();
  tabInv["deraumere"] = inv.getDeraumere();
  tabInv["sibur"] = inv.getSibur();
  tabInv["mendiane"] = inv.getMendiane();
  tabInv["phiras"] = inv.getPhiras();
  tabInv["thystame"] = inv.getThystame();
  return tabInv;
}

bool   Ai::checkIfPerson(const Inventory &inv) {
  if (_bag.getPlayer() <= inv.getPlayer())
    return true;
  return false;
}


void  Ai::whatMaterialToFind(const Inventory &obj) {
  std::map<std::string, int>  usTab;
  std::map<std::string, int>  objTab;

  usTab = returnTabInv(_bag);
  objTab = returnTabInv(obj);

  for(std::map<std::string, int>::iterator i = usTab.begin(); i != usTab.end(); i++) {
    if (usTab[i->first] < objTab[i->first])
      _materialObj = i->first;
  }
}

void  Ai::getCaseIncantation() {
  std::map<std::string, int> tab = returnTabInv(_viewMaterial[0]);
  int inc = 0;

  for(std::map<std::string, int>::iterator i = tab.begin(); i != tab.end(); i++) {
    if (i->first != "player")
      while (inc < i->second) {
        take(i->first);
        inc++;
      }
    inc = 0;
  }
}

bool  Ai::checkElevation() {
  Inventory obj = *_invToInc[_level - 1];

  look("checkElevation");
  if (inventoryCompare(_bag, *_invToInc[_level - 1])) {
    if (_bag.getPlayer() != obj.getPlayer())
      return true;
    setMaterials(*_invToInc[_level - 1]);
    getCaseIncantation();
    incantation("incantation");
    return true;
  }
  else
    whatMaterialToFind(*_invToInc[_level - 1]);
  return false;
}

int   Ai::aiBrain() {
  srand(time(NULL));
  fork("beginning");
  while (_isRunning) {
    if (_isDead == true)
      return (0);
    randInventory();
    inventory("remake");
    if (_bag.getFood() < 10) {
      while (_bag.getFood() < 40) {
        if (look("food") == -1)
          return (0);
        fillPath("food");
        for (int i = 0; i < static_cast<int>(_path.size()); i++)
          {
            std::map<Ai::ActionType, action_pointer>::iterator it;
            it = _TabAction.find(_path[i]);
            if (it != _TabAction.end())
              {
                if (((*this).*(*it).second)("food") == -1)
                  return (0);
              }
          }
        }
    }
    else if (checkElevation())
      continue;
    else if (_CalledSomeone)
      continue;
    else if (_isCalled == false)
    {
      if (look(_materialObj) == -1)
        return (0);
      fillPath(_materialObj);
      for (int i = 0; i < static_cast<int>(_path.size()); i++)
        {
          std::map<Ai::ActionType, action_pointer>::iterator it;
          it = _TabAction.find(_path[i]);
          if (it != _TabAction.end())
            {
              if (((*this).*(*it).second)(_materialObj) == -1)
                return (0);
            }
        }
      }
    _nbResponse++;
  }
  return (0);
}
