cmake_minimum_required(VERSION 3.5)
project(mathlib VERSION 0.5.0 LANGUAGES CXX)

include(GNUInstallDirs)

set(my_package_name Mathlib)

# make sure that custom modules like UseLATEX are found
list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_SOURCE_DIR}/cmake")

# make sure that library names generated in different configurations don't collide
set(CMAKE_DEBUG_POSTFIX "-d")

# -----------------------------------------------------------
# set options
# -----------------------------------------------------------
option(enable_doxygen "Enables building doxygen docs" ON)
option(build_notes    "Enable building latex notes"   ON)
option(build_utest    "Enable/disable utests"         OFF)

# -----------------------------------------------------------
# import the NaiveCalculator::calculator target
# -----------------------------------------------------------
set(NAIVE_CALCULATOR_INSTALL_DIR "$ENV{HOME}/local/naive_calculator")

if (EXISTS "${NAIVE_CALCULATOR_INSTALL_DIR}")
  message("--> Using installed version of naive_calculator in ${NAIVE_CALCULATOR_INSTALL_DIR}.")

  # make sure that our naive_calculator is found
  set(CMAKE_PREFIX_PATH "${NAIVE_CALCULATOR_INSTALL_DIR}")
  find_package(NaiveCalculator REQUIRED)
else()
  message("--> Using naive_calculator without installing it.")
  add_subdirectory("external/naive_calculator")
endif()

# -----------------------------------------------------------
# create interface to a header-only library
# -----------------------------------------------------------
add_library(transforms INTERFACE)
target_compile_definitions(transforms INTERFACE INCREMENT_BY_TWO)
target_include_directories(transforms INTERFACE "${CMAKE_SOURCE_DIR}/external/transforms")

# -----------------------------------------------------------
# add executables
# -----------------------------------------------------------
add_executable(example_calculator example_calculator.cpp)
target_link_libraries(example_calculator NaiveCalculator::calculator transforms)
target_compile_features(example_calculator PRIVATE cxx_auto_type)
target_compile_options(example_calculator PRIVATE -Wall)
# make sure that the installed executable example_calculator would
# find the installed libcalculator.dylib
#  - INSTALL_RPATH_USE_LINK_PATH TRUE is necessary when using an installed naive_calculator
#  - INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib" is necessary when building naive_calculator
set_target_properties(example_calculator
  PROPERTIES
  INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib"
  INSTALL_RPATH_USE_LINK_PATH TRUE)

# -----------------------------------------------------------
# unit tests
# -----------------------------------------------------------
if(build_utest)
  include(CTest)
  add_subdirectory(utest)
  add_subdirectory(python)
endif(build_utest)

# -----------------------------------------------------------
# doxygen docs
# -----------------------------------------------------------
if (enable_doxygen)
  add_subdirectory(docs/doxygen)
endif(enable_doxygen)

# -----------------------------------------------------------
# latex notes
# -----------------------------------------------------------
if (build_notes)
  add_subdirectory(docs/latex_notes)
endif(build_notes)

# -----------------------------------------------------------
# cpplint custom target (see README.md for a better approach)
# -----------------------------------------------------------
include(Cpplint)

set(SOURCES_TO_LINT
  "example_calculator.cpp"
  "external/naive_calculator/calculator/core/operators.h"
  "external/naive_calculator/calculator/core/add.h"
  "external/naive_calculator/calculator/core/add.cpp"
  "external/naive_calculator/calculator/core/sub.h"
  "external/naive_calculator/calculator/core/sub.cpp"
  "external/naive_calculator/calculator/private/private_utils.h"
  "external/naive_calculator/calculator/utils/ostream_specialization.h"
  "external/transforms/increment.h")

if(CPPLINT_FOUND)
  add_lint_target(lint "${SOURCES_TO_LINT}")
endif(CPPLINT_FOUND)

# -----------------------------------------------------------
# install target
# -----------------------------------------------------------
set(install_configdir "${CMAKE_INSTALL_LIBDIR}/cmake/${my_package_name}")

install(TARGETS example_calculator
  EXPORT "${my_package_name}Targets"
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY external/transforms/
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/transforms"
  FILES_MATCHING PATTERN "*.h*")

install(FILES LICENSE
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

# Export the targets to a script (from the install trees)
install(EXPORT "${my_package_name}Targets"
  FILE "${my_package_name}Targets.cmake"
  NAMESPACE "${my_package_name}::"
  DESTINATION "${install_configdir}")

# -----------------------------------------------------------
# config
# -----------------------------------------------------------
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${my_package_name}ConfigVersion.cmake"
  VERSION "${PROJECT_VERSION}"
  COMPATIBILITY AnyNewerVersion)

configure_package_config_file(
  "${CMAKE_CURRENT_LIST_DIR}/cmake/${my_package_name}Config.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/${my_package_name}Config.cmake"
  INSTALL_DESTINATION "${install_configdir}")

# Install helper files
install(
  FILES
  "${CMAKE_CURRENT_BINARY_DIR}/${my_package_name}Config.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/${my_package_name}ConfigVersion.cmake"
  DESTINATION "${install_configdir}")

# -----------------------------------------------------------
# register in package registry (~/.cmake/packages)
# -----------------------------------------------------------
export(PACKAGE "${my_package_name}")

# -----------------------------------------------------------
# CPack package creation
# -----------------------------------------------------------
set(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}.${CMAKE_PROJECT_VERSION}")
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
include(CPack)

# -----------------------------------------------------------
# organize targets in an IDE
# -----------------------------------------------------------
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
if(CPPLINT_FOUND)
  set_target_properties(lint PROPERTIES FOLDER internal)
endif(CPPLINT_FOUND)

if(build_utest)
  set_target_properties(gmock gmock_main gtest gtest_main
    test_fail test_transforms test_naive_calculator
    PROPERTIES FOLDER utest)
endif(build_utest)
