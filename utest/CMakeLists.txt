# -----------------------------------------------------------
# download and unpack googletest at configure time
# -----------------------------------------------------------
configure_file(${CMAKE_SOURCE_DIR}/cmake/GoogleTest-CMakeLists.txt.in
  ${CMAKE_BINARY_DIR}/googletest-download/CMakeLists.txt)

file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download/build")

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" ..
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download/build)

if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download/build)

if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# -----------------------------------------------------------
# add googletest directly to our build. This defines the gtest and gtest_main targets.
# -----------------------------------------------------------
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# -----------------------------------------------------------
# link against gtest (or gtest_main)
# -----------------------------------------------------------
add_executable(test_naive_calculator test_naive_calculator.cpp)
target_compile_features(test_naive_calculator PRIVATE cxx_auto_type) # needed for gtest!
target_link_libraries(test_naive_calculator gtest NaiveCalculator::calculator)
add_test(NAME test_naive_calculator COMMAND test_naive_calculator)

add_executable(test_transforms test_transforms.cpp)
target_compile_features(test_transforms PRIVATE cxx_auto_type)
target_link_libraries(test_transforms gtest transforms)
add_test(NAME test_transforms COMMAND test_transforms)

# -----------------------------------------------------------
# add a test which succeeds when the target fails to compile
# for the right reason (ensured by using a static assertion)
# -----------------------------------------------------------
# EXCLUDE_FROM_ALL: don't build the target by default
add_library(test_fail STATIC EXCLUDE_FROM_ALL "${CMAKE_SOURCE_DIR}/broken_code.cpp")
add_test(NAME test_fail
  COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target test_fail)
set_property(TEST test_fail PROPERTY
  PASS_REGULAR_EXPRESSION "This is not the ultimate answer")
