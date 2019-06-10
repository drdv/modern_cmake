# ------------------------------------------------------------------------
# Try to find cpplint.py.
#
# If cpplint.py is not available, download it (it is assumed that wget is
# available). The following variables are set:
#  - CPPLINT_FOUND: YES/NO
#  - CPPLINT_WHERE: location of cpplint.py
#  - CPPLINT_FLAGS: flags to be passed to cpplint
#
# Define a function add_lint_target.
# ------------------------------------------------------------------------
find_program(CPPLINT_WHERE cpplint.py "${PROJECT_SOURCE_DIR}/misc")

# disable filters
set(CPPLINT_FILTERS
  -build/include_what_you_use
  -build/namespaces
  -build/header_guard
  -legal/copyright
  -readability/namespace
  -whitespace/comments
  -whitespace/blank_line
  )

# list to string
string(REPLACE ";" "," CPPLINT_FILTERS "${CPPLINT_FILTERS}")

set(CPPLINT_FLAGS
  "--filter=${CPPLINT_FILTERS}"
  "--extensions=cpp,hpp,h"
  "--linelength=100")

unset(CPPLINT_FILTERS)

# make sure that cpplint.py is available
if(CPPLINT_WHERE STREQUAL "CPPLINT_WHERE-NOTFOUND")
  message("--> Downloading cpplint.py ...")

  set(wget_command wget)
  execute_process(COMMAND "${wget_command}" -P "${PROJECT_SOURCE_DIR}/misc"
    "https://raw.githubusercontent.com/google/styleguide/gh-pages/cpplint/cpplint.py"
    RESULT_VARIABLE return_status)

  if(return_status EQUAL 0)
    set(CPPLINT_WHERE "${PROJECT_SOURCE_DIR}/misc/cpplint.py")
    set(CPPLINT_FOUND YES)
  else()
    message("[${wget_command}] ${return_status}")
    set(CPPLINT_FOUND NO)
  endif()
else()
  message("--> Found cpplint.py: ${CPPLINT_WHERE}")
  set(CPPLINT_FOUND YES)
endif()

# Add a target (TARGET_NAME) that runs cpplint.py on SOURCES_LIST
function(add_lint_target TARGET_NAME SOURCES_LIST)
  list(REMOVE_DUPLICATES SOURCES_LIST)
  add_custom_target(${TARGET_NAME}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    COMMAND "${CPPLINT_WHERE}" ${CPPLINT_FLAGS} ${SOURCES_LIST}
    COMMENT "Linting ${SOURCES_LIST}")
endfunction()
