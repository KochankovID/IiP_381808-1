#pragma once
#include <string>
class Matrix

{
public:
	// Конструкторы ---------------------------------
	Matrix(); // Конструктор по умолчанию -----------
	Matrix(int** num, int length); // Конструктор инициализатор
	Matrix(int* num, int length); // Конструктор инициализатор
	explicit Matrix(int lenght); // Конструктор инициализатор (создает матрицу заданной длинны из 0)
	Matrix(const Matrix& copy); // Конструктор копирования 

	// Методы класса --------------------------------
	void matrixSetLenght(int r); // Изменение размера матрицы
	void setElement(int n, int m, int value); // Задать элемент по индексам
	int getElement(int n, int m); // Получить значение элемента по индексам
	int getLenght() const; // Получение длинны матрицы
	const int** getMatrix() const; // Получение матрицы
	bool isDiagonalDominance() const; // Проверка диагонального преобладания
	void sumMatrix(const Matrix& m); // Сумма матриц одного размера
	Matrix transpanent() const; // Возвращает транспонированную матрицу
	int getDet() const; // Вычисление определителя матрицы
	int getAlgDop(int firstn, int firstm) const; //Вычисление алгебраического дополнения для элемента
	Matrix getMinor(int firstn, int firstm) const; //Возвращает минор заданного элемента данной матрицы

	// Перегрузки операторов ------------------------
	Matrix& operator= (const Matrix& m); // Оператор присваивания
	Matrix operator+ (const Matrix& m) const; // Оператор суммы
	Matrix operator* (const Matrix& m) const; // Оператор произведения
	Matrix operator* (const int k) const; // Оператор произведения на число
	friend Matrix operator* (const int k, const Matrix& m); // Оператор произведения на число
	friend std::ostream& operator<<(std::ostream& out, const Matrix& m); // Оператор вывод матрицы в поток
	friend std::istream& operator>>(std::istream& out, Matrix& m); // Оператор чтение матрицы из потока
	int* operator[] (int index); // Оператор индексации
	const int* operator[] (int index) const; // Оператор индексации константы
	bool operator==(const Matrix& m) const; // Оператор сравнения матриц


	// Деструктор -----------------------------------
	~Matrix();

private:

	// Поля класса ----------------------------------
	int lenght_; // Длинна матрицы
	int** mat; // Матрица

	// Скрытые матоды класса ------------------------
	void initMat(); // Выделение памяти для матрицы
	void isInRange(int index) const; // Проверяет, находится ли индекс в допустимых границах
};

// Объявления инлайн методов ------------------------
inline int Matrix::getLenght() const {
	return lenght_;
}

inline const int** Matrix::getMatrix() const {
	return const_cast<const int**>(mat); // этот подход считается не безопасным, но в данном случае без него
	// нельзя обойтись, так как метод с модификатором const следит за тем, что бы ПОЛЯ  класса не 
	// изменяли своего значения, и указатель mat в нем расскатривается как КОНСТАНТНЫЙ указатель,
	// применияя преобразования к узакателю НА КОНСТАНТУ и возвращаа копию его значения, константность
	// объекта сохраняется
}

// Перечисление типов исключений -------------------
enum Exeptions
{
	OutOfMatrix, IndexOutOfRange, NotEqualsRange, DeterminIsZero
};

// Структура исключений ----------------------------
struct MatrixExeption
{
	Exeptions type;
	std::string error;
	MatrixExeption(Exeptions i, std::string s) : type(i), error(s) {}
};