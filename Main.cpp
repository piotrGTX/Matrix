#include <iostream>
#include <fstream>
#include <string>
#include "Matrix.h"


using namespace std;

void ExampleA() {
	Matrix a = Matrix::myMatrixExampleA();
	Matrix b = Matrix::myVectorExampleA();

	/*
	Matrix a(10, (double) 0);
	Matrix b(10, (size_t) 1);

	for (size_t i = 0; i < 10; i++) {
		a[i][i] = rand() % 10 + 1;
		for (size_t j = 0; j < 10; j++) {
			if (i != j) 
				a[i][j] = rand() % 2;
		}
		b[i][0] = 10 * (i + 1);
	}

	a.print();
	b.print();
	*/

	Matrix result2 = a.metodaJacobiego(b);
	result2.print();
	cout << "------" << endl;
	Matrix result3 = a.metodaSeidla(b);
	result3.print();
	cout << "------" << endl;

	ofstream out("Jacobi.txt");
	for (size_t i = 0; i < result2.getN(); i++) {
		out << result2[i][0] << endl;
	}
	out.close();

	out = ofstream("Seidle.txt");
	for (size_t i = 0; i < result3.getN(); i++) {
		out << result3[i][0] << endl;
	}
	out.close();


}

int main() {

	try {
		ExampleA();
	}
	catch (string e) {
		cout << "Error: " << e << endl;
	}

	system("PAUSE");

	return 0;
}