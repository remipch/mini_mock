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

# Add an executable to execute tests :
add_executable(test_my_project my_project.cpp test_my_project.cpp)

# Auto populate the tests from test source file
# Note : CMake must be reconfigured if tests are added/renamed/removed from test source file
set(TEST_REGEX "^TEST\\(([A-Za-z0-9_]+).*")
file(STRINGS test_my_project.cpp detected_tests REGEX ${TEST_REGEX})
foreach(test ${detected_tests})
    STRING(REGEX REPLACE ${TEST_REGEX} "\\1" test ${test})
    message(STATUS "detected test ${test}")
    add_test(NAME mini_mock_example_${test} COMMAND test_my_project ${test})
endforeach()

# Alternatively, tests can be added manually with following commands :
# add_test(NAME  mini_mock_example_when_my_project_is_used_before_initialization_then_it_returns_error
#          COMMAND test_my_project when_my_project_is_used_before_initialization_then_it_returns_error)
# add_test(NAME  mini_mock_example_when_my_project_is_initialized_incorrectly_then_it_returns_error
#          COMMAND test_my_project when_my_project_is_initialized_incorrectly_then_it_returns_error)
# add_test(NAME  mini_mock_example_when_my_project_is_initialized_correctly_then_the_lib_is_initialized_correctly
#          COMMAND test_my_project when_my_project_is_initialized_correctly_then_the_lib_is_initialized_correctly)
# add_test(NAME  mini_mock_example_when_my_project_is_initialized_correctly_but_the_lib_fails_then_it_returns_error
#          COMMAND test_my_project when_my_project_is_initialized_correctly_but_the_lib_fails_then_it_returns_error)
# add_test(NAME  mini_mock_example_when_my_project_is_initialized_twice_then_it_returns_error
#          COMMAND test_my_project when_my_project_is_initialized_twice_then_it_returns_error)
# add_test(NAME  mini_mock_example_when_my_project_do_work_and_the_lib_fails_then_it_returns_error
#          COMMAND test_my_project when_my_project_do_work_and_the_lib_fails_then_it_returns_error)
# add_test(NAME  mini_mock_example_when_my_project_do_small_work_then_the_lib_is_called_correctly
#          COMMAND test_my_project when_my_project_do_small_work_then_the_lib_is_called_correctly)
# add_test(NAME  mini_mock_example_when_my_project_do_big_work_then_the_lib_is_called_correctly
#          COMMAND test_my_project when_my_project_do_big_work_then_the_lib_is_called_correctly)
# add_test(NAME  mini_mock_example_when_multiple_callbacks_are_recorded_they_are_called_in_correct_order
#          COMMAND test_my_project when_multiple_callbacks_are_recorded_they_are_called_in_correct_order)
# add_test(NAME  mini_mock_example_when_no_callback_is_recorded_and_mock_is_called_then_test_fails
#          COMMAND test_my_project when_no_callback_is_recorded_and_mock_is_called_then_test_fails)
# add_test(NAME  mini_mock_example_when_some_callbacks_are_never_called_then_test_fails
#          COMMAND test_my_project when_some_callbacks_are_never_called_then_test_fails)

