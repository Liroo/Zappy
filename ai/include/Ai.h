#ifndef AI_H
# define AI_H

# include <iostream>
# include <vector>
# include <map>
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
  typedef  void(Inventory::*method_pointer)();
  std::map<std::string, method_pointer> _TabAdd;
  typedef  const int &(Inventory::*pointer)() const;
  std::map<std::string, pointer> _TabMaterial;
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

  void forward();
  void right();
  void left();
  void look();
  void inventory();
  void broadcast(std::string const &);
  void fork();
  void eject();
  void take(std::string const &);
  void set(std::string const &);
  void incantation();

  int aiBrain();
  void fillBag();
  bool  checkHook(const std::string &);
  void fillView();
  void fillPath(const std::string &);
  void ReplaceStringInPlace(std::string& subject, const std::string& search, const std::string& replace);
};

#endif
