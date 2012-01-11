#include <iostream>
#include "scoped_ptr.hpp"
#include "auto_ptr.hpp"


// Sample object
class object {
public:
	int x;
	
	object(int t = 0) { x = t; }	
};

int main () 
{
	int * arrrr = new int[14];
	int * marrr;
	marrr = (int *) malloc (14);
	for (int i = 0; i < 14; i++) 
	{
		arrrr[i] = i;
		marrr[i] = i + 1;
	}

	// SCOPED POINTER
	std::cout << "SCOPED_PTR: " << std::endl;

	scoped_ptr <int> arr (arrrr, arrdeleter <int> ());
	scoped_ptr <int> array (marrr, mfree <int> ());

	std::cout << arr.pointer() << ": Array created with 'new': ";

	for (int i = 0; i < 14; i++) 
		std::cout << arr.pointer()[i] << " ";

	std::cout << "has an address " << &arr << std::endl;

	std::cout << array.pointer() << ": Array created with 'malloc': ";

	for (int i = 0; i < 14; i++) 
		std::cout << array.pointer()[i] << " ";

	std::cout << "has an address " << &array << std::endl;

	std::cout << "Objects of class 'object' created with 'new' in loop of 3: " << std::endl;

	for (int i = 0; i < 3; i++) 
	{
		object * t = new object (i);
		scoped_ptr <object> tre (t, objdeleter <object> ());
		std::cout << "Pointer object address: " << &tre << " -> " << tre.pointer()->x << std::endl;
	}

	std::cout << std::endl;

	// AUTO POINTER
	std::cout << "AUTO_PTR: " << std::endl;

	auto_ptr <int> aarr(arrrr, arrdeleter <int> ());
	auto_ptr <int> aarray(marrr, mfree <int> ());

	std::cout << aarr.pointer() << ": Array created with 'new': ";
	
	for (int i = 0; i < 14; i++) 
		std::cout << aarr.pointer()[i] << " ";
	
	std::cout << "has an address " << &aarr << std::endl;

	std::cout << aarray.pointer() << ": Array created with 'malloc': ";

	for (int i = 0; i < 14; i++) 
		std::cout << aarray.pointer()[i] << " ";
	
	std::cout << "has an address " << &aarray << std::endl << std::endl;

	auto_ptr <int> copy = aarr;
	
	std::cout << copy.pointer() << ": Copy of pointer to first array: ";
	
	for (int i = 0; i < 14; i++) 
		std::cout << copy.pointer()[i] << " ";
	
	std::cout << "has an address " << &copy << std::endl;
	std::cout << "Old pointer points to address " << aarr.pointer() << std::endl << std::endl;

	std::cout << "Objects of class 'object' created with 'new' in loop of 3: " << std::endl;
	
	for (int i = 0; i < 3; i++) 
	{
		object * t = new object(i);
		auto_ptr <object> tre(t, objdeleter <object> ());
		std::cout << "Pointer object address: " << &tre << " -> " << tre.pointer()->x << std::endl;
	}
	
	std::cout << std::endl;
	return 0;
}