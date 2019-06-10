/*
  Use the naive_calculator library.
*/
#include <calculator/core.h>
#include <calculator/utils.h>
#include <increment.h>

int main() {

  calculator::Add add(1, 2);
  calculator::Sub sub(1, 2);
  std::cout << &add << ": " << add.compute()
            << " (" << add.the_ultimate_answer() << ")" << "\n";

  // use auto in order to demonstrate adding the cxx_auto_type feature
  auto answer = sub.the_ultimate_answer();
  std::cout << &sub << ": " << sub.compute()
            << " (" << answer << ")" << "\n";

  std::cout << "increment(1): " << increment(1) << "\n";

  return 0;
}
