#pragma once
#include <string>
#include <Windows.h>
#include "..\Task4\Collection.h"
class ClassMenu
{
public:
	// Конструкторы -------------------------------
	ClassMenu(); // Конструктор по умолчанию
	ClassMenu(int kol, const std::string* menu); // Конструктор инициализатор
	explicit ClassMenu(int kol); // Конструктор инициализатор (создает меню с kol пустыми пунктами)
	ClassMenu(const std::string menuStr); // Конструктор приведения типа (Разбивает строку по символу\n);
	ClassMenu(const ClassMenu& m); // Конструктор копирования

	// Методы класса ------------------------------
	void DrawMenuH(const int& x = 0, const int& y = 0, const int& margin = 1); // Вызов горизонтального меню (координаты и отступы)
	void DrawMenuW(const int& x = 0, const int& y = 0, const int& margin = 1); // Вызов Вертикального меню (координаты и отступы)
	void DrawCMenu(const int& kolClauses, const int* numOfcluses, const std::string* titles, const int& x = 0, const int& y = 0, const int& margin = 1, const int& margin1 = 1); // Вызов Вертикального меню (координаты и отступы)
	void setKol(int kol);// Задать число команд меню
	int getKol() const; // Узнать число команд меню
	int getLastClause() const; // Узнать номер последнего выбранного пользователем пункта меню
	// Деструктор ---------------------------------
	~ClassMenu();

	// Перегрузки операторов ----------------------
	std::string& operator[] (int index); // Оператор индексации
	const std::string& operator[] (int index) const; // Оператор индексации константы
	friend std::ostream& operator<<(std::ostream& out, const ClassMenu& m); // Оператор вывод меню в поток
	friend std::istream& operator>>(std::istream& in, ClassMenu& m); // Оператор чтение меню из потока

private:
	int kol_, // Количество пунктов меню
		last_clause_; // Последний выбранный пользователем пункт
	Collection<std::string> menu_; // Массив пунктов меню
	void isInRange(int index)const; // Проверка индекса 
	void startMenu(int x, int y, void(ClassMenu::*paint)(HANDLE, COORD, const int&, const int&) const,const int& but1,const int& but2, const int& margin); // Вывод меню на консоль в заданные координаты с выбором режима отображения и управляющими клавишами
	void startMenu(int x, int y, void(ClassMenu::*paint)(HANDLE, COORD, const int&, const int&, const int&, const int& , const int* , const std::string* ) const, const int& but1, const int& but2, const int& margin, const int & margin1, const int& kolclauses, const int* numOfClauses, const std::string* titles); // Вывод меню на консоль в заданные координаты с выбором режима отображения и управляющими клавишами
	bool isInRangeNoThrowable(int index)const; // Проверка индекса без вызова исключения
	void paintH(HANDLE hout, COORD point, const int& k, const int& margin) const; // Функция прорисовки меню на консоли
	void paintW(HANDLE hout, COORD point, const int& k, const int& margin) const; // Функция прорисовки меню на консоли
	void paintCompositMenu(HANDLE hout, COORD point, const int& k, const int& margin, const int & margin1, const int& kolclauses, const int* numOfClauses, const std::string* titles) const; // Функция прорисовки меню на консоли
};

// Перечисление типов исключений ------------------
enum Exeptions
{
	OutOfRange, InvalideMargine
};

// Структура исключений ----------------------------
struct MenuExeption
{
	Exeptions type; // Тип исключения
	std::string error; // Описание ошибки
	MenuExeption(Exeptions i, std::string s) : type(i), error(s) {} // Конструктор структуры исключений
};

inline void ClassMenu::DrawMenuH(const int & x, const int & y, const int& margin)
{
	startMenu(x, y, &ClassMenu::paintH, VK_LEFT, VK_RIGHT, margin);
}

inline void ClassMenu::DrawMenuW(const int & x, const int & y, const int& margin)
{
	startMenu(x, y, &ClassMenu::paintW, VK_UP, VK_DOWN, margin);
}

inline void ClassMenu::DrawCMenu(const int & kolClauses, const int* numOfcluses, const std::string* titles, const int & x, const int & y, const int & margin, const int& margin1)
{
	startMenu(x, y, &ClassMenu::paintCompositMenu, VK_UP, VK_DOWN, margin, margin1, kolClauses, numOfcluses, titles);
}

// Определение инлайн функций ----------------------
inline void ClassMenu::setKol(int kol)
{
	if (kol < 0) { throw MenuExeption(MenuExeption(OutOfRange, "Введенное число команд меню неверное!")); }
	if (kol < kol_) {
		for (int i = kol_ - 1; i > kol; i--) {
			menu_.RemoveAt(i);
		}
	}
	else {
		for (int i = kol_ - 1; i < kol; i++) {
			menu_.Add("");
		}
	}
	kol_ = kol;
}

inline int ClassMenu::getKol() const
{
	return kol_;
}

inline int ClassMenu::getLastClause() const
{
	return last_clause_;
}
