#include "Interface.h"
#include <fstream>
#include <iostream>
#include <bass.h>
#include <Windows.h>
#include <id3v2lib.h>
#include <boost_1_69_0/boost/lexical_cast.hpp>
#include "..\Task3\ClassMenu.h"

using namespace std;
Interface::Interface(): Archive(new ClassSongs("Saved.txt")), Menu(new ClassMenu())
{
	// Установка нужного шрифта консоли
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX cfie;
	ZeroMemory(&cfie, sizeof(cfie));
	cfie.cbSize = 16;
	lstrcpyW(cfie.FaceName, L"Lucida Console");

	SetCurrentConsoleFontEx(hStdOut, false, &cfie);
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	BASS_Init(-1, 44100, 0, 0, NULL);

}

void Interface::StartMenu()
{
	while (true) {
		Menu->setKol(7);
		(*Menu)[0] = "Поэты";
		(*Menu)[1] = "Композиторы";
		(*Menu)[2] = "Исполнители";
		(*Menu)[3] = "Песни";
		(*Menu)[4] = "Поиск";
		(*Menu)[5] = "Добавить песню";
		(*Menu)[6] = "Выход";
		string title[] = { "Ilya_Player Version 1" };
		int a[] = { 0 };
		(*Menu).DrawCMenu(1, a, title, 0, 0, 2, 2);

		switch ((*Menu).getLastClause()) {
		case 1: MenuWAP();
			break;
		case 2: MenuWAC();
			break;
		case 3: MenuWAE();
			break;
		case 4: MenuWAS();
			break;
		case 5: SearchMenu();
			break;
		case 6: try {
			AddSong();
		}
				catch (std::runtime_error e) {
					cout << e.what();
					getchar();
		}
			break;
		case 7: (*Archive).saveArchive();
			return;
			break;
		}
	}
}

void Interface::MenuWAP()
{
	Collection<string> titles;
	titles.Add("Исполнители");
	Collection<int> nums;
	nums.Add(0);
	Collection<Person*> Poets = (*Archive).getPoets();
	(*Menu).setKol(Poets.Count()+1);
	for (int i = 0; i < Poets.Count(); i++) {
		(*Menu)[i] = "Имя: " + Poets[i]->Name() + " Фамилия: " + Poets[i]->Female() + " Возраст: " + std::to_string(Poets[i]->Age());
	}
	if (Poets.Count() == 0) {
		(*Menu).setKol(1);
		(*Menu)[0] = "Поэты не найдены!";
	}
	else {
		titles.Add("--------------------------------------------");
		nums.Add(Poets.Count());
		(*Menu)[Poets.Count()] = "Назад";
	}
	(*Menu).DrawCMenu(nums.Count(), nums.AsArray(), titles.AsArray(),0,0,1,2);
	if ((*Menu).getLastClause() != (Poets.Count()+1)) {
		OptionsPersonMenu(Poets[(*Menu).getLastClause()-1], &ClassSongs::getAllPoetSongs, &ClassSongs::ChangeAllPoets);
		return;
	}
}

void Interface::MenuWAC()
{
	Collection<string> titles;
	titles.Add("Композиторы ");
	Collection<int> nums;
	nums.Add(0);
	Collection<Person*> Compositers = (*Archive).getComositers();
	(*Menu).setKol(Compositers.Count() + 1);
	for (int i = 0; i < Compositers.Count(); i++) {
		(*Menu)[i] ="Имя: " + Compositers[i]->Name() + " Фамилия: " + Compositers[i]->Female() + " Возраст: " + std::to_string(Compositers[i]->Age());
	}
	if (Compositers.Count() == 0) {
		(*Menu).setKol(1);
		(*Menu)[0] = "Композиторы не найдены!";
	}
	else {
		(*Menu)[Compositers.Count()] = "Назад";
		titles.Add("--------------------------------------------");
		nums.Add(Compositers.Count());
	}
	(*Menu).DrawCMenu(nums.Count(), nums.AsArray(), titles.AsArray(), 0, 0, 1, 2);
	if ((*Menu).getLastClause() != (Compositers.Count() + 1)) {
		OptionsPersonMenu(Compositers[(*Menu).getLastClause()-1], &ClassSongs::getAllCompositerSongs, &ClassSongs::ChangeAllCompositers);
		return;
	}
}

