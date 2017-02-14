#ifndef BASE_H
#define BASE_H

class Base{
  public:
   Base() {};
   virtual void execution() = 0;
   virtual char* getCMD() = 0; //returns char* cmd
   virtual char* at(int index) = 0; //return a char* at x index
   virtual int getSize() = 0; //returns the size of argv
   virtual void setSuccess(bool b) = 0;
   virtual bool getSuccess() = 0;
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
    char* getCMD(); //returns char* cmd
    char* at(int index); //return a char* at x index
    int getSize(); //returns the size of argv
    void setSuccess(bool b);
    bool getSuccess();
};

class Single : public Base{
  private: 
    Base* child;
  public:
    Single(Base* b);
    void execution();
    char* getCMD(); //returns char* cmd
    char* at(int index); //return a char* at x index
    int getSize(); //returns the size of argv
    void setSuccess(bool b);
    bool getSuccess(); 
};

#endif