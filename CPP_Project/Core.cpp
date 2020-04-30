// this script contains a demonstration of core c++ functions and features

# include <iostream> // this is the library for c++
# include <cstring> // using strings in c++
# include <exception> // use self made exceptions
# include <iomanip> // access manipulators that take parameters (such as setw( )),
# include <fstream> // reading in and writing out to files
# include <cctype> // use eof() function
# include <strstream> // use array based I/O
# include "util.h" // utility library to format output

using namespace std;

// define functions to show each feature usage
void ShowBasics(); // show basic usage of functions and other features
void ShowPointer(); // show usage of pointers
void ShowClass(); // show usage of classes
void ShowException(); // show usage of try catch exception
void ShowStream(); // show usage of custom stream functions and flags
void ShowFile(); // show usage of file input and output

// define forever constant values in this script
#define SIZE 100 

// define custom classes, structs and unions
class myclassbase {
public: // the following functions and variables are public and usable by all
	int sti = 0; // a const variable in a class, does not need to initialize an object to call this, originally set to 0
	int nsti = 0; // a public variable for the class

	int getplus(const int* a); // a function that intakes a const parameter

	int getPV(); // invoking the this pointer to access parameters within the class
	void setPV(int n) { pvalue = n; }
	// a virtual function will always remain virtual no matter how many times the base class gets inherits
	virtual void vfunc() { // this is a virtual function, it will be overwritten in the derived class
		cout << "This is base's vfunc().\n";
	}

	// Note:
	// pure virtual functions are just virtual functions with nothing within the brackets. 
	// this is legal. for example virtual void compute = 0

	myclassbase(); // this is a constructor, have no return type, happens when the class is created
	myclassbase(int k);// another constructor that handles one input parameter

	~myclassbase(); // destructor, happens when the class is destroyed

	// Note:
	// the sequence for constructors and destructors for base and derived is
	// Constructing base
	// Constructing derived
	// Destructing derived
	// Destructing base
	// constructor sequence from base to derived, destructor sequence from derived to base

	// friend keyword allows the access of x's private variables(if x's type is the same as the class)
	// also makes sum a global function
	friend int sum(myclassbase x);

	// friend keyword can be used on a class as well, this means
	// that the myclassderived object can access the stack object's private values 
	friend class myclasserived;

	// operator overloading
	int operator[](int i) { return i; } // overloading operator[] for the class object

	myclassbase operator+(myclassbase myclass); // overload myclass1+myclass2

	// use friend to create an override operator function, this only overwrites the operator for myclassbase - myclassbase
	friend myclassbase operator-(myclassbase myclass1, myclassbase myclass2);

	myclassbase operator()(int i, int j); // overload the () operator when using myclass(1,3) returns the overloaded operator

	void* operator new(size_t size); // overloading new operator for this class

	void operator delete(void* p); // overloading delete operator for this class

	// void* operator new[](size_t size); // overloading arrays

	// void operator delete[](void* p); // delete array overloading

	myclassbase *operator->() {return this;} //overloading the -> operator

	// by doing this , the overloaded operator << function can now access the phonebook object o's 
	// private variables and functions
	friend ostream& operator<<(ostream& stream, myclassbase myclass); 
	// overloading the input operator
	friend istream& operator>>(istream& stream, myclassbase& myclass);

	// Note:
	// the comma operator can be overloaded as well, operator,()
	// operator+, operator-, operator*,operator/,operator++,operator--,operator+=
	// can be overloaded. ++a calls operator++, a++ calls operator++(int x)
	// you can turn the operator overload functions into friend functions, however, friend overload
	// cannot overload the = (), [] or -> operators
	// friend operator overloading adds flexibility, can have 100 + obj or obj + 100, if only in class
	// operator overloading, obj + 100 works, but 100 + obj doesn't

private: // the following functions and variables are private and usable only by the class itself
	int pvalue; // a value that is private
protected: 
	// the following functions and variables are protected, they act like private when accessed by
	// other classes but like public when accessed by derived classes
	int pctvalue; // a value that is protedted

};

class secondclass { public:int value; protected:int pctvalue; }; // only a temp class to demonstrate multiple inheritance

// myclassderived inherits everything from myclassbase due to the use of public
// myclassderived does not inherit any public instance from secondclass, any usage must consist of secondclass::variablename
// a::base, b::base, c::a,b is legal, but must be careful of the naming usage.
class myclassderived : public myclassbase,secondclass{ // multiple inheritance
public:
	void set(int i, int j) { myclassbase::setPV(i); secondclass::value = j; } // a way to access the private variable without declaring it as public
	void vfunc() { // derive function from parent's virtual function
		cout << "This is derived's vfunc().\n";
	}
};

