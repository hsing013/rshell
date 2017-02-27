#include <iostream>
#include <string.h> //for strtok
#include <unistd.h> //for execvp
#include <stdio.h> // for perror
#include <errno.h>
#include <sys/types.h> 
#include <sys/wait.h> //for waitpid
#include <stdlib.h> // for exit
#include "base.h"
using namespace std;



Executable::Executable(int size, char* argv[]){
  this->ran = false;
  this->size = size;
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
  if (ran){
    return false;
  }
  else {
    this->ran = true; //sets if it has been ran or not
  }
  
  if (strcmp(args[0], "exit") == 0){ // if the command is exit, it exits
    exit(0);
  }

  pid_t pid = fork(); //creates child process

  if (pid == -1){ //to handle fork error
    perror("fork");
    return false;
  }
  else if (pid == 0){ //child process
    execvp(args[0], args);
    perror("execvp");
    exit(0);
  }
  else if(pid > 0){
    int status;
    if(waitpid(pid, &status, 0) == -1){ //makes the parent process wait
      cout << "wait" << endl;
      perror("waitpid");
    }
  }
  return true;
}


