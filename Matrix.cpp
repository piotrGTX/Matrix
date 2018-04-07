#include "Matrix.h"

Matrix Matrix::myMatrixExampleA() {
	// 165664
	const size_t N = 9 * 6 * 4;
	Matrix myMatrixCore = Matrix(N, (double)0);

	double a1 = 5 + 6;
	double a2 = (-1);
	double a3 = (-1);

	for (size_t i = 0; i < N; i++) {
		myMatrixCore[i][i] = a1;
		if (i + 1 < N) {
			myMatrixCore[i][i + 1] = a2;
		}
		if (i + 2 < N) {
			myMatrixCore[i][i + 2] = a3;
		}
		if (i > 0) {
			myMatrixCore[i][i - 1] = a2;
		}
		if (i > 1) {
			myMatrixCore[i][i - 2] = a3;
		}
	}

	return myMatrixCore;
}

Matrix::Matrix(size_t N, size_t M) : MatrixCore(N, M) {}
Matrix::Matrix(size_t N) : MatrixCore(N) {}
Matrix::Matrix(size_t N, size_t M, double value) : MatrixCore(N, M, value) {}
Matrix::Matrix(size_t N, double value) : MatrixCore(N, value) {}
Matrix::Matrix(const MatrixCore & matrix) : MatrixCore(matrix) {}
Matrix::Matrix(MatrixCore && matrix) : MatrixCore(matrix) {}

bool Matrix::isTriangularUpper() const {
	if (!this->isSquared()) {
		throw "Bad size !";
	}

	for (size_t i = 1; i < N; i++) {
		for (size_t j = 0; j < i; j++) {
			if (this->arr[i][j] != 0) {
				return false;
			}
		}
	}
	return true;
}

bool Matrix::isTriangularLower() const {
	if (!this->isSquared()) {
		throw "Bad size !";
	}

	for (size_t i = 0; i < (N - 1); i++) {
		for (size_t j = (i + 1); j < N; j++) {
			if (this->arr[i][j] != 0) {
				return false;
			}
		}
	}
	return true;
}

Matrix Matrix::getTriangularUpper() const {
	if (!this->isSquared()) {
		throw "Bad size !";
	}

	Matrix result = Matrix(*this);

	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j <= i; j++) {
			result[i][j] = 0;
		}
	}
	return result;
}

Matrix Matrix::getTriangularLower() const {
	if (!this->isSquared()) {
		throw "Bad size !";
	}

	Matrix result = Matrix(*this);

	for (size_t i = 0; i < N; i++) {
		for (size_t j = i; j < N; j++) {
			result[i][j] = 0;
		}
	}
	return result;
}

Matrix Matrix::getDiagnonal() const {
	if (!this->isSquared()) {
		throw "Bad size !";
	}

	Matrix result = Matrix(*this);

	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j < N; j++) {
			if (i != j) {
				result[i][j] = 0;
			}
		}
	}
	return result;
}

bool Matrix::isSquared() const {
	return (this->N == this->M);
}


Vector Matrix::podstawienieWPrzod(const Vector & other) const {
	if (this->N != other.M) {
		throw "Bad size !";
	}
	else if (!this->isTriangularLower()) {
		throw "Bad MatrixCore !";
	}

	Vector result = Vector(other.M);

	for (size_t i = 0; i < this->N; i++) {
		double sum = 0;
		for (size_t j = 0; j < i; j++) {
			sum += (result[j] * (*this)[i][j]);
		}
		result[i] = (result[i] - sum) / (*this)[i][i];
	}

	return result;
}

Vector Matrix::factoryzacjaJacobbiego(const Vector & other, double epsilon) const {
	if (this->N != other.M) {
		throw "Bad size !";
	}

	Vector result = Vector(other.M);

	Vector 

	return result;
}
