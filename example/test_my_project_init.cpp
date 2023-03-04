#include "mini_mock.hpp"
#include "my_project.hpp"
#include "mock_the_lib.hpp"

/******** Test my_project initialization ********/

TEST(when_my_project_is_used_before_initialization_then_it_returns_error,[]() {
    EXPECT(my_project_do_work(2)==MY_PROJECT_INCORRECT_STATE);
});

TEST(when_my_project_is_initialized_incorrectly_then_it_returns_error,[]() {
    EXPECT(my_project_initialize("incorrect_args")==MY_PROJECT_INCORRECT_ARGUMENT);
});

TEST(when_my_project_is_initialized_correctly_then_the_lib_is_initialized_correctly,[]() {
    MINI_MOCK_ON_CALL(the_lib_initialize,[](bool b,int i){
        EXPECT(b);
        EXPECT(i==10);
        return THE_LIB_OK;
    });
    EXPECT(my_project_initialize("correct_args")==MY_PROJECT_OK);
});

TEST(when_my_project_is_initialized_correctly_but_the_lib_fails_then_it_returns_error,[]() {
    MINI_MOCK_ON_CALL(the_lib_initialize,[](bool b,int i){
        return THE_LIB_ERROR;
    });
    EXPECT(my_project_initialize("correct_args")==MY_PROJECT_CANNOT_INITIALIZE);
});

TEST(when_my_project_is_initialized_twice_then_it_returns_error,[]() {
    MINI_MOCK_ON_CALL(the_lib_initialize,[](bool b,int i){
        return THE_LIB_OK;
    });
    my_project_initialize("correct_args");
    EXPECT(my_project_initialize("correct_args")==MY_PROJECT_INCORRECT_STATE);
});

END_TESTS
