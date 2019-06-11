cmake_minimum_required(VERSION 3.5)
project(calculator VERSION 1.0.0 LANGUAGES CXX)

include(GNUInstallDirs)

set(my_package_name NaiveCalculator)

# -----------------------------------------------------------
# create a (shared library) target
# -----------------------------------------------------------
set(calculator_headers
  "${CMAKE_CURRENT_SOURCE_DIR}/calculator/core/operators.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/calculator/core/add.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/calculator/core/sub.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/calculator/core.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/calculator/utils.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/calculator/utils/ostream_specialization.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/calculator/private/private_utils.h")

set(calculator_sources
  "${PROJECT_SOURCE_DIR}/calculator/core/add.cpp"
  "${PROJECT_SOURCE_DIR}/calculator/core/sub.cpp")

# adding `calculator_headers` only affects what files are included in an IDE
add_library(calculator SHARED "${calculator_sources}" "${calculator_headers}")

target_include_directories(calculator
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/calculator/private")

# this permits to install the PUBLIC_HEADER below
# otherwise we have to list them
set_target_properties(calculator PROPERTIES PUBLIC_HEADER "${calculator_headers}")

# This is needed in order to be able to use this library without
# installing it first. This can be done by using
# add_subdirectory(...) instead of find_package(...)
add_library("${my_package_name}::calculator" ALIAS calculator)

# -----------------------------------------------------------
# install target
# -----------------------------------------------------------
set(install_configdir "${CMAKE_INSTALL_LIBDIR}/cmake/${my_package_name}")

install(TARGETS calculator
  EXPORT "${my_package_name}Targets"
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/calculator")

install(FILES LICENSE
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/calculator")

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
