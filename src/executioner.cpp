#include "executioner.h"
#include <iostream>
#include <vector>
#include <string>
#include <string.h> //for strtok
#include <unistd.h> //for execvp
#include <stdio.h> // for perror
#include <errno.h>
#include <stdlib.h> // for exit
#include <vector>
#include <queue>
#include <stack>
#include <utility>
#include <sys/types.h>
#include <pwd.h>
using namespace std;


extern queue<string> Q; 

string fetchConnector(string s){
  if (s == "&&"){
    return "&&";
  }
  else if (s == "||"){
    return "||";
  }
  else if (s == "|"){
    return "|";
  }
  else if (s == ">"){
    return ">";
  }
  else if (s == "<"){
    return "<";
  }
  else if (s == ">>"){
    return ">>";
  }
  else{
    return ";";
  }
}

Executioner::Executioner(string input){
  this->input = input;
}

string Executioner::fetchFile(){
  return "This is the Executioner.";
}

/*parses the input and then executes each
command */
bool Executioner::execute(int b, int b2){
  if (input.size() == 0){ // returns if input is 0
    return false;
  }
  vector<Base*> execs; //holds the executables;
  vector<string> connect; //holds the connectors;
  int sizeOfArray = input.size() + 1;
  char** args = new char*[sizeOfArray];
  char* c = const_cast<char*>(input.c_str()); // makes the string volatile to put into char* cs
  char* tok = strtok(c, " "); // using strtok to break the input
  unsigned i = 0;
  while (tok != NULL){
    args[i] = tok;
    tok = strtok(NULL, " ");
    ++i;
  }
  char** argc = new char*[100]; // temporary holds a command and its arguements
  bool counter = false; // remains true until next command is found
  args[i] = NULL;
  int size = i + 1; //holds the size of the array
  int j = 0; //holds the current index of the array
  bool testType = false; //true if a test is detected
  bool precedType = false; //true if parantheses are present
  int skip = 0;
  for (int i = 0; i < size; ++i){ // makes each command and its arguements into an Executable
    string s;
    if (args[i] != NULL){
      s.append(args[i]);
    }
    else{
      s = "NULL";
    }
    if (((!counter) && s == "[") || (!counter && s == "test")){
      counter = true;
      testType = true;
    }
    else if (!counter){
      if (s == "("){
        precedType = true;
      }
      argc[j] = args[i];
      counter = true;
      ++j;
    }
    else if (s == "NULL"){ // makes an Executable that has no connector
      argc[j + 1] = NULL;
      if (!testType){
        execs.push_back(new Executable(j, argc, precedType));
        connect.push_back(";");
      }
      else{
        execs.push_back(new Test(j, argc, precedType));
        connect.push_back(";");
        testType = false;
      }
      precedType = false;
      break;
    }
    else if ((s == "||" || s == "&&" || s == ";" || s == "|" || s == "<" || s == ">" || s == ">>") && !precedType){ // makes an Executable
      argc[j + 1] = NULL;
      if (!testType){
        execs.push_back(new Executable(j, argc, precedType));
        connect.push_back(fetchConnector(s));
      }
      else{
        execs.push_back(new Test(j, argc, precedType));
        connect.push_back(fetchConnector(s));
        testType = false;
      }
      precedType = false;
      counter = false;
      j = 0;
    }
    else if (s == "(" && precedType){ 
      ++skip;
    }
    else if (s == ")" && precedType && skip != 0){
      argc[j] = c;
      ++j;
      --skip;
    }
    else if (s == ")" && (precedType != false) && (skip == 0)){ //makes an executable or a test with a substring that has parantheses around it
      argc[j + 1] = NULL;
      if (i + 1 != size){
        string strTemp;
        const char* ch = args[i + 1];
        if (ch != NULL){
          strTemp.append(ch);
        }
        else{
          strTemp = ";";
        }
        if (ch == NULL){
          connect.push_back(";");
        }
        else{
           connect.push_back(fetchConnector(strTemp));
        }

        if (!testType){
          execs.push_back(new Executable(j, argc, precedType));
        }
        else{
          execs.push_back(new Test(j, argc, precedType));
        }
        precedType = false;
        counter = false;
        j = 0;
        ++i;
      }
      else{
        if (!testType){
          execs.push_back(new Executable(j, argc, precedType));
        }
        else{
          execs.push_back(new Test(j, argc, precedType));
        }
        connect.push_back(";");
        precedType = false;
        counter = false;
        j = 0;
      }
    }
    else{
      if ((s == "[" || s == "test") && precedType){
        testType = true;
      }
      argc[j] = args[i];
      ++j;
    }
  }
  delete[] args; //deallocate memory
  delete[] argc; //deallocate memory
  stack<Base*> redirect; //holds connectors that perform redirection
  vector<Base*> destroy; // holds connectors that are to be destroyed later
  vector<bool> results;
  bool previousResult = false; //holds the output of the last command, initial is false
  j = 0;
  for (unsigned i = 0; i < execs.size(); ++i, ++j){
    if (connect.at(i) == ";"){ //executes noneConnector commands
      noneConnector* nc = new noneConnector(execs.at(j));
      previousResult = nc->execute(previousResult, 1);
      results.push_back(previousResult);
      destroy.push_back(nc);
      previousResult = false;
    }
    else if (connect.at(i) == "&&"){ // executes andConnector commands
      if (i + 1 == execs.size()){
        cout << "Your input is incomplete e.g(echo hello &&   )" << endl;
        return false;
      }
      andConnector* ac = new andConnector(execs.at(j), execs.at(j + 1));
      previousResult = ac->execute(previousResult, 1);
      if (connect.at(j + 1) == ";"){
        connect.at(j + 1) = "done";
      }
      destroy.push_back(ac);
      results.push_back(previousResult);
    }
    else if (connect.at(i) == "|" || connect.at(i) == "<" || connect.at(i) == ">" || connect.at(i) == ">>"){ // executes Pipe connector commands
      if (i + 1 == execs.size()){
        cout << "Your input is incomplete e.g(ls |  )" << endl;
        return false;
      }
      /*puts all the connectors that perform redirection
        onto a stack where each layer is connected to
        one another */
      for (unsigned h = i; h < connect.size(); ++h){
        if (connect.at(h) == "|" && redirect.empty()){
          redirect.push(new Pipe(execs.at(h), execs.at(h + 1)));
        }
        else if (connect.at(h) == "<" && redirect.empty()){
          redirect.push(new Input(execs.at(h), execs.at(h + 1)));
        }
        else if (connect.at(h) == ">" && redirect.empty()){
          redirect.push(new Output(execs.at(h), execs.at(h + 1)));
        }
        else if (connect.at(h) == ">>" && redirect.empty()){
          redirect.push(new Output2(execs.at(h), execs.at(h + 1)));
        }
        else if (connect.at(h) == "|"){
          if (h == connect.size() - 1){
            cout << "Your input is incomplete e.g(ls |  )" << endl;
            return false;
          }
          redirect.push(new Pipe(redirect.top(), execs.at(h + 1)));
          ++i;
          ++j;
        }
        else if (connect.at(h) == "<"){
          if (h == connect.size() - 1){
            cout << "Your input is incomplete e.g(ls |  )" << endl;
            return false;
          }
          redirect.push(new Input(redirect.top(), execs.at(h + 1)));
          ++i;
          ++j;
        }
        else if (connect.at(h) == ">"){
          if (h == connect.size() - 1){
            cout << "Your input is incomplete e.g(ls |  )" << endl;
            return false;
          }
          redirect.push(new Output(redirect.top(), execs.at(h + 1)));
          ++i;
          ++j;
        }
        else if (connect.at(h) == ">>"){
          if (h == connect.size() - 1){
            cout << "Your input is incomplete e.g(ls |  )" << endl;
            return false;
          }
          redirect.push(new Output2(redirect.top(), execs.at(h + 1)));
          ++i;
          ++j;
        }
        else{
          break;
        }
      }
      Base* p = redirect.top();
      previousResult = p->execute(previousResult, 1);
      int temp = connect.size();
      if (j + 1 != temp && connect.at(j + 1) == ";"){
        connect.at(j + 1) = "done";
      }
      results.push_back(previousResult);
      while (!redirect.empty()){
        destroy.push_back(redirect.top());
        redirect.pop();
      }
    }
    else if (connect.at(i) == "||"){ // executes orConnector commands
      if (i + 1 == execs.size()){
        cout << "Your input is incomplete e.g(echo hello ||   )" << endl;
        return false;
      }
      orConnector* oc = new orConnector(execs.at(j), execs.at(j + 1));
      previousResult = oc->execute(previousResult, 1);
      if (connect.at(j + 1) == ";"){
        connect.at(j + 1) = "done";
      }
      if (i != execs.size() - 1 && connect.at(i + 1) == ";"){
        ++j;
        ++i;
      }
      destroy.push_back(oc);
      results.push_back(previousResult);
    }
  }
  bool finalResult = results.at(results.size() - 1);
  results.resize(0);
  connect.resize(0);
  for (unsigned i = 0; i < execs.size(); ++i){ //deallocates memory
    delete execs.at(i);
  }
  for (unsigned i = 0; i < destroy.size(); ++i){ //deallocate memory
    delete destroy.at(i);
  }
  return finalResult; //sends back the result of the last command, useful for precedence
}