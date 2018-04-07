#include "Matrix.h"

Matrix Matrix::myMatrixExampleA() {
	// 165664
	const size_t N = 9 * 6 * 4;
	Matrix myMatrix = Matrix(N, (double) 0);

	double a1 = 5 + 6;
	double a2 = (-1);
	double a3 = (-1);

	for (size_t i = 0; i < N; i++) {
		myMatrix[i][i] = a1;
		if (i + 1 < N) {
			myMatrix[i][i + 1] = a2;
		}
		if (i + 2 < N) {
			myMatrix[i][i + 2] = a3;
		}
		if (i > 0) {
			myMatrix[i][i - 1] = a2;
		}
		if (i > 1) {
			myMatrix[i][i - 2] = a3;
		}
	}
	
	return myMatrix;
}

Matrix::Matrix(size_t N, size_t M) : N(N), M(M) {
	this->arr = new double*[N];
	for (size_t i = 0; i < N; i++) {
		this->arr[i] = new double[M];
	}
}

Matrix::Matrix(size_t N) : Matrix(N, N) {
	// Nop
}

Matrix::Matrix(size_t N, size_t M, const double ** new_arr) : Matrix(N,M) {
	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j < M; j++) {
			this->arr[i][j] = new_arr[i][j];
		}
	}
}

Matrix::Matrix(size_t N, const double** new_arr) : Matrix(N, N, new_arr) {
	// Nop
}

Matrix::Matrix(const Matrix & matrix) : Matrix(matrix.N, matrix.M, (const double**)matrix.arr) {
	// Nop
}

Matrix::Matrix(Matrix && matrix) : N(matrix.N), M(matrix.M) {
	std::swap(this->arr, matrix.arr);
}

Matrix::Matrix(size_t N, size_t M, double value) : Matrix(N, M) {
	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j < M; j++) {
			this->arr[i][j] = value;
		}
	}
}

Matrix::Matrix(size_t N, double value) : Matrix(N, N, value) {
	// Nop
}

Matrix::~Matrix() {
	if (this->arr) {
		for (size_t i = 0; i < N; i++) {
			delete[] this->arr[i];
		}
		delete[] this->arr;
	}
}

double * const Matrix::operator[](size_t index) {
	return this->arr[index];
}

const double * const Matrix::operator[](size_t index) const {
	return this->arr[index];
}

Matrix Matrix::operator+(const Matrix & other) const {
	if (this->N != other.N || this->M != other.M) {
		throw "Bad size !";
	}

	Matrix new_matrix = Matrix(*this);
	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j < N; j++) {
			new_matrix[i][j] += other[i][j];
		}
	}

	return new_matrix;
}

Matrix Matrix::operator-(const Matrix & other) const {
	if (this->N != other.N || this->M != other.M) {
		throw "Bad size !";
	}

	Matrix new_matrix = Matrix(*this);
	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j < N; j++) {
			new_matrix[i][j] -= other[i][j];
		}
	}

	return new_matrix;
}

Matrix Matrix::operator*(double value) const {
	Matrix new_matrix = Matrix(*this);
	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j < N; j++) {
			new_matrix[i][j] *= value;
		}
	}

	return new_matrix;
}

Matrix Matrix::operator*(const Matrix & other) const {
	if (this->M != other.N) {
		throw "Bad size !";
	}

	Matrix new_matrix(this->N, other.M);
	for (size_t i = 0; i < this->N; i++) {
		for (size_t j = 0; j < other.M; j++) {
			double suma = 0;
			for (size_t k = 0; k < this->M; k++) {
				suma += (*this)[i][k] * other[k][j];
			}
			new_matrix[i][j] = suma;
		}
	}
	return new_matrix;
}

void Matrix::print() const {
	for (size_t i = 0; i < this->N; i++) {
		for (size_t j = 0; j < this->M; j++) {
			std::cout << (*this)[i][j] << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

bool Matrix::isTriangularUpper() const {
	if (this->N != this->M) {
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
	if (this->N != this->M) {
		throw "Bad size !";
	}

	for (size_t i = 0; i < (N-1); i++) {
		for (size_t j = (i + 1); j < N; j++) {
			if (this->arr[i][j] != 0) {
				return false;
			}
		}
	}
	return true;
}

Matrix Matrix::getTriangularUpper() const {
	Matrix result = Matrix(*this);

	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j <= i; j++) {
			result[i][j] = 0;
		}
	}
	return result;
}

Matrix Matrix::getTriangularLower() const {
	Matrix result = Matrix(*this);

	for (size_t i = 0; i < N; i++) {
		for (size_t j = i; j < N; j++) {
			result[i][j] = 0;
		}
	}
	return result;
}

Matrix Matrix::getDiagnonal() const {
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
