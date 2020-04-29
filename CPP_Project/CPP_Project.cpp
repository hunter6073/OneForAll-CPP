/***********************************************************
* Project: Relearn C++ in an hour

* Author: Ted Wong(Hechun Wang)

* Description: this project is to help programmers with former knowledge with C++ relearn the essentials 
* in a short amount of time. There are currently around 1000 lines of code to cover the essentials.
* the contents of this script covers the following:
* 1. C++ Core Basics
* 2. C++ Pointers
* 3. C++ Class
* 4. C++ Exception
* 5. C++ Streams
* 6. C++ File I/O

* Note: this project is created using visual studio 2019 on windows, you can import this project 
* and run it to see the results. If you choose to use a different IDE or use 
* linux system to compile this program, then please change the headers accordingly to avoid errors

* Another note is all essential features are commented with keywords, so if you need to look at an example for
* a specific feature, such as 'virtual functions' or 'polymorphism', perform keyword search for their examples
* (This is not yet fully implemented)

* The code are originally from "C++: The complete reference, fourth edition" by Herbert Schildt

* Progress:
* Next step is to add in keywords for easy searching

***********************************************************/
// 

# include <iostream> // this is the library for c++
# include "Base.h" // use own header to link up other source files
using namespace std; // using standard name space

int main()
{	

	// Search for all core c++ libraries and functions in the "Core.cpp" script
	ShowCore();
	
	// Search for all utility libraries and functions in the 'UtilLib.cpp' script
	ShowUtility();

	/*************************************
	
	* you're welcome to tweak this project as you like and correct my wrongs, additional features are very welcome!
	* perhaps add a script to show multithreading?
	* perhaps add a script to introduce sockets and web related issues?
	* perhaps add a script to introduce linux based libraries?
	* hope to see additions!
	
	**************************************/

	return 0; 
}