#include <iostream>
using namespace std;

int main(){
    int i = 1;
    bool b = false;
    cout << i << endl;
    i = b;
    cout << i << endl;
    if (i == false){
        cout << "hoopla" << endl;
    }
}