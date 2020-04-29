#include <strstream>
using namespace std;
#pragma once
// this is the header file, it will automatically link up functions from other cpp scripts
// you only need to put their declaration here for them to work in another script

// show the usage of utility libraries, the source script for this function is stored in "Utility.cpp"
void ShowUtility();

// show the core usage of c++ stl 
void ShowCore();

// the use of extern keyword, the variable first is first defined here with a value 10,
// then used in the Core.cpp script by outputting its function
int first = 0;