#ifndef PIPE_h
#define PIPE_h  
#include "base.h"
#include <iostream>
using namespace std;

class Pipe : public Executable{
  public:
    Pipe(int size, char* argv[], bool preced);
    ~Pipe() {};
    bool execute(bool b);
};

#endif