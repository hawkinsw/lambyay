#include "expression.h"
#include "ids.h"
#include <iostream>
#include <vector>
#include <cassert>

/*
 * Ids
 */
Ids::Ids(Id *id) {
  mIds.push_back(id);
}

Ids &Ids::operator+(const Ids &operand) {
  mIds.insert(mIds.begin(), operand.mIds.begin(), operand.mIds.end());
  return *this;
}

Ids &Ids::operator-(const Ids &operand) {
  for (auto id : operand.mIds)
    std::erase_if(mIds, [&id](Id *x) { return *x == *id; });
  return *this;
}

bool Ids::isFree(const Id &toCheck) const {
  for (auto id : mIds)
    if (*id == toCheck)
      return true;
  return false;
}

std::ostream &operator<<(std::ostream &os, Ids ids) {
  os << "(Ids: ";
  for (auto id : ids.mIds) {
    if (id)
      id->print();
  }
  os << ")";
  return os;
}

Id Ids::firstNotIn() {
  std::sort(mIds.begin(), mIds.end(), [](Id *a, Id *b) {
      return *a < *b;
  });

  /*
   * Handle the special case when the set of Ids is empty.
   */
  if (mIds.empty())
    return Id('a');

  if (**mIds.begin() != Id('a'))
    return Id(**mIds.begin()-1);


  /*
   * Only loop to one before the last element so that we can always
   * compare current to the next. This loop does not execute if the
   * number of Ids in the set is 1.
   */
  for (auto current = mIds.begin(); current != mIds.end()-1; current++) {
    auto next = current + 1;

    if ((**current)+1 != **next) {
      return Id(**current+1);
    }
  }

  /*
   * No more ids left to use!
   */
  assert(**(mIds.end()-1) != Id('z'));

  /*
   * No gap? Get the id after the last id in the set.
   */
  return Id((**(mIds.end()-1))+1);
}
