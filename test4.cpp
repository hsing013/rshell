#include <iostream>
using namespace std;

class hoopla{
  public:
    virtual void print() = 0;
};

class ohm : public hoopla{
  private:
    double data;
  public:
    ohm(double data){
      this->data = data;
    }
    void print(){
      return;
    }
};

class man : public hoopla{
  public:
    main();
    void hello(){
      cout << "hello" << endl;
    }
};

int main(){
  ohm *temp = new ohm(9);
  // cout << temp->print() << endl;
  man* temp2 = new man();
  temp2->hello();
  return 0;
}
/*test concluded that you cannot
change the type of the function
that was inherited from a base 
class */

//virtual functions are required to be implemented in the inherited classes