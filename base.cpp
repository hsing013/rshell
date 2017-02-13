#include <iostream>
#include <string.h> //for strtok
#include <unistd.h> //for execvp
#include <stdio.h> // for perror
#include <errno.h>
#include "base.h"
using namespace std;

Executable::Executable(char* cmd, int size, char* argv[]){
  success = false;
  this->cmd = cmd;
  this->size = size;
  argv[size + 1];
  for(unsigned i = 0; i < size; ++i){
    this->argv[i] = argv[i];
  }
}

Single::Single(Executable* b){ //to be implemented
  
}