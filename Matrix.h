#pragma once
#include "MatrixCore.h"
#include "Vector.h"

class Matrix : public MatrixCore {

public:

	static Matrix myMatrixExampleA();

	// Nie zainicjowana
	Matrix(size_t N, size_t M);
	Matrix(size_t N);
	// Zainicjowana przy pomocy value
	Matrix(size_t N, size_t M, double value);
	Matrix(size_t N, double value);
	// Rzutowanie
	Matrix(const MatrixCore& matrix);
	Matrix(MatrixCore&& matrix);

	bool isSquared() const;
	bool isTriangularUpper() const;
	bool isTriangularLower() const;

	Matrix getTriangularUpper() const;
	Matrix getTriangularLower() const;
	Matrix getDiagnonal() const;

	Vector podstawienieWPrzod(const Vector & other) const;
	Vector factoryzacjaJacobbiego(const Vector & other, double epsilon) const;

};

