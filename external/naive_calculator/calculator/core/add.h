#pragma once
#include "operators.h"

namespace calculator {

class Add: public BinaryOperator{
 public:
  Add(int left, int right): BinaryOperator(left, right) {}

  int compute() const;
  int the_ultimate_answer() const;
};

}
