#include "connectors.h"
#include "base.h"
#include <iostream>
using namespace std;

andConnector::andConnector(Base* a, Base* b){
    child1 = a;
    child2 = b;
}
andConnector::~andConnector(){}

/* if b is true that means that
child1 has been executed therefore
only execute child2. else execute
both and return the AND of both results */
bool andConnector::execute(bool b){
  bool result = b;
  bool result2 = false;
  if (b){
    result2 = child2->execute(true);
  }
  else{
    result = child1->execute(true);
    result2 = child2->execute(result);
  }
  return result && result2;
}

orConnector::orConnector(Base* a, Base* b){
  child1 = a;
  child2 = b;
}

orConnector::~orConnector(){}

/*returns the OR of both commands
  child2 is passed in the result of
  child1, where if the value passed in
  was true then child2 returns false 
  else returns true */
bool orConnector::execute(bool b){
  bool result = false;
  bool result2 = false;
  if (b){
    return true;
  }
  result = child1->execute(true);
  result2 = child2->execute(!result);
  
  return (result || result2); 
}

noneConnector::noneConnector(Base* a){
  child1 = a;
}
/* store the result from the execution
and send it back */
noneConnector::~noneConnector(){}
bool noneConnector::execute(bool b){
  bool result = child1->execute(true);
  return result;
}