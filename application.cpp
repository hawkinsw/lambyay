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

Expression *Application::rename(const Id &from, Expression *to) {
  if (mFunction->free().isFree(from)) {
    const auto oldFunction = mFunction;
    mFunction = mFunction->rename(from, to);
    delete oldFunction;
  }
  if (mApplicant->free().isFree(from)) {
    const auto oldApplicant = mApplicant;
    mApplicant = mApplicant->rename(from, to);
    delete oldApplicant;
  }
  return new Application(mFunction, mApplicant);
}

Expression *Application::reduce() {
  return mFunction->substitute(mApplicant);
}

