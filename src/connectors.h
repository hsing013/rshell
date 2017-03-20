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
    string fetchFile();
};

class orConnector : public Base{
  private:
    Base* child1;
    Base* child2;
  public:
    ~orConnector() {};
    orConnector(Base* a, Base* b);
    bool execute(int b, int b2);
    string fetchFile();
};

class noneConnector : public Base{
  private:
    Base* child1;
  public:
    ~noneConnector() {};
    noneConnector(Base* a);
    bool execute(int b, int b2);
    string fetchFile();
};

class Pipe : public Base{
  private:
    Base* child1;
    Base* child2;
  public:
     ~Pipe() {};
     Pipe(Base* a, Base* b);
     bool execute(int b, int b2);
     string fetchFile();     
};

class Input : public Base{
  private:
    Base* child1;
    Base* child2;
  public:
    Input(Base* a, Base* b);
    ~Input() {};
    bool execute(int b, int b2);
    string fetchFile();
};

class Output : public Base{
  private:
    Base* child1;
    Base* child2;
  public:
    Output(Base* a, Base* b);
    ~Output() {};
    bool execute(int b, int b2);
    string fetchFile();
};

class Output2 : public Base{
  private:
    Base* child1;
    Base* child2;
  public:
    Output2(Base* a, Base* b);
    ~Output2() {};
    bool execute(int b, int b2);
    string fetchFile();
};
#endif