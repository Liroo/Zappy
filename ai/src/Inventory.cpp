# include "Inventory.h"

Inventory::Inventory() : _food(0), _linemate(0), _deraumere(0), _sibur(0), _mendiane(0), _phiras(0), _thystame(0) {}

Inventory::~Inventory() {}

const int &Inventory::getLinemate() const {
  return _linemate;
}

void Inventory::addLinemate() {
  _linemate++;
}

void Inventory::setLinemate(const int &mat) {
  _linemate = mat;
}

const int &Inventory::getDeraumere() const {
  return _deraumere;
}

void Inventory::addDeraumere() {
  _deraumere++;
}

void Inventory::setDeraumere(const int &mat) {
  _deraumere = mat;
}

const int &Inventory::getSibur() const {
    return _sibur;
}

void Inventory::addSibur() {
  _sibur++;
}


void Inventory::setSibur(const int &mat) {
  _sibur = mat;
}

const int &Inventory::getMendiane() const {
  return _mendiane;
}

void Inventory::addMendiane() {
  _mendiane++;
}

void Inventory::setMendiane(const int &mat) {
  _mendiane = mat;
}

const int &Inventory::getPhiras() const {
  return _phiras;
}

void Inventory::addPhiras() {
  _phiras++;
}

void Inventory::setPhiras(const int &mat) {
  _phiras = mat;
}

const int &Inventory::getThystame() const {
  return _thystame;
}

void Inventory::addThystame() {
  _thystame++;
}

void Inventory::setThystame(const int &mat) {
  _thystame = mat;
}

const int &Inventory::getFood() const {
  return _food;
}

void Inventory::addFood() {
  _food++;
}

void Inventory::setFood(const int &mat) {
  _food = mat;
}
