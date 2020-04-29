// this script contains utility function that formats the output for all scripts

# include <iostream> // this is the library for c++
# include <cstring> // using strings in c++
# include <exception> // use self made exceptions
# include <iomanip> // access manipulators that take parameters (such as setw( )),
# include <fstream> // reading in and writing out to files
# include <cctype> // use eof() function
# include <strstream> // use array based I/O
using namespace std;

// A simple custom output manipulator.
// custom displays using output manipulators to display Right Arrow
ostream& end(ostream& stream)
{
	// set things here will only result in current stream manipulation, further out stream will not be affected
	// stream.setf(ios::showbase);
	// stream.setf(ios::hex, ios::basefield);
	stream << "\n-------------------------------" << endl;
	return stream;
}