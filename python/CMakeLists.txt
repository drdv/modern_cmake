# using ctest
add_test (NAME python-tests
  COMMAND py.test -v "${CMAKE_CURRENT_SOURCE_DIR}/utest")
add_custom_target(python_utest_ctest
  COMMAND CTEST_OUTPUT_ON_FAILURE=1 GTEST_COLOR=1 PYTEST_ADDOPTS="--color=yes" ${CMAKE_CTEST_COMMAND})

# one could use the custom command directly (without ctest)
add_custom_target(python_utest_custom COMMAND py.test -v "${CMAKE_CURRENT_SOURCE_DIR}/utest")
