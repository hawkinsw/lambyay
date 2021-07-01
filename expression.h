#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <iostream>
#include <vector>

class Expression;
class Id;
class FreeVariables;

class Expression {
  public:
  Expression();

  virtual void print();

  virtual Expression *reduce();

  virtual FreeVariables free();
};

class Id : public Expression {
  public:
    Id(std::string *id);

    void print() override;
    FreeVariables free() override;

    bool operator==(const Id &right) {
      return this->mId == right.mId;
    }

  private:
    std::string mId;
};

class Application : public Expression {
  public:
    Application(Expression *function, Expression *applicant);

    void print() override;
    FreeVariables free() override;

  private:
    Expression *mFunction, *mApplicant;
};

class Function : public Expression {
  public:
    Function(Id *param, Expression *body) :
      mParam(param),
      mBody(body) {};

    void print() override;
    FreeVariables free() override;

  private:
    Id *mParam = nullptr;
    Expression *mBody = nullptr;
};
#endif
