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

Ai::Ai() : _level(1), _life(1260), _action({Ai::ActionType::UNKNOWN, ""}), _dir(Ai::Direction::UNKNOWN), _nbResponse(0) {
  _TabAdd["food"] = &Inventory::addFood;
  _TabAdd["linemate"] = &Inventory::addLinemate;
  _TabAdd["deraumere"] = &Inventory::addDeraumere;
  _TabAdd["sibur"] = &Inventory::addSibur;
  _TabAdd["mendiane"] = &Inventory::addMendiane;
  _TabAdd["phiras"] = &Inventory::addPhiras;
  _TabAdd["thystame"] = &Inventory::addThystame;
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
  std::cout << _response << '\n';;
}

void Ai::setResponse(const std::string &var) {
  _response = var;
}

void Ai::forward() {
  connect.sendToServ(strdup("forward"));
  std::cout << "forward" << std::endl;
  _response = connect.getResponse();
  printResponse();
  _action.first = Ai::ActionType::FORWARD;
  _life--;
}

void Ai::right() {
  connect.sendToServ(strdup("right"));
  std::cout << "right" << std::endl;
  _response = connect.getResponse();
  printResponse();
  _action.first = Ai::ActionType::RIGHT;
  _life--;
}

void Ai::left() {
  connect.sendToServ(strdup("left"));
  std::cout << "left" << std::endl;
  _response = connect.getResponse();
  printResponse();
  _action.first = Ai::ActionType::LEFT;
  _life--;
}

void Ai::look() {
  connect.sendToServ(strdup("look"));
  std::cout << "look" << std::endl;
  _response = connect.getResponse();
  printResponse();
  _action.first = Ai::ActionType::LOOK;
  _life--;
}

void Ai::inventory() {
  connect.sendToServ(strdup("inventory"));
  std::cout << "inventory" << std::endl;
  _response = connect.getResponse();
  printResponse();
  _action.first = Ai::ActionType::INVENTORY;
  _life--;
}

void Ai::broadcast(std::string const &var) {
  connect.sendToServ(strdup("broadcast"));
  std::cout << "broadcast" << var << std::endl;
  _response = connect.getResponse();
  printResponse();
  _action.first = Ai::ActionType::BROADCAST;
  _life--;
}

void Ai::fork() {
  connect.sendToServ(strdup("fork"));
  std::cout << "fork" << std::endl;
  _response = connect.getResponse();
  printResponse();
  _action.first = Ai::ActionType::FORK;
  _life--;
}

void Ai::eject() {
  connect.sendToServ(strdup("eject"));
  std::cout << "eject" << std::endl;
  _response = connect.getResponse();
  printResponse();
  _action.first = Ai::ActionType::EJECT;
  _life--;
}

void Ai::take(std::string const &var) {
  connect.sendToServ(strdup("take"));
  std::cout << "take" << var << std::endl;
  _response = connect.getResponse();
  printResponse();
  _action.first = Ai::ActionType::TAKE;
  _life--;
}

void Ai::set(std::string const &var) {
  connect.sendToServ(strdup("set"));
  std::cout << "set" << var << std::endl;
  _response = connect.getResponse();
  printResponse();
  _action.first = Ai::ActionType::SET;
  _life--;
}

void Ai::incantation() {
  connect.sendToServ(strdup("incantation"));
  std::cout << "incantation" << std::endl;
  _response = connect.getResponse();
  printResponse();
  _action.first = Ai::ActionType::INCANTATION;
  _life--;
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
        std::map<std::string, method_pointer>::iterator it;
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

bool  Ai::checkHook(const std::string &response) {
  std::size_t found = response.find(']');

  if (found != std::string::npos)
    return true;
  return false;
}

bool  Ai::checkDebHook(const std::string &response) {
  std::size_t found = response.find('[');

  if (found != std::string::npos)
    return true;
  return false;
}

int   Ai::aiBrain() {
  std::cout << "aaaaaaa" << std::endl;
  inventory();
  forward();
  right();
  left();
  fork();
  eject();
  /*std::cout << response;
  if ((_action.first == Ai::ActionType::LOOK) && checkDebHook(response)) {
    _response = response;
    return (0);
  }
  else if ((_action.first == Ai::ActionType::LOOK) && checkHook(response)) {
    _response = _response + response;
    fillView();
    return (0);
  }
  else if (_action.first == Ai::ActionType::LOOK)
    _response = _response + response;
  else
    _response = response;
  if (_action.first == Ai::ActionType::INVENTORY)
    fillBag();
  if (_nbResponse == 0)
    connect.sendToServ(strdup("toto");
  else if (_nbResponse == 2)
    inventory();
  else if (_nbResponse >= 3)
    look();
  _nbResponse++;*/
  return (0);
}
