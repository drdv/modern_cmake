#pragma once
#include "operators.h"

namespace calculator {

class Sub: public BinaryOperator{
 public:
  Sub(int left, int right): BinaryOperator(left, right) {}

  int compute() const;
  int the_ultimate_answer() const;
};

}
