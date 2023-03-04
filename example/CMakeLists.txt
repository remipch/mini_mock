# A simple minimal CMake to illustrate how to build a test made with MiniMock

cmake_minimum_required(VERSION 3.0)

# MiniMock requires at least C++ 11
set(CMAKE_CXX_STANDARD 11)

# Enable CTest features (provides 'add_test' command below)
enable_testing()

# Include directory containing "mini_mock.hpp"
include_directories(..)

# Build a minimal example project
project(mini_mock_example)

# A real-world scenario would build production code
# with a concrete library implementation with something like :
# add_executable(mini_mock_example_production main.cpp the_lib.cpp my_project.cpp)

# Create one executable for each test source
set(tests "test_my_project_init" "test_my_project_work")
foreach(test_file ${tests})
  set(test_source "${test_file}.cpp")
  message(STATUS "create ${test_file} executable from source: ${test_source}")
  add_executable("${test_file}" my_project.cpp  "${test_source}")

  # Auto populate the tests from test source file
  # Note : CMake must be reconfigured if tests are added/renamed/removed from test source file
  set(TEST_REGEX "^TEST\\(([A-Za-z0-9_]+).*")
  file(STRINGS ${test_source} detected_tests REGEX ${TEST_REGEX})
  foreach(test ${detected_tests})
      STRING(REGEX REPLACE ${TEST_REGEX} "\\1" test ${test})
      message(STATUS "  add test: ${test}")
      add_test(NAME ${test_file}_${test} COMMAND ${test_file} ${test})
  endforeach()
endforeach()
