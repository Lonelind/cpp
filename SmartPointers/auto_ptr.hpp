#pragma once

#include "deleter.hpp"

template <class T> 
class auto_ptr 
{
private:
	T * ptr;
	deleter <T> del;

public:
    explicit auto_ptr (T * p = 0) 
    { 
	    ptr = p; 
	}
    
    explicit auto_ptr (T * p, const deleter <T> & d) 
    { 
	    ptr = p; 
	    del = d; 
	}
    
    ~auto_ptr() 
    {
    	if (!isNull())
    	{
    		std::cout << "At address " << this;    	
    		del(ptr);
    	}
    }

	auto_ptr(auto_ptr <T> & p) 
	{
		if (!isNull()) 
	    {
    		std::cout << "At address " << &p;    	
	      	del(ptr);
	    }
		ptr = p.pointer();
  		p.ptr = 0; 
	}

	auto_ptr <T> & operator = (auto_ptr <T> & p) const 
	{
		if (this != &p) 
		{
		    if (!isNull()) 
		    {
	    		std::cout << "At address " << this;    	
		      	del(ptr);
		    }
		    ptr = p.pointer();
		    p.ptr = 0;    
  		}
  		return *this;
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