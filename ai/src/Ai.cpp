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

Ai::Ai() : _level(1), _life(1260), _action({Ai::ActionType::UNKNOWN, ""}), _dir(Ai::Direction::UNKNOWN), _nbResponse(0), _isRunning(true) {
  _TabAdd["food"] = &Inventory::addFood;
  _TabAdd["linemate"] = &Inventory::addLinemate;
  _TabAdd["deraumere"] = &Inventory::addDeraumere;
  _TabAdd["sibur"] = &Inventory::addSibur;
  _TabAdd["mendiane"] = &Inventory::addMendiane;
  _TabAdd["phiras"] = &Inventory::addPhiras;
  _TabAdd["thystame"] = &Inventory::addThystame;

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

void Ai::forward(const std::string &var) {
  (void)var;
  connect.sendToServ(strdup("forward"));
  std::cout << "forward" << std::endl;
  _response = connect.getResponse();
  _action.first = Ai::ActionType::FORWARD;
  _life--;
  if (checkBroadcast(_response) == false)
    printResponse();
}

void Ai::right(const std::string &var) {
  (void)var;
  connect.sendToServ(strdup("right"));
  std::cout << "right" << std::endl;
  _response = connect.getResponse();
  _action.first = Ai::ActionType::RIGHT;
  _life--;
  if (checkBroadcast(_response) == false)
    printResponse();
}

void Ai::left(const std::string &var) {
  (void)var;
  connect.sendToServ(strdup("left"));
  std::cout << "left" << std::endl;
  _response = connect.getResponse();
  _action.first = Ai::ActionType::LEFT;
  _life--;
  if (checkBroadcast(_response) == false)
    printResponse();
}

void Ai::look(const std::string &var) {
  (void)var;
  connect.sendToServ(strdup("look"));
  std::cout << "look" << std::endl;
  _response = connect.getResponse();
  _action.first = Ai::ActionType::LOOK;
  _life--;
  if (checkBroadcast(_response) == false)
    {
      while (checkHook(_response) == false)
        _response += connect.getResponse();
      printResponse();
      fillView();
    }
}

void Ai::inventory(const std::string &var) {
  (void)var;
  connect.sendToServ(strdup("inventory"));
  std::cout << "inventory" << std::endl;
  _response = connect.getResponse();
  _action.first = Ai::ActionType::INVENTORY;
  _life--;
  if (checkBroadcast(_response) == false)
    {
      printResponse();
      fillBag();
    }
}

void Ai::broadcast(const std::string &var) {
  connect.sendToServ(strcat(strdup("broadcast "), var.c_str()));
  std::cout << "broadcast" << var << std::endl;
  _response = connect.getResponse();
  _action.first = Ai::ActionType::BROADCAST;
  _life--;
}

void Ai::fork(const std::string &var) {
  (void)var;
  connect.sendToServ(strdup("fork"));
  std::cout << "fork" << std::endl;
  _response = connect.getResponse();
  _action.first = Ai::ActionType::FORK;
  _life--;
  if (checkBroadcast(_response) == false)
    printResponse();
}

void Ai::eject(const std::string &var) {
  (void)var;
  connect.sendToServ(strdup("eject"));
  std::cout << "eject" << std::endl;
  _response = connect.getResponse();
  _action.first = Ai::ActionType::EJECT;
  _life--;
  if (checkBroadcast(_response) == false)
    printResponse();
}

void Ai::take(const std::string &var) {
  connect.sendToServ(strcat(strdup("take "), var.c_str()));
  std::cout << "take " << var << std::endl;
  _response = connect.getResponse();
  _action.first = Ai::ActionType::TAKE;
  _life--;
  if (checkBroadcast(_response) == false)
      printResponse();
}

void Ai::set(std::string const &var) {
  connect.sendToServ(strcat(strdup("set "), var.c_str()));
  std::cout << "set " << var << std::endl;
  _response = connect.getResponse();
  if (checkBroadcast(_response) == false)
    {
      printResponse();
      _action.first = Ai::ActionType::SET;
      _life--;
    }
}

void Ai::incantation(std::string const &var) {
  (void)var;
  connect.sendToServ(strdup("incantation"));
  std::cout << "incantation" << std::endl;
  _response = connect.getResponse();
  if (checkBroadcast(_response) == false)
    {
      printResponse();
      _action.first = Ai::ActionType::INCANTATION;
      _life--;
    }
}

void Ai::fillBag() {
  std::stringstream ss(_response);
  std::vector<std::string> sepFirst;
  std::string tmp;
  std::vector<std::pair<std::string, int>> inv;
  std::pair<std::string, int> temp;
  std::vector<std::string>::const_iterator it;
  int inc = 0;

  while (ss >> tmp) {
    for(unsigned int i=0; i< tmp.size(); ++i) {
      if(tmp[i] == ',' || tmp[i] == '[' || tmp[i] == ']')
        tmp.erase(i,1);
      }
    sepFirst.push_back(tmp);
  }
  for (it = sepFirst.begin();it!=sepFirst.end();it++){
    if ((inc % 2) == 0)
      temp.first = sepFirst[inc];
    else {
      temp.second = std::stoi(sepFirst[inc]);
       inv.push_back(temp);
    }
    inc++;
  }
  _bag.setFood(inv[0].second);
  _bag.setLinemate(inv[1].second);
  _bag.setDeraumere(inv[2].second);
  _bag.setSibur(inv[3].second);
  _bag.setMendiane(inv[4].second);
  _bag.setPhiras(inv[5].second);
  _bag.setThystame(inv[6].second);
  _response = "";
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

  _viewMaterial.clear();
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
      // random
      _path.push_back(ActionType::FORWARD);
      _path.push_back(ActionType::LEFT);
    }
}

