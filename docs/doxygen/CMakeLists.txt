configure_file(Doxyfile.in Doxyfile @ONLY)

find_package(Doxygen)
if(DOXYGEN_FOUND)
  add_custom_target(doxygen ${DOXYGEN_EXECUTABLE} "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
    COMMENT "Build doxygen documentation")

  set_target_properties(doxygen PROPERTIES FOLDER internal)

else()
  message("--> [SKIP] doxygen documentation")
endif(DOXYGEN_FOUND)
