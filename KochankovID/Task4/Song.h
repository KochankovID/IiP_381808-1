#pragma once
#include "Person.h"
#include "Data.h"

class Song
{
public:

	// Конструкторы ----------------------------------------------------------
	// Конструктор инициализатор (и конструктор по умоланию)
	Song(const std::string& Location_ = "Неизвестно", const std::string& NameSong_ = "Неизвестно", 
		const std::string& Album_ = "Неизвестно",
		const int& day_ = 0, const int& month_ = 0, const int& year_ = 0);
	// Решение использовать такой коструктор обоснованно сокращением числа 
	// одинаковых конструкторов (т.к. песню можно создать не зная каких-либо или всех данных)

	 // Конструктор копирования
	Song(const Song& copy);

	// Методы класса ---------------------------------------------------------
	// Вывод песни на консоль
	void OutSong(const std::string& str = "") const;

	// Методы доступа и редактирования полей
	Data& DataRelease() { return dataRelease; };
	std::string& Location() { return location; };
	std::string& NameSong() { return nameSong; };
	std::string& Album() { return album; };
	Person& Poet() { return poet; };
	Person& Compositer() { return compositer; };
	Person& Executor() { return executor; };

	// Методы константного доступа
	const Data& DataRelease() const { return dataRelease; };
	const std::string& Location() const { return location; };
	const std::string& NameSong() const { return nameSong; };
	const std::string& Album() const { return album; };
	const Person& Poet() const { return poet; };
	const Person& Compositer() const { return compositer; };
	const Person& Executor() const { return executor; };

	// Перегрузка операторов -------------------------------------------------
	// Перегрузка операции вывода в поток
	friend std::ostream& operator<< (std::ostream& stream, const Song& C);

	// Перегрузка операции ввода из потока
	friend std::istream& operator>> (std::istream& stream, Song& C);

	// Перегрузка оператора сравнения
	bool operator== (const Song& p) const;

	// Перегрузка оператора присваивания
	Song* operator= (const Song& copy);

	// Деструктор ------------------------------------------------------------
	~Song();
private:
	// Поля класса -----------------------------------------------------------
	std::string nameSong, // Имя песни
		album, // Альбом
		location; // Путь к песне (либо на диске либо прямая url) 
	Data dataRelease; // Дата выхода
	Person poet; // Поэт
	Person compositer; // Композитор
	Person executor; // Исполнитель
};

// Определение "инлайн" функций
inline void Song::OutSong(const std::string & str) const
{
	std::cout << str << nameSong << ' ' << album << ' ' << dataRelease;
}