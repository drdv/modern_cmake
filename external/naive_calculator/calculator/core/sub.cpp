#include "sub.h"
#include <private_utils.h>

namespace calculator {

int Sub::compute() const {return m_left - m_right;}
int Sub::the_ultimate_answer() const {return private_function();}

} // namespace calculator
