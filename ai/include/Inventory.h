#ifndef INVENTORY_H
# define INVENTORY_H

class Inventory {
public:
  Inventory();
  ~Inventory();

private:
  int linemate;
  int deraumere;
  int sibur;
  int mendiane;
  int phiras;
  int thystame;

public:
  const int &getLinemate() const;
  void setLinemate(const int &);
  const int &getDeraumere() const;
  void setDeraumere(const int &);
  const int &getSibur() const;
  void setSibur(const int &);
  const int &getMendiane() const;
  void setMendiane(const int &);
  const int &getPhiras() const;
  void setPhiras(const int &);
  const int &getThystame() const;
  void setThystame(const int &);
};

#endif
