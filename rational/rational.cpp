#include <iostream>
#include "Rational.hpp"

using namespace std;

int main() {
	Rational A;
	Rational B(1,3);
	cout << A << " " << B << endl;
	Rational C = A * B;
	cout << C << endl;
	A += C;
	A -= B;
	cout << A << endl;
	++B;
	Rational P = B - A;
	cout << B << endl << P << endl;
	++A;
	cout << A << endl << B << endl;
	cout << double(P) << endl;
	Rational T(-2);
	cout << T << endl;
	Rational Q(12, 8, false);
	cout << Q << endl;
	return 0;
}