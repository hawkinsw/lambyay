#include "expression.h"
#include "ids.h"
#include <iostream>
#include <vector>
#include <cassert>

/*
 * Id
 */
Id::Id(std::string *id) {
  assert(id->length() == 1);
  mId = (*id)[0];
}

Id::Id(char id) {
  mId = id;
}

void Id::print() {
  std::cout << "(Id: " << mId << ")";
}

Ids Id::free() {
  return Ids(this);
}

Ids Id::bound() {
  return Ids();
}

Expression *Id::copy() {
  return new Id(this->mId);
}

Expression *Id::rename(const Id &from, Expression *to) {
  if (*this == from) {
    return to->copy();
  }
  return new Id(this->mId);
}
