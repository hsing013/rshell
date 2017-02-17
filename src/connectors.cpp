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

orConnector::~orConnector(){}

/*if child1 executes, send false
if child1 fails, execute child2 
and if child2 executes, send true 
if b is true, return false as that
indicates that child1 has been executed */
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
  return (result || result2); //always sends back false
}

noneConnector::noneConnector(Base* a){
  child1 = a;
}
/* store the result from the execution
and send it back */
noneConnector::~noneConnector(){}
bool noneConnector::execute(bool b){
  bool result = child1->execute(false);
  return result;
}