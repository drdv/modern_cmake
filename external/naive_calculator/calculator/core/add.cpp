#include "add.h"
#include <private_utils.h>

namespace calculator {

int Add::compute() const {return m_left + m_right;}
int Add::the_ultimate_answer() const {return private_function();}

} // namespace calculator
