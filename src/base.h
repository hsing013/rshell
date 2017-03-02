#ifndef BASE_H
#define BASE_H
#include <iostream>
#include <queue>
using namespace std;

class Base{
  public:
    Base() {};
    virtual ~Base() {};
    virtual bool execute(bool b) = 0;
};

class Executable : public Base{
  protected:
    int size;
    bool ran; //false if is not been executed, true if otherwise
    bool preced;
    char** args;
    queue<string> q;
  public:
    Executable(int size, char* argv[], bool preced, queue<string> &q);
    ~Executable();
    bool execute(bool b);
};

class Test : public Base{
  private:
    int size;
    bool ran;
    bool preced;
    char** args;
    queue<string> q;
  public:
    Test(int size, char* argv[],bool preced, queue<string> &q);
    ~Test();
    bool execute(bool b);
};

#endif