// a generic class 
// use typename keyword instead of using class
// if a template function and a normal function(with datatype)with matching inputs is defined under the same name, the template function comes into effect
template <typename Type1, typename Type2> class mygenericclass
{
	Type1 i;
	Type2 j;
public:
	mygenericclass(Type1 a, Type2 b) { i = a; j = b; cout <<"a generic class has been created: "<< i << ' ' << j << end;}
};

// an exception class
class MyException {
public:
	char str_what[80];
	int what;

	MyException() { *str_what = 0; what = 0; }

	MyException(char* s, int e) {
		strcpy_s(str_what, s);
		what = e;
	}

};

// member syntax initialization
class IntPair {
public:
	int a;
	int b;

	IntPair(int i, int j) : a(i), b(j) { }// this constructor initializes a const value in the class
};

class MyClass2 {
	IntPair nums; // now OK
	mutable int i; // i is mutable in const context
	int j; // j is an ordinary int
public:

	// Initialize nums object using initialization syntax.
	MyClass2(int x, int y) : nums(x, y) { }

	int getNumA() { return nums.a; }
	int getNumB() { return nums.b; }

	explicit MyClass2(int s): nums(s,0) { // Demo class can only be instantiated using Demo dem(1) and not Demo dem = 1
					   // because the use of explicit keyword, also, nums must be initialized
		j = s;
	}

	// the const keyword does not allow editing within the braces unless the variable to be edited is mutable
	int geti() const {
		return i; // ok
	}

	void seti(int x) const {
		i = x; // now, OK because i is mutable
	}

	/* The following function won't compile.
	  void setj(int x) const {
		j = x; // Still Wrong! because the use of const
	  }
	*/
	void f2(int a) volatile {}; // volatile member function
	// The volatile keyword tells the compiler that a variable's value may be changed in ways
	// not explicitly specified by the program, ie being used outside of the program
};

// creating a struct called employee with an entity emp, used in c
struct employee
{
	char name[80];
	int age;
	float wage;
} em; // create an employee object em here

// creating a union, the same union objects uses the same values in memory
union swap_byte { 
	int swap();
	unsigned short u = 10;
};

// defining a customized namespace
namespace CounterNameSpace {
	int upperbound;
	int lowerbound;
}

// unnamed namespace, this s a namespace that only works in this file, all 
// parameters are exposed and usable in this file only
namespace {
	// you can do include operations to make sure the library only happens in this namespace
# include <strstream> // use array based I/O
	int k;
}
// this is nested namespace, in order to access j, the syntax is NS1::NS2::j
namespace NS1 {
	int i;
	namespace NS2 { // a nested namespace
		int j;
	}
}


// define global functions
void my_Thandler(); // custom handler to handle termination process during try catch
int series(void); // you can put void in a bracket for null parameter or put nothing in it
void sqrval(const int* val);//function to demonstrate const_cast 
double dfA(double d = 0.0); // function that has a default parameter
void neg(int* i); // function that handles reference

// define global variables
char carray[SIZE] = "this is not a full char array";
char carrayfull[] = "this is a full char array";
int num = 0; // a global int variable
int* pi = &num; // point the pointer to an int's address
myclassbase myclass;

// using templates, the data type for this function swapargs can be anything
// a template can have two different datatypes
// template <class type1, class type2> void myfunc(type1 x, type2 y) for multiple class input
template <class X> void swapargs(X& a, X& b);

// define global manimupators 
istream& getpass(istream& stream);// A simple input manipulator.

// main function
void ShowCore()
{
	cout << "show C++ core features:" << end;
	ShowBasics(); // show basic usage of functions and other features
	cout << endl;

	cout << "show C++ pointer features:" << end;
	ShowPointer(); // show usage of pointers
	cout << endl;

	cout << "show C++ class features:" << end;
	ShowClass(); // show usage of classes
	cout << endl;

	cout << "show C++ exception features:" << end;
	ShowException(); // show usage of try catch exception
	cout << endl;
	cout << "show C++ stream features:" << end;
	ShowStream(); // show usage of custom stream functions and flags
	cout << endl;

	cout << "show C++ file IO features:" << end;
	ShowFile(); // show usage of file input and output
	cout << endl;

}

