### Mathlib
 A dummy math library used to demonstrate how to use `cmake` (for my personal
 reference)

### References I have found useful
 + https://www.youtube.com/watch?v=rLopVhns4Zs&feature=youtu.be
 + https://codingnest.com/basic-cmake-part-2
 + https://pabloariasal.github.io/2018/02/19/its-time-to-do-cmake-right
 + https://cgold.readthedocs.io/en/latest/tutorials/variables.html
 + https://github.com/onqtam/awesome-cmake

### Compile with unit test support
 + `cmake -D build_utest=ON -B build && cd build`
 + `make`
 + `utest/test_naive_calculator`
 + Running utests:
   + `make test` (default option)
   + running the tests using the `ctest` command gives us more control
     + `ctest -R naive_calculator` would execute only `test_naive_calculator`
     + `ctest` has many useful flags (see `ctest --help`)

### Docs
 + `make doxygen` (doxygen)
 + `make note` (latex notes)

### Linting
 + **option 1**: lint all files during compilation (by setting built-in properties)
   + `cmake "-DCMAKE_CXX_CLANG_TIDY=/full/path/to/clang-tidy;-checks=*" ..`
   + `cmake "-DCMAKE_CXX_CPPLINT=/full/path/to/cpplint.py;--linelength=100" ..`
   + note: only header files that are included in source files are linted
     + for header-only libraries we could rely on the unit-tests to include the headers
 + **option 2**: lint selected files on demand (using a custom target)
   + see example in `CMakeLists.txt`

### Install
 + `cmake -DCMAKE_INSTALL_PREFIX=~/local/mathlib -B build && cd build`
 + `make && make install`

### Packaging
 + `make package`
