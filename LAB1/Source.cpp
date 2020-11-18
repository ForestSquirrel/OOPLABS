#include "Matrix.h"
#include <iostream>
using namespace std;
int main() {
	Matrix matr(3);
	Matrix ones(3);
	ones.ones();
	float elem[9] = { 1,2,3,4,1,6,7,8,1 };
	matr.fill(elem, 9);
	cout << "matr" << endl;
	matr.printToConsole();
	cout << "ones" << endl;
	ones.printToConsole();
	Matrix sum = matr + ones;
	cout << "sum" << endl;
	sum.printToConsole();
	Matrix subtr = matr - ones;
	cout << "subtr" << endl;
	subtr.printToConsole();
	Matrix multy = matr * ones;
	cout << "multy" << endl;
	multy.printToConsole();
	Matrix multyScalar = matr * 5;
	cout << "multyScalar" << endl;
	multyScalar.printToConsole();
	if (matr == matr)
		cout << "equal" << endl;
	if (matr == ones)
		cout << "equal" << endl;
	else
		cout << "not equal" << endl;
	float det = matr.determinant();
	return 0;
}