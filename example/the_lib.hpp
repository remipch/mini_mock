// Fake library header to illustrate MiniMock

// Just declare a few functions with different signatures
// - void/non-void
// - with/without arguments

#define THE_LIB_OK (25)
#define THE_LIB_ERROR (-15)

int the_lib_initialize(bool b,int i);

void the_lib_do_something(float f);

int the_lib_do_something_without_arg ();
