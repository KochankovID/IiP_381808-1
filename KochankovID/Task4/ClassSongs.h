#pragma once
#include "Song.h"
#include "Collection.h"
#include <iostream>

class ClassSongs
{
public:
	// Конструкторы ----------------------------------------------------------
	// Конструктор по умолчанию
	ClassSongs();

	// Конструктор инициализатор
	explicit ClassSongs(const std::string& file);

	// Конструктор копирования (запрещен)
	ClassSongs(const ClassSongs& copy) = delete;

	// Методы класса ---------------------------------------------------------
	// Метод доступа и редактирования коллекции песен
	Collection<Song>& songs() { return Songs; };

	// Метод поиска песен по названию (с возможностью редактирования)
	Collection<Song*> getNameSongs(std::string name);

	// Метод поиска поэта по названию (с возможностью редактирования)
	Collection<Person*> getPoets(std::string name);
	Collection<Person*> getPoets();

	// Метод поиска композитора по названию (с возможностью редактирования)
	Collection<Person*> getComositers(std::string name);
	Collection<Person*> getComositers();

	// Метод поиска исполнителя по названию (с возможностью редактирования)
	Collection<Person*> getExecutorts(std::string name);
	Collection<Person*> getExecutorts();

	//--------------------------------------------------------------------
	// Метод поиска всех песен поэта (с возможностью редактирования)
	Collection<Song*> getAllPoetSongs(const Person& poet);

	// Метод поиска всех песен композитора (с возможностью редактирования)
	Collection<Song*> getAllCompositerSongs(const Person& compositer);

	// Метод поиска всех песен исполнителя (с возможностью редактирования)
	Collection<Song*> getAllExecutorSongs(const Person& executor);
	//--------------------------------------------------------------------

	// Метод изменения поэта
	void ChangeAllPoets(const Person& poet, const Person& poet1);

	// Метод изменения композитора
	void ChangeAllCompositers(const Person& compositer, const Person& compositer1);

	// Метод изменения исполнителя
	void ChangeAllExecutors(const Person& executor, const Person& executor1);

	// Сортировка песен по названию
	void sort();

	// Метод сохраняющий архив песен в файл хранения
	void saveArchive();

	// Перегрузка операторов --------------------------------------------------------
	friend std::ostream& operator<< (std::ostream& stream, const ClassSongs& C); // Перегрузка операции вывода в поток
	friend std::istream& operator>> (std::istream& stream, ClassSongs& C); // Перегрузка операции ввода из потока

	// Деструктор ---------------------------------------------------------------------
	~ClassSongs();
private:
	// Скрытые поля класса ------------------------------------------------------------

	// Коллекции песен и информация о них
	Collection<Song> Songs; // Коллекция песен
	std::string file; // Имя файла в кором сохраняется информация
};
