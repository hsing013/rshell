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
#include "base.h"
#include "connectors.h"
using namespace std;

void execution(string input); // carrys out the execution of the input


int main(){
  bool run = true; // true until user wants to exit where it becomes false
  while (run){
    string input;
    cout << "$ ";
    getline(cin, input);
    if (input == "exit"){
      exit(0);
    }

    int size = input.size();
    char* argv[size + 1];
    char* c = const_cast<char*>(input.c_str()); // makes the string volatile to put into char* c
    char* tok = strtok(c, " ");
    int i = 0;

    while (tok != NULL){
      argv[i] = tok;
      tok = strtok(NULL, " ");
      ++i;
    }
    size = i;
    argv[i] = NULL;
  
    // for(unsigned i = 0; i < size; ++i){
    //   cout << argv[i] << " ";
    // }
    
    Executable* e = new Executable(size, argv);
    Executable* e2 = new Executable(size, argv);

    noneConnector* nc = new noneConnector(e);
    cout << nc->execute(false) << endl;

    andConnector* ac = new andConnector(e, e2);
    cout << ac->execute(false) << endl;

    orConnector* oc = new orConnector(e, e2);
    cout << oc->execute(false) << endl;

    

    
    
    // execvp(argv[0], argv);
    // if(-1 == execvp(tok, argv)){
    //   perror("execvp failed ");
    // }
    
  }
}

void execution(string input){
  vector<Base*> execs; //holds the executables;
  vector<Base*> connect; //holds the connectors;
}
