#include <iostream>
#include <string.h> //for strtok
#include <unistd.h> //for execvp
#include <stdio.h> // for perror
#include <errno.h>
#include <queue>
#include <sys/types.h> 
#include <sys/stat.h> // for struct stat
#include <sys/wait.h> //for waitpid
#include <stdlib.h> // for exit
#include "base.h"
#include "executioner.h"
using namespace std;

extern queue<string> Q;

Executable::Executable(int size, char* argv[], bool preced){
  this->ran = false;
  this->size = size;
  this->preced = preced;
  int i = 0;
  args = new char*[500];
  for (i = 0; i < size; ++i){
    this->args[i] = argv[i];
  }
  args[i] = NULL;
}

Executable::~Executable(){
  delete[] args;
}

/*executes the command using
execvp, fork and waitpid */
bool Executable::execute(bool b){
  bool ret = true;
  if (ran){
    return false;
  }
  else {
    this->ran = true; //sets if it has been ran or not
  }

  if (!b){
    if (preced){
      Q.pop();
    }
    return false;
  }

  /*If it enclosed within paranthese, then
    it makes a new instance of Executioner
    and passes in a string from a queue
    to be ran */
  if (preced){ 
    string temp;
    temp = Q.front();
    Q.pop();
    Executioner* e = new Executioner(temp);
    bool result = e->execute(false);
    delete e;
    return result;
  }
  if (strcmp(args[0], "exit") == 0){ // if the command is exit, it exits
    exit(0);
  }
  pid_t pid = fork(); //creates child process

  if (pid == -1){ //to handle fork error
    perror("fork");
    ret = false;
  }
  else if (pid == 0){ //child process
    if (execvp(args[0], args) == -1){
      perror("execvp");
      ret = false;
      exit(1);
    }
  }
  else if(pid > 0){
    int status;
    if(waitpid(pid, &status, 0) == -1){ //makes the parent process wait
      perror("waitpid");
    }
    if (WEXITSTATUS(status) != 0){
      ret = false;
    }
  }
  return ret;
}

Test::Test(int size, char* argv[], bool preced){
  this->ran = false;
  this->size = size;
  this->preced = preced;
  int i = 0;
  args = new char*[500];
  for (i = 0; i < size; ++i){
    this->args[i] = argv[i];
  }
  args[i] = NULL;
}

Test::~Test(){
  delete[] args;
}
bool Test::execute(bool b){
  int i = 0;
  string flag;
  if (ran){
    return false;
  }
  else {
    this->ran = true; //sets if it has been ran or not
  }

  if (!b){
    if (preced){
      Q.pop();
    }
    return false;
  }

  if (preced){ 
    string temp;
    temp = Q.front();
    Q.pop();
    Executioner* e = new Executioner(temp);
    bool result = e->execute(false);
    delete e;
    return result;
  }

  for (i = 0; i < size; ++i){
    if (strcmp(args[i], "-e") == 0){
      break;
    }
    else if (strcmp(args[i], "-f") == 0){
      break;
    }
    else if (strcmp(args[i], "-d") == 0){
      break;
    }
  }
  if (i >= size - 1){
    i = -1;
  }
  else{
    flag = args[i];
  }
  struct stat sb;
  int status = stat(args[i + 1], &sb);
  if (status == -1){
    perror("stat");
    cout << "(False)" << endl;
    return false;
  }
  if (flag == "-d"){
    if (S_ISDIR(sb.st_mode)){
      cout << "(TRUE)" << endl;
      return true;
    }
    else{
      cout << "(False)" << endl;
      return false;
    }
  }
  else if (flag == "-f"){
    if (S_ISREG(sb.st_mode)){
      cout << "(TRUE)" << endl;
      return true;
    }
    else{
      cout << "(False)" << endl;
      return false;
    }
  }
  else {
    cout << "(TRUE)" << endl;
    return true;
  }
  return false;
}
