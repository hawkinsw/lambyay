#include "expression.h"
#include "freevariables.h"
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

FreeVariables Function::free() {
  return mBody->free() - FreeVariables(mParam);
}

Expression *Function::rename(const Id &from, Expression *to) {
  if (this->free().isFree(from)) {
    const auto oldBody = mBody;
    mBody = mBody->rename(from, to);
    delete oldBody;
  }
  return new Function(mParam, mBody);
}

Expression *Function::substitute(Expression *substitution) {
  return mBody->rename(*mParam, substitution);
}
