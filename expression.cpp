#include "expression.h"
#include "freevariables.h"
#include <iostream>
#include <vector>


/*
 * Expression
 */
Expression::Expression() { }

void Expression::print() {
  std::cout << "()";
}

Expression *Expression::reduce() {
  std::cout << "Reducing." << std::endl;
  return nullptr;
}

FreeVariables Expression::free() {
  return FreeVariables();
}
