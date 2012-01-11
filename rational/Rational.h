#pragma once
#include <ostream>

class Rational {
private:
    unsigned n;
    unsigned d;
    bool s;

public:
    // getters, setters & modificators;
    unsigned numerator() const;
    unsigned denominator() const;

    void set_numerator(unsigned num);
    void set_denominator(unsigned den);

    bool sign() const; // returns current sign
    void set_sign(bool es);

    void revert(); // reverts sign
    Rational& invert(); // inverts fraction

    // additional methods
    Rational& reduce();

    // constructors & destructors
    Rational();
    Rational(unsigned num, unsigned den);
    Rational(unsigned num, unsigned den, bool sign);    
    Rational(int num, int den);
    Rational(unsigned num);
    Rational(int num); 
    Rational(const Rational& r);

    // operators
    Rational& operator= (const Rational& r); 
    Rational& operator+= (const Rational& r); 
    Rational& operator-= (const Rational& r); 
    Rational& operator*= (const Rational& r); 
    Rational& operator/= (const Rational& r); 
    Rational& operator++();
    Rational operator++(int);
    Rational& operator--();
    Rational operator--(int);

    operator double ();
};

unsigned abs(int a);
bool common_sign(int a, int b);
unsigned gcd(unsigned a, unsigned b);    

Rational operator+ (const Rational& a, const Rational& b);
Rational operator- (const Rational& a, const Rational& b);
Rational operator* (const Rational& a, const Rational& b);
Rational operator/ (const Rational& a, const Rational& b);

bool operator== (const Rational& a, const Rational& b);
bool operator!= (const Rational& a, const Rational& b);
bool operator<= (const Rational& a, const Rational& b);
bool operator>= (const Rational& a, const Rational& b);
bool operator<  (const Rational& a, const Rational& b);
bool operator>  (const Rational& a, const Rational& b);

std::ostream& operator<<(std::ostream &s, const Rational &d);