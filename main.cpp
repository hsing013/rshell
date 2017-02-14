#include <iostream>
#include <vector>
#include <string>
#include <string.h> //for strtok
#include <unistd.h> //for execvp
#include <stdio.h> // for perror
#include <errno.h>
#include "base.h"
using namespace std;



int main(){
  bool run = true; // true until user wants to exit where it becomes false
  while (run){
    string input;
    cout << "$ ";
    getline(cin, input);
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
    tok = argv[0];
    Executable* b = new Executable(tok, size, argv);
    Single* sing = new Single(b);
    sing->execution();
    return 0;
    // execvp(tok, argv);
    // if(-1 == execvp(tok, argv)){
    //   perror("execvp failed ");
    // }
    
  }

  return 0;
}

