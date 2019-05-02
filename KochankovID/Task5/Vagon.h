#pragma once
#include "Place.h"

using std::string;

class Vag
{
public:
	// Конструкторы ----------------------------------------------------------
	// Конструктор инициализатор
	Vag(const string& Type_,Place* pl, const int& lenth);

	// Конструктор по умолчанию
	Vag();

	// Конструктор копирования
	Vag(const Vag& copy);

	// Методы класса ---------------------------------------------------------
	// Получение массива мест
	int GetCouuntPlace() const { return TypesOfPlaces; }

	// Получение типа вагона
	string GetType() const { return type; }

	// Добавление массива мест
	void addPlace(Place* p, const int& lenth);

	// Добавление одного места
	void addPlace(const Place& p);

	// Удаление массива мест
	void removePlaces(const string* s, const int& lenth);

	// Удаление места
	void removePlacesAt(const int& n);

	// Перегрузка операторов ----------------------------------------------------------
	// Перегрузка операции вывода в поток
	friend std::ostream& operator<< (std::ostream& stream, const Vag& C);

	// Перегрузка операции ввода из потока
	friend std::istream& operator>> (std::istream& stream, Vag& C);

	// Перегрузка оператора индексирования
	Place& operator[](const int& i);

	// Перегрузка оператора индексирования для констант
	const Place& operator[](const int& i) const;

	// Перегрузка оператора присваивания
	Vag* operator= (const Vag& copy);

	// Класс Исключения ---------------------------------------------------------------
	class VagonExeption : public std::runtime_error {
	public:
		VagonExeption(const string& s) : std::runtime_error(s) {}
		~VagonExeption() {};
	};

	// Деструктор ---------------------------------------------------------------------
	~Vag();

private:
	// Скрытые поля класса ------------------------------------------------------------
	// Тип вагона
	string type;

	// Количество мест разных типов в вагоне
	int TypesOfPlaces;

	// Массив мест
	Place* places;
};