void Interface::MenuWAE()
{
	Collection<string> titles;
	titles.Add("Исполнители");
	Collection<int> nums;
	nums.Add(0);
	Collection<Person*> Executors = (*Archive).getExecutorts();
	(*Menu).setKol(Executors.Count() + 1);
	for (int i = 0; i < Executors.Count(); i++) {
		(*Menu)[i] = "Имя: "+Executors[i]->Name() + " Фамилия: " + Executors[i]->Female() + " Возраст: " + std::to_string(Executors[i]->Age());
	}
	if (Executors.Count() == 0) {
		(*Menu).setKol(1);
		(*Menu)[0] = "Исполнители не найдены!";
	}
	else {
		titles.Add("--------------------------------------------");
		nums.Add(Executors.Count());
		(*Menu)[Executors.Count()] = "Назад";
	}
	(*Menu).DrawCMenu(nums.Count(), nums.AsArray(), titles.AsArray(), 0, 0, 1, 2);
	if ((*Menu).getLastClause() != (Executors.Count() + 1)) {
		OptionsPersonMenu(Executors[(*Menu).getLastClause()-1], &ClassSongs::getAllExecutorSongs, &ClassSongs::ChangeAllExecutors);
		return;
	}
}

void Interface::MenuWAS()
{
	Collection<Song>& Songs = (*Archive).songs();
	Collection<string> titles;
	titles.Add("Песен: " + std::to_string(Songs.Count()));
	Collection<int> nums;
	nums.Add(0);
	(*Menu).setKol(Songs.Count() + 1);

	for (int i = 0; i < Songs.Count(); i++) {
		(*Menu)[i] = Songs[i].NameSong() + " Альбом: " + Songs[i].Album() + " Исполнитель: " + Songs[i].Executor().Name() +
			" Поэт: " + Songs[i].Poet().Name() + " Композитор: " + Songs[i].Compositer().Name();
	}
	if (Songs.Count() == 0) {
		(*Menu).setKol(1);
		(*Menu)[0] = "Песни не найдены!";
	}
	else {
		titles.Add("--------------------------------------------");
		nums.Add(Songs.Count());
		(*Menu)[Songs.Count()] = "Назад";
	}
	(*Menu).DrawCMenu(nums.Count(), nums.AsArray(), titles.AsArray(), 0, 0, 1, 2);
	if ((*Menu).getLastClause() != (Songs.Count() + 1)) {
		OptionsSongMenu(&Songs[(*Menu).getLastClause()-1]);
		return;
	}
}

void Interface::MenuWAS(Person * peson, Collection<Song*>(ClassSongs::*songs)(const Person&))
{
	Collection<string> titles;
	titles.Add("Песни");
	Collection<int> nums;
	nums.Add(0);
	Collection<Song*> Songs = (Archive._Myptr()->*songs)(*peson);
	(*Menu).setKol(Songs.Count() + 1);

	for (int i = 0; i < Songs.Count(); i++) {
		(*Menu)[i] = Songs[i]->NameSong() + " Альбом: " + Songs[i]->Album() + " Исполнитель: " + Songs[i]->Executor().Name() +
			" Поэт: " + Songs[i]->Poet().Name() + " Композитор: " + Songs[i]->Compositer().Name();
	}
	if (Songs.Count() == 0) {
		(*Menu).setKol(1);
		(*Menu)[0] = "Песни не найдены!";
	}
	else {
		titles.Add("--------------------------------------------");
		nums.Add(Songs.Count());
		(*Menu)[Songs.Count()] = "Назад";
	}
	(*Menu).DrawCMenu(nums.Count(), nums.AsArray(), titles.AsArray(), 0, 0, 1, 2);
	if ((*Menu).getLastClause() != (Songs.Count() + 1)) {
		PlaySong(Songs[(*Menu).getLastClause()-1]);
		return;
	}
}

