#pragma once
#include "MatrixCore.h"

class Vector : public MatrixCore {
public:

	static Vector myVectorExampleA();

	// Nie zainicjowana
	Vector(size_t N);
	// Zainicjowana przy pomocy value
	Vector(size_t N, double value); // Kopiowanie
	Vector(const Vector& matrix);
	// Przenosz¹cy
	Vector(Vector&& matrix);

	double& operator[](size_t index);
	const double& operator[](size_t index) const;

	void print() const;

	double norm() const;
};

