#pragma once
#include <iostream>
#include <string>

class Data {
public:
	// Конструкторы ----------------------------------------------------------
	// Конструктор инициализатор
	Data(const int& day_, const int& month_, const int& year_);

	// Конструктор копирования 
	Data(const Data& copy) : day(copy.day), 
		month(copy.month), year(copy.year) {}

	// Конструктор по умолчанию
	Data() : year(0), month(0), day(0) {}

	// Методы класса ---------------------------------------------------------
	// Вывод даты на консоль
	void OutData(const std::string& str = "") const;

	// Перевод даты в строку
	std::string ToString() const;

	// Методы доступа и редактирования полей
	int& Day() { return day; };
	int& Month() { return month; };
	int& Year() { return year; };

	// Методы константного доступа 
	const int& Day() const { return day; };
	const int& Month() const { return month; };
	const int& Year() const { return year; };

	// Перегрузка операторов -------------------------------------------------
	 // Перегрузка оператора присваивания
	Data* operator= (const Data& copy);

	// Перегрузка операции вывода в поток
	friend std::ostream& operator<< (std::ostream& stream, const Data& C);

	// Класс исключения
	class InvalideData : public std::out_of_range {
	public:
		// Конструктор класса исключения
		InvalideData(const std::string& Message_);

		// Деструктор класса исключения
		~InvalideData();
	};
	// Перегрузка операции ввода из потока
	friend std::istream& operator>> (std::istream& stream, Data& C);

	// Перегрузка оператора сравнения
	bool operator== (const Data& p) const;

	// Деструктор ------------------------------------------------------------
	~Data();

private:
	// Поля класса -----------------------------------------------------------
	int year; // Год
	int month; // Месяц
	int day; // День

	// Метод проверки соответствия формату введенных данных
	void IsRight() const;
};


// Обявления "инлайн" функций
inline void Data::OutData(const std::string& str) const
{
	std::cout << str << day << '.' << month << '.' << year;
}

inline std::string Data::ToString() const
{
	return std::string(std::to_string(day) + '.' + std::to_string(month) + '.' + std::to_string(year));
}
