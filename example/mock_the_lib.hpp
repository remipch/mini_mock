#pragma once

#include "the_lib.hpp"

MINI_MOCK_FUNCTION(the_lib_initialize,int,(bool b,int i),(b,i));

MINI_MOCK_FUNCTION(the_lib_do_something,void,(float f),(f));

MINI_MOCK_FUNCTION(the_lib_do_something_without_arg,int,(),());
