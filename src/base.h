#ifndef BASE_H
#define BASE_H
#include <iostream>
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
    char** args;
  public:
    Executable(int size, char* argv[]);
    ~Executable();
    bool execute(bool b);
};

class Test : public Base{
  private:
    int size;
    bool ran;
    char** args;
  public:
    Test(int size, char* argv[]);
    ~Test();
    bool execute(bool b);
};

#endif