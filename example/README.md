# MiniMock example

This simple example contains :
- An external library named `the_lib`, offering a few functions declared in [the_lib.hpp](the_lib.hpp).
- A project named `my_project` to be tested, defined in [my_project.cpp](my_project.cpp) and using `the_lib` functions.
- A mock, defined in [mock_the_lib.hpp](mock_the_lib.hpp).
- Two test files, [test_my_project_init.cpp](test_my_project_init.cpp) and [test_my_project_work.cpp](test_my_project_work.cpp), using `my_project` and `mock_the_lib`.
- A [CMake file](CMakeLists.txt) to build all the tests.

To build this project :
```bash
cd mini_mock/example
mkdir build
cd build
cmake ..
make
```

Tests can be launched with CTest in command line :
```bash
cd mini_mock/example/build

# Execute all tests :
ctest

# Execute all tests and print passed and failed conditions with detailed messages :
ctest -V

# Execute all tests matching a regex :
ctest -V -R <my_regex>
ctest -V -R "token"   # execute all tests containing "token"
ctest -V -R "^prefix" # execute all tests starting with "prefix"
ctest -V -R "suffix$" # execute all tests ending with "suffix"
```
