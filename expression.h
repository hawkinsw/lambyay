#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <iostream>
#include <vector>

class Expression;
class Id;
class Ids;

class Expression {
  public:
    Expression();

    /*
     * Print this expression.
     */
    virtual void print();

    /*
     * Return a list of all the free variables in this expression.
     */
    virtual Ids free() = 0;

    /*
     * Return a list of all bound variables in this expression.
     */
    virtual Ids bound() = 0;

    /*
     * Returns a pointer to a new expression with _from_ replaced
     * by _to_ only if _from_ is a free variable. 
     *
     * NB: It initially may seem like we would have to call rename
     * recursively on any subexpressions no matter whether from
     * is free here or not. However, that is not true -- if a variable
     * is bound at this level, it cannot be unbound in a more-nested
     * expression.
     *
     * All expressions must implement rename.
     */
    virtual Expression *rename(const Id &from, Expression *to) = 0;

    /*
     * Returns a pointer to a new Expression that is a copy of
     * this Expression.
     *
     * All expressions must implement copy.
     */
    virtual Expression *copy() = 0;

    /*
     * Returns a pointer to the reduced version of this expression.
     * If there is no way to reduce, this function will simpy return
     * a pointer to itself.
     */
    virtual Expression *reduce() {
      return this;
    };

    /*
     * Returns a pointer to an expression where this expression
     * has been applied to applicant. If an application is not
     * applicable, then simply return a pointer to this expression.
     */
    virtual Expression *apply(Expression *applicant) {
      return this;
    };
};

class Id : public Expression {
  public:
    Id(std::string *id);
    Id(char id);

    void print() override;
    Ids free() override;
    Ids bound() override;
    Expression *rename(const Id &from, Expression *to) override;
    virtual Expression *copy() override;

    bool operator==(const Id &right) {
      return this->mId == right.mId;
    }

    bool operator!=(const Id &right) {
      return !(*this == right);
    }

    bool operator<(const Id &operand) const {
      return this->mId < operand.mId;
    }

    Id operator+(const int increase) const {
      return Id(this->mId + increase);
    }

    Id operator-(const int decrease) const {
      return Id(this->mId - decrease);
    }

  private:
    char mId;
};

class Application : public Expression {
  public:
    Application(Application *application);
    Application(Expression *function, Expression *applicant);

    void print() override;
    Ids free() override;
    Ids bound() override;
    Expression *rename(const Id &from, Expression *to) override;
    Expression *reduce() override;
    virtual Expression *copy() override;

  private:
    Expression *mFunction, *mApplicant;
};

class Function : public Expression {
  public:
    Function(Id *param, Expression *body) :
      mParam(param),
      mBody(body) {};

    void print() override;
    Ids free() override;
    Ids bound() override;
    Expression *rename(const Id &from, Expression *to) override;
    virtual Expression *copy() override;

    Expression *apply(Expression *applicant) override;

  private:
    Id *mParam = nullptr;
    Expression *mBody = nullptr;
};
#endif
