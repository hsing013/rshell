#include "connectors.h"
#include "base.h"
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h> // for perror
using namespace std;

andConnector::andConnector(Base* a, Base* b){
    child1 = a;
    child2 = b;
}

/* if b is true that means that
child1 has been executed therefore
only execute child2. else execute
both and return the AND of both results */
bool andConnector::execute(int b, int b2){
  bool result = b;
  bool result2 = false;
  if (b){
    result2 = child2->execute(true, 0);
  }
  else{
    result = child1->execute(true, 0);
    result2 = child2->execute(result, -99);
  }
  return result && result2;
}

orConnector::orConnector(Base* a, Base* b){
  child1 = a;
  child2 = b;
}

/*returns the OR of both commands
  child2 is passed in the result of
  child1, where if the value passed in
  was true then child2 returns false 
  else returns true */
bool orConnector::execute(int b, int b2){
  bool result = false;
  bool result2 = false;
  if (b){
    return true;
  }
  result = child1->execute(true, 0);
  result2 = child2->execute(!result, -99);
  
  return (result || result2); 
}

noneConnector::noneConnector(Base* a){
  child1 = a;
}

/* store the result from the execution
and send it back */
bool noneConnector::execute(int b, int b2){
  bool result = child1->execute(true, 0);
  return result;
}

Pipe::Pipe(Base* a, Base* b){
  child1 = a;
  child2 = b;
}

bool Pipe::execute(int b, int b2){
  int pipefd[2]; //
  int result = pipe(pipefd); //creates a pipe
  if (result == -1){
    perror("pipe");
    return false;
  }
  // cout << pipefd[1] << endl;
  if (child1->execute(b, pipefd[1]) == false){
    return false;
  }
  // cout << pipefd[1] << endl;
  close(pipefd[1]);
  // cout << pipefd[0] << endl;
  if (child2->execute(pipefd[0], b2) == false){
    return false;
  }

  close(pipefd[0]);

  return true;
}