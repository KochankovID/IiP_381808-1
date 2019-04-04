#include "ClassSongs.h"
#include <fstream>
#include <string>

using namespace std;

ClassSongs::ClassSongs() : 
	Songs(), file("Saved.txt")
{
	ifstream ofs(file);
	ofs.close();
}

ClassSongs::ClassSongs(const std::string& file_) : file(file_), Songs()
{
	ifstream fileSaved;
	fileSaved.open(file);
	fileSaved >> Songs;
	fileSaved.close();
}

Collection<Song*> ClassSongs::getNameSongs(std::string name)
{
	Collection<Song*> songs;
	for (int i = 0; i < Songs.Count(); i++) {
		if (Songs[i].NameSong().find(name) != -1) {
			songs.Add(&Songs[i]);
		}
	}
	return songs;
}

Collection<Person*> ClassSongs::getPoets(std::string name)
{
	Collection<Person*> Persons;
	for (int i = 0; i < Songs.Count(); i++) {
		if ((Songs[i].Poet().Name() != "Неизвестно")&&(Songs[i].Poet().Name().find(name) != -1)) {
			int j = 0;
			for (; j < Persons.Count(); j++) {
				if (Songs[i].Poet() == *(Persons[j])) {
					break;
				}
			}
			if (j == Persons.Count()) {
				Persons.Add(&Songs[i].Poet());
			}
		}
	}
	return Persons;
}

Collection<Person*> ClassSongs::getPoets()
{
	Collection<Person*> Persons;
	for (int i = 0; i < Songs.Count(); i++) {
		int j = 0;
		for (; j < Persons.Count(); j++) {
			if (Songs[i].Poet() == *(Persons[j])) {
				break;
			}
		}
		if ((j == Persons.Count()) && (Songs[i].Poet().Name() != "Неизвестно")) {
			Persons.Add(&Songs[i].Poet());
		}
	}
	return Persons;
}

Collection<Person*> ClassSongs::getComositers(std::string name)
{
	Collection<Person*> Persons;
	for (int i = 0; i < Songs.Count(); i++) {
		if ((Songs[i].Compositer().Name() != "Неизвестно") && (Songs[i].Compositer().Name().find(name) != -1)) {
			int j = 0;
			for (; j < Persons.Count(); j++) {
				if (Songs[i].Compositer() == *(Persons[j])) {
					break;
				}
			}
			if (j == Persons.Count()) {
				Persons.Add(&Songs[i].Compositer());
			}
		}
	}
	return Persons;
}

Collection<Person*> ClassSongs::getComositers()
{
	Collection<Person*> Persons;
	for (int i = 0; i < Songs.Count(); i++) {
		int j = 0;
		for (; j < Persons.Count(); j++) {
			if (Songs[i].Compositer() == *(Persons[j])) {
				break;
			}
		}
		if ((j == Persons.Count()) && (Songs[i].Compositer().Name() != "Неизвестно")) {
			Persons.Add(&Songs[i].Compositer());
		}
	}
	return Persons;
}

Collection<Person*> ClassSongs::getExecutorts(std::string name)
{
	Collection<Person*> Persons;
	for (int i = 0; i < Songs.Count(); i++) {
		if ((Songs[i].Executor().Name() != "Неизвестно") && (Songs[i].Executor().Name().find(name) != -1)) {
			int j = 0;
			for (; j < Persons.Count(); j++) {
				if (Songs[i].Executor() == *(Persons[j])) {
					break;
				}
			}
			if (j == Persons.Count()) {
				Persons.Add(&Songs[i].Executor());
			}
		}
	}
	return Persons;
}

Collection<Person*> ClassSongs::getExecutorts()
{
	Collection<Person*> Persons;
	for (int i = 0; i < Songs.Count(); i++) {
		int j = 0;
		for (; j < Persons.Count(); j++) {
			if (Songs[i].Executor() == *(Persons[j])) {
				j = -1;
				break;
			}
		}
		if ((j == Persons.Count())&&(Songs[i].Executor().Name() != "Неизвестно")) {
			Persons.Add(&Songs[i].Executor());
		}
	}
	return Persons;
}

Collection<Song*> ClassSongs::getAllPoetSongs(const Person & poet)
{
	Collection<Song*> songs;
	for (int i = 0; i < Songs.Count(); i++) {
		if (Songs[i].Poet() == poet) {
			songs.Add(&Songs[i]);
		}
	}
	return songs;
}

Collection<Song*> ClassSongs::getAllCompositerSongs(const Person & compositer)
{
	Collection<Song*> songs;
	for (int i = 0; i < Songs.Count(); i++) {
		if (Songs[i].Compositer() == compositer) {
			songs.Add(&Songs[i]);
		}
	}
	return songs;
}

Collection<Song*> ClassSongs::getAllExecutorSongs(const Person & executor)
{
	Collection<Song*> songs;
	for (int i = 0; i < Songs.Count(); i++) {
		if (Songs[i].Executor() == executor) {
			songs.Add(&Songs[i]);
		}
	}
	return songs;
}

void ClassSongs::ChangeAllPoets(const Person & poet, const Person& poet1)
{
	for (int i = 0; i < Songs.Count(); i++) {
		if (Songs[i].Poet() == poet) {
			Songs[i].Poet() = poet1;
		}
	}
}

void ClassSongs::ChangeAllCompositers(const Person & compositer, const Person& compositer1)
{
	for (int i = 0; i < Songs.Count(); i++) {
		if (Songs[i].Compositer() == compositer) {
			Songs[i].Compositer() = compositer1;
		}
	}
}

void ClassSongs::ChangeAllExecutors(const Person & executor, const Person& executor1)
{
	for (int i = 0; i < Songs.Count(); i++) {
		if (Songs[i].Executor() == executor) {
			Songs[i].Executor() = executor1;
		}
	}
}

void ClassSongs::sort()
{
	Song tmp;
	for (int i = 0; i < Songs.Count(); i++) {
		for (int j = 0; j < Songs.Count()-i-1; j++) {
			if (strcmp(Songs[j].NameSong().c_str(), Songs[j + 1].NameSong().c_str())>0) {
				tmp = Songs[j];
				Songs[j] = Songs[j + 1];
				Songs[j + 1] = tmp;
			}
		}
	}
}

void ClassSongs::saveArchive()
{
	ofstream fileSave;
	fileSave.open(file);
	fileSave << Songs;
	fileSave.close();

}

ClassSongs::~ClassSongs()
{
}

std::ostream & operator<<(std::ostream & stream, const ClassSongs & C)
{
	stream << C.Songs;
	return stream;
}

std::istream & operator>>(std::istream & stream, ClassSongs & C)
{
	stream >> C.Songs;
	return stream;
}
