#include "expression.h"
#include "freevariables.h"
#include <iostream>
#include <vector>

/*
 * Application
 */
Application::Application(Expression *function, Expression *applicant):
  mFunction(function), mApplicant(applicant) {}

void Application::print() {
  std::cout << "(";
  std::cout << "Application: function: ";
  mFunction->print();
  std::cout << ", applicant: ";
  mApplicant->print();
  std::cout << ")";
}

FreeVariables Application::free() {
  return mFunction->free() + mApplicant->free();
}
