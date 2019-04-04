#pragma once
#include <string>
#include <iostream>


class Person
{
public:
	// Конструкторы ----------------------------------------------------------
	// Конструктор инициализатор (а так же по умолчанию)
	Person(const std::string& Name_ = "Неизвестно", 
		const std::string& Female_ = "Неизвестно", 
		const std::string& Biography_ = "Неизвестно", 
		const int& Age_ = 0);
	// Применил такое решение, что бы не писать 5 почти одинаковых конструкторов

	// Конструктор копирования
	Person(const Person& copy);

	// Методы класса ---------------------------------------------------------
	// Методы доступа и редактирования полей
	std::string& Name() { return name; };
	std::string& Female() { return female; };
	std::string& Biography() { return biography; };
	int& Age() { return age; };

	// Методы константного доступа 
	const std::string& Name() const { return name; };
	const std::string& Female() const { return female; };
	const std::string& Biography() const { return biography; };
	const int& Age() const { return age; };

	// Вывод информации о человеке на консоль
	void OutPerson(const std::string& str = "") const;

	// Перегрузка операторов -------------------------------------------------
	 // Перегрузка операции вывода в поток
	friend std::ostream& operator<< (std::ostream& stream, const Person& C);

	// Перегрузка операции ввода из потока
	friend std::istream& operator>> (std::istream& stream, Person& C);

	// Перегрузка оператора присваивания
	Person* operator= (const Person& copy);

	// Перегрузка оператора сравнения
	bool operator== (const Person& p) const;

	// Класс исключения ------------------------------------------------------
	class AgeError : public std::out_of_range { // Ошибка возраста (запрещает задавать нереальный возраст автору)
	public:

		// Конструктор класса исключения
		AgeError(const std::string& Message_);

		// Деструктор класса исключения
		~AgeError();
	};

	// Деструктор ------------------------------------------------------------
	~Person();
private:
	// Скрытые поля класса ---------------------------------------------------
	std::string name, // Имя
		female, // Фамилия
		biography; // Биография
	int age; // Возраст
};

// Обявления "инлайн" функций
inline void Person::OutPerson(const std::string & str) const
{
	std::cout << str << name << ' ' << female << ' ' << age;
}