void Interface::SearchMenu()
{
	Collection<string> titles;
	Collection<int> nums;
	titles.Add("Поиск");
	nums.Add(0);
	cout << "Песни, исполнители, композиторы, поэты... :";
	string str;
	std::getline(cin, str);
	while (0 == str.find(' '))
		str.erase(0, 1);

	Collection<Song*> Songs = (*Archive).getNameSongs(str);
	Collection<Person*> Poets = (*Archive).getPoets(str);
	Collection<Person*> Compositers = (*Archive).getComositers(str);
	Collection<Person*> Executors = (*Archive).getExecutorts(str);

	(*Menu).setKol(Songs.Count()+Poets.Count()+Compositers.Count()+Executors.Count() + 1);
	for (int i = 0; i < Songs.Count(); i++) {
		(*Menu)[i] = Songs[i] ->NameSong() + " Альбом: " + Songs[i] ->Album();
	}

	if (Songs.Count() != 0) {
		titles.Add("Песни: ");
		nums.Add(0);
	}

	for (int i = 0; i < Poets.Count(); i++) {
		(*Menu)[Songs.Count() + i] = "Имя: " + (*Poets[i]).Name() + " Фамилия: " + (*Poets[i]).Female() + " Возраст: " + std::to_string((*Poets[i]).Age());
	}

	if (Poets.Count() != 0) {
		titles.Add("Поэты: ");
		nums.Add(Songs.Count());
	}

	for (int i = 0; i < Compositers.Count(); i++) {
		(*Menu)[Songs.Count() + Poets.Count()+i] = "Имя: " + (*Compositers[i]).Name() + " Фамилия: " + (*Compositers[i]).Female() + " Возраст: " + std::to_string((*Compositers[i]).Age());
	}

	if (Compositers.Count() != 0) {
		titles.Add("Композиторы: ");
		nums.Add(Songs.Count() + Poets.Count());
	}

	for (int i = 0; i < Executors.Count(); i++) {
		(*Menu)[Songs.Count()+Compositers.Count() + Poets.Count() + i] = "Имя: " + (*Executors[i]).Name() + " Фамилия: " + (*Executors[i]).Female() + " Возраст: " + std::to_string((*Executors[i]).Age());
	}

	if (Executors.Count() != 0) {
		titles.Add("Исполнители: ");
		nums.Add(Compositers.Count() + Songs.Count() + Poets.Count());
	}


	if (Executors.Count() + Compositers.Count() + Songs.Count() + Poets.Count() == 0) {
		(*Menu).setKol(1);
		(*Menu)[0] = "Ничего не найденно!";
	}
	else {
		titles.Add("--------------------------------------------");
		nums.Add(Compositers.Count() + Songs.Count() + Poets.Count()+Executors.Count());
		(*Menu)[Executors.Count() + Compositers.Count() + Songs.Count() + Poets.Count()] = "Назад";
	}

	(*Menu).DrawCMenu(nums.Count(), nums.AsArray(), titles.AsArray(), 0, 0, 1, 1);

	if ((*Menu).getLastClause() != (Executors.Count() + Compositers.Count() + Songs.Count() + Poets.Count()+1)) {
		if ((*Menu).getLastClause() <= Songs.Count()) {
			OptionsSongMenu(Songs[(*Menu).getLastClause()-1]);
		}
		else {
			if ((*Menu).getLastClause() <= (Songs.Count() + Poets.Count())) {
				OptionsPersonMenu(Poets[(*Menu).getLastClause()-1-Songs.Count()], &ClassSongs::getAllPoetSongs, &ClassSongs::ChangeAllPoets);
			}
			else {
				if ((*Menu).getLastClause() <= (Songs.Count() + Poets.Count() + Compositers.Count())) {
					OptionsPersonMenu(Compositers[(*Menu).getLastClause()-1- Songs.Count()-Poets.Count()], &ClassSongs::getAllCompositerSongs, &ClassSongs::ChangeAllCompositers);
				}
				else {
						OptionsPersonMenu(Executors[(*Menu).getLastClause()-1 - Songs.Count() - Poets.Count()-Compositers.Count()], &ClassSongs::getAllExecutorSongs, &ClassSongs::ChangeAllExecutors);
				}
			}
		}
		return;
	}
}

void Interface::OptionsPersonMenu(Person* person, Collection<Song*>(ClassSongs::*songs)(const Person&), void(ClassSongs::*change)(const Person&, const Person&))
{
	Collection<string> titles;
	Collection<int> nums;
	titles.Add("Опции");
	nums.Add(0);

	Menu->setKol(5);
	(*Menu)[0] = "Посмотреть информацию";
	(*Menu)[1] = "Редактировать информацию";
	(*Menu)[2] = "Показать все песни";
	(*Menu)[3] = "Удалить";
	(*Menu)[4] = "Выход в меню";
	(*Menu).DrawCMenu(1, nums.AsArray(), titles.AsArray(), 0, 0, 2, 2);

	Person copy(*person);
	Person deleter;
	switch ((*Menu).getLastClause()) {
	case 1: InfoPerson(person);
		break;
	case 2: RedactPeron(person, change);
		break;
	case 3: MenuWAS(person,songs);
		break;
	case 4: 
		(Archive._Myptr()->*change)(copy, deleter);
		Archive->saveArchive();
		break;
	case 5: return;
		break;
	}
}

