#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "Matrix.h"


using namespace std;

typedef Matrix(Matrix::*MetodaRozwiazywania)(const Matrix&) const;

clock_t statystykaMetody(const Matrix A, const Matrix b, MetodaRozwiazywania metoda, const string& nazwa) {
	clock_t start, stop;

	try {
		cout << "----" << endl;
		cout << nazwa << endl;
		start = clock();
		const Matrix result = (A.*metoda)(b);
		stop = clock() - start;
		cout << "Czas: " << stop << endl;
	}
	catch (string e) {
		cout << "Problem z " << nazwa << ": " << e << endl;
	}

	return stop;
}

void Example_B() {

	cout << "Zadanie B" << endl;

	const size_t N = 964; // 6 - przedostania cyfra indeksu, 4 ostatnia cyfra indeksu
	const Matrix A = Matrix::myMatrixExample(N, 5 + 6, -1, -1);
	const Matrix b = Matrix::myVectorExample(N);

	statystykaMetody(A, b, &Matrix::metodaJacobiego, "metoda Jacobiego");
	statystykaMetody(A, b, &Matrix::metodaSeidla, "metoda Gaussa-Seidla");
	cout << endl;
}

void Example_C() {

	cout << "Zadanie C" << endl;

	const size_t N = 964; // 6 - przedostania cyfra indeksu, 4 ostatnia cyfra indeksu
	const Matrix A = Matrix::myMatrixExample(N, 3, -1, -1); // Wynika z zadania
	const Matrix b = Matrix::myVectorExample(N);

	statystykaMetody(A, b, &Matrix::metodaJacobiego, "metoda Jacobiego");
	statystykaMetody(A, b, &Matrix::metodaSeidla, "metoda Gaussa-Seidla");
	statystykaMetody(A, b, &Matrix::faktoryzacjaLU, "faktoryzacja LU");
	cout << endl;
}

void Example_E() {

	cout << "Zadanie E" << endl;

	const size_t elements[] = { 100, 500, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000, 5500, 6000, 6500, 7000, 8000 };

	const clock_t time_limit = 60000;
	clock_t last_max_time = 0;
	ofstream file = ofstream("stat.txt");
	try {
		file << "N" << '\t' << "Czas Jacobiego" << '\t' << "Czas Gaussa-Seidla" << '\t' << "Czas LU" << endl;
		for (const size_t e : elements) {
			cout << endl << "------ Ilosc elementow: " << e << endl << endl;
			const Matrix A = Matrix::myMatrixExample(e, 5 + 6, -1, -1);
			const Matrix b = Matrix::myVectorExample(e);

			clock_t time_a = statystykaMetody(A, b, &Matrix::metodaJacobiego, "metoda Jacobiego");
			clock_t time_b = statystykaMetody(A, b, &Matrix::metodaSeidla, "metoda Gaussa-Seidla");
			clock_t time_c = 0;
			if (last_max_time <= time_limit) {
				time_c = statystykaMetody(A, b, &Matrix::faktoryzacjaLU, "faktoryzacja LU");
				if (time_c > last_max_time)
					last_max_time = time_c;
			}

			file << e << '\t' << time_a << '\t' << time_b << '\t' << time_c << endl;
		}
	}
	catch (string e) {
		cout << e << endl;
	}
	file.close();

	cout << endl;

}

void Example_A() {

	// Wyœwietli fragmengt macierzy A i wektora B

	const size_t N = 964; // 6 - przedostania cyfra indeksu, 4 ostatnia cyfra indeksu
	const Matrix A = Matrix::myMatrixExample(N, 5+6, -1, -1);
	const Matrix b = Matrix::myVectorExample(N);

	cout << endl;
	for (size_t i = 0; i < 10; i++) {
		cout << '\t';
		for (size_t y = 0; y < 10; y++) {
			cout << A[i][y] << '\t';
		}
		cout << "   " << b[i][0] << endl;
	}

	cout << endl << endl;
}

int main() {

	//Example_A();
	Example_B();
	//Example_C();
	//Example_E();

	system("PAUSE");

	return 0;
}