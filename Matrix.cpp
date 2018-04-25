#include "Matrix.h"


Matrix Matrix::myMatrixExample(const size_t N, const double a1, const double a2, const double a3) {
	// 195664
	Matrix result = Matrix(N, (double)0);

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

Matrix Matrix::myVectorExample(const size_t N) {
	// 165664
	Matrix result = Matrix(N, (size_t) 1);

	const size_t f = 5 + 1; // 3 Cyfra mojego indeksu + 1
	for (size_t i = 0; i < N; i++) {
		result[i][0] = sin((i + 1)*f);
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

Matrix & Matrix::operator=(Matrix && matrix) {
	std::swap(this->N, matrix.N);
	std::swap(this->M, matrix.M);
	std::swap(this->arr, matrix.arr);

	return (*this);
}

Matrix & Matrix::operator=(const Matrix & matrix) {

	if (this->arr) {
		for (size_t i = 0; i < N; i++) {
			delete[] this->arr[i];
		}
		delete[] this->arr;
	}

	this->M = matrix.M;
	this->N = matrix.N;

	this->arr = new double*[N];
	for (size_t i = 0; i < N; i++) {
		this->arr[i] = new double[M];
		for (size_t j = 0; j < N; j++) {
			this->arr[i][j] = matrix[i][j];
		}
	}

	return (*this);
}

double * const Matrix::operator[](size_t index) {
	return this->arr[index];
}

const double * const Matrix::operator[](size_t index) const {
	return this->arr[index];
}

Matrix Matrix::operator+(const Matrix & other) const {
	if (!this->equalsSize(other)) {
			 std::string("Operacja + zly rozmiar: " + std::to_string(this->M) + "x" + std::to_string(this->N) + " vs " + std::to_string(other.M) + "x" + std::to_string(other.N));
	}

	Matrix new_Matrix = Matrix(*this);
	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j < M; j++) {
			new_Matrix[i][j] += other[i][j];
		}
	}

	return new_Matrix;
}

Matrix Matrix::operator-(const Matrix & other) const {
	if (!this->equalsSize(other)) {
		throw std::string("Operacja - zly rozmiar: " + std::to_string(this->M) + "x" + std::to_string(this->N) + " vs " + std::to_string(other.M) + "x" + std::to_string(other.N));
	}

	Matrix new_Matrix = Matrix(*this);
	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j < M; j++) {
			new_Matrix[i][j] -= other[i][j];
		}
	}

	return new_Matrix;
}

Matrix Matrix::operator*(double value) const {
	Matrix new_Matrix = Matrix(*this);
	for (size_t i = 0; i < N; i++) {
		for (size_t j = 0; j < M; j++) {
			new_Matrix[i][j] *= value;
		}
	}

	return new_Matrix;
}

