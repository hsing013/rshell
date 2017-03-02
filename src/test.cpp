#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <queue>
using namespace std;

void nm(queue<int> &q);

int main(){
  struct stat sb;
  string input = "/hom/harsh/Desktop/CS_100/rshell/src/";
  queue<int> q;
  q.push(6);
  q.push(7);
  nm(q);
  cout << q.front();
  // char const* argv[2];
  // argv[0] = "Desktop/CS_100/rshell/src/main.cpp";
  // argv[1] = "rshell";
  // int status = stat(input.c_str(), &sb);
  // if (status == -1){
  //   perror("stat");
  // }
  // cout << status << endl;
  // if(S_ISDIR(sb.st_mode)){
  //   cout << "Hoopla" << endl;
  // }
  // else{
  //   cout << "no" << endl;
  // }
  return 0;
}

void nm(queue<int> &q){
  q.pop();
}