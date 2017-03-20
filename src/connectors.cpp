#include "connectors.h"
#include "base.h"
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <fstream>
#include <stdio.h> // for perror
using namespace std;

andConnector::andConnector(Base* a, Base* b){
    child1 = a;
    child2 = b;
}

string andConnector::fetchFile(){
  return "This is the andConnector.";
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

string orConnector::fetchFile(){
  return "This is the orConnector.";
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

string noneConnector::fetchFile(){
  return "This is the noneConnector.";
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

string Pipe::fetchFile(){
  return "This is the Pipe connector.";
}

bool Pipe::execute(int b, int b2){
  int pipefd[2]; 
  int result = pipe(pipefd); //creates a pipe
  if (result == -1){
    perror("pipe");
    return false;
  }
  // cout << pipefd[1] << endl;
  if (child1->execute(b, pipefd[1]) == false){
    child2->execute(0, -99);
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

Input::Input(Base* a, Base* b){
  child1 = a;
  child2 = b;
}

string Input::fetchFile(){
  return "This is the Input connector.";
}

bool Input::execute(int b, int b2){
  string file = child2->fetchFile();
  b = open(file.c_str(),O_RDONLY);
  return child1->execute(b, b2);
}

Output::Output(Base* a, Base* b){
  child1 = a;
  child2 = b;
}

string Output::fetchFile(){
  return "This is the Output connector.";
}

bool Output::execute(int b, int b2){
  string file = child2->fetchFile();
  b2 = open(file.c_str(),O_WRONLY| O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
  return child1->execute(b, b2);
}

Output2::Output2(Base* a, Base* b){
  child1 = a;
  child2 = b;
}

string Output2::fetchFile(){
  return "This is the Output2 connector.";
}

bool Output2::execute(int b, int b2){
  string file = child2->fetchFile();
  b2 = open(file.c_str(), O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
  return child1->execute(b, b2);
}