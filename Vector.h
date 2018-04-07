#pragma once
#include "Matrix.h"

class Vector : public Matrix
{
public:

	static Vector myVectorExampleA();

	// Nie zainicjowana
	Vector(size_t N);
	// Zainicjowana przy pomocy value
	Vector(size_t N, double value);
	// Zainicjowana przy pomocy elmentów
	Vector(size_t N, const double **new_arr);
	// Kopiowanie
	Vector(const Vector& matrix);
	// Przenosz¹cy
	Vector(Vector&& matrix);

	double& operator[](size_t index);
	const double& operator[](size_t index) const;

	// Matrix^(-1) * Vector = Vector 
	Vector podstawienieWPrzod(const Matrix & other) const;

	void print() const;

	double norm() const;
};

