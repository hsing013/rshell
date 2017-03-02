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
#include <utility>
#include <sys/types.h>
#include <pwd.h>
#include "executioner.h"
using namespace std;

queue<string> Q;

void execution(string input); // carrys out the execution of the input
void commentCheck(string &input); //checks for a comment symbol #
void semicolonExtend(string &input); //adds space between semicolons
pair<bool, bool> checkInput(string &input, char c, char c2); //checks if the amount of parantheses is correct and the amount of brackets
void addSpaceParan(string &input); //adds space between parantheses 
queue<string> precedenceParser(string input); //queues parts of the string that are enclosed in parantheses

int main(){
  bool run = true; // true until user wants to exit 
  while (run){
    string input;
    queue<string> q;
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
    pair<bool, bool> results = checkInput(input, '[', ']'); //checks brackets
    if (!results.first){
      cout << "You have entered the wrong amount of brackets. Try again." << endl << endl;
      continue;
    }
    results = checkInput(input, '(' , ')'); //checks parantheses
    if (!results.first){
      cout << "You have entered the wrong amount of parantheses. Try again." << endl << endl;
      continue;
    }
    semicolonExtend(input);
    if (input == "exit"){ // checks if user inputed exit
      return 0;
    }
    if (results.second){
      Q = precedenceParser(input);
      addSpaceParan(input);
    }
    cout << input << endl;
    // return 0;
    Executioner * e = new Executioner(input);
    e->execute(false);
    delete e;
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

pair<bool, bool> checkInput(string &input, char c, char c2){
  int count = 0; //keeps count of '('
  int count2 = 0; //keeps count of ')'
  bool hasParan = false; //true if input contains a parantheses
  bool correct = false; // true if the amount of parantheses is correct
  pair<bool, bool> ret;
  for (unsigned i = 0; i < input.size(); ++i){
    if (input.at(i) == c){
      hasParan = true;
      ++count;
    }
    else if (input.at(i) == c2){
      ++count2;
    }
  }
  if (count - count2 != 0){
    ret = make_pair(correct, hasParan);
    return ret;
  }
  correct = true;
  ret = make_pair(correct, hasParan);
  return ret;
}

void addSpaceParan(string &input){
  char rightParan = '(';
  char leftParan = ')';
  vector<int> index;  // holds where the parantheses appear
  for (unsigned i = 0; i < input.size(); ++i){
    if(input.at(i) == leftParan){
     index.push_back(i);
    }
  }
  for (unsigned i = 0; i < index.size(); ++i){
    input.insert(index.at(i), " ");
    if (i + 1 != index.size()){
      index.at(i + 1) += 1;
    }
  }
  index.resize(0);
  for (unsigned i = 0; i < input.size(); ++i){
    if(input.at(i) == rightParan){
      index.push_back(i + 1);
    }
  }
  for (unsigned i = 0; i < index.size(); ++i){
    input.insert(index.at(i), " ");
    if (i + 1 != index.size()){
      index.at(i + 1) += 1;
    }
  }
}

queue<string> precedenceParser(string input){
  queue<string> q; //queue that stores all the strings with parantheses
  char rightParan = '(';
  char leftParan = ')';
  int skip = 0;
  int start, end; //holds the beginning of substring and the end 
  bool set = false;
  for (unsigned j = 0; j < input.size(); ++j){
    if (input.at(j) == rightParan){
      for (unsigned i = j; i < input.size(); ++i){
        if (input.at(i) == '(' && !set){
          start = i + 1;
          set = true;
        }
        else if (input.at(i) == '(' && set){
          ++skip;
        }
        else if (input.at(i) == leftParan && skip == 0){
          end = i - start;
          string temp = input.substr(start, end);
          cout << "q: " << temp << endl;
          addSpaceParan(temp);
          q.push(temp);
          break;
        }  
        else if (input.at(i) == ')'){
          --skip;
        }
      }
    }
    set = false;
  }
  return q;
}