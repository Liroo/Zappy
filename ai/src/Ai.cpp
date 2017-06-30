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

Ai::Ai() : _level(1), _life(1260), _action({Ai::ActionType::UNKNOWN, ""}), _dir(Ai::Direction::UNKNOWN), test(0) {}

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

void Ai::setResponse(const std::string &var) {
  _response = var;
}

void Ai::forward() {
  sendToServ("forward");
  std::cout << "forward" << std::endl;
  _action.first = Ai::ActionType::FORWARD;
  _life--;
}

void Ai::right() {
  sendToServ("right");
  std::cout << "right" << std::endl;
  _action.first = Ai::ActionType::RIGHT;
  _life--;
}

void Ai::left() {
  sendToServ("left");
  std::cout << "left" << std::endl;
  _action.first = Ai::ActionType::LEFT;
  _life--;
}

void Ai::look() {
  sendToServ("look");
  std::cout << "look" << std::endl;
  _action.first = Ai::ActionType::LOOK;
  _life--;
}

void Ai::inventory() {
  sendToServ("inventory");
  std::cout << "inventory" << std::endl;
  _action.first = Ai::ActionType::INVENTORY;
  _life--;
}

void Ai::broadcast(std::string const &var) {
  sendToServ("broadcast");
  std::cout << "broadcast" << var << std::endl;
  _action.first = Ai::ActionType::BROADCAST;
  _life--;
}

void Ai::fork() {
  sendToServ("fork");
  std::cout << "fork" << std::endl;
  _action.first = Ai::ActionType::FORK;
  _life--;
}

void Ai::eject() {
  sendToServ("eject");
  std::cout << "eject" << std::endl;
  _action.first = Ai::ActionType::EJECT;
  _life--;
}

void Ai::take(std::string const &var) {
  sendToServ("take");
  std::cout << "take" << var << std::endl;
  _action.first = Ai::ActionType::TAKE;
  _life--;
}

void Ai::set(std::string const &var) {
  sendToServ("set");
  std::cout << "set" << var << std::endl;
  _action.first = Ai::ActionType::SET;
  _life--;
}

void Ai::incantation() {
  sendToServ("incantation");
  std::cout << "incantation" << std::endl;
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

bool  Ai::checkHook(const std::string &response) {
  std::size_t found = response.find(']');

  if (found != std::string::npos)
    return false;
  return true;
}

int Ai::sendToServ(const std::string &varMessage)
{
  char  message[varMessage.length()];

  std::cout << "test";
  strcpy(message, const_cast<char*>(varMessage.c_str()));
  sprintf(message, "%s\r\n", message);
  if (send(_fd, message, strlen(message), 0) < 0) {
    std::cout << "Message sending error" << std::endl;
    return (1);
  }
  std::cout << "fintest";
  return (0);
}

int   Ai::aiBrain(std::string const &response) {
  if ((_action.first == Ai::ActionType::INVENTORY || _action.first == Ai::ActionType::LOOK) && checkHook(response)) {
    _response = _response + response;
    return (0);
  }
  else if (_action.first == Ai::ActionType::INVENTORY || _action.first == Ai::ActionType::LOOK)
    _response = _response + response;
  else
    _response = response;
  if (_action.first == Ai::ActionType::INVENTORY)
    fillBag();
  std::cout << getResponse();
  if (test == 0)
    sendToServ("toto");
  else if (test == 1)
    inventory();
  else if (test == 2)
    look();
  test++;
  return (0);
}