void ShowBasics() {
	// Note:
	// basic data types: char, int, float, double, bool
	// sign, unsigned, long, short are keywords to apply to numerical based types,
	// long and short limits the length of float and double
	// sign, unsigned can be assigned to characters, chars are unsigned by default
	// sign makes a character positive by setting the highest order bit to 0,
	// while unsigned sets it to 1(negative)

	int num = 1; // num here is a local integer variable
	cout << "[Core01] local num is: " << num << " and global num is: " << ::num<<end; // using global variable with same name as local variable;

	int& ref = num; // independent reference to local num
	ref = 1001;
	cout << "[Core02] after changing the reference variable, the value of the referenced item is now: " << num << end;

	string str = carray; // assign string to char array will only take in the filled char, will neglect the unfilled blanks
	cout << "[Core03] string is: " << str << end;

	// Note:
	// There are four storage class specifiers: extern, static, register, auto
	// extern can get global values from inside of the script and outside, it's good practice to define
	// all global variables in one script and visit it in other scripts using the extern keyword
	extern int first; // links to the first variable in Base.h, then outputs its value
	cout << "[Core04] using extern keyword to link up a variable to a different script: " << first << end;

	//a static local variable is a local variable that retains its value between function calls
	cout << "[Core05] using a static variable in the function series(), the first call is: " << series() << "\n"; // output 23
	cout << "using a static variable in the function series(), the second call is: " << series() << end; // output 46

	//Standard C++ states that register is a "hint to the implementation that 
	// the object so declared will be heavily used, so stored in cpu instead of memory
	register int temp = 0; // temp is still int, but stored in cpu so that when next called it gets called faster

	// simple true false condition in one line with casting
	temp = temp > 9 ? (int)(3 / 2) : (int)(1 / 3); // return 3/2 if temp > 9 and 1/3 if temp < 9
	cout << "[Core06] temp(1/3) is :" << temp << end;// output is 0, c and c++ rounds down

	// sizeof can show you how large a data type takes in memory
	cout << "[Core07] the size of double in this operating system is: " << sizeof(double) << end;

	/* this code is to get continuous inputs until the user enters an exit command, uncomment to see it in action
	string command;
	while(cin>>command){ // cin, get a variable from console input, or cin stream input
	if(command == "exit")
	{
		break;
	}
	cout<<command<<endl;
	}
	*/

	// using a struct pointer to point employee_1 to emp
	struct employee emp;
	struct employee* employee_1 = &emp; /* address of emp into p */
	// setting and getting info from a pointer uses the "->" arrow in c++
	employee_1->wage = 35;
	cout << "[Core08] employee's wage is: " << employee_1->wage << end;

	swap_byte us1; // this is a union
	cout << "[Core09] union shares memory with variables: " << ++us1.u<<end;

	// traverse the char array and output the contents using a for loop
	cout << "[Core10] traversing a char array using arr[i] in for loop:" << endl;
	for (int i = 0; carray[i]; i++) // empty space will be neglected
	{
		cout << carray[i]; // output a variable
	}
	cout << end;

	// a function can have a default parameter
	cout << "[Core11] dfa with no input variables is: " << dfA() << " and with input is: " << dfA(22.3) << end;

	int si = 10, sj = 20;

	cout << "[Core12] Original i, j: " << si << ' ' << sj << '\n';
	// using the swapargs function for different data types
	swapargs<int>(si, sj); // swap integers
	cout << "swapped i, j: " << si << ' ' << sj << end;


	myclassbase* bp, b_ob;
	myclassderived* dp, d_ob;

	dp = dynamic_cast<myclassderived*> (&d_ob); // perform a dynamic casting from derived to derived
	// a dynamic casting can be done from derived to derived,
	// from derived to base, and from base to base,
	// but from base to derived is not okay
	if (dp) {
		cout << "[Core13]Cast from Derived * to Derived * OK.\n";
		dp->getPV();
		cout << end;
	}
	else
		cout << "Error\n";

	cout << endl;

	// use const cast to cast away const and edit const variables
	cout << "[Core14] num before call: " << num;
	sqrval(&num);
	cout << "num after call: " << num << end;

	// use static_cast is the same as (double)num
	cout << "[Core15] static cast int into double: " << static_cast<double> (num) / 3 << end; // static cast a value from one type to another;

	// use reinterpret_cast
	char* stp = carray;
	num = reinterpret_cast<int> (stp); // cast pointer to integer
	cout << "[Core16] reinterpret_cast from char* to int: " << num << end;

	// using namespace
	CounterNameSpace::lowerbound = 3; // using an item in a namespace in its full form
	cout << "[Core17] full namespace usage: " << CounterNameSpace::lowerbound << end;
	using CounterNameSpace::lowerbound; // only lowerbound is visible, if you want to use upperbound, you have to use CounterNameSpace::upperbound
	lowerbound = 10; // OK because lowerbound is visible
	using namespace CounterNameSpace; // all members are visible, you can simply use lowerbound and upperbound without adding CounterNameSpace::
	upperbound = 100; // OK because all members are now visible
	cout << "[Core18] lowerbound: " << lowerbound << " upperbound: " << upperbound << endl;

	// this is an assembly code using asm keyword
	// asm int 5; // generate intertupt 5, don't use this unless absolutely necessary
}

