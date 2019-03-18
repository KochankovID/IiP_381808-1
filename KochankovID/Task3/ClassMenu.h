#pragma once
#include <string>
#include <Windows.h>
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
	void startMenu(int x, int y); // Вывод меню на консоль в заданные координаты
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
	std::string* menu_; // Массив пунктов меню
	void isInRange(int index)const; // Проверка индекса 
	bool isInRangeNoThrowable(int index)const; // Проверка индекса без вызова исключения
	void paint(HANDLE hout, COORD point, int k) const; // Функция прорисовки меню на консоли
};

// Перечисление типов исключений ------------------
enum Exeptions
{
	OutOfRange
};

// Структура исключений ----------------------------
struct MenuExeption
{
	Exeptions type; // Тип исключения
	std::string error; // Описание ошибки
	MenuExeption(Exeptions i, std::string s) : type(i), error(s) {} // Конструктор структуры исключений
};

// Определение инлайн функций ----------------------
inline void ClassMenu::setKol(int kol) throw(MenuExeption)
{
	isInRange(kol);
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
