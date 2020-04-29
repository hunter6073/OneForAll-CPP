// this script contains a demonstration of utility usage such as <vector>, <string> and <algorithms>

# include <iostream> // this is the library for c++
# include <vector> // use vector utility
# include <list> // use list utility
# include <map> // use a map(key value pairs)
# include <algorithm> // use utility algorithms
# include <functional> // use built in function objects
# include <cstring> // using strings in c++
# include "util.h" // utility library to format output

using namespace std;

void ShowVectors(); // show the common usage of vectors
void ShowLists(); // show the common usage of lists
void ShowMaps(); // show the common usage of maps
void ShowAlgorithms(); // show the common usage of algorithm library and built in function objects
void ShowStrings(); // show the common usage of string library

// main function
void ShowUtility() {

	cout << "show vector related usage:" << end;
	ShowVectors(); // show the common usage of vectors
	cout << endl;
	cout << "show list related usage:" << end;
	ShowLists(); // show the common usage of lists
	cout << endl;
	cout << "show map related usage:" << end;
	ShowMaps(); // show the common usage of maps
	cout << endl;
	cout << "show algorithms related usage:" << end;
	ShowAlgorithms(); // show the common usage of algorithm library and built in function objects
	cout << endl;
	cout << "show strings related usage:" << end;
	ShowStrings();// show the common usage of string library
	cout << endl;
}

/************************************** function declarations ************************************/

// utility function to ouptut a vector
template<class T> void printVector(string s, vector<T> v)
{
	cout << s << endl;
	// use the vector's size to traverse the vector
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << end;
}

// utility function to ouptut a list
template<class T> void printList(string s, list<T> l)
{
	cout << s << endl;
	// use the list's iterator to traverse the list
	auto p = l.begin();
	while (p != l.end()) {
		cout << *p << " ";
		p++;
	}
	cout << end;
}

// customized bool function for counter_if testing
bool isA(char x)
{
	if (x == 'A')
	{
		return true;
	}
	return false;
}

// custom comparing function for sort(vector1, vector2)
bool compareInterval(int i1, int i2)
{
	return (i1 > i2); // in decreasing order
}

void ShowVectors() {

	// Note: using vectors offers random access
	vector<int> v(10); // create a vector of length 10, these 10 items in the vector are defined as 0'
	printVector("[UtilLib01] the vector initialized is:", v);

	for (int i = 0; i < 10; i++) { v[i] = i; } // assign values to each element of the vector
	printVector("[UtilLib02] the vector after assigning is:", v);

	vector<int> sub(v.begin() + 1, v.begin() + 4); // getting a sub vector from the 2nd item to the 4th item
	printVector("[UtilLib03] the sub vector after slicing is:", sub);

	reverse(sub.begin(), sub.end()); // reverse a list
	printVector("[UtilLib04] the sub vector after reversing is:", sub);

	v.push_back(13);// append the value 13 as an item to the vector's tail

	vector<int>::iterator p; // create an iterator for the vector

	p = v.begin() + 2; // point the iterator to the 3rd element

	// insert 10 0s into v starting from the 3rd element
	v.insert(p, 10, 0); // if only insert one item, do v.insert(p,0), this by default inserts only one item
	printVector("[UtilLib05] the vector after inserting the 0s is:", v);

	// traverse the vector by using the pointer iterator
	p = v.begin(); // point the iterator pointer to the beginning of the vector
	while (p != v.end()) {
		*p += 1; // change the contents of the vector using iterator pointer
		p++; // move the pointer iterator forward
	}
	printVector("[UtilLib06] the vector after adding 1 to each item is:", v);

	v.erase(v.begin(), v.begin() + 4); // remove the first 4 elements
	printVector("[UtilLib07] the vector after removing the first 4 items is:", v);

	vector<int> v2(10); // create a new vector filled with 0s

	v.insert(v.end(), v2.begin(), v2.end());// Insert v2 into the end of v
	printVector("[UtilLib08] after appending v2 to v, v is now:", v);

	sort(v.begin(), v.end()); // sort a vector
	printVector("[UtilLib09] after sorting v, v is now:", v);

	sort(v.begin(), v.end(), compareInterval); // sort a vector using custom compare function
	printVector("[UtilLib10] after sorting v using custom comparing function, v is now:", v);
}


