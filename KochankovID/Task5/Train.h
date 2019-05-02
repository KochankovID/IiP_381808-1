#pragma once
#include <string>
#include "Vagon.h"

using std::string;

class Train
{
public:
	// Конструкторы ----------------------------------------------------------
	// Конструктор по умолчанию
	Train();

	// Конструктор инициализатор
	explicit Train(const string& name_,const int& count_ = 0);

	// Конструктор инициализатор
	Train(const string& name_, const int& count_, Vag* Vags_);

	// Конструктор копирования
	Train(const Train& copy);

	// Методы класса ---------------------------------------------------------
	// Получение массива вагонов
	const Vag* getVags() const { return Vags; };

	// Получение числа вагонов
	int getNumVags() const { return kollofVags; };

	// Получение имени поезда
	string getName() const { return nameTrain; };

	// Добавление массива вагонов
	void addVagon(Vag* v, const int& lenth);

	// Добавление одного вагона
	void addVagon(const Vag& v);

	// Удаление массива вагонов
	void removeVagon(const string* v, const int& lenth);

	// Удаление одного вагона
	void removeVagon(const int& v);

	// Перегрузка операторов ----------------------------------------------------------
	// Перегрузка операции вывода в поток
	friend std::ostream& operator<< (std::ostream& stream, const Train& C);

	// Перегрузка операции ввода из потока
	friend std::istream& operator>> (std::istream& stream, Train& C);

	// Перегрузка оператора индексирования
	Vag& operator[](const int& i);

	// Перегрузка оператора индексирования для констант
	const Vag& operator[](const int& i) const;

	// Перегрузка оператора присваивания
	Train* operator= (const Train& copy);

	// Класс Исключения ---------------------------------------------------------------
	class TrainExeption : public std::runtime_error {
	public:
		TrainExeption(const string& s) : std::runtime_error(s) {}
		~TrainExeption() {};
	};

	// Деструктор ---------------------------------------------------------------------
	virtual ~Train();

private:
	// Скрытые поля класса ------------------------------------------------------------
	// Имя поезда
	string nameTrain;

	// Количество вагонов
	int kollofVags;

	// Массив вагонов
	Vag* Vags;
};

