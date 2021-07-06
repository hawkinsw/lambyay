#include "expression.h"
#include "ids.h"
#include <iostream>
#include <vector>
#include <cassert>

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

Ids Application::ids() {
  return mFunction->ids() + mApplicant->ids();
}

Expression *Application::rename(const Id &from, Expression *to) {
  Expression *newFunction = nullptr;
  Expression *newApplicant = nullptr;

  if (mFunction->free().contains(from)) {
    newFunction = mFunction->rename(from, to);
  } else {
    newFunction = mFunction->copy();
  }

  if (mApplicant->free().contains(from)) {
    newApplicant = mApplicant->rename(from, to);
  } else {
    newApplicant = mApplicant->copy();
  }
  return new Application(newFunction, newApplicant);
}

Expression *Application::reduce() {
  /*
   * The reduction of an application is the reduced body of the function
   * where its parameter is replaced with the reduced applicant.
   */

  Expression *reducedFunction = nullptr;
  Expression *reducedApplicant = nullptr;

  if (mFunction->willReduce())
    reducedFunction = mFunction->reduce();
  else 
    reducedFunction = mFunction->copy();

  if (mApplicant->willReduce())
    reducedApplicant = mApplicant->reduce();
  else 
    reducedApplicant = mApplicant->copy();

  auto boundInFunction = reducedFunction->bound();
  auto idsInFunction = reducedFunction->ids();
  auto combinedIds = idsInFunction + reducedApplicant->free();
  auto freeInApplicant = reducedApplicant->free();

  for (auto id = freeInApplicant.begin(); id!=freeInApplicant.end(); id++) {
    if (reducedFunction->bound().contains(**id)) {
      auto replacement = combinedIds.firstNotIn();
      auto oldReducedFunction = reducedFunction;
      reducedFunction = reducedFunction->rename(**id, &replacement);
      delete oldReducedFunction;
    }
  }

  auto result = reducedFunction->apply(reducedApplicant);

  delete reducedFunction;
  delete reducedApplicant;

  return result;
}

Expression *Application::copy() {
  return new Application(mFunction->copy(), mApplicant->copy());
}
