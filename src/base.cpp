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

string Executable::fetchFile(){
  string temp = args[0];
  return temp;
}

/*executes the command using
execvp, fork and waitpid */
bool Executable::execute(int b, int b2){
  bool ret = true;
  if (ran){
    return false;
  }
  else {
    this->ran = true; //sets if it has been ran or not
  }
  /*if b is false, then that
    means previous AND child didnt 
    execute or it can mean that previous
    OR child did execute*/
  if (!b && b2 == -99){ 
    if (preced){
      Q.pop();
    }
    return false;
  }
  if (b2 == -99){
    b2 = 1;
  }
  if (strcmp(args[0], "exit") == 0){ // if the command is exit, it exits
    exit(0);
  }
  /*If it enclosed within paranthese, then
    it makes a new instance of Executioner
    and passes in a string from a queue
    to be ran and the sends back the result */
  if (preced){ 
    string temp;
    temp = Q.front();
    Q.pop();
    Executioner* e = new Executioner(temp);
    bool result = e->execute(false, 0);
    delete e;
    return result;
  }
 
  pid_t pid = fork(); //creates child process

  if (pid == -1){ //to handle fork error
    perror("fork");
    ret = false;
  }
  else if (pid == 0){ //child process
    if (dup2(b, 0) == -1){
      perror("dup2");
      return false;
    }
    if (dup2(b2, 1) == -1){
      perror("dup2");
      return false;
    }
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

string Test::fetchFile(){
  string temp = args[0];
  return temp;
}

bool Test::execute(int b, int b2){
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
  /*If it enclosed within paranthese, then
    it makes a new instance of Executioner
    and passes in a string from a queue
    to be ran and the sends back the result */
  if (preced){ 
    string temp;
    temp = Q.front();
    Q.pop();
    Executioner* e = new Executioner(temp);
    bool result = e->execute(false, 0);
    delete e;
    return result;
  }

  for (i = 0; i < size; ++i){ //checks for flags
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
  if (i >= size - 1){ //if no flag exists makes i = -1
    i = -1;
  }
  else{
    flag = args[i];
  }
  struct stat sb; //uses stat for test
  int status = stat(args[i + 1], &sb); //calls stats
  if (status == -1){
    perror("stat"); 
    cout << "(False)" << endl;
    return false;
  }
  if (flag == "-d"){ //if flag -d was set
    if (S_ISDIR(sb.st_mode)){
      cout << "(TRUE)" << endl;
      return true;
    }
    else{
      cout << "(False)" << endl;
      return false;
    }
  }
  else if (flag == "-f"){ //if flag -f was set
    if (S_ISREG(sb.st_mode)){
      cout << "(TRUE)" << endl;
      return true;
    }
    else{
      cout << "(False)" << endl;
      return false;
    }
  } 
  else { //if none or -e flag was set
    cout << "(TRUE)" << endl;
    return true;
  }
  return false;
}

