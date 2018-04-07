#pragma once
#include <iostream>

class Matrix {
public:

	static Matrix myMatrixExampleA();

	// Nie zainicjowana
	Matrix(size_t N, size_t M);
	Matrix(size_t N);
	// Zainicjowana przy pomocy value
	Matrix(size_t N, size_t M, double value);
	Matrix(size_t N, double value);
	// Zainicjowana jawnie podanymi elementami
	Matrix(size_t N, size_t M, const double **new_arr);
	Matrix(size_t N, const double **new_arr);
	// Kopiowanie
	Matrix(const Matrix& matrix);
	// Przenosz�cy
	Matrix(Matrix&& matrix);

	~Matrix();

	const size_t N, M;

	double* const operator[](size_t index);
	const double* const operator[](size_t index) const;

	Matrix operator+(const Matrix& other) const;
	Matrix operator-(const Matrix& other) const;
	Matrix operator*(double value) const;
	Matrix operator*(const Matrix& other) const;

	void print() const;

	bool isTriangularUpper() const;
	bool isTriangularLower() const;

	Matrix getTriangularUpper() const;
	Matrix getTriangularLower() const;
	Matrix getDiagnonal() const;

protected:

	double ** arr;
};
