#include <iostream>
#include "Matrix.h"

using namespace std;
Matrix::Matrix()
{
	lenght_ = 2;
	initMat();
	for (int i = 0; i < lenght_; i++) {
		for (int j = 0; j < lenght_; j++) {
			mat[i][j] = 0;
		}
	}
}

Matrix::Matrix(int** num, int lenght)
{
	lenght_ = lenght;
	initMat();
	for (int i = 0; i < lenght_; i++) {
		for (int j = 0; j < lenght_; j++) {
			mat[i][j] = num[i][j];
		}
	}
}

Matrix::Matrix(int *num, int lenght)
{
	lenght_ = lenght;
	initMat();
	for (int i = 0; i < lenght_; i++) {
		for (int j = 0; j < lenght_; j++) {
			mat[i][j] = num[j + i*lenght_];
		}
	}
}

Matrix::Matrix(int lenght)
{
	lenght_ = lenght;
	initMat();
	for (int i = 0; i < lenght_; i++) {
		for (int j = 0; j < lenght_; j++) {
			mat[i][j] = 0;
		}
	}
}

Matrix::Matrix(const Matrix & copy)
{
	lenght_ = copy.lenght_;
	initMat();
	const int** num = copy.getMatrix();
	for (int i = 0; i < lenght_; i++) {
		for (int j = 0; j < lenght_; j++) {
			mat[i][j] = num[i][j];
		}
	}
}

void Matrix::matrixSetLenght(int r) {
	if ( r > lenght_) {
		throw MatrixExeption(OutOfMatrix, "Длинна матрицы не может быть больше размера матрицы!");
	}
	if (r < 0) {
		throw MatrixExeption(OutOfMatrix, "Длинна матрицы не может быть меньше нуля!");
	}
	else {
		lenght_ = r;
	}
}

void Matrix::setElement(int n, int m, int value)
{
	isInRange(n);
	isInRange(m);
	mat[n][m] = value;
}

int Matrix::getElement(int n, int m)
{
	isInRange(n);
	return mat[n][m];
}

bool Matrix::isDiagonalDominance() const
{
	int sum = 0;
	for (int i = 0; i < lenght_; i++) {
		for (int j = 0; j < lenght_; j++) {
			if (i != j) {
				sum += mat[i][j];
			}
		}
	}
	for (int i = 0; i < lenght_; i++) {
		if (mat[i][i] < sum) {
			return false;
		}
	}
	return true;
}

void Matrix::sumMatrix(const Matrix & m)
{
	if (lenght_ != m.lenght_) {
		throw MatrixExeption(NotEqualsRange, "Невозможно выполнить сложение матриц разного размера");
	}
	for (int i = 0; i < lenght_; i++) {
		for (int j = 0; j < lenght_; j++) {
			mat[i][j] += m.mat[i][j];
		}
	}
}

Matrix Matrix::transpanent() const
{
	Matrix transp(lenght_);
	for (int i = 0; i < lenght_; i++) {
		for (int j = 0; j < lenght_; j++) {
			transp[i][j] = mat[j][i];
		}
	}
	return transp;
}

int Matrix::getDet() const
{
	int det = 0;
	for (int i = 0; i < lenght_; i++) {
		det += mat[0][i] * getAlgDop(0,i);
	}
	return det;
}

int Matrix::getAlgDop(int firstn, int firstm) const
{
	int sum = 0;
	Matrix minor = getMinor(firstn, firstm);
	if (minor.lenght_ == 2) {
		int y = (minor.mat[0][0] * minor.mat[1][1] - minor.mat[1][0] * minor.mat[0][1])*(((firstn + firstm) % 2) > 0 ? -1 : 1);
		return (minor.mat[0][0] * minor.mat[1][1] - minor.mat[1][0] * minor.mat[0][1])*(((firstn+firstm) % 2) > 0 ? -1:1);
	}
	else {
		for (int i = 0; i < minor.lenght_; i++) {
			sum += minor.mat[0][i] * (((firstn + firstm) % 2) > 0 ? -1 : 1) * minor.getAlgDop(0, i);
			return sum;
		}
	}
}

