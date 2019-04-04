#pragma once
#include "ClassSongs.h"
#include "..\Task3\ClassMenu.h"
class Interface
{
public:
	// Конструкторы ----------------------------------------------------------
	// Конструктор по умолчанию
	Interface();

	// Конструткор копирования (запрет создания копии)
	Interface(const Interface& copy) = delete;

	// Методы класса ---------------------------------------------------------
	// Начало работы с интерфейсом загрузка начального меню 
	void StartMenu();

	// Вызов меню всех поэтов
	void MenuWAP();

	// Вызов меню всех композиторов
	void MenuWAC();

	// Вызов меню всех исполнителей
	void MenuWAE();

	// Вызов меню всех песен
	void MenuWAS();
	void MenuWAS(Person* peson, Collection<Song*>(ClassSongs::*songs)(const Person&));

	// Вызов меню поиска
	void SearchMenu();

	// Меню выбора действия над человеком
	void OptionsPersonMenu(Person* person, Collection<Song*>(ClassSongs::*songs)(const Person&), void(ClassSongs::*change)(const Person&, const Person&));

	// Меню выбора действия над песней
	void OptionsSongMenu(Song* song);

	// Меню информации о поэте
	void InfoPerson(Person* person);

	// Меню информации о песне
	void InfoSong(const Song* song);

	// Меню редактирования песни
	void RedactSong(Song* song);

	// Меню редактирования информации о поэте
	void RedactPeron(Person* person, void(ClassSongs::*change)(const Person&, const Person&));

	// Проигрыватель
	void PlaySong(const Song* song);

	//Меню добавления песни
	void AddSong();

	// Деструктор ------------------------------------------------------------
	~Interface();

private:
	// Поля класса -----------------------------------------------------------
	std::unique_ptr<ClassSongs> Archive; // Хранилище
	std::unique_ptr<ClassMenu> Menu; // Указатель на меню
	

};

