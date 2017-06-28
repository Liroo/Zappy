//
// Ai.cpp for  in /home/andre/reseau/Zappy/ai/src
//
// Made by andre
// Login   <andre@epitech.net>
//
// Started on  Tue Jun 27 03:01:54 2017 andre
// Last update Tue Jun 27 03:02:16 2017 andre
//

# include "Ai.h"

Ai::Ai() : _level(1), _life(1260), _action({Ai::ActionType::UNKNOWN, ""}), _dir(Ai::Direction::UNKNOWN) {}

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
  std::cout << "forward" << std::endl;
  _life--;
}

void Ai::right() {
  std::cout << "right" << std::endl;
  _life--;
}

void Ai::left() {
  std::cout << "left" << std::endl;
  _life--;
}

void Ai::look() {
  std::cout << "look" << std::endl;
  _life--;
}

void Ai::inventory() {
  std::cout << "inventory" << std::endl;
  _life--;
}

void Ai::broadcast(std::string const &var) {
  std::cout << "broadcast" << var << std::endl;
  _life--;
}

void Ai::fork() {
  std::cout << "fork" << std::endl;
  _life--;
}

void Ai::eject() {
  std::cout << "eject" << std::endl;
  _life--;
}

void Ai::take(std::string const &var) {
  std::cout << "take" << var << std::endl;
  _life--;
}

void Ai::set(std::string const &var) {
  std::cout << "set" << var << std::endl;
  _life--;
}

void Ai::incantation() {
  std::cout << "incantation" << std::endl;
  _life--;
}

int Ai::aiBrain(std::string const &response) {
  _response = response;
  std::cout << getResponse();
  return (0);
}
