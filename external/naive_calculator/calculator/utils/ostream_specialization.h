#pragma once

#include <iostream>
#include "calculator/core/operators.h"

namespace calculator {

std::ostream& operator<<(std::ostream& os, const BinaryOperator* op) {
  os << "[left: " << op->get_left() << ", right: " << op->get_right() << "]";
  return os;
}

}
