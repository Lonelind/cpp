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
	virtual void operator() (T* d) const { cout << "object deleted" << endl; }
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



// SCOPED POINTER
template <class T> 
class scoped_ptr {
private:
	explicit scoped_ptr(const scoped_ptr <T>& p) {}
	scoped_ptr <T>& operator = (const scoped_ptr <T>& p) const {}
	T* ptr;
	deleter <T> del;

public:
    explicit scoped_ptr(T* p = 0) { ptr = p; }
    explicit scoped_ptr(T* p, const deleter <T>& d) { ptr = p; del = d; }
    ~scoped_ptr() {
    	if (!isNull())
    		del(ptr);
    }

    T& operator *() const { return *ptr; }
    T* operator ->() const { return ptr; }
    T* pointer() const { return ptr; }
     
	bool isNull() const { return ptr == 0; }
};

// AUTO POINTER
template <class T> 
class auto_ptr {
private:
	T* ptr;
	deleter <T> del;

public:
    explicit auto_ptr(T* p = 0) { ptr = p; }
    explicit auto_ptr(T* p, const deleter <T>& d) { ptr = p; del = d; }
    ~auto_ptr() {
    	if (!isNull())
    		del(ptr);
    }
	auto_ptr(auto_ptr <T>& p) {
		ptr = p.pointer();
  		p.ptr = 0; 
	}

	auto_ptr <T>& operator = (auto_ptr <T>& p) const {
		if (this != &p) {
		    if (!isNull()) {
		      	del(ptr);
		    }
		    ptr = p.pointer();
		    p.ptr = 0;    
  		}
  		return *this;
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

	// SCOPED POINTER
	cout << "SCOPED_PTR: " << endl;

	scoped_ptr<int> arr(arrrr, arrdeleter<int>());
	scoped_ptr<int> array(marrr, mfree<int>());
	cout << "Array created with 'new': ";
	for (int i = 0; i < 14; i++) 
		cout << arr.pointer()[i] << " ";
	cout << "DONE" << endl;

	cout << "Array created with 'malloc': ";
	for (int i = 0; i < 14; i++) 
		cout << array.pointer()[i] << " ";
	cout << "DONE" << endl << endl;

	cout << "Objects of class 'object' created with 'new' in loop of 3: " << endl;
	for (int i = 0; i < 3; i++) {
		object* t = new object(i);
		scoped_ptr<object> tre(t, objdeleter<object>());
		cout << "Pointer object address: " << &tre << " -> " << tre.pointer()->x << " ";
	}
	cout << endl;

	// AUTO POINTER
	cout << "AUTO_PTR: " << endl;

	auto_ptr<int> aarr(arrrr, arrdeleter<int>());
	auto_ptr<int> aarray(marrr, mfree<int>());
	cout << "Array created with 'new': ";
	for (int i = 0; i < 14; i++) 
		cout << aarr.pointer()[i] << " ";
	cout << "points at address " << aarr.pointer() << endl;

	cout << "Array created with 'malloc': ";
	for (int i = 0; i < 14; i++) 
		cout << aarray.pointer()[i] << " ";
	cout << "points at address " << aarray.pointer() << endl << endl;

	auto_ptr<int> copy = aarr;
	cout << "Copy of pointer to first array: ";
	for (int i = 0; i < 14; i++) 
		cout << copy.pointer()[i] << " ";
	cout << "points at address " << copy.pointer() << endl;
	cout << "Old pointer points to address " << aarr.pointer() << endl << endl;

	cout << "Objects of class 'object' created with 'new' in loop of 3: " << endl;
	for (int i = 0; i < 3; i++) {
		object* t = new object(i);
		auto_ptr<object> tre(t, objdeleter<object>());
		cout << "Pointer object address: " << &tre << " -> " << tre.pointer()->x << " ";
	}
	cout << endl;
	return 0;
}