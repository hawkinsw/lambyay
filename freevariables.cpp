#include "expression.h"
#include "freevariables.h"
#include <iostream>
#include <vector>

/*
 * FreeVariables
 */
FreeVariables::FreeVariables(Id *id) {
  mIds.push_back(id);
}

FreeVariables &FreeVariables::operator+(const FreeVariables &operand) {
  mIds.insert(mIds.begin(), operand.mIds.begin(), operand.mIds.end());
  return *this;
}

FreeVariables &FreeVariables::operator-(const FreeVariables &operand) {
  for (auto id : operand.mIds)
    std::erase_if(mIds, [&id](Id *x) { return *x == *id; });
  return *this;
}

std::ostream &operator<<(std::ostream &os, FreeVariables fv) {
  os << "(Free variables: ";
  for (auto id : fv.mIds) {
    if (id)
      id->print();
  }
  os << ")";
  return os;
}
