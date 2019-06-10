#pragma once

template <class T>
T increment(T number) {
#ifdef INCREMENT_BY_TWO
  return number + 2;
#else
  return number + 1;
#endif
}
