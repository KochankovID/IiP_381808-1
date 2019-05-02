#pragma once
#include <string>

using std::string;

class Place
{
public:
	// Конструкторы ----------------------------------------------------------
	// Конструктор по умолчанию
	Place();

	// Конструктор инициализатор
	explicit Place(const string& name_, const int& count_ = 0, const int& amaunt_ = 0);

	// Конструктор копирования
	Place(const Place& copy);

	// Методы класса ---------------------------------------------------------
	// Получение массива состояний продажи мест
	int GetCouuntPlace() const { return kolPlace; }

	// Получение типа мест
	string GetType() const { return typePlace; }

	// Получение типа мест
	int GetAmaunt() const { return amaunt; }

	// Покупка места
	void BuyPlace(const int& p);

	// Отмена покупки места
	void UnreservedPlace(const int& p);

	// Удаление мест
	void removePlaces(const int& n);

	// Перегрузка операторов ----------------------------------------------------------
	// Перегрузка операции вывода в поток
	friend std::ostream& operator<< (std::ostream& stream, const Place& C);

	// Перегрузка операции ввода из потока
	friend std::istream& operator>> (std::istream& stream, Place& C);

	// Перегрузка оператора индексирования
	bool& operator[](const int& i);

	// Перегрузка оператора индексирования для констант
	const bool& operator[](const int& i) const;

	// Перегрузка оператора присваивания
	Place* operator= (const Place& copy);

	// Класс Исключения ---------------------------------------------------------------
	class PlaceExeption : public std::runtime_error {
	public:
		PlaceExeption(const string& s) : std::runtime_error(s) {}
		~PlaceExeption() {};
	};

	// Деструктор ---------------------------------------------------------------------
	~Place();

private:
	// Скрытые поля класса ------------------------------------------------------------
	// Тип мест
	string typePlace;

	// Количесвто мест
	int kolPlace;
	
	// Массив состояний : Доступны (true) / Проданны (false)
	bool* plc;

	// Стоимость таких мест
	int amaunt;
};

