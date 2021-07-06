#ifndef FREE_VARIABLES_H
#define FREE_VARIABLES_H

class Id;

class Ids {
  public:

    Ids() {}

    Ids(Id *id);

    Ids &operator+(const Ids &operand);
    Ids &operator-(const Ids &operand);

    bool contains(const Id &id) const;

    Id firstNotIn();

    auto begin() {
      return mIds.begin();
    }

    auto end() {
      return mIds.end();
    }

    friend std::ostream &operator<<(std::ostream &os, Ids ids);

    private:
      std::vector<Id*> mIds{};
};
#endif
