#ifndef AI_H
# define AI_H

# include <iostream>
# include <vector>
# include <map>
# include <functional>
# include "Inventory.h"
# include "ConnectClient.h"

class Ai {
public:
  Ai();
  ~Ai();

public:
  enum class ActionType {
    UNKNOWN = -1,
    FORWARD,
    RIGHT,
    LEFT,
    LOOK,
    INVENTORY,
    BROADCAST,
    FORK,
    EJECT,
    TAKE,
    SET,
    INCANTATION
  };

  enum class Direction {
    UNKNOWN = -1,
    UP,
    RIGHT,
    DOWN,
    LEFT
  };

private:
  // perso
  typedef  void(Inventory::*add_pointer)();
  std::map<std::string, add_pointer> _TabAdd;
  typedef  const int &(Inventory::*material_pointer)() const;
  std::map<std::string, material_pointer> _TabMaterial;
  typedef  int (Ai::*action_pointer)(const std::string &);
  std::map<ActionType, action_pointer> _TabAction;
  std::vector<std::vector<ActionType>> _closeAction;
  int _level;
  Inventory _bag;
  std::vector<Inventory> _viewMaterial;
  int _life;
  std::pair<Ai::ActionType, std::string>  _action;
  Ai::Direction _dir;
  std::vector<ActionType> _path;
  std::string _response;
  int _fd;
  int _nbResponse;
  bool  _isRunning;
  std::vector<Inventory*>  _invToInc;
  std::string _materialObj;
  bool  _isCalled;
  bool  _CalledSomeone;
  int		_goToPlayer;
  bool  _isDead;

public:
  ConnectClient connect;

public:
  const int &getLevel() const;
  void setLevel(const int &);
  const Inventory &getBag() const;
  void setBag(const Inventory &);
  const std::vector<Inventory> &getViewMaterial() const;
  void setViewMaterial(const std::vector<Inventory> &);
  const int &getLife() const;
  void setLife(const int &);
  const std::pair<Ai::ActionType, std::string> &getAction() const;
  void setAction(const std::pair<Ai::ActionType, std::string> &);
  const std::string &getResponse() const;
  void printResponse();
  void setResponse(const std::string &);
  const int &getFd() const;
  void setFd(const int &);

  int	forward(const std::string &);
  int right(const std::string &);
  int left(const std::string &);
  int look(const std::string &);
  int inventory(const std::string &);
  int broadcast(const std::string &);
  int fork(const std::string &);
  int eject(const std::string &);
  int take(const std::string &);
  int set(const std::string &);
  int incantation(const std::string &);

  int aiBrain();
  void fillBag();
  bool checkHook(const std::string &);
  void fillView();
  void fillPath(const std::string &);
  void goToPlayer();
  int checkServerMessage(const std::string &);
  void ReplaceStringInPlace(std::string& subject, const std::string& search, const std::string& replace);
  void randInventory();
  bool  checkElevation();
  bool  inventoryCompare(const Inventory &, const Inventory &);
  void  whatMaterialToFind(const Inventory &);
  std::map<std::string, int>  returnTabInv(const Inventory &) const;
  void  setMaterials(const Inventory &);
  void  getCaseIncantation();
  bool  checkIfPerson(const Inventory &);
};

#endif
