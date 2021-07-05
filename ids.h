#ifndef FREE_VARIABLES_H
#define FREE_VARIABLES_H

class Id;

class Ids {
  public:

    Ids() {}

    Ids(Id *id);

    Ids &operator+(const Ids &operand);
    Ids &operator-(const Ids &operand);

    bool isFree(const Id &id) const;

    Id firstNotIn();

    friend std::ostream &operator<<(std::ostream &os, Ids ids);

    private:
      std::vector<Id*> mIds{};
};
#endif
