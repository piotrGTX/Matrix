#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "Matrix.h"


using namespace std;

void Example(const size_t N) {

	Matrix a = Matrix::myMatrixExample(N);
	Matrix b = Matrix::myVectorExample(N);

	clock_t start, stop;

	cout << "N = " << N << endl;

	start = clock();
	Matrix result2 = a.metodaJacobiego(b);
	stop = clock() - start;
	cout << "Jacobi: " << stop / 1000.0 << endl;
	//result2.print();
	//cout << "------" << endl;
	start = clock();
	Matrix result3 = a.metodaSeidla(b);
	stop = clock() - start;
	cout << "Seidla: " << stop / 1000.0 << endl;
	//result3.print();
	//cout << "------" << endl;
	start = clock();
	Matrix result4 = a.faktoryzacjaLU(b);
	stop = clock() - start;
	cout << "LU: " << stop / 1000.0 << endl;

	ofstream out("Wyniki.txt");
	for (size_t i = 0; i < result2.getN(); i++) {
		out << result2[i][0] << '\t' << result3[i][0] << '\t' << result4[i][0] << endl;
	}
	out.close();

	cout << endl;
}

void ExampleB() {
	Matrix a = Matrix((size_t)3, (double) 0);
	Matrix b = Matrix((size_t)3, (size_t) 1);

	a[0][0] = 1;
	a[0][1] = 2;
	a[0][2] = 3;
	a[1][1] = 1;
	a[2][2] = 3;

	b[0][0] = 20;
	b[1][0] = 5;
	b[2][0] = 9;

	Matrix c = a.podstawienieWTyl(b);
	c.print();
	c = a.metodaJacobiego(b);
	c.print();
	c = a.metodaSeidla(b);
	c.print();
	c = a.faktoryzacjaLU(b);
	c.print();
}

int main() {

	try {
		for (size_t i = 500; i <= 5000; i += 500) {
			Example(i);
		}
		//ExampleB();
	}
	catch (string e) {
		cout << "Error: " << e << endl;
	}

	system("PAUSE");

	return 0;
}