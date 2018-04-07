#include "MatrixCore.h"

MatrixCore::MatrixCore(size_t N, size_t M) : N(N), M(M) {
	this->arr = new double*[N];
	for (size_t i = 0; i < N; i++) {
		this->arr[i] = new double[M];
	}
}

MatrixCore::MatrixCore(size_t N) : MatrixCore(N, N) {
	// Nop
}

MatrixCore::MatrixCore(size_t N, size_t M, const double ** new_arr) : MatrixCore(N,M) {
	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j < M; j++) {
			this->arr[i][j] = new_arr[i][j];
		}
	}
}

MatrixCore::MatrixCore(size_t N, const double** new_arr) : MatrixCore(N, N, new_arr) {
	// Nop
}

MatrixCore::MatrixCore(const MatrixCore & MatrixCore) : MatrixCore(MatrixCore.N, MatrixCore.M, (const double**)MatrixCore.arr) {
	// Nop
}

MatrixCore::MatrixCore(MatrixCore && MatrixCore) : N(MatrixCore.N), M(MatrixCore.M) {
	this->arr = nullptr;
	std::swap(this->arr, MatrixCore.arr);
}

MatrixCore::MatrixCore(size_t N, size_t M, double value) : MatrixCore(N, M) {
	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j < M; j++) {
			this->arr[i][j] = value;
		}
	}
}

MatrixCore::MatrixCore(size_t N, double value) : MatrixCore(N, N, value) {
	// Nop
}

MatrixCore::~MatrixCore() {
	if (this->arr) {
		for (size_t i = 0; i < N; i++) {
			delete[] this->arr[i];
		}
		delete[] this->arr;
	}
}

double * const MatrixCore::operator[](size_t index) {
	return this->arr[index];
}

const double * const MatrixCore::operator[](size_t index) const {
	return this->arr[index];
}

MatrixCore MatrixCore::operator+(const MatrixCore & other) const {
	if (this->N != other.N || this->M != other.M) {
		throw "Bad size !";
	}

	MatrixCore new_MatrixCore = MatrixCore(*this);
	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j < N; j++) {
			new_MatrixCore[i][j] += other[i][j];
		}
	}

	return new_MatrixCore;
}

MatrixCore MatrixCore::operator-(const MatrixCore & other) const {
	if (this->N != other.N || this->M != other.M) {
		throw "Bad size !";
	}

	MatrixCore new_MatrixCore = MatrixCore(*this);
	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j < N; j++) {
			new_MatrixCore[i][j] -= other[i][j];
		}
	}

	return new_MatrixCore;
}

MatrixCore MatrixCore::operator*(double value) const {
	MatrixCore new_MatrixCore = MatrixCore(*this);
	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j < N; j++) {
			new_MatrixCore[i][j] *= value;
		}
	}

	return new_MatrixCore;
}

MatrixCore MatrixCore::operator*(const MatrixCore & other) const {
	if (this->M != other.N) {
		throw "Bad size !";
	}

	MatrixCore new_MatrixCore(this->N, other.M);
	for (size_t i = 0; i < this->N; i++) {
		for (size_t j = 0; j < other.M; j++) {
			double suma = 0;
			for (size_t k = 0; k < this->M; k++) {
				suma += (*this)[i][k] * other[k][j];
			}
			new_MatrixCore[i][j] = suma;
		}
	}
	return new_MatrixCore;
}

void MatrixCore::print() const {
	for (size_t i = 0; i < this->N; i++) {
		for (size_t j = 0; j < this->M; j++) {
			std::cout << (*this)[i][j] << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

