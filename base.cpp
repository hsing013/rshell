#include <iostream>
#include <string.h> //for strtok
#include <unistd.h> //for execvp
#include <stdio.h> // for perror
#include <errno.h>
#include <sys/types.h> 
#include <sys/wait.h> //for waitpid
#include "base.h"
using namespace std;



Executable::Executable(int size, char* argv[]){
  this->ran = false;
  this->size = size;
  unsigned i = 0;
  for (i = 0; i < size; ++i){
    this->args[i] = argv[i];
  }
  args[i] = NULL;
  // for (unsigned i = 0; i < size; ++i){
  //   cout << args[i] << " ";
  // }
}

bool Executable::execute(bool b){
  if (ran){
    return false;
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


