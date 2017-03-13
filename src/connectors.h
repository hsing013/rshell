#ifndef CONNECT_H
#define CONNECT_H
#include "base.h"

class andConnector : public Base{
  private:
    Base* child1;
    Base* child2;
  public:
    ~andConnector() {};
    andConnector(Base* a, Base* b);
    bool execute(int b, int b2);
};

class orConnector : public Base{
  private:
    Base* child1;
    Base* child2;
  public:
    ~orConnector() {};
    orConnector(Base* a, Base* b);
    bool execute(int b, int b2);
};

class noneConnector : public Base{
  private:
    Base* child1;
  public:
    ~noneConnector() {};
    noneConnector(Base* a);
    bool execute(int b, int b2);
};

class Pipe : public Base{
  private:
    Base* child1;
    Base* child2;
  public:
     ~Pipe() {};
     Pipe(Base* a, Base* b);
     bool execute(int b, int b2);
};


#endif