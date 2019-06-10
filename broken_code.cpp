/*
  Here we raise a static assertion so that this code doesn't compile. See the
  `test_fail` target in `utest/CMakeLists.txt` which tests whether we have a
  failure during compilation.
*/
#include <type_traits>

int main() {

  const int x = 43;
  static_assert(x == 42, "This is not the ultimate answer.");

  return 0;
}
