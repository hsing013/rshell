#include "connectors.h"
#include "base.h"
#include <iostream>
using namespace std;

andConnector::andConnector(Base* a, Base* b){
    child1 = a;
    child2 = b;
}

bool andConnector::execute(bool b){
  bool result = b;
  bool result2 = false;
  if (b){
    result2 = child2->execute(false);
  }
  else{
    result = child1->execute(false);
    result2 = child2->execute(false);
  }
  return result && result2;
}

orConnector::orConnector(Base* a, Base* b){
  child1 = a;
  child2 = b;
}

bool orConnector::execute(bool b){
  bool result = b;
  bool result2 = false;
  if (b){
    return false;
  }
  else if (child1->execute(false)){
    return false;
  }
  else if (child2->execute(false)){
    return true;
  }
  return (result || result2);
}

noneConnector::noneConnector(Base* a){
  child1 = a;
}
bool noneConnector::execute(bool b){
  bool result = child1->execute(false);
  return result;
}