#include "expression.h"
#include "freevariables.h"
#include <iostream>
#include <vector>

/*
 * Id
 */
Id::Id(std::string *id) {
  mId = *id;
}

void Id::print() {
  std::cout << "(Id: " << mId << ")";
}

FreeVariables Id::free() {
  return FreeVariables(this);
}
