#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
using namespace std;

int main(){
  struct stat sb;
  string input = "/home/harsh/Desktop/CS_100/rshell/src/";
  // char const* argv[2];
  // argv[0] = "Desktop/CS_100/rshell/src/main.cpp";
  // argv[1] = "rshell";
  int status = stat(input.c_str(), &sb);
  perror("stat");
  cout << status << endl;
  if(S_ISDIR(sb.st_mode)){
    cout << "Hoopla" << endl;
  }
  else{
    cout << "no" << endl;
  }
  return 0;
}
