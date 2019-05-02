#pragma once
#include "Day.h"

class GorkyRailway
{
public:
	// Конструкторы ----------------------------------------------------------
	// Конструктор инициализатор
	GorkyRailway(const Day* days_, const int& lenth_);

	// Конструктор инициализатор
	explicit GorkyRailway(const int& lenth_);

	GorkyRailway(const GorkyRailway&) = delete;

	// Методы класса ---------------------------------------------------------
	// Получение массива дней
	const Day* getDays() const { return days; };

	// Получение числа дней
	int getNumsDay() const { return KollOfDays; };

	// Добавление массива дней
	void addDays(Day* v, const int& lenth);

	// Добавление одного дня
	void addDay(const Day& v);

	// Удаление промежутка дней
	void removeDays(const int& first, const int& last);

	// Перегрузка операторов --------------------------------------------------
	// Перегрузка операции вывода в поток
	friend std::ostream& operator<< (std::ostream& stream, const GorkyRailway& C);

	// Перегрузка операции ввода из потока
	friend std::istream& operator>> (std::istream& stream, GorkyRailway& C);

	// Перегрузка оператора индексирования
	Day& operator[](const int& i);

	// Перегрузка оператора индексирования для констант
	const Day& operator[](const int& i) const;

	// Перегрузка оператора присваивания
	GorkyRailway* operator= (const GorkyRailway& copy) = delete;

	// Класс Исключения ---------------------------------------------------------------
	class RailwayExeption : public std::runtime_error {
	public:
		RailwayExeption(const string& s) : std::runtime_error(s){}
		~RailwayExeption() {};
	};

	// Деструктор ---------------------------------------------------------------------
	~GorkyRailway();
private:
	// Скрытые поля класса ------------------------------------------------------------
	// Количество дней
	int KollOfDays;

	// Массив дней
	Day* days;
};

