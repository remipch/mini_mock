#include "my_project.hpp"
#include "the_lib.hpp"

// Fake project to illustrate MiniMock

static bool my_project_is_initialized = false;

int my_project_initialize(std::string s) {
    if(my_project_is_initialized) {
        return MY_PROJECT_INCORRECT_STATE;
    }
    if(s!="correct_args") {
        return MY_PROJECT_INCORRECT_ARGUMENT;
    }
    if(the_lib_initialize(true,10)!=THE_LIB_OK) {
        return MY_PROJECT_CANNOT_INITIALIZE;
    }
    my_project_is_initialized = true;
    return MY_PROJECT_OK;
}

int my_project_do_work(int i) {
    if(!my_project_is_initialized) {
        return MY_PROJECT_INCORRECT_STATE;
    }
    if(the_lib_do_something_without_arg()!=THE_LIB_OK) {
        return MY_PROJECT_CANNOT_WORK;
    }
    if(i>10) {
        the_lib_do_something((float)(i*2));
    }
    return MY_PROJECT_OK;
}
