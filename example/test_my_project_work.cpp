#include "mini_mock.hpp"
#include "my_project.hpp"
#include "mock_the_lib.hpp"

/******** Test my_project doing actual work ********/

// We don't need a framework to manage 'SetUp' and 'TearDown' features,
// simply create and reuse function(s) depending on what needs to be done in tests
void init_my_project_correctly() {
    MINI_MOCK_ON_CALL(the_lib_initialize,[](bool b,int i){
        return THE_LIB_OK;
    });
    my_project_initialize("correct_args");
}

TEST(when_my_project_do_work_and_the_lib_fails_then_it_returns_error,[]() {
    init_my_project_correctly();

    MINI_MOCK_ON_CALL(the_lib_do_something_without_arg,[](){
        return THE_LIB_ERROR;
    });
    EXPECT(my_project_do_work(5)==MY_PROJECT_CANNOT_WORK);
});

TEST(when_my_project_do_small_work_then_the_lib_is_called_correctly,[]() {
    init_my_project_correctly();

    MINI_MOCK_ON_CALL(the_lib_do_something_without_arg,[](){
        return THE_LIB_OK;
    });
    EXPECT(my_project_do_work(5)==MY_PROJECT_OK);
});

TEST(when_my_project_do_big_work_then_the_lib_is_called_correctly,[]() {
    init_my_project_correctly();

    MINI_MOCK_ON_CALL(the_lib_do_something_without_arg,[](){
        return THE_LIB_OK;
    });
    MINI_MOCK_ON_CALL(the_lib_do_something,[](float f){
        EXPECT(NEAR(f,200));
    });
    EXPECT(my_project_do_work(100)==MY_PROJECT_OK);
});

/******** Show extended or incorrect use of MiniMock : following tests can fail on purpose ********/

TEST(when_multiple_callbacks_are_recorded_they_are_called_in_correct_order,[]() {
    init_my_project_correctly();

    // For a given mocked function, the callbacks will be called
    // in the same order they were registered
    // Here, the 3rd call to the_lib will return an error
    MINI_MOCK_ON_CALL(the_lib_do_something_without_arg,[](){
        return THE_LIB_OK;
    },2);
    MINI_MOCK_ON_CALL(the_lib_do_something_without_arg,[](){
        return THE_LIB_ERROR;
    },1);
    MINI_MOCK_ON_CALL(the_lib_do_something_without_arg,[](){
        return THE_LIB_OK;
    },6);
    MINI_MOCK_ON_CALL(the_lib_do_something,[](float f){
        EXPECT(NEAR(f,100));
    },1);
    MINI_MOCK_ON_CALL(the_lib_do_something,[](float f){
        EXPECT(NEAR(f,200));
    },2);
    EXPECT(my_project_do_work(2)==MY_PROJECT_OK);
    EXPECT(my_project_do_work(2)==MY_PROJECT_OK);
    EXPECT(my_project_do_work(2)==MY_PROJECT_CANNOT_WORK); // 3rd call to the_lib will fail
    EXPECT(my_project_do_work(50)==MY_PROJECT_OK);  // call the_lib_do_something(100)
    EXPECT(my_project_do_work(100)==MY_PROJECT_OK); // call the_lib_do_something(200)
    EXPECT(my_project_do_work(2)==MY_PROJECT_OK);
    EXPECT(my_project_do_work(100)==MY_PROJECT_OK); // call the_lib_do_something(200)
    EXPECT(my_project_do_work(2)==MY_PROJECT_OK);
    EXPECT(my_project_do_work(2)==MY_PROJECT_OK);
});

TEST(when_no_callback_is_recorded_and_mock_is_called_then_test_fails,[]() {
    init_my_project_correctly();

    // Test will fail because callback 'the_lib_do_something_without_arg' has not been registered :
    my_project_do_work(2);
});

TEST(when_some_callbacks_are_never_called_then_test_fails,[]() {
    init_my_project_correctly();

    MINI_MOCK_ON_CALL(the_lib_do_something_without_arg,[](){
        return THE_LIB_OK;
    },4);
    my_project_do_work(2);
    my_project_do_work(2);

    // Test will fail at the end because we registered 4 calls to 'the_lib_do_something_without_arg'
    // but only 2 had happen
});

CREATE_MAIN_ENTRY_POINT();
