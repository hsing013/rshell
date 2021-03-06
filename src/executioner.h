#ifndef EXECUTIONER_H
#define EXECUTIONER_H
#include "base.h"
#include "connectors.h"
using namespace std;

class Executioner : public Base{
  private:
    string input;
  public:
    Executioner(string input);
    ~Executioner() {};
    bool execute(int b, int b2);
    string fetchFile();
};

#endif