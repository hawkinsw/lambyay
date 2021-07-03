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

FreeVariables Expression::free() {
  return FreeVariables();
}

Id Expression::firstFree() {
  return free().firstFree();
}