bool  Ai::checkHook(const std::string &response) {
  std::size_t found = response.find(']');

  if (found != std::string::npos)
    return true;
  return false;
}

bool  Ai::checkBroadcast(const std::string &response) {
  std::string a = response;
  std::size_t found = a.find("message");
  int pos = 0;

  if (found != std::string::npos)
    {
      a.erase(0, 8);
      pos = std::stoi(a.substr(0, 1));
      std::size_t comma = a.find(", ");
      if (comma != std::string::npos)
        {
          if (a.size() >= 4)
            a.erase(0, 3);
          if (a.size() >= 1)
            {
              try
                {
                    if (std::stoi(a.substr(0, 1)) == _level)
                      {
                        if (_action.first == ActionType::LOOK)
                          {
                            while (checkHook(_response) == false)
                              _response += connect.getResponse();
                            printResponse();
                            fillView();
                          }
                        else if (_action.first == ActionType::INVENTORY)
                          {
                            _response = connect.getResponse();
                            printResponse();
                            fillBag();
                          }
                        else
                          {
                            _response = connect.getResponse();
                            printResponse();
                          }
                        for (int i = 0; i < static_cast<int>(_closeAction[pos].size()); i++)
                          {
                            std::map<Ai::ActionType, action_pointer>::iterator it;
                            it = _TabAction.find(_closeAction[pos][i]);
                            if (it != _TabAction.end())
                              ((*this).*(*it).second)("food");
                          }
                        return true;
                      }
                }
              catch (std::invalid_argument&)
                {
                  return false;
                }
            }
        }
    }
  return false;
}

int   Ai::aiBrain() {

  while (_isRunning) {
    inventory("zaza");
    if (_bag.getFood() < 10) {
      look("food");
      fillPath("food");
      for (int i = 0; i < static_cast<int>(_path.size()); i++)
        {
          std::map<Ai::ActionType, action_pointer>::iterator it;
          it = _TabAction.find(_path[i]);
          if (it != _TabAction.end())
            ((*this).*(*it).second)("food");
        }
      // while (y a des trucs dans le vector, on les fait)
    }
    // else if (checkElevationPartenaire)
    //   golerejoindre
    // else if (checkElevation)
    //   elevation
    else
      look("food"); // material
      // while (y a des trucs dans le vector, on les fait)
  }
  return (0);
}