void Interface::OptionsSongMenu(Song* song)
{
	Collection<string> titles;
	Collection<int> nums;
	titles.Add("Опции");
	nums.Add(0);

	Menu->setKol(5);
	(*Menu)[0] = "Воспризвести";
	(*Menu)[1] = "Посмотреть информацию";
	(*Menu)[2] = "Редактировать информацию";
	(*Menu)[3] = "Удалить";
	(*Menu)[4] = "Выход в меню";
	(*Menu).DrawCMenu(1, nums.AsArray(), titles.AsArray(), 0, 0, 2, 2);

	switch ((*Menu).getLastClause()) {
	case 1: PlaySong(song);
		break;
	case 2: InfoSong(song);
		break;
	case 3: RedactSong(song);
		break;
	case 4:
		(*Archive).songs().Remove(*song);
		Archive->saveArchive();
		break;
	case 5: return;
		break;
	}
}

void Interface::InfoPerson(Person * person)
{
	Collection<string> titles;
	Collection<int> nums;
	titles.Add("Информация");
	nums.Add(0);
	(*Menu).setKol(1);
	(*Menu)[0] = "Имя: " + person->Name() + "\nФамилия: "+ person->Female()
		+ "\nВозраст: " + std::to_string(person->Age())+"\nБиография: " + person->Biography();
	(*Menu).DrawCMenu(1, nums.AsArray(), titles.AsArray(), 0, 0, 2, 2);
	return;
}

void Interface::InfoSong(const Song * song)
{
	Collection<string> titles;
	Collection<int> nums;
	titles.Add("Информация");
	nums.Add(0);
	(*Menu).setKol(1);
	(*Menu)[0] = "Имя песни: " + song->NameSong() + "\nАльбом: " + song->Album()
		+ "\nДата релиза: " + song->DataRelease().ToString() + "\nПуть до песни: " + song->Location();
	(*Menu).DrawCMenu(1, nums.AsArray(), titles.AsArray(), 0, 0, 2, 2);
	return;
}

void Interface::RedactSong(Song * song)
{
	Collection<string> titles;
	Collection<int> nums;
	titles.Add("Редактирование информации");
	nums.Add(0);
	while (true) {

		Menu->setKol(8);
		(*Menu)[0] = "Имя песни: " + song->NameSong();
		(*Menu)[1] = "Альбом: " + song->Album();
		(*Menu)[2] = "Дата релиза: " + song->DataRelease().ToString();
		(*Menu)[3] = "Путь: " + song->Location();
		(*Menu)[4] = "Поэт: " + song->Poet().Name() + " " + song->Poet().Female();
		(*Menu)[5] = "Композитор: " + song->Compositer().Name() + " " + song->Compositer().Female();
		(*Menu)[6] = "Исполнитель: " + song->Executor().Name() + " " + song->Executor().Female();
		(*Menu)[7] = "Выход в меню";
		(*Menu).DrawCMenu(1, nums.AsArray(), titles.AsArray(), 0, 0, 2, 2);

		switch ((*Menu).getLastClause()) {
		case 1: cout << "Введите имя песни: ";
			std::getline(cin, song->NameSong());

			break;
		case 2: cout << "Введите альбом: ";
			std::getline(cin, song->Album());
			
			break;
		case 3: cout << "Введите дату релиза: ";
			try {
				cin >> song->DataRelease();
			}
			catch (Data::InvalideData e) {
				cout << e.what();
				
			}
			break;
			
		case 4: cout << "Введите путь: ";
			std::getline(cin, song->Location());
			
			break;
		case 5: RedactPeron(&song->Poet(), &ClassSongs::ChangeAllPoets);
			break;
		case 6: RedactPeron(&song->Compositer(), &ClassSongs::ChangeAllCompositers);
			break;
		case 7: RedactPeron(&song->Executor(), &ClassSongs::ChangeAllExecutors);
			break;
		case 8:
			Archive->sort();
			Archive->saveArchive();
			return;
			break;
		}
	}
}

