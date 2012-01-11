#include <iostream>
#include <cstdlib>

using namespace std;

class object {
public:
	int x;
	
	object(int t = 0) { x = t; }	
};

// DELETERS
template <class T>
class deleter {
public:
	virtual void operator() (T* d) const { cout << " the pointer was deleted!" << endl; }
};

template <class T>
class mfree : public deleter <T> {
public:
	virtual void operator() (T* d) const { free(d); }
};

template <class T>
class arrdeleter : public deleter <T> {
public:	
	virtual void operator() (T* d) const { delete[] d; }	
};

template <class T>
class objdeleter : public deleter <T> {
public:
	virtual void operator() (T* d) const { delete d; }
};


// POINTER
template <class T> 
class scoped_ptr {
private:
	scoped_ptr(const scoped_ptr <T>& p);
	scoped_ptr <T>& operator = (const scoped_ptr <T>& p) const;
	T* ptr;
	deleter <T> del;

public:
    explicit scoped_ptr(T* p, const deleter <T>& d) : ptr (p), del (d) { }
    ~scoped_ptr() {
    	if (!isNull()) {
    		std::cout << "At address " << this;
    		del(ptr);
    	}
    }

    T& operator *() const { return *ptr; }
    T* operator ->() const { return ptr; }
    T* pointer() const { return ptr; }
     
	bool isNull() const { return ptr == 0; }
};

// MAIN
int main () {
	int* arrrr = new int[14];
	int* marrr;
	marrr = (int*) malloc(14);
	for (int i = 0; i < 14; i++) {
		arrrr[i] = i;
		marrr[i] = i + 1;
	}

	scoped_ptr <int> arr (arrrr, arrdeleter <int> ());
	scoped_ptr <int> array (marrr, mfree <int> ());

	cout << arr.pointer() << ": Array created with 'new': ";

	for (int i = 0; i < 14; i++) 
		cout << arr.pointer()[i] << " ";

	cout << "has an address " << &arr << endl;

	cout << array.pointer() << ": Array created with 'malloc': ";

	for (int i = 0; i < 14; i++) 
		cout << array.pointer()[i] << " ";

	cout << "has an address " << &array << endl;

	cout << "Objects of class 'object' created with 'new' in loop of 3: " << endl;

	for (int i = 0; i < 3; i++) 
	{
		object * t = new object (i);
		scoped_ptr <object> tre (t, objdeleter <object> ());
		cout << "Pointer object address: " << &tre << " -> " << tre.pointer()->x << endl;
	}

	cout << endl;

	return 0;
}