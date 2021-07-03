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

Expression *Id::rename(const Id &from, Expression *to) {
  if (*this == from) {
    std::cout << "Renaming!!! " << std::endl;
    return to;
  }
  return new Id(&this->mId);
}
