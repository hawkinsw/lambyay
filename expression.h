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

    virtual FreeVariables free();

    virtual Expression *rename(const Id &from, Expression *to) = 0;
    virtual Expression *reduce() {
      return nullptr;
    };
    virtual Expression *substitute(Expression *) {
      return this;
    }

    virtual Id firstFree();

  private:
};

class Id : public Expression {
  public:
    Id(std::string *id);

    void print() override;
    FreeVariables free() override;
    Expression *rename(const Id &from, Expression *to) override;

    bool operator==(const Id &right) {
      return this->mId == right.mId;
    }

    bool operator<(const Id &operand) const {
      return this->mId < operand.mId;
    }

  private:
    std::string mId;
};

class Application : public Expression {
  public:
    Application(Application *application);
    Application(Expression *function, Expression *applicant);

    void print() override;
    FreeVariables free() override;
    Expression *rename(const Id &from, Expression *to) override;
    Expression *reduce() override;

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
    Expression *rename(const Id &from, Expression *to) override;
    Expression *substitute(Expression *substitution) override;

  private:
    Id *mParam = nullptr;
    Expression *mBody = nullptr;
};
#endif
