#ifndef BASE_H
#define BASE_H

class Base{
  public:
   Base();
   virtual void execution() = 0;
   virtual char* cmdReturn() = 0; //returns char* cmd
   virtual char* at(int index) = 0; //return a char* at x index
   virtual int sizerReturn() = 0; //returns the size of argv
   virtual void setSuccess() = 0;
};


class Executable : public Base{
  private:
    char* cmd;
    int size;
    char* argv[];
    bool success; // false if not executed successfully, true if otherwise
  public:
    Executable(char* cmd, int size, char* argv[]);
    void execution(); 
    char* cmdReturn(); //returns char* cmd
    char* at(int index); //return a char* at x index
    int sizerReturn(); //returns the size of argv
    void setSuccess();
};

class Single : public Base{
  private: 
    Executable* child;
  public:
    Single(Executable* b);
    void execution();
    char* cmdReturn(); //returns char* cmd
    char* at(int index); //return a char* at x index
    int sizerReturn(); //returns the size of argv
    void setSuccess();
};

#endif