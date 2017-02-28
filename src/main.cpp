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
void semicolonExtend(string &input);
bool checkInput(string &input, char c, char c2); //checks if the amount of parantheses is correct and the amount of brackets


int main(){
  bool run = true; // true until user wants to exit 
  while (run){
    string input;
    struct passwd* pass = getpwuid(getuid()); //gets the user name
    char* userName = pass->pw_name;
    if(userName == NULL){
      perror("getpwuid(getuid) error");
    }
    char machineName[200];
    gethostname(machineName, sizeof machineName); // gets the machine name 

    cout << userName << "@" << machineName << ":~$ ";

    getline(cin, input); // gets input
    commentCheck(input); 
    bool boolean = checkInput(input, '(', ')'); //checks parantheses
    if (!boolean){
      cout << "You have entered the wrong amount of parantheses. Try again." << endl << endl;
      continue;
    }
    boolean = checkInput(input, '[' , ']'); //checks brackets
    if (!boolean){
      cout << "You have entered the wrong amount of brackets. Try again." << endl << endl;
      continue;
    }
    semicolonExtend(input);
    if (input == "exit"){ // checks if user inputed exit
      return 0;
    }
    
    execution(input);
  }
}

/*parses the input and then executes each
command */
void execution(string input){
  if (input.size() == 0){ // returns if input is 0
    return;
  }
  vector<Base*> execs; //holds the executables;
  vector<string> connect; //holds the connectors;

  char const* temp[5];      //holds connectors for comparison
  temp[0] = "&&";
  temp[1] = "||";
  temp[2] = ";";
  temp[3] = "[";
  temp[4] = "]";
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
  for (int i = 0; i < size; ++i){ // makes each command and its arguements into an Executable
    c = args[i];
    if (((!counter) && strcmp(c, temp[3]) == 0) || (!counter && strcmp(c, "test") == 0)){
      counter = true;
      testType = true;
    }
    else if (!counter){
      argc[j] = c;
      counter = true;
      ++j;
    }
    else if (c == NULL){ // makes an Executable that has no connector
      argc[j + 1] = NULL;
      if (!testType){
        execs.push_back(new Executable(j, argc));
        connect.push_back(";");
      }
      else{
        execs.push_back(new Test(j, argc));
        connect.push_back(";");
        testType = false;
      }
      break;
    }
    else if (strcmp(c, temp[1]) == 0){ // makes an Executable that has the orConnector
      argc[j + 1] = NULL;
      if (!testType){
        execs.push_back(new Executable(j, argc));
        connect.push_back("||");
      }
      else{
        execs.push_back(new Test(j, argc));
        connect.push_back("||");
        testType = false;
      }
      counter = false;
      j = 0;
    }
    else if (strcmp(c, temp[2]) == 0){ // makes an Executable that has a semicolon connecter
      argc[j + 1] = NULL;
      if (!testType){
        execs.push_back(new Executable(j, argc));
        connect.push_back(";");
      }
      else{
        execs.push_back(new Test(j, argc));
        connect.push_back(";");
        testType = false;
      }
      counter = false;
      j = 0;
    }
    else if (strcmp(c, temp[0]) == 0){ // makes an Executable that has andConnector
      argc[j + 1] = NULL;
      if (!testType){
        execs.push_back(new Executable(j, argc));
        connect.push_back("&&");
      }
      else{
        execs.push_back(new Test(j, argc));
        connect.push_back("&&");
        testType = false;
      }
      counter = false;
      j = 0;
    }
    else{
      argc[j] = c;
      ++j;
    }
  }
  delete[] args; //deallocate memory
  delete[] argc; //deallocate memory
  vector<Base*> destroy; // holds connectors that are to be destroyed later
  bool previousResult = false; //holds the output of the last command, initial is false
  j = 0;
  for (unsigned i = 0; i < execs.size(); ++i, ++j){
    if (connect.at(i) == ";"){ //executes noneConnector commands
      noneConnector* nc = new noneConnector(execs.at(j));
      nc->execute(previousResult);
      previousResult = false;
      destroy.push_back(nc);
    }
    else if (connect.at(i) == "&&"){ // executes andConnector commands
      if (i + 1 == execs.size()){
        cout << "Your input is incomplete e.g(echo hello &&   )" << endl;
        break;
      }
      andConnector* ac = new andConnector(execs.at(j), execs.at(j + 1));
      previousResult = ac->execute(previousResult);
      if (connect.at(j + 1) == ";"){
        connect.at(j + 1) = "done";
      }
      destroy.push_back(ac);
    }
    else if (connect.at(i) == "||"){ // executes orConnector commands
      if (i + 1 == execs.size()){
        cout << "Your input is incomplete e.g(echo hello ||   )" << endl;
        break;
      }
      orConnector* oc = new orConnector(execs.at(j), execs.at(j + 1));
      previousResult = oc->execute(previousResult);
      if (connect.at(j + 1) == ";"){
        connect.at(j + 1) = "done";
      }
      ++j;
      ++i;
      destroy.push_back(oc);
    }
  }
  connect.resize(0);
  for (unsigned i = 0; i < execs.size(); ++i){ //deallocates memory
    delete execs.at(i);
  }
  for (unsigned i = 0; i < destroy.size(); ++i){ //deallocate memory
    delete destroy.at(i);
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

/*finds any semicolon and adds a
space before it so it is alone.
this enables the parsing algorithm
to work properly */
void semicolonExtend(string &input){
 char semicolon = ';';
 vector<int> index;  // holds where semicolon appears
 for (unsigned i = 0; i < input.size(); ++i){
   if(input.at(i) == semicolon){
     index.push_back(i);
   }
 }
 for (unsigned i = 0; i < index.size(); ++i){
   input.insert(index.at(i), " ");
   if (i + 1 != index.size()){
     index.at(i + 1) += 1;
   }
 }
}

bool checkInput(string &input, char c, char c2){
  int count = 0; //keeps count of '('
  int count2 = 0; //keeps count of ')'
  for (unsigned i = 0; i < input.size(); ++i){
    if (input.at(i) == c){
      ++count;
    }
    else if (input.at(i) == c2){
      ++count2;
    }
  }
  if (count - count2 != 0){
    return false;
  }
  return true;
}

