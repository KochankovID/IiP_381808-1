#include <fstream>
#include <iostream>
#include <locale>
#include <string>
#include "Matrix.h"

using namespace std;
int main()
{
	setlocale(LC_CTYPE, "Russian");

	// Тест конструкторов ----------------------------
	Matrix m1 = Matrix();
	cout << m1;
	cout << endl;
	int ** a = new int*[3];

	for (int i = 0; i < 3; i++) {
		a[i] = new int[3];
		for (int j = 0; j < 3; j++) {
			if (i == j) {
				a[i][j] = 1;
			}
			else {
				a[i][j] = j;
			}
		}
	}
	Matrix m2 = Matrix(a, 3); // инициализатор
	cout << m2;
	cout << endl;
	for (int i = 0; i < 3; i++) {
		delete[]a[i];
	}
	delete a;

	int* b = new int[9];
	for (int i = 0; i < 9; i++) {
		b[i] = i;
	}
	Matrix m3 = Matrix(b, 3); // Инициализатор
	cout << m3;
	cout << endl;
	delete b;

	Matrix m4 = Matrix(4); // Инициализатор
	cout << m4 << endl;

	Matrix m5 = Matrix(m4); // Копирования
	cout << m5 << endl;

	// Тест методов ---------------------------------
	
	try {
		m5.matrixSetLenght(3); // Изменение размера матрицы
	}
	catch (MatrixExeption& error) {
		cout << error.error << endl;
	}
	cout << m5 << endl;
	
	try {
		m5.setElement(1, 1, 1); // Задать элемент по индексам
	}
	catch (MatrixExeption& error) {
		cout << error.error << endl;
	}
	cout << m5 << endl;
	
	try {
		cout << m5.getElement(1, 1) << endl; // Получить значение элемента по индексам
	}
	catch (MatrixExeption& error) {
		cout << error.error << endl;
	}
	cout << m5.getLenght() << endl; // Получение длинны матрицы

	const int** m = m5.getMatrix(); // Получение матрицы
	for (int i = 0; i < m5.getLenght(); i++) {
		for (int j = 0; j < m5.getLenght(); j++) {
			cout << m[i][j] << ' ';
		}
		cout << endl;
	}
	cout << m5.isDiagonalDominance() << endl; // Проверка диагонального преобразования
	
	try {
		m5.sumMatrix(m3);
		cout << m5 << endl; // Сумма матриц
	}
	catch (MatrixExeption& erroor) {
		cout << erroor.error << endl;
	}

	cout << "Определитель матрицы: " << m5.getDet() << endl; // Определитель матрицы

	cout << endl;
	// Тест работы с файлами
	ofstream file;
	file.open("Text.txt");
	file << m5;
	file.close();
	ifstream file1;
	file1.open("Text.txt");
	file1 >> m5;
	file1.close();
	cout << m5 << endl;

	system("pause");
}

