#ifndef CONNECT_H
#define CONNECT_H
#include "base.h"

class andConnector : public Base{
  private:
    Base* child1, child2;
  public:
    andConnector(Base* a, Base* b);
    bool execute(bool b);
};

class orConnector : public Base{
  private:
    Base* child1, child2;
  public:
    orConnector(Base* a, Base* b);
    bool execute(bool b);
};

class noneConnector : public Base{
  private:
    Base* child1;
  public:
    noneConnector(Base* a);
    bool execute(bool b);
};



#endif