void Interface::RedactPeron(Person * person, void(ClassSongs::*change)(const Person&, const Person&))
{
	Person copy = *person;
	while (true) {
		Collection<string> titles;
		Collection<int> nums;
		titles.Add("Редактирование информации");
		nums.Add(0);

		Menu->setKol(5);
		(*Menu)[0] = "Имя: " + person->Name();
		(*Menu)[1] = "Фамилия: " + person->Female();
		(*Menu)[2] = "Возраст: " + std::to_string(person->Age());
		(*Menu)[3] = "Биография: " + person->Biography();
		(*Menu)[4] = "Назад";
		(*Menu).DrawCMenu(1, nums.AsArray(), titles.AsArray(), 0, 0, 2, 2);

		switch ((*Menu).getLastClause()) {
		case 1: cout << "Введите имя: ";
			std::getline(cin,person->Name());
			
			break;
		case 2: cout << "Введите фамилию: ";
			std::getline(cin, person->Female());
			
			break;
		case 3: cout << "Введите возраст: ";
			try {
				cin >> person->Age();
			}
			catch (Person::AgeError e) {
				cout << e.what();
				
			}
			cin.ignore(cin.rdbuf()->in_avail());
			break;
		case 4:cout << "Введите Биографию: ";
			std::getline(cin, person->Biography());
			
			break;
		case 5: 	
			(Archive._Myptr()->*change)(copy, *person);
			Archive->saveArchive();
			return;
			break;
		}
	}
}

void Interface::PlaySong(const Song * song)
{

	HSTREAM stream;	/* дескриптор потока */
	stream = BASS_StreamCreateFile(FALSE, song->Location().c_str(), 0, 0, 0);
	if (!stream) {
		stream = BASS_StreamCreateURL(song->Location().c_str(), 0, 0, NULL, 0);
		if (!stream) {
			throw std::runtime_error("По указанному пути не удалось найти файл!");
		}
	}
	/* воспроизводим звук */
	BASS_ChannelPlay(stream, TRUE);
	string butt = "||";
	while (true) {
		(*Menu).setKol(2);
		(*Menu)[0] = butt;
		(*Menu)[1] = "Выход";
		(*Menu).DrawMenuH(3, 10, 5);
		switch ((*Menu).getLastClause()) {
		case 1: butt == "||" ? butt = "|>" : butt = "||";
			if (butt == "|>") {
				/* останавливаем звучание */
				BASS_ChannelPause(stream);
			}
			else {
				/* возобновляем звучание */
				BASS_ChannelPlay(stream, false);
			}
			break;
		case 2: 
			/* останавливаем звучание */
			BASS_ChannelStop(stream);
			/* освобождаем ресурсы */
			BASS_StreamFree(stream);
			return;
			break;
		}
	}
}

void Interface::AddSong()
{
	Song newSong;
	cout << "Введите адрес / ссылку на песню: ";
	std::getline(cin,newSong.Location());

	ID3v2_tag* tag = load_tag(newSong.Location().c_str()); // Load the full tag from the file
	if (tag == NULL)
	{
		throw std::runtime_error("Файл, заданный пользователем имеет неверный формат!");
	}
	string o;

	ID3v2_frame* NameSong = tag_get_title(tag);
	if (NameSong != NULL) {
		ID3v2_frame_text_content* Namesongs = parse_text_frame_content(NameSong);
		o = Namesongs->data;
		o = o.substr(0, Namesongs->size);
		newSong.NameSong() = o;
	}


	ID3v2_frame* artist_frame = tag_get_artist(tag); 
	ID3v2_frame_text_content* Executor = parse_text_frame_content(artist_frame);
	o = Executor->data;
	if (Executor != NULL) {
		o = o.substr(0, Executor->size);
		newSong.Executor().Name() = o;
	}

	ID3v2_frame* Album = tag_get_album(tag);
	if (Album != NULL) {
		ID3v2_frame_text_content* Album_ = parse_text_frame_content(Album);
		o = Album_->data;
		o = o.substr(0, Album_->size);
		newSong.Album() = o;
	}

	ID3v2_frame* Compositer = tag_get_composer(tag);
	if (Compositer != NULL) {
		ID3v2_frame_text_content* Compositer_ = parse_text_frame_content(Compositer);
		o = Compositer_->data;
		o = o.substr(0, Compositer_->size);
		newSong.Compositer().Name() = o;
	}
	Archive->songs().Add(newSong);
	RedactSong(&Archive->songs()[Archive->songs().Find(newSong)]);
}


Interface::~Interface()
{
	(*Archive).saveArchive();
	Menu.reset();
	Archive.reset();
}