Matrix Matrix::operator*(const Matrix & other) const {
	if (!this->canBeMultiple(other)) {
		throw std::string("Operacja * zly rozmiar: " + std::to_string(this->M) + "x" + std::to_string(this->N) + " vs " + std::to_string(other.M) + "x" + std::to_string(other.N));
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

bool Matrix::isTriangularUpper() const {
	if (!this->isSquared()) {
		return false;
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
		return false;
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

Matrix Matrix::podstawienieWPrzod(const Matrix & vector) const {
	if (!this->canBeMultiple(vector)) {
		throw std::string("Bad size !");
	}
	else if (!this->isTriangularLower()) {
		throw std::string("Matrix isn't triangular lower !");
	}
	else if (!vector.isVector()) {
		throw std::string("Matrix have to be vector !");
	}

	Matrix result = Matrix(vector);
	for (size_t i = 0; i < this->N; i++) {
		double sum = 0;
		for (size_t j = 0; j < i; j++) {
			sum += (result[j][0] * (*this)[i][j]);
		}
		if ((*this)[i][i] == 0) {
			throw "Zero on diagonal !";
		}
		result[i][0] = (result[i][0] - sum) / (*this)[i][i];
	}

	return result;
}

Matrix Matrix::podstawienieWTyl(const Matrix & vector) const {
	if (!this->canBeMultiple(vector)) {
		throw std::string("Bad size !");
	}
	else if (!this->isTriangularUpper()) {
		this->isTriangularUpper();
		throw std::string("Matrix isn't triangular upper !");
	}
	else if (!vector.isVector()) {
		throw std::string("Matrix have to be vector !");
	}

	Matrix result = Matrix(vector);
	for (int i = (this->N - 1); i >= 0; i--) {
		double sum = 0;
		for (int j = (this->N - 1); j > i; j--) {
			sum += (result[j][0] * (*this)[i][j]);
		}
		if ((*this)[i][i] == 0) {
			throw "Zero on diagonal !";
		}
		result[i][0] = (result[i][0] - sum) / (*this)[i][i];
	}

	return result;
}

Matrix Matrix::metodaJacobiego(const Matrix & vector) const {
	const Matrix U = this->getTriangularUpper();
	const Matrix L = this->getTriangularLower();
	const Matrix D = this->getDiagnonal();

	const Matrix helper = D.podstawienieWPrzod(vector);
	Matrix residuum = Matrix(vector.N, (size_t) 1);
	Matrix r = Matrix(vector.N, (size_t) 1, (double) 1.0);

	const double limit_e = 1e-9; // Wartoœæ akceptowalna
	const size_t max_i = 400; // Maksymalna iloœæ iteracji

	residuum = (*this) * r - vector;
	size_t i = 0;
	while (residuum.norm() > limit_e && i < max_i) {
		r = helper - D.podstawienieWPrzod((L + U)*r);
		residuum = (*this) * r - vector;
		i++;
	}

	if (i >= max_i) {
		std::cout << "Przerwane z powodu ilosci iteracji !" << std::endl;
	}
	std::cout << "Norma z residuum: " << residuum.norm() << std::endl;
	std::cout << "Ilosc iteracji: " << i << std::endl;

	return r;
}

Matrix Matrix::metodaSeidla(const Matrix & vector) const {
	const Matrix U = this->getTriangularUpper();
	const Matrix L = this->getTriangularLower();
	const Matrix D = this->getDiagnonal();

	const Matrix helper = (D+L).podstawienieWPrzod(vector);
	Matrix residuum = Matrix(vector.N, (size_t) 1);
	Matrix r = Matrix(vector.N, (size_t) 1, (double) 1.0);

	const double limit_e = 1e-9; // Wartoœæ akceptowalna
	const size_t max_i = 400; // Maksymalna iloœæ iteracji

	residuum = (*this) * r - vector;
	size_t i = 0;
	while (residuum.norm() > limit_e && i < max_i) {
		r = helper - (D+L).podstawienieWPrzod(U*r);
		residuum = (*this) * r - vector;
		i++;
	}
	
	if (i >= max_i) {
		std::cout << "Przerwane z powodu ilosci iteracji !" << std::endl;
	}
	std::cout << "Norma z residuum: " << residuum.norm() << std::endl;
	std::cout << "Ilosc iteracji: " << i << std::endl;

	return r;
}

Matrix Matrix::faktoryzacjaLU(const Matrix & vector) const {
	Matrix U = Matrix(*this);
	Matrix L = Matrix(this->N, (double) 0); // Jednostkowy
	for (size_t i = 0; i < L.getN(); i++)
		L[i][i] = 1;

	for (size_t k = 0; k < (this->N - 1); k++) {
		for (size_t j = k + 1; j < (this->N); j++) {
			L[j][k] = U[j][k] / U[k][k];
			for (size_t i = k; i < this->N; i++) {
				U[j][i] = U[j][i] - (L[j][k] * U[k][i]);
			}
		}
	}

	// Usuwanie œmieci 
	U = U.getTriangularUpper() + U.getDiagnonal();
	L = L.getTriangularLower() + L.getDiagnonal(); 

	const Matrix Y = L.podstawienieWPrzod(vector);
	const Matrix X = U.podstawienieWTyl(Y);

	return X;
}

double Matrix::norm() const {
	double result = 0;
	for (size_t i = 0; i < N; i++) {
		result += (*this)[i][0] * (*this)[i][0];
	}
	return sqrt(result);
}

size_t Matrix::getN() const {
	return this->N;
}

size_t Matrix::getM() const {
	return this->M;
}
