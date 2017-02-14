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

void Executable::execution(){
  return;
}
char* Executable::getCMD(){
  return cmd;
}
char* Executable::at(int index){
  return argv[index];
}
int Executable::getSize(){
  return size;
}
void Executable::setSuccess(bool b){
  success = b;
}
bool Executable::getSuccess(){
  return success;
}

Single::Single(Base* b){ 
  this->child = b;
}
void Single::execution(){
  int size = getSize();
  char* argv[size + 1];
  for (unsigned i = 0; i < size; ++i){
    argv[i] = at(i);
  }
}
char* Single::getCMD(){
  return child->getCMD();
}
char* Single::at(int index){
  return child->at(index);
}
int Single::getSize(){
  return child->getSize();
}
void Single::setSuccess(bool b){
  child->setSuccess(b);
}
bool Single::getSuccess(){
  return child->getSuccess();
}