void ShowPointer() {
	*pi++;
	cout << "[Core19] after performing *pi++, *pi is now:" << *pi << "at address: " << pi << end;

	// traversing an array using pointer
	char* cp = carray; // point the char* pointer to the beginning of the carray, which is c[0]

	// keep traversing until cp reaches a null value in the array,
	//which will happen if the array is defined larger than the contents it contains
	cout << "[Core20] traversing a char array using pointer cp, in the form of *cp++:" << endl;
	while (*cp != NULL)
	{
		cout << *cp++;
	}
	cout << end;

	// traversing an array in an array-like fashion using pointer
	cp = carray; // return cp to the head of the array
	cout << "[Core21] traversing a char array using pointer cp, in the form of cp[i]:" << endl;
	for (int i = 0; i < SIZE; i++)
	{
		if (cp[i] == NULL)
		{
			break;
		}
		else
		{
			cout << cp[i];
		}
	}
	cout << end;

	// Note:
	// new and delete keywords are used to allocate and free memory at run time
	// c++ also supports dynamic memory allocation functions called malloc and free
	int* p; // p is an int pointer now

	try { // try catch to catch bad allocation, this is only in c++ for checking allocation errors
		p = new int; // allocate space for an int pointer
		p = new int[10]; // allocate p with the space of an array with 10 items, now p is an array pointer
		delete[] p; // release the array pointer p and frees up memory
		p = new int(87); // allocate space for an integer to p and then initialize p to 87
		delete p; // delete pointer p and frees up memory

	}
	catch (bad_alloc xa) {// happens when there is an allocation failure
		cout << "Allocation Failure\n";
		// exit the program manually, will not go to any lines after this line
		exit(12); //return code 12 when program ends
	}

	// using a pointer function
	cout << "[Core22] num is originally: " << num;
	neg(&num);
	cout << " but after a pointer function that changes its value, it is now:" << num << end;

	// using a pointer to fire a function
	int (*fp)() = series; // a pointer to a function
	cout << "[Core23] using a function pointer to fire the function: " << fp << end;

}