void ShowLists() {

	// using a list only allows sequential access, cannot do random access

	list<int> lst({ 1,21,33,4,15 }); // create a list with 10 items
	printList("[UtilLib11] the initial list is:", lst);

	for (int i = 0; i < 5; i++) {
		if (i % 2 == 0)
		{
			lst.push_back(i); // push_back is append to end, push_front is insert from beginning
		}
		else
		{
			lst.push_front(i); // push_front is insert from beginning
		}
	}
	printList("[UtilLib12] the list after pushing is:", lst);

	// sort the list
	lst.sort(); // sort intakes a function that compares two object, look this up online
	printList("[UtilLib13] the sorted list is(from small to large):", lst);

	reverse(lst.begin(), lst.end()); // reverse a list
	printList("[UtilLib14] the reverse sorted list is(from large to small):", lst);

	list<int> lst2({ 1,24,2 });
	lst2.sort();
	lst.sort();
	lst.merge(lst2); // merge lst2 with lst1, both lsts must be sorted in order for this to work
	printList("[UtilLib15] the merged list is:", lst);

	lst.pop_back(); // pop an item at the end of the list
	printList("[UtilLib16] the list after popping back is:", lst);
	lst.pop_front(); // pop an item at the front of the list
	printList("[UtilLib17] the list after popping front is:", lst);


}

void ShowMaps() {
	map<char, int> m;

	// put pairs into map
	for (int i = 0; i < 26; i++) {
		m.insert(pair<char, int>('A' + i, 65 + i));
	}

	char ch = 'A';

	map<char, int>::iterator pm;

	// find value given key
	cout << "[UtilLib18] finding the value for ch = 'A' in the map:" << endl;
	pm = m.find(ch);
	if (pm != m.end())
	{
		cout << "Its ASCII value is  " << pm->second << end; // use -> second to get the value of the key in the map
	}
	else
	{
		cout << "Key not in map.";
	}
}


void ShowAlgorithms() {
	vector<char> vc({ 'A','B','C' });

	// count(start pointer, end pointer, look for object with this value)
	int counter = count(vc.begin(), vc.end(), 'A'); // use count function from <algorithm>
	cout << "[UtilLib19] the count for 'A' is :" << counter << end;

	// the last parameter in countif is a custom function that returns a true or false value 
	// you can use custom functions to count your values
	counter = count_if(vc.begin(), vc.end(), isA);
	cout << "[UtilLib20] the count for 'A' is :" << counter << end;



	list<double> dubs({ 1,2,3,4,5 });
	printList("[UtilLib21] Original contents of dubs:", dubs);
	list<double>::iterator pd = dubs.begin();

	// use the negate function object with transform function to turn every item in the list into negative
	transform(dubs.begin(), dubs.end(), // use transform function from <algorithm>
		dubs.begin(),
		negate<double>()); // use the built in function negate from <functional>, these functions can only happen in a transform
	printList("[UtilLib22] Negated contents of dubs:", dubs);

}

void ShowStrings() {
	// strings are containers
	string str1("Strings handling is easy");

	// most common usage
	string str2 = " in c++"; // defining a string
	str1 += str2; // merging two strings

	cout << "[UtilLib23] ";
	// use size() to traverse a string
	for (int i = 0; i < str1.size(); i++)
		cout << str1[i];
	cout << end;

	// use iterator
	string::iterator p;
	p = str1.begin();
	cout << "[UtilLib24] ";
	while (p != str1.end())
		cout << *p++;
	cout << end;

	// use the count() algorithm
	int counter = count(str1.begin(), str1.end(), 'i');
	cout << "[UtilLib25] There are " << counter << " i's in str1" << end;

	// use transform() to upper case the string
	transform(str1.begin(), str1.end(), str1.begin(),
		toupper);
	p = str1.begin();
	cout << "[UtilLib26] ";
	while (p != str1.end())
		cout << *p++;
	cout << end;

	// find and rfind for string 
	string s1 = "Quick of Mind, Strong of Body, Pure of Heart";
	string s2;

	int index = s1.find("Mind"); // use find() function to locate where the word occured
	if (index != string::npos) { // if there is indeed a return value
		cout << "[UtilLib27] Match found at " << index << endl;
		cout << "Remaining string is:\n";
		s2.assign(s1, index, s1.size()); // use assign function to locate the string from index to s1.size(), which is the end of s1
		cout << s2;
	}
	cout << end;

	// use rfind to find list "of", will return the last find result
	index = s1.rfind("of");
	if (index != string::npos) {
		cout << "[UtilLib28] Match found at " << index << endl;
		cout << "Remaining string is:\n";
		s2.assign(s1, index, s1.size());
		cout << end;
	}
}
