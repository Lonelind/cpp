#pragma once

#include "deleter.hpp"

template <class T> 
class scoped_ptr 
{
private:
	scoped_ptr (const scoped_ptr <T> & p) throw (); // call not permitted

	scoped_ptr <T> & operator = (const scoped_ptr <T> & p) const throw (); // call not permitted

	T * ptr;
	deleter <T> del;

public:
	explicit scoped_ptr (T * p, const deleter <T> & d) : ptr (p), del (d) { }

	~scoped_ptr() 
	{
		if (!isNull())
		{
			std::cout << "At address " << this;
			del (ptr);
		}
	}

	T & operator * () const 
	{ 
		return *ptr; 
	}

	T * operator -> () const 
	{ 
		return ptr; 
	}

	T * pointer () const 
	{ 
		return ptr; 
	}
	 
	bool isNull () const 
	{ 
		return ptr == 0; 
	}
};