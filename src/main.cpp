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
#include <sys/types.h>
#include <pwd.h>
#include "base.h"
#include "connectors.h"
using namespace std;

void execution(string input); // carrys out the execution of the input
void commentCheck(string &input); //checks for a comment symbol #

int main(){
  bool run = true; // true until user wants to exit 
  while (run){
    string input;
    struct passwd* pass = getpwuid(getuid()); //gets the user name
    char* userName = pass->pw_name;
    if(userName == NULL){
      perror("getlogin() error");
    }
    char machineName[200];
    gethostname(machineName, sizeof machineName);

    cout << userName << "@" << machineName << ":~$ ";

    getline(cin, input);

    if (input == "exit"){
      exit(0);
    }
    commentCheck(input);
    execution(input);
  }
}

/*parses the input and then executes each
command */
void execution(string input){
  vector<Base*> execs; //holds the executables;
  vector<string> connect; //holds the connectors;

  char const* temp[3];      //holds connectors for comparison
  temp[0] = "&&";
  temp[1] = "||";
  temp[2] = ";";
  char* args[input.size() + 1];
  char* c = const_cast<char*>(input.c_str()); // makes the string volatile to put into char* c
  char* tok = strtok(c, " "); // using strtok to break the input
  unsigned i = 0;
  while (tok != NULL){
    args[i] = tok;
    tok = strtok(NULL, " ");
    ++i;
  }
  char* argc[100]; // temporary holds a command and its arguements
  bool counter = false; // remains true until next command is found
  args[i] = NULL;
  int size = i + 1; //holds the size of the array
  int j = 0;
  for (i = 0; i < size; ++i){ // makes each command and its arguements into an Executable
    c = args[i];
    if (!counter){
      argc[j] = c;
      counter = true;
      ++j;
    }
    else if (c == NULL){
      execs.push_back(new Executable(j, argc));
      connect.push_back(";");
      break;
    }
    else if (strcmp(c, temp[1]) == 0){
      execs.push_back(new Executable(j, argc));
      connect.push_back("||");
      counter = false;
      j = 0;
    }
    else if (strcmp(c, temp[2]) == 0){
      execs.push_back(new Executable(j, argc));
      connect.push_back(";");
      counter = false;
      j = 0;
    }
    else if(strcmp(c, temp[0]) == 0){
      execs.push_back(new Executable(j, argc));
      connect.push_back("&&");
      counter = false;
      j = 0;
    }
    else{
      argc[j] = c;
      ++j;
    }
  }
  bool previousResult = false; //holds the output of the last command, initial is false
  j = 0;
  for (unsigned i = 0; i < execs.size(); ++i, ++j){ //NEED TO IMPLEMENT DECONSTRUCTORS!!!
    if (connect.at(i) == ";"){
      noneConnector* nc = new noneConnector(execs.at(j));
      nc->execute(previousResult);
      previousResult = false;
    }
    else if (connect.at(i) == "&&"){
      if (i + 1 == execs.size()){
        cout << "Your input is incomplete e.g(echo hello &&   )" << endl;
        break;
      }
      andConnector* ac = new andConnector(execs.at(j), execs.at(j + 1));
      previousResult = ac->execute(previousResult);
      // ++j;
    }
    else if (connect.at(i) == "||"){
      if (i + 1 == execs.size()){
        cout << "Your input is incomplete e.g(echo hello ||   )" << endl;
        break;
      }
      orConnector* oc = new orConnector(execs.at(j), execs.at(j + 1));
      previousResult = oc->execute(previousResult);
      ++j;
      ++i;
    }
  }

}
/*checks for comment symbol, if found
then it deletes the substring from the 
comment symbol to the end */
void commentCheck(string &input){
  char comment = '#';
  for (unsigned i = 0; i < input.size(); ++i){
    if (input.at(i) == comment){
      input.replace(i, input.size() - (i), "");
      break;
    }
  }
  // cout << input << endl;
}