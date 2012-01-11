#include <iostream>

using namespace std;

template <class T> class array {
private:
	T *arr;
	size_t msize;

public:
	size_t size() const {
                return msize;
        }

	void resize(size_t esize) {
		T *earr = new T[esize];
		if (esize < msize) for (size_t i = 0; i < esize; i++) earr[i] = arr[i];
		else for (size_t i = 0; i < msize; i++) earr[i] = arr[i];
		msize = esize;
		arr = new T[esize];
		arr = earr;
	}

	T& operator [] (size_t i) {
		return arr[i];
	}

	inline T operator [] (size_t i) const {
		return arr[i];
	}

	void operator = (array b) {
		msize = b.size();
		arr = new int[b.size()];
		for (size_t i = 0; i < b.size(); i++) arr[i] = b[i];
	}

	T get (size_t index) {
		return arr[index];
	}

	void set (size_t index, T value) {
		if (index == msize) {
			resize(msize+1);
			arr [msize] = value;
		} 
		else if ((index >= 0) && (index < msize)) arr[index] = value;
		else if (index < 0) set (0, value);
		else if (index >= msize) set (msize - 1, value);
	}

	void push_back(T value) {
		resize(msize + 1);
		set(msize-1, value);
	}

	array() {
		msize = 0;
	}

	array(size_t esize) {
		msize = esize;
		arr = new T[esize];
	}

	array(const array &oth) {
		msize = oth.size();
		arr = new T[msize];
		for (size_t i = 0; i < msize; i++) {
			set(i,oth[i]);
		}
	}

	~array() {
		delete[] arr;
	}
	
};


int main () {
	array <int> a;
	array <float> b;
	cout << a.size() << endl;
	for (int i = 0; i < 10; i++) {
		a.push_back(i+1);
		cout << a[i] << " ";
	}
	cout << endl;
	a.resize(5);
	cout << a.size() << endl;
	for (int i = 0; i < a.size(); i++) {
		cout << a[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < 10; i++) {
		float t = i;
		b.push_back((t+1)*3332/1000);
		cout << b[i] << " ";
	}
	cout << endl;
	array <int> c = a;
	array <int> d(a);
	return 0;
}
