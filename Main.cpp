#include <iostream>
#include <string>
#include "Matrix.h"

using namespace std;


void ExampleA() {
	Matrix A = Matrix::myMatrixExampleA();
	Matrix b = Matrix::myVectorExampleA();
}

int main() {

	ExampleA();

	system("PAUSE");

	return 0;
}