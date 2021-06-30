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

  virtual Expression *reduce() {
    std::cout << "Reducing." << std::endl;
    return nullptr;
  }

};

class Id : public Expression {
  public:
  Id(std::string *id) {
    mId = *id;
  }

  void print() {
    std::cout << "(Id: " << mId << ")";
  }

  private:
    std::string mId;
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
    Function(Id *param, Expression *body) :
      mParam(param),
      mBody(body) {}
    void print() {
      std::cout << "(";
      std::cout << "Function: param: ";
      mParam->print();
      std::cout << ", body: ";
      mBody->print();
      std::cout << ")";
    }
  private:
    Id *mParam = nullptr;
    Expression *mBody = nullptr;

};
#endif
