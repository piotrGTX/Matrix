#include <iostream>
#include "Matrix.h"

using namespace std;

void ExampleA() {
	Matrix A = Matrix::myMatrixExampleA();
	Vector b = Vector::myVectorExampleA();
}

int main() {

	ExampleA();

	Matrix A(5, (double) 2);
	A[0][0] = A[4][4] = A[0][4] = A[4][0] = 7;

	Matrix B = A.getTriangularLower();
	Matrix C = A.getDiagnonal();
	Matrix D = A.getTriangularUpper();

	A.print();
	B.print();
	C.print();
	(C+D).print();

	system("PAUSE");

	return 0;
}