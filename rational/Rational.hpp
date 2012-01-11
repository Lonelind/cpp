#include "Rational.h"

unsigned Rational::numerator() const { return n; }
unsigned Rational::denominator() const { return d; }

void Rational::set_numerator(unsigned num) { n = num; }

void Rational::set_denominator(unsigned den) { d = den; }

bool Rational::sign() const { return s; }

void Rational::set_sign(bool es) { s = es; }

void Rational::revert() { 
    s = n != 0 ? !s : true; 
}

Rational& Rational::invert() {
    unsigned t = n;
    n = d;
    d = t;
    return *this;
}

Rational& Rational::reduce() {
    unsigned g = gcd (n, d);  
    if (g != 1) {
        n /= g;
        d /= g;
    }
    return *this;
}

Rational::Rational() {
    n = 0;
    d = 1;
    s = true;
}

Rational::Rational(unsigned num, unsigned den) {
    n = num;
    d = den;
    s = true;
    reduce();
}

Rational::Rational(unsigned num, unsigned den, bool sign) {
    n = num;
    d = den;
    s = num != 0 ? sign : true;
    reduce();
}

Rational::Rational(int num, int den) {
    n = abs(num);
    d = abs(den);
    s = common_sign(num,den);
    reduce();
}

Rational::Rational(unsigned num) {
    n = num;
    d = 1;
    s = true;
} 

Rational::Rational(int num) {
    n = abs(num);
    d = 1;
    s = num < 0 ? false : true;
} 

Rational::Rational(const Rational& r) {
    n = r.numerator();
    d = r.denominator();
    s = r.sign();
}

Rational& Rational::operator= (const Rational& r) {
    n = r.numerator();
    d = r.denominator();
    s = r.sign();
    return *this;
} 

Rational& Rational::operator+= (const Rational& r) {
    unsigned en;
    bool es;
    if (s == r.sign()) {
        en = n * r.denominator() + r.numerator() * d;
        es = s;
    } else {
        en = abs(n * r.denominator()) >= abs(r.numerator() * d) ?
                n * r.denominator() - r.numerator() * d :
                r.numerator() * d - n * r.denominator();
        if (s) {
            es = abs(n * r.denominator()) >= abs(r.numerator() * d) ? true : false;
        } else {
            es = abs(n * r.denominator()) >= abs(r.numerator() * d) ? false : true;            
        }
    } 
    unsigned ed = d * r.denominator();
    n = en;
    d = ed;
    s = es;
    return reduce();
} 

Rational& Rational::operator-= (const Rational& r) {
    Rational t = r;
    t.revert();
    unsigned en;
    bool es;
    if (s == t.sign()) {
        en = n * t.denominator() + t.numerator() * d;
        es = s;
    } else {
        en = abs(n * t.denominator()) >= abs(t.numerator() * d) ?
                n * t.denominator() - t.numerator() * d :
                t.numerator() * d - n * t.denominator();
        if (s) {
            es = abs(n * t.denominator()) >= abs(t.numerator() * d) ? true : false;
        } else {
            es = abs(n * t.denominator()) >= abs(t.numerator() * d) ? false : true;            
        }
    } 
    unsigned ed = d * t.denominator();
    n = en;
    d = ed;
    s = es;
    return reduce();
} 

Rational& Rational::operator*= (const Rational& r) {
    n = n * r.numerator();
    d = d * r.denominator();
    s = s == r.sign() ? true : false;
    return reduce();
}

Rational& Rational::operator/= (const Rational& r) {
    Rational t = r;
    t.invert();
    n = n * t.numerator();
    d = d * t.denominator();
    s = s == t.sign() ? true : false;
    return reduce();   
}

Rational& Rational::operator++() {
    unsigned en;
    bool es;
    if (!s) {
        en = n < d ? d - n : n - d;
        es = n < d ? true : false;
    } else {
        en = n + d;
        es = true;        
    }
    n = en;
    s = es;
    return reduce();
}

Rational Rational::operator++(int) {
    unsigned en;
    bool es;
    if (!s) {
        en = n < d ? d - n : n - d;
        es = n < d ? true : false;
    } else {
        en = n + d;
        es = true;        
    }
    Rational t(en, d, es);
    return t.reduce();    
}

Rational& Rational::operator--() {
    unsigned en;
    bool es;
    if (s) {
        en = n < d ? d - n : n - d;
        es = n < d ? false : true;
    } else {
        en = n + d;
        es = false;        
    }
    n = en;
    s = es;
    return reduce();    
}

Rational Rational::operator--(int) {
    unsigned en;
    bool es;
    if (s) {
        en = n < d ? d - n : n - d;
        es = n < d ? false : true;
    } else {
        en = n + d;
        es = false;        
    }
    Rational t(en, d, es);
    return t.reduce();   
}

Rational::operator double () {
    double t = double(n) / double(d);
    if (!s) t *= -1;
    return t;
}

unsigned abs(int a) {
    return a < 0 ? -a : a;
}

bool common_sign(int a, int b) {
    if (((a < 0) && (b < 0)) || ((a >= 0) && ( b >= 0))) return true;
    else return false;
}

