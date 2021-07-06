#include "expression.h"
#include "ids.h"
#include <iostream>
#include <vector>

/*
 * Function
 */
void Function::print() {
  std::cout << "(";
  std::cout << "Function: param: ";
  mParam->print();
  std::cout << ", body: ";
  mBody->print();
  std::cout << ")";
}

Ids Function::free() {
  return mBody->free() - Ids(mParam);
}

Ids Function::bound() {
  return mBody->bound() + Ids(mParam);
}

Ids Function::ids() {
  return mBody->ids() + mParam->ids();
}

Expression *Function::rename(const Id &from, Expression *to) {
  if (this->free().contains(from)) {
    return new Function(static_cast<Id*>(mParam->copy()), mBody->rename(from, to));
  }
  return new Function(static_cast<Id*>(mParam->copy()), mBody->copy());
}

Expression *Function::copy() {
  return new Function(static_cast<Id*>(mParam->copy()), mBody->copy());
}

Expression *Function::apply(Expression *applicant) {
  return mBody->rename(*mParam, applicant);
}
