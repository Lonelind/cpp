#pragma once

#include <cstdlib>
#include <iostream>

template <class T>
class deleter 
{
public:
	virtual void operator () (T * d) const 
	{ 
		std::cout << " the pointer was deleted!" << std::endl; // signs that is called
	}
};

template <class T>
class mfree : public deleter <T> // works with malloc
{
public:
	virtual void operator () (T * d) const 
	{ 
		free(d); 
	}
};

template <class T>
class arrdeleter : public deleter <T> // works with new[]
{
public:	
	virtual void operator () (T * d) const 
	{ 
		delete[] d; 
	}	
};

template <class T>
class objdeleter : public deleter <T> // works with new
{
public:
	virtual void operator () (T * d) const 
	{ 
		delete d; 
	}
};