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
  // cout << "HOOPLA" << endl;
  this->ran = false;
  this->size = size;
  int i = 0;
  args = new char*[500];
  for (i = 0; i < size; ++i){
    this->args[i] = argv[i];
  }
  args[i] = NULL;
  // for (i = 0; i < size; ++i){
  //   cout << args[i] << " " << endl;
  // }
}

Executable::~Executable(){
  delete[] args;
}

bool Executable::execute(bool b){
  if (ran){
    return false;
  }
  else {
    this->ran = true; //sets if it has been ran or not
  }
  
  if (strcmp(args[0], "exit") == 0){
    exit(0);
  }

  pid_t pid = fork();

  if (pid == -1){ //to handle fork error
    perror("fork");
    return false;
  }
  else if (pid == 0){ //child process
    execvp(args[0], args);
    perror("execvp");
    return false;
  }
  else if(pid > 0){
    int status;
    if(waitpid(pid, &status, 0) == -1){ //makes the parent process wait
      perror("waitpid");
    }
  }
  return true;
}


