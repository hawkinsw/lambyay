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

Expression *Function::rename(const Id &from, Expression *to) {
  if (this->free().isFree(from)) {
    const auto oldBody = mBody;
    mBody = mBody->rename(from, to);
    delete oldBody;
  }
  return new Function(mParam, mBody);
}

Expression *Function::copy() {
  return new Function(mParam, mBody);
}

Expression *Function::apply(Expression *applicant) {
  return mBody->rename(*mParam, applicant);
}