Matrix Matrix::getMinor(int firstn, int firstm) const
{
	int minusi = 0, minusj = 0;
	Matrix minor = Matrix(lenght_-1);
	for (int i = 0; i < lenght_; i++) {
		minusj = 0;
		for (int j = 0; j < lenght_; j++) {
			if (i == firstn) {
				minusi = 1;
			}
			else {
				if (j == firstm) {
					minusj = 1;
				}
				else {
					minor[i - minusi][j - minusj] = mat[i][j];
				}
			}
		}
	}
	return minor;
}

Matrix & Matrix::operator=(const Matrix & m)
{
	if (this == &m) {
		return *this;
	}
	if (m.lenght_ > lenght_) {
		for (int i = 0; i < lenght_; i++) {
			delete[]mat[i];
		}
		delete[]mat;
		lenght_ = m.lenght_;
		initMat();
	}
	else {
		lenght_ = m.lenght_;
	}

	const int** num = m.getMatrix();
	for (int i = 0; i < lenght_; i++) {
		for (int j = 0; j < lenght_; j++) {
			mat[i][j] = num[i][j];
		}
	}
	return *this;
}

Matrix Matrix::operator+(const Matrix & m) const
{
	Matrix tmp(*this);
	tmp.sumMatrix(m);
	return tmp;
}

Matrix Matrix::operator*(const Matrix & m) const
{
	if (lenght_ != m.lenght_) {
		throw MatrixExeption(NotEqualsRange, "Невозможно выполнить умножение матриц разного размера");
	}
	Matrix tmp(lenght_);
	for (int i = 0; i < lenght_; i++) {
		for (int j = 0; j < lenght_; j++) {
			for (int o = 0; o < lenght_; o++) {
				tmp[i][j] += mat[i][o] * m.mat[o][j];
			}
		}
	}
	return tmp;
}

Matrix Matrix::operator*(const int k) const
{
	Matrix tmp(*this);
	for (int i = 0; i < lenght_; i++) {
		for (int j = 0; j < lenght_; j++) {
			tmp[i][j] *= k;
		}
	}
	return tmp;
}

int* Matrix::operator[](int index)
{
	isInRange(index);
	return mat[index];
}

const int* Matrix::operator[](int index) const
{
	isInRange(index);
	return mat[index];
}

bool Matrix::operator==(const Matrix & m) const
{
	if (lenght_ != m.lenght_) {
		return false;
	}
	for (int i = 0; i < lenght_; i++) {
		for (int j = 0; j < lenght_; j++) {
			if (mat[i][j] != m.mat[i][j]) {
				return false;
			}
		}
		return true;
	}
}

Matrix::~Matrix()
{
	for (int i = 0; i < lenght_; i++) {
		delete []mat[i];
	}
	delete []mat;
}

void Matrix::initMat()
{
	mat = new int*[lenght_];
	for (int i = 0; i < lenght_; i++) {
		mat[i] = new int[lenght_];
	}
}

void Matrix::isInRange(int index) const
{
	if ((index > lenght_) || (index < 0)) {
		throw MatrixExeption(IndexOutOfRange, "Индекс выходит за размер матрицы!");
	}
}

Matrix operator*(const int k, const Matrix & m)
{
	Matrix tmp(m);
	for (int i = 0; i < m.lenght_; i++) {
		for (int j = 0; j < m.lenght_; j++) {
			tmp[i][j] *= k;
		}
	}
	return tmp;
}

ostream& operator<<(ostream& out, const Matrix& m)
{
	out << m.lenght_ << endl; // Для совместимости с вводом из файла

	for (int i = 0; i < m.lenght_; i++) {
		for (int j = 0; j < m.lenght_; j++) {
			out << m.mat[i][j] << ' ';
		}
		out << std::endl;
	}
	return out;
}

istream& operator>>(istream & in, Matrix & m)
{
	int len;
	in >> len;
	m.matrixSetLenght(len);
	for (int i = 0; i < m.lenght_; i++) {
		for (int j = 0; j < m.lenght_; j++) {
			in >> m.mat[i][j];
		}
	}
	return in;
}
