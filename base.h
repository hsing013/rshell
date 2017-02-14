#ifndef BASE_H
#define BASE_H

class Base{
  public:
    Base() {};
    virtual bool execute(bool b) = 0;
};

class Executable : public Base{
  private:
    int size;
    bool ran; //false if is not been executed, true if otherwise
    char* args[500];
  public:
    Executable(int size, char* argv[]);
    bool execute(bool b);
};


#endif