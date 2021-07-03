#ifndef FREE_VARIABLES_H
#define FREE_VARIABLES_H

class Id;

class FreeVariables {
  public:

    FreeVariables() {}

    FreeVariables(Id *id);

    FreeVariables &operator+(const FreeVariables &operand);
    FreeVariables &operator-(const FreeVariables &operand);

    bool isFree(const Id &id) const;

    Id firstFree();

    friend std::ostream &operator<<(std::ostream &os, FreeVariables fv);

    private:
      std::vector<Id*> mIds{};
};
#endif
