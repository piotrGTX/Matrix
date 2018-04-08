#pragma once
#include <iostream>
#include <string>


class Matrix {
public:

	static Matrix myMatrixExampleA();
	static Matrix myVectorExampleA();

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
	// Przenoszący
	Matrix(Matrix&& matrix);

	~Matrix();

	Matrix & operator=(const Matrix & matrix);
	Matrix & operator=(Matrix&& matrix);
	 
	double* const operator[](size_t index);
	const double* const operator[](size_t index) const;

	Matrix operator+(const Matrix& other) const;
	Matrix operator-(const Matrix& other) const;
	Matrix operator*(double value) const;
	Matrix operator*(const Matrix& other) const;

	void print() const;

	bool isSquared() const;
	bool isTriangularUpper() const;
	bool isTriangularLower() const;
	bool isVector() const;

	bool equalsSize(const Matrix& other) const;
	bool canBeMultiple(const Matrix& other) const;

	Matrix getTriangularUpper() const;
	Matrix getTriangularLower() const;
	Matrix getDiagnonal() const;

	Matrix podstawienieWPrzod(const Matrix & vector) const;
	Matrix metodaJacobiego(const Matrix& vector) const;
	Matrix metodaSeidla(const Matrix& vector) const;

	double norm() const;

	size_t getN() const;
	size_t getM() const;

private:

	size_t N, M;
	double ** arr;
};
