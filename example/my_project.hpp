#include <string>

// Fake project to illustrate MiniMock

#define MY_PROJECT_OK (12)
#define MY_PROJECT_INCORRECT_STATE (-14)
#define MY_PROJECT_INCORRECT_ARGUMENT (-45)
#define MY_PROJECT_CANNOT_INITIALIZE (-84)
#define MY_PROJECT_CANNOT_WORK (-87)

int my_project_initialize(std::string s);

int my_project_do_work(int i);
