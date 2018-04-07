#include "Vector.h"

Vector Vector::myVectorExampleA() {
	// 165664
	const size_t N = 9 * 6 * 4;
	Vector myVector = Vector(N);

	const size_t f = 5;
	for (size_t i = 0; i < N; i++) {
		myVector[i] = sin(i*(f + 1));
	}

	return myVector;
}

Vector::Vector(size_t N) : Matrix(N, (size_t)1) {
	// Nop
}

Vector::Vector(size_t N, double value) : Matrix(N, (size_t)1, value) {
	// Nop
}

Vector::Vector(size_t N, const double ** new_arr) : Matrix(N, (size_t)1, (const double**)new_arr) {
	// Nop
}

Vector::Vector(const Vector & vector) : Vector(vector.N, (const double**)vector.arr) {
	// Nop
}

Vector::Vector(Vector && vector) : Vector(vector.N) {
	std::swap(this->arr, vector.arr);
}

double& Vector::operator[](size_t index) {
	return this->arr[index][0];
}

const double& Vector::operator[](size_t index) const {
	return this->arr[index][0];
}

Vector Vector::podstawienieWPrzod(const Matrix & other) const {

	if (other.N != other.M) {
		throw "Bad size !";
	}
	else if (!other.isTriangularLower()) {
		throw "Bad Matrix !";
	}

	Vector result = Vector(*this);

	for (size_t i = 0; i < other.N; i++) {
		double sum = 0;
		for (size_t j = 0; j < i; j++) {
			sum += (result[j] * other[i][j]);
		}
		result[i] = (result[i] - sum) / other[i][i];
	}

	return result;
}

void Vector::print() const {
	for (size_t i = 0; i < N; i++) {
		std::cout << (*this)[i] << ' ';
	}
	std::cout << std::endl;
}

double Vector::norm() const {
	double result = 0;
	for (size_t i = 0; i < N; i++) {
		result += pow((*this)[i], 2);
	}
	return sqrt(result);
}

