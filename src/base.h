#ifndef BASE_H
#define BASE_H
#include <iostream>
#include <queue>
using namespace std;

class Base{
  public:
    Base() {};
    virtual ~Base() {};
    virtual bool execute(int b, int b2) = 0;
    virtual string fetchFile() = 0; //returns args[0], useful for I/0 redirection
};

class Executable : public Base{
  protected:
    int size;
    bool ran; //false if is not been executed, true if otherwise
    bool preced;
    char** args;
  public:
    Executable() {};
    Executable(int size, char* argv[], bool preced);
    ~Executable();
    bool execute(int b, int b2);
    string fetchFile();
};

class Test : public Executable{
  public:
    Test(int size, char* argv[], bool preced);
    ~Test() {};
    bool execute(int b, int b2);
    string fetchFile();
};


#endif