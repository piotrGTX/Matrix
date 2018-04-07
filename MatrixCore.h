#pragma once
#include <iostream>

class MatrixCore {
public:

	// Nie zainicjowana
	MatrixCore(size_t N, size_t M);
	MatrixCore(size_t N);
	// Zainicjowana przy pomocy value
	MatrixCore(size_t N, size_t M, double value);
	MatrixCore(size_t N, double value);
	// Zainicjowana jawnie podanymi elementami
	MatrixCore(size_t N, size_t M, const double **new_arr);
	MatrixCore(size_t N, const double **new_arr);
	// Kopiowanie
	MatrixCore(const MatrixCore& MatrixCore);
	// Przenosz¹cy
	MatrixCore(MatrixCore&& MatrixCore);

	~MatrixCore();

	const size_t N, M;

	double* const operator[](size_t index);
	const double* const operator[](size_t index) const;

	MatrixCore operator+(const MatrixCore& other) const;
	MatrixCore operator-(const MatrixCore& other) const;
	MatrixCore operator*(double value) const;
	MatrixCore operator*(const MatrixCore& other) const;

	void print() const;

protected:

	double ** arr;
};

