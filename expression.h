#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <iostream>
#include <vector>

class Expression {
  public:
  Expression() { }

  virtual void print() {
    std::cout << "()";
  }
};

class Ids : public Expression {
  public:
  Ids(std::string *id) {
    mIds.push_back(*id);
  }

  void add(std::string *id) {
    mIds.push_back(*id);
  }

  void print() {
    std::cout << "(Ids: ";
    for (auto id : mIds ) {
      std::cout << id << ", ";
    }
    std::cout << ")";
  }

  private:
    std::vector<std::string> mIds;
};


class Application : public Expression {
  public:
    Application(Expression *function, Expression *applicant):
      mFunction(function),
      mApplicant(applicant) {}

    void print() {
      std::cout << "(";
      std::cout << "Application: function: ";
      mFunction->print();
      std::cout << ", applicant: ";
      mApplicant->print();
      std::cout << ")";
    }
  private:
    Expression *mFunction, *mApplicant;
};

class Function : public Expression {
  public:
    Function(Ids *params, Expression *body) :
      mParams(params),
      mBody(body) {}
    void print() {
      std::cout << "(";
      std::cout << "Function: params: ";
      mParams->print();
      std::cout << ", body: ";
      mBody->print();
      std::cout << ")";
    }
  private:
    Ids *mParams = nullptr;
    Expression *mBody = nullptr;

};
#endif
