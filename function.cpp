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