void ShowClass() {
	// a class may be defined within a function
	class tempclass {
	public:
		void output() {
			cout << "this is a class whithin a function" << end;
		}
	} tmp;

	tempclass t;
	t.output();

	cout << "[Core24] using the getplus(i) function from myclass, the result is: " << myclass.getplus(pi) << end; // use a function from the class

	// defining a friend function within a class enables the (global) function to use the class' private variables
	cout << "[Core25] using sum() is a friend function that can access the class' private variables:" << sum(myclass) << end;

	// change the static value in the class, after which all reference to sti in base class will be changed 
	/* something wrong here, fix
	myclassbase::sti = 1;
	cout << "after changing sti in myclassbase, it is now: " << myclassbase::sti;
	cout << "\n-------------------------------" << endl;
	*/

	// Note: multiple ways to create an object(array)
	// create an object the same as the original, is not a reference, changes happen in myclass2 will not reflect on myclass
	// myclassbase myclass2 = myclass; 
	// creating multiple instances with multiple constructor parameters
	// myclassbase myclassarray[2] = {(1,2),(2,3)}; if myclassbase takes in more than 2 parameters for its constructor
	// myclasssbase myclassarray[2] = { 1,2 };if myclassbase takes in 1 parameter for its constructor
	// myclasssbase myclassarray[2] = { mstack(1),mstack(1,2) }; this is a more direct way of initializing
	// 	myclassbase myclass2 = 1; // this is the same as myclassbase myclass2(1)

	myclassbase* pcb = new myclassbase; // an object pointer initialized with new, it is now allocated with the memory of myclassbase size
	pcb = &myclass; // point the pointer to an object
	cout << "[Core26] displaying object's function value via pointer: " << pcb->getplus(pi) << end;// accessing an object's function via pointer

	// getPV function access the class' private value by using this keyword
	cout << "[Core27] using this keyword to access private variables and functions whithin a class: " << myclass.getPV() << end;

	// overloading a class' operator
	cout << "[Core28] overloading the [] operator for a class: " << myclass[1] << end;

	// Note:
	// a poiner with base type can point to a derived type object and access the base type functions,
	// it cannot access to any of the derived type's function

	int myclassbase::* data = &myclassbase::nsti; // data member pointer that points to an int variable in the class
	int (myclassbase:: * func)(const int* a) = &myclassbase::getplus;// function member pointer that points to a function in the class
	cout << "[Core29]using the data pointer within a class: " << myclass.*data << endl; // using the data pointer within a class
	cout << "using the function pointer within a class: " << (myclass.*func)(pi) << endl; // using the data pointer within a class
	cout << "using the data pointer within a class via pointer" << pcb->*data << end;

	//Note
	// the difference between p=&myclassbase.nsti and d = &myclassbase::nsti is that p is a pointer
	// to an integer inside a specific object, however, d is a offset that indicates
	// where nsti will be found in any object of type myclassbase

	myclassbase myclasstemp = myclass + myclass; // override + for myclassbase class
	delete& myclasstemp; // override delete for myclassbase class

	// Note:
	// when deriving from a private class, such as mstack:stack(without public keyword), only variables that fall under proteced are accessible by the mstack object
	// while public and private variables and functions are not accessible, the protected variables become private to the derived class, now when new children inherits
	// the derived class, the protected values from the grandparent class are unaccessible

	myclassderived myderived; // t is derived from multiple base classes
	myderived.set(1, 2);
	myderived.getPV(); // myderived can access multiple parent classes' functions
	myclass.vfunc(); // use base class' vfunc
	myderived.vfunc(); // user derived class' vfunc

	// use generic classes
	mygenericclass<int, double> gob1(10, 0.23);

	MyClass2 mc2(3, 4); // using member declaration
	cout << "[Core30] using member declaration: " << mc2.getNumA() << end;
}

void ShowException() {

	try { // start a try block

		// attempt to do something here
		throw 100; // throw an error manually ,the error object is an int with value of 100
		throw myclass; // throw an error, the error object is a class myclassbase
		throw MyException((char*)"not positive", 12); // throw a custom exception class
		cout << "This will not execute"; // this line will not execute

	}
	catch (int i) { // catch an error
		// typeid shows the name of the object class
		cout << "[Core31] Caught an exception -- type of the error is: " << typeid(i).name() << end;

	}
	catch (myclassbase myclass) // when catching a base class and a derived class, base class has priority over derived class
	{
		cout << "Caught an exception -- type of the error is: " << typeid(myclass).name() << end;
		throw; // rethrow i out of current try catch to be handled by the outer try catch
	}
	catch (MyException e) { // catch an error, myexception is a class
		cout << e.str_what << ": " << e.what << end;
	}
	catch (...) { // catch all exceptions
		cout << "Caught an exception!\n";
	}

	// set handler for terminate event, this means when encountering any issues, the error will be 
	// thrown in a way that is defined in my_Thandler, and since my_Thandler uses abort(), it will terminate the try catch

	set_terminate(my_Thandler);
	try {
		throw 100; // throw an error
	}
	catch (int i)
	{
		// this won't work anymore because my_Thandler does not throw anything
	}
	catch (...) {// this will be the only working catch, no other catch works because set_terminate does not throw anything
		cout << "123 \n";
	}

}

