#include "expression.h"
#include "ids.h"
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

Ids Application::free() {
  return mFunction->free() + mApplicant->free();
}

Ids Application::bound() {
  return mFunction->bound() + mApplicant->bound();
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
  /*
   * The reduction of an application is the reduced body of the function
   * where its parameter is replaced with the reduced applicant.
   */

  auto reducedFunction = mFunction->reduce();
  auto reducedApplicant = mApplicant->reduce();
  return reducedFunction->apply(reducedApplicant);
}

Expression *Application::copy() {
  return new Application(mFunction, mApplicant);
}
