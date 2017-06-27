#ifndef AI_H
# define AI_H

# include <iostream>
# include <vector>
# include "Inventory.h"

class Ai {
public:
  Ai();
  ~Ai();

private:
  // perso
  int level;
  Inventory bag;
  std::vector<Inventory> viewMaterial;

public:
  const int &getLevel() const;
  void setLevel(const int &);
  const Inventory &getBag() const;
  void setBag(const Inventory &);
  const std::vector<Inventory> &getViewMaterial() const;
  void setViewMaterial(const std::vector<Inventory> &);
};

#endif
