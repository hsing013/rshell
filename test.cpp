
#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <vector>
#include <unistd.h>
using namespace std;


int main ()
{
  vector<char*> v(3);
  int i = 0;
  char str[] ="ls -a -b";
  char * pch;
  string s = "ls -a";
  printf ("Splitting string \"%s\" into tokens:\n",str);
  pch = strtok(str," ");
  while (pch != NULL)
  {
    v.at(i) = pch;
    pch = strtok (NULL, " ");
    ++i;
  }
  char* temp = v.at(0);
  // execvp(temp, v); doesnt work with vectors
  return 0;
}

//split string by tokenizer

	

// int main(){
//    string s = "This is,  a test";
//    tokenizer<> tok(s);
//    for(tokenizer<>::iterator beg=tok.begin(); beg!=tok.end();++beg){
//        cout << *beg << "\n";
//    }
// }