# MiniMock : a minimalist, header-only, C/C++ mock library

## Introduction

MiniMock is a tentative to create a minimalist mock library with following characteristics :
- Easy to integrate : header-only, `#include` it and you're done.
- Lightweight : approximatively 100 lines of code.
- No dependency other than C++11.
- Use native langage features instead of reinventing them differently.
- Easy to learn : it provides a very limited set of functions while covering a wide range of use cases.

In short, MiniMock offers basic mock features by providing only 9 macros :
- 3 macros to structure tests : `BEGIN_TESTS`, `TEST`, `END_TESTS`.
- 4 macros to compare things : `EXPECT`, `EXPECT_MSG`, `ASSERT_MSG`, `NEAR`.
- 2 macros to mock functions : `MINI_MOCK_FUNCTION`, `MINI_MOCK_ON_CALL`.

And that's it !

#### Limitations

MiniMock has the following limitations :
- Currently it's a quick-and-dirty-proof-of-concept
not tested in a wide range of platforms/use-cases/projects/real-world-serious-things.
- Internally heavily uses C++ macros and obscure hacks
- Currently covers only non-object functions (classes cannot be mocked yet).
- Currently does not accept several functions with the same name.
- Some complex features typically provided by usual mock frameworks are not and won't be provided (ex : `Times(AtLeast(17))`).
- It has been developped and tested with gcc, the macro-related-magic-stuff is not guaranted to work with other tools.

#### Why using MiniMock ?

- You want to explore alternatives to existing mock tools.
- You search a quick, easy and lightweight way to add some tests to your project.

#### Why not using MiniMock ?

- You already master an existing mock framework and are happy with it.
- You need a strong, mature framework, created and maintained by a strong organization.
- You strongly believe that C++ macros are ugly, evil and "unclean-code".
- You value consiseness over expliciteness or simplicity.

#### Why did I do MiniMock ?

While working on a side project, I wanted to quickly add a few unit tests.

So I started to explore a few mock frameworks and encountered a few questions :
- How can I quickly integrate them in my project ?
- Why do they all reinvent tools to do basic things that are already in the langage itself ?
    - `ASSERT_EQ`, `EXPECT_GE` (and 100 of them) to compare things but we already have `==` or `>=` native operators.
    - Standard matchers `EXPECT_THAT(value2, MatchesRegex("Line \\d+"));` but the langage already provides them in a standard way.
    - Custom matchers to be created in a specific way instead of a simple function `bool compare(Thing foo,Thing bar)` ?
- Why do they invent a new langage `EXPECT_CALL(foo, Describe(5)).Times(3).WillRepeatedly(Return("Category 5"));` ?

In other words, I feel they all define a whole new langage with its own complexity and slow learning curve.

So I thought : is it possible to generalize most of these use cases in a basic, simple, native, minimalist form ?

## MiniMock basics

#### Integrating

A single `include` is required to use MiniMock in your tests :
```C++
#include "mini_mock.hpp"
```

#### Tests structure

Three macros allow to declare tests :
```C++
BEGIN_TESTS

TEST(my_first_test) {
    ...
}

TEST(my_second_test) {
    ...
}

END_TESTS
```
These macros create a main entry point (`int main(int argc, char **argv)`) that requires the test name
as the first argument and executes it.

It seems to be a de-facto standard in the world of test frameworks, making :
- MiniMock easy to integrate with existing test launchers (I use CTest which is offered with CMake).
- MiniMock easy to launch manually in command line : `my_test   my_first_test`.
- Each test executed in a known clean state because a new application is launched for each test execution.

Note : because `BEGIN_TESTS`, `TEST`, `END_TESTS` macros are actually the `main` function body, you cannot
define other functions in between (yes it's hacky).

#### Comparisons

Three macros allow to compare things in a test body :
```C++
// If condition is false :
// - an automatic message will be printed (containing file name and line number)
// - the test continues
// - the test will fail at the end
EXPECT(condition);

// If condition is false :
// - the given message will be printed
// - the test continues
// - the test will fail at the end
EXPECT_MSG(condition,message);

// If condition is false :
// - the given message will be printed
// - the test fails and stops immediately
ASSERT_MSG(condition,message);
```

And a shortcut makes it easy to compare floating point values :
```C++
// NEAR is true if val1 is near val2 :
NEAR(val1,val2)

// NEAR use ACCEPTABLE_DIFFERENCE constant
// which can be redefined by user if a different value is needed :
ACCEPTABLE_DIFFERENCE = 0.000001
```

#### Mocking

A single macro allows to define a mocked function with its signature :
```C++
MINI_MOCK_FUNCTION(function_name,return_type,arguments_def,arguments);
```
For example :
```C++
MINI_MOCK_FUNCTION(external_library_do_something,int,(bool b,int i),(b,i));
```
This macro magically creates a few types, variables and functions that will be used internally by MiniMock.

A single macro allows to register a callback to be called when a mocked function is called :
```C++
// 'function_name' is the name of the function that has been declared with MINI_MOCK_FUNCTION
// 'callback' will be called in place of the mocked function
// 'expected_calls_count' defines the exact times that the callback must be called
MINI_MOCK_ON_CALL(function_name,callback,expected_calls_count=1);
```
For example :
```C++
MINI_MOCK_ON_CALL(external_library_do_something,[](bool b,int i){
    // Simply check the input parameters if it makes sense
    EXPECT(!b);
    EXPECT(i==10);
    // Simply return the value
    return 15;
},3); // this function must be called exactly 3 times by code under test
```

Several callbacks can be recorded successively for the same function, in the exact order in which they must be called.

## Example

To illustrate MiniMock usage, a minimal example is presented in [example](example) subfolder.
