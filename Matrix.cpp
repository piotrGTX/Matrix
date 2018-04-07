#include "Matrix.h"


Matrix Matrix::myMatrixExampleA() {
	// 165664
	const size_t N = 9 * 6 * 4;
	Matrix result = Matrix(N, (double)0);

	double a1 = 5 + 6;
	double a2 = (-1);
	double a3 = (-1);

	for (size_t i = 0; i < N; i++) {
		result[i][i] = a1;
		if (i + 1 < N) {
			result[i][i + 1] = a2;
		}
		if (i + 2 < N) {
			result[i][i + 2] = a3;
		}
		if (i > 0) {
			result[i][i - 1] = a2;
		}
		if (i > 1) {
			result[i][i - 2] = a3;
		}
	}

	return result;
}

Matrix Matrix::myVectorExampleA() {
	// 165664
	const size_t N = 9 * 6 * 4;
	Matrix result = Matrix(N, (size_t) 1);

	const size_t f = 5;
	for (size_t i = 0; i < N; i++) {
		result[i][0] = sin((i + 1)*(f + 1));
	}

	return result;
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

Matrix::Matrix(const Matrix & matrix) : Matrix(matrix.N, matrix.M, (const double**)matrix.arr) {
	// Nop
}

Matrix::Matrix(Matrix && matrix) : N(matrix.N), M(matrix.M) {
	this->arr = nullptr;
	std::swap(this->arr, matrix.arr);
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
	if (!this->equalsSize(other)) {
		throw std::string("Bad size !");
	}

	Matrix new_Matrix = Matrix(*this);
	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j < N; j++) {
			new_Matrix[i][j] += other[i][j];
		}
	}

	return new_Matrix;
}

Matrix Matrix::operator-(const Matrix & other) const {
	if (!this->equalsSize(other)) {
		throw std::string("Bad size !");
	}

	Matrix new_Matrix = Matrix(*this);
	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j < N; j++) {
			new_Matrix[i][j] -= other[i][j];
		}
	}

	return new_Matrix;
}

Matrix Matrix::operator*(double value) const {
	Matrix new_Matrix = Matrix(*this);
	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j < N; j++) {
			new_Matrix[i][j] *= value;
		}
	}

	return new_Matrix;
}

Matrix Matrix::operator*(const Matrix & other) const {
	if (!this->canBeMultiple(other)) {
		throw std::string("Bad size !");
	}

	Matrix new_Matrix(this->N, other.M);
	for (size_t i = 0; i < this->N; i++) {
		for (size_t j = 0; j < other.M; j++) {
			double suma = 0;
			for (size_t k = 0; k < this->M; k++) {
				suma += (*this)[i][k] * other[k][j];
			}
			new_Matrix[i][j] = suma;
		}
	}
	return new_Matrix;
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
	if (!this->isSquared()) {
		throw std::string("Bad size !");
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
		throw std::string("Bad size !");
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

bool Matrix::isVector() const {
	return (this->M == 1);
}

bool Matrix::equalsSize(const Matrix & other) const {
	return this->M == other.M && this->N == other.N;
}

bool Matrix::canBeMultiple(const Matrix & other) const {
	return this->M == other.N;
}

Matrix Matrix::getTriangularUpper() const {
	if (!this->isSquared()) {
		throw std::string("Bad size !");
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
		throw std::string("Bad size !");
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
		throw std::string("Bad size !");
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


Matrix Matrix::podstawienieWPrzod(const Matrix & other) const {
	if (!this->canBeMultiple(other)) {
		throw std::string("Bad size !");
	}
	else if (!this->isTriangularLower()) {
		throw std::string("Bad Matrix !");
	}
	else if (!other.isVector()) {
		throw std::string("Matrix have to be vector !");
	}

	Matrix result = Matrix(other);
	for (size_t i = 0; i < this->N; i++) {
		double sum = 0;
		for (size_t j = 0; j < i; j++) {
			sum += (result[j][0] * (*this)[i][j]);
		}
		result[i][0] = (result[i][0] - sum) / (*this)[i][i];
	}

	return result;
}

double Matrix::norm() const {
	double result = 0;
	for (size_t i = 0; i < N; i++) {
		result += (*this)[i][0] * (*this)[i][0];
	}
	return sqrt(result);
}