unsigned gcd(unsigned a, unsigned b) {
    while (a != 0 && b != 0) {
        if (a >= b) a = a % b;
        else b = b % a;
    }
    return a + b;
}

Rational operator+ (Rational& a, Rational& b) {
    unsigned en;
    bool es;
    if (a.sign() == b.sign()) {
        en = a.numerator() * b.denominator() + b.numerator() * a.denominator();
        es = a.sign();
    } else {
        en = abs(a.numerator() * b.denominator()) >= abs(b.numerator() * a.denominator()) ?
                a.numerator() * b.denominator() - b.numerator() * a.denominator() :
                b.numerator() * a.denominator() - a.numerator() * b.denominator();
        if (a.sign()) {
            es = abs(a.numerator() * b.denominator()) >= abs(b.numerator() * a.denominator()) ? true : false;
        } else {
            es = abs(a.numerator() * b.denominator()) >= abs(b.numerator() * a.denominator()) ? false : true;            
        }
    } 
    unsigned ed = a.denominator() * b.denominator();
    Rational r (en, ed, es);
    return r.reduce();
}

Rational operator- (Rational& a, Rational& b) {
    b.revert();
    unsigned en;
    bool es;
    if (a.sign() == b.sign()) {
        en = a.numerator() * b.denominator() + b.numerator() * a.denominator();
        es = a.sign();
    } else {
        en = abs(a.numerator() * b.denominator()) >= abs(b.numerator() * a.denominator()) ?
                a.numerator() * b.denominator() - b.numerator() * a.denominator() :
                b.numerator() * a.denominator() - a.numerator() * b.denominator();
        if (a.sign()) {
            es = abs(a.numerator() * b.denominator()) >= abs(b.numerator() * a.denominator()) ? true : false;
        } else {
            es = abs(a.numerator() * b.denominator()) >= abs(b.numerator() * a.denominator()) ? false : true;            
        }
    } 
    unsigned ed = a.denominator() * b.denominator();
    Rational r(en, ed, es);
    return r.reduce();
}
 
Rational operator* (Rational& a, Rational& b) {
    Rational r(a.numerator() * b.numerator(), a.denominator() * b.denominator(), a.sign() == b.sign() ? true : false);
    return r.reduce();
}

Rational operator/ (Rational& a, Rational& b) {
    b.invert();
    Rational r(a.numerator() * b.numerator(), a.denominator() * b.denominator(), a.sign() == b.sign() ? true : false);
    return r.reduce();
}

bool operator== (const Rational& a, const Rational& b) {
    if ((a.numerator() == b.numerator()) && 
        (a.denominator() == b.denominator()) && 
        (a.sign() == b.sign())) return true;
    else return false;
}

bool operator!= (const Rational& a, const Rational& b) {
    if ((a.numerator() == b.numerator()) && 
        (a.denominator() == b.denominator()) && 
        (a.sign() == b.sign())) return false;
    else return true;
}

bool operator<= (const Rational& a, const Rational& b) {
    if (a == b) return true;
    else {
        unsigned an = a.numerator();
        unsigned ad = a.denominator();
        unsigned as = a.sign();
        unsigned bn = b.numerator();
        unsigned bd = b.denominator();
        unsigned bs = b.sign();
        if (as != bs) return as ? false : true;
        else {
            an *= bd;
            bn *= ad;
            return an < bn ? true : false;
        }
    }
}

bool operator>= (const Rational& a, const Rational& b) {
    if (a == b) return true;
    else {
        unsigned an = a.numerator();
        unsigned ad = a.denominator();
        unsigned as = a.sign();
        unsigned bn = b.numerator();
        unsigned bd = b.denominator();
        unsigned bs = b.sign();
        if (as != bs) return as ? true : false;
        else {
            an *= bd;
            bn *= ad;
            return an < bn ? false : true;
        }
    }    
}

bool operator<  (const Rational& a, const Rational& b) {
    if (a == b) return false;
    else {
        unsigned an = a.numerator();
        unsigned ad = a.denominator();
        unsigned as = a.sign();
        unsigned bn = b.numerator();
        unsigned bd = b.denominator();
        unsigned bs = b.sign();
        if (as != bs) return as ? false : true;
        else {
            an *= bd;
            bn *= ad;
            return an < bn ? true : false;
        }
    }
}

bool operator>  (const Rational& a, const Rational& b) {
    if (a == b) return false;
    else {
        unsigned an = a.numerator();
        unsigned ad = a.denominator();
        unsigned as = a.sign();
        unsigned bn = b.numerator();
        unsigned bd = b.denominator();
        unsigned bs = b.sign();
        if (as != bs) return as ? true : false;
        else {
            an *= bd;
            bn *= ad;
            return an < bn ? false : true;
        }
    }   
}

std::ostream& operator<<(std::ostream &s, const Rational &d) {
    if (d.denominator() != 1) {
        if (d.sign())
            s << d.numerator() << "/" << d.denominator();
        else
            s << "-" << d.numerator() << "/" << d.denominator();
    } else {
        if (d.sign())
            s << d.numerator();
        else
            s << "-" << d.numerator();
    }
    return s;
}