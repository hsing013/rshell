#include <unistd.h>
#include <iostream>
using namespace std;


int main(){
  cout << "Before" << endl;
  int pid = fork();
  cout << pid << endl;
  string s = "ls";
  if (pid==0) {
      execvp(s.c_str(), "-a");
   }
   cout << "done" << endl;

   return 0;
}