void ShowStream() {

	// C++ I/O system operates through streams
	cerr << "[Core32] error" << end;   // standard error output
	clog << "[Core33] log"<<end; // buffered version of cerr

	// Note: 
	// there are many flags that could be set to a stream:
	// skipws: skip white space, left/right: output is left/right justified
	// internal: a numeric value is padded to fill a field by inserting spaces between any sign or base character
	// showbase: causes the base of numeric values to be shown
	// uppercase: shows the output in full upper case
	// showpos: if the numeric value is positive, adds a + sign before the value
	// showpoint: causes a decimal point and trailing zeros to be displayed for all floating-point output
	// scientific: floating-point numeric values are displayed using scientific notation
	// fixed: floating-point values are displayed using normal notation
	// unitbuf: the buffer is flushed after each insertion operation.
	// boolalpha: Booleans can be input or output using the keywords true and false

	// Note:
	// Since it is common to refer to the oct, dec, and hex fields, they can be collectively 
	// referred to as basefield. Similarly, the left, right, and internal fields can be referred 
	// to as adjustfield. Finally, the scientific and fixed fields can be referenced as floatfield.

	// the class of a flag is ios::fmtflags
	ios::fmtflags df(cout.flags()); // get default flags to reset them after this function

	// You can OR together two or more flags
	cout.setf(ios::showpoint | ios::showpos); // this is the same as cout.setf(ios::showpoint);cout.setf(ios::showpos);
	cout << "[Core34] showpoint and showpos renders: "<<100.0; // displays +100.000
	cout.unsetf(ios::showpoint); // use unsetf to unset a flag for a stream
	cout << " after removing showpoint flag: " << 100.0<<end;

	// an overloaded use of the sef function, only the flags occured in flag1 and flag2 of the setf
	// function is in effect
	cout.flags(df); // reset the flags, or set flags to default flag bits
	cout.setf(ios::showpoint | ios::showpos, ios::showpoint); // only used in very special situations
	cout << "[Core35] only showpoint works: "<<100.0 << end; // displays 100.000, not +100.000

	cout.flags(df);
	cout.precision(4); // set precision for stream
	cout.width(10);
	cout.fill('*'); // set char to fill whitespaces
	cout << "[Core36] 10.12345 with precision 4 and width 10 is:" << 10.12345<<end; // displays *****10.12

	cout.flags(df);
	// field width applies to strings, too
	cout.width(10);
	cout.unsetf(ios::right); // unset right justify
	cout.setf(ios::left); // left justify
	cout << "[Core37] 10.12"<<end; // displays 10.12*****

	cout <<"[Core38] hex(100): "<< hex << 100 << end;
	// setfill: set the fill character
	// setw: Set the field width to w.
	// setfill, setw and other functions only apply to the current stream if used in this fashion
	cout <<"[Core38] "<< setfill('?') << setw(10) << 2343.0 << end;

	// use the boolalpha flag and dec only in this output
	cout <<"[Core39] "<< dec << true << " " << boolalpha << true << end;

	// overloading << operators using custom ostream, also using a custom manipulator flag
	cout << "[Core40] output myclass with a customized flag: "<<myclass<<end;
	// custom input for the in stream
	//cin >> ppa;

	// demonstration of using a custom input 
	//char pw[80];
	//cin >> getpass >> pw;

	cout.flags(df); // reset the flags
	// buffered stream output
	// initializing an array based ostrstream with 80 chars as its size and arrstr as the storage array
	ostrstream outs(carray, sizeof(carray));
	outs << "C++ array-based I/O. "; // output the string into outs
	outs << 1024 << hex << " "; // output 1024 in hex into outs
	outs.setf(ios::showbase); // set the outs stream's showbase flag
	outs << 100 << ' ' << 99.789 << ends; // output 100 99.789 into the outs stream
	outs << ends;  // null terminate
	cout <<"[Core41] " << outs.pcount() << endl; // display how many chars in outs
	cout << "carray after ostrstream is: "<<carray << end;  // display string on console

	char arrstr[80] = "10 Hello 0x75 42.73 OK";
	// using an input stream based on array IO
	istrstream ins(arrstr);
	int arri;
	float arrf;
	// reading: 10 Hello
	ins >> arri;
	ins >> arrstr;
	cout << "[Core42] read from istrstream:" << end;
	cout << arri << " " << arrstr << endl;
	// reading 0x75 42.73 OK
	ins >> hex >> arri;
	ins >> arrf;
	ins >> arrstr;
	cout <<"[Core43] "<< hex << arri << " " << arrf << " " << arrstr << end;

	// perform both input and output
	strstream strio(carray, sizeof(carray), ios::in | ios::out);
	int ioa, iob;
	string iostr;
	strio << "10 20 testing "; // write into strio
	strio >> ioa >> iob >> iostr; // read from strio
	cout << "[Core44] both input and output ";
	cout << ioa << " " << iob << " " << iostr << end;

	// use dynamic arrays in array based IO
	char* arrp;
	outs.seekp(0, outs.beg); // go to head and clear the stream buffer
	outs.flush();
	outs << "C++ array-based I/O ";
	outs << -10 << hex << " ";
	outs.setf(ios::showbase);
	outs << 100 << ends;
	arrp = outs.str(); // Freeze dynamic buffer and return pointer to it
	cout << "[Core45] outs is:\n";
	cout << arrp << end;

	
	// binary I/O in array form
	char* bbbp = (char*)"this is a test\1\2\3\4\5\6\7";
	ins = istrstream(bbbp);
	char bbbc;
	cout << "[Core46] binary I/O in array form\n";
	// read and display binary info
	while (!ins.eof()) {
		ins.get(bbbc);
		cout << hex << (int)bbbc << ' ';
	}
	cout << end;


	cout.flags(df); // reset the flags

}

void ShowFile() {
	// Note:
	// there are different flags you can use to open a file
	/*
	ios::app // append to the end of the file
	ios::ate
	ios::binary // open a file in binary form, only ones and zeros
	ios::in
	ios::out // opens a normal output file
	ios::trunc
	*/

	// using ofstream to write some output to a file
	ofstream out("INVNTRY"); // output, normal file, overwrite everytime, will create a file if not exist by default
	if (!out) {
		cout << "Cannot open INVENTORY file"<<end;
		return ;
	}
	// write into file, each item is seperated via space
	out << "Radios " << 39.95 << endl;
	out.close();


	// read from the file
	ifstream in("INVNTRY"); // input
	if (!in) {
		cout << "Cannot open INVENTORY file"<<end;
		return ;
	}
	char item[20];
	float cost;
	// output the content of the first line of the file
	in >> item >> cost;
	cout << "[Core47] " <<item << " " << cost << end;
	in.close();

	// write [A-Z] characters to disk
	out = ofstream("INVNTRY", ios::out | ios::binary); // ios::output means for output only
	for (int i = 65; i < 91; i++) out.put((char)i);
	out.flush(); // flush the buffer to output everything into the file
	out.close();

	// read a file in characters
	char ch;
	in = ifstream((char*)"INVNTRY", ios::in | ios::binary); // ios::in means for input only
	cout << "[Core48]  ";
	while (in.get(ch)) { // in will be false when eof is reached

		ios::iostate st; // the iostate of the current pointer
		st = in.rdstate(); // get the current pointer's readstate
		if (st & ios::eofbit || in.eof()) // if the state of the pointer is end of file ,the two things are the same
		{
			cout << "EOF encountered\n";
		}
		else if (st & ios::failbit || in.fail()) // if the state of the pointer is a failed bit
		{
			cout << "Non-Fatal I/O error\n";
		}
		else if (st & ios::badbit || in.bad()) // if the state of the pointer is a bad bit
		{
			cout << "Fatal I/O error\n";
		}
		/* good bit
		else if (in.good())
		{
			 cout << "good bit";
		}
		*/
		if (in) cout << ch;
	}
	cout << end;

	// write an object into a file and read it
	// set the employee struct object
	em.age = 35;
	strcpy_s(em.name, "Ralph Trantor"); // cannot do em.name = "ralph trantor"
	em.wage = 235;

	// write data
	out = ofstream ("INVNTRY", ios::out | ios::binary);
	// you can write anything into the file by using out.write(address of object, size of object),
	// this can be a class object, a struct object, an int or an array
	out.write((char*)&em, sizeof(struct employee)); // convert employee object into a char* and write into file
	out.close();
	// now, read back;
	in = ifstream("INVNTRY", ios::in | ios::binary);
	in.read((char*)&em, sizeof(struct employee)); // read an object from a file
	// see how many bytes have been read
	cout <<"[Core49] "<< in.gcount() << " bytes read\n";
	cout << "name: "<<em.name<<" age:"<<em.age << end;
	in.close();

	// using getline to read lines from the file
	out = ofstream ("INVNTRY"); // output two lines into the file
	out << "Radios " << 39.95 << endl;
	out << "this is the second line" << endl;
	out.close();
	in = ifstream("INVNTRY"); // input
	char str[255];
	in.ignore(10, ' '); // ignore reading of the input stream until 10 characters is read or a space is read
	cout << "[Core50] peek:" << in.peek() << "\n"; // peek into the next character
	in.putback('-'); // put a character into the head of the stream
	while (in) { //!in.eof() is the same as in in the condition
		
		in.getline(str, 255);  // delim defaults to '\n', read 255 bit into the string
		if (in) cout << "getline:" << str << endl;
	}
	in.close();
	cout << end;

	// using seekp() and seekg() functions to move the pointer to the correct location
	fstream fs = fstream("INVNTRY", ios::in | ios::out | ios::binary);
	fs.seekp(12, ios::beg); // move the out pointer to 12 chars after the flag, the offset can be a negative number
	// ios::beg is the beginning of the file
	// ios::cur is the current pointer position of the file 
	// ios::end is the end of file

	// use a tellp and a tellg function to see where the file pointer is at
	// they return the same value for out pointer
	// in pointer can only use tellg()
	cout << "[Core51] out tellp:" << fs.tellp() << " out tellg:" << fs.tellg() << end;
	fs.put('t'); // put a character at this position of the pointer
	fs.close();

}

