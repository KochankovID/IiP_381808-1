#pragma once
#include "Train.h"

class Day
{
public:
	// Конструкторы ----------------------------------------------------------
	// Конструктор по умолчанию
	Day();

	// Конструктор инициализатор
	Day(const Train* trains_, const int& lenght);

	// Конструктор копирования
	Day(const Day& copy);

	// Методы класса ---------------------------------------------------------
	// Получение массива поездов
	const Train* getTrains() const { return trains; };

	// Получение числа поездов
	int getNumTrains() const { return KollOfTrains; };

	// Добавление массива поездов
	void addTrain(Train* v, const int& lenth);

	// Добавление одного поезда
	void addTrain(const Train& v);

	// Удаление массива поездов
	void removeTrain(const string* v, const int& lenth);

	// Удаление одного поезда
	void removeTrain(const int& v);

	// Класс Исключения ---------------------------------------------------------------
	class DayExeption : public std::runtime_error {
	public:
		DayExeption(const string& s) : std::runtime_error(s) {}
		~DayExeption() {};
	};

	// Перегрузка операторов ----------------------------------------------------------
	// Перегрузка операции вывода в поток
	friend std::ostream& operator<< (std::ostream& stream, const Day& C);

	// Перегрузка операции ввода из потока
	friend std::istream& operator>> (std::istream& stream, Day& C);

	// Перегрузка оператора индексирования
	Train& operator[](const int& i);

	// Перегрузка оператора индексирования для констант
	const Train& operator[](const int& i) const;\

	// Перегрузка оператора присваивания
	Day* operator= (const Day& copy);

	// Деструктор ---------------------------------------------------------------------
	~Day();
private:
	// Скрытые поля класса ------------------------------------------------------------
	// Массив поездов
	Train* trains;

	// Количество поездов
	int KollOfTrains;

};