/*************************************** myclassbase functions and operator overloading ************************************/

// this is a constructor that takes no parameters
myclassbase::myclassbase() 
{ 
	pvalue = 0; 
	cout << "myclass base object created with pvalue 0"<<end;
} 

// another constructor that handles one input parameter
myclassbase::myclassbase(int k) { 
	pvalue = k; 
	cout << "myclass base object created with pvalue " << k<<end;
} 

myclassbase::~myclassbase() { // constructor function for stack
	cout << "myclassbase object destroyed"<<end;
}

myclassbase myclassbase::operator+(myclassbase myclass2)
{
	myclassbase temp;
	temp.nsti = this->nsti + myclass2.nsti;
	return temp;
}

myclassbase myclassbase::operator()(int i, int j) // overload the () operator when using myclass(1,3) returns the overloaded operator
{
	myclassbase temp;
	temp.nsti = i + j;
	return temp;
}

void* myclassbase:: operator new(size_t size) {
	void* p;
	cout << "overloading new operator for myclassbase.\n";
	p = malloc(size);
	if (!p) {
		bad_alloc ba;
		throw ba;
	}
	return p; // returns a void* pointer
}

void myclassbase::operator delete(void* po)
{
	cout << "overloading delete operator for myclassbase\n";
	//free(po); // errors here, fix
}

// overwrites operator- for all myclassbase objects 
myclassbase operator-(myclassbase myclass1,myclassbase myclass2)
{
	myclassbase temp;
	temp.nsti = myclass1.nsti - myclass2.nsti;
	return temp;
}

//myclassbase* myclassbase::operator->() { return this; } //overloading the -> operator

// Display name and phone number. a custom output stream for the myclassbase class
ostream& operator<<(ostream& stream, myclassbase myclass)
{
	stream << myclass.getPV() << " ";
	return stream; // must return stream
}

// custom input stream for the myclassbase class
istream& operator>>(istream& stream, myclassbase& myclass)
{
	cout << "Enter nsti value: ";
	stream >> myclass.nsti;
	cout << "\n";
	return stream;
}

// the usage of const limits the user to changing the parameters
int myclassbase::getplus(const int* a)
{
	// *a += 1; this doesn't work because a is uneditable due to the const keyword
	return *a;
}

// invoking the this pointer to access parameters within the class
int myclassbase::getPV() {
	// invoking the this pointer
	return this->pvalue;
}

/******************************* function implementations ****************************************/

// inline very small functions makes the program run faster, 
// only inline the key functions to make the program faster
inline int sum(myclassbase x) // because sum is a friend of stack, it can directly access stack's private variables
{
	return x.pvalue;
}

void neg(int* i) // uses a pointer to perform an action that changes the value of the parameter passed
{
	*i = -*i;
}

double dfA(double d) // default parameters
{
	return d;
}

template <class X> void swapargs(X& a, X& b)
{
	X temp;

	temp = a;
	a = b;
	b = temp;
}

int swap_byte::swap() { // initializing a union function
	return u; // output the union's shared variable
}

// A simple input manipulator.
istream& getpass(istream& stream)
{
	cout << '\a';  // sound bell
	cout << "Enter password: ";

	return stream;
}

// use const cast to cast away const and allow editing
void sqrval(const int* val) // here val is a const variable, theroretically it should not be able to change
{
	int* p;

	// cast away const-ness.
	p = const_cast<int*> (val); // p is now val but without const
	*p = *val * *val; // now, modify object val through p
}

void my_Thandler() { // using abort function
	cout << "Inside new terminate handler\n";
	abort(); // terminate try catch process
}

// a function to show how static variables work in functions
int series(void)
{
	static int series_num;
	series_num = series_num + 23; // static variable series_num will keep adding and not return to 0
	return series_num;
}