#include "Song.h"
#include <boost_1_69_0/boost/algorithm/string/replace.hpp>

Song::Song(const std::string & Location_, const std::string & NameSong_, const std::string & Album_,
	const int& day_, const int& month_, const int& year_) : location(Location_), 
	nameSong(NameSong_), album(Album_), dataRelease(day_,month_, year_), poet(), compositer(), executor()
{
}

Song::Song(const Song & copy)
{
	location = copy.location;
	nameSong = copy.nameSong;
	album = copy.album;
	dataRelease = copy.dataRelease;
	poet = copy.poet;
	compositer = copy.compositer;
	executor = copy.executor;
}

bool Song::operator==(const Song & p) const
{
	if ((nameSong == p.nameSong) && (album == p.album) && (location == p.location) && (poet == p.poet)
		&& (compositer == p.compositer) && (executor == p.executor) && (dataRelease == p.dataRelease)) {
		return true;
	}
	return false;
}

Song * Song::operator=(const Song & copy)
{
	location = copy.location;
	nameSong = copy.nameSong;
	album = copy.album;
	dataRelease = copy.dataRelease;
	poet = copy.poet;
	compositer = copy.compositer;
	executor = copy.executor;
	return this;
}

Song::~Song()
{
}

std::ostream & operator<<(std::ostream & stream, const Song & C)
{
	std::string location = C.location;
	std::string nameSong = C.nameSong;
	std::string album = C.album;

	boost::replace_all(location, std::string(" "), std::string("#&@"));
	boost::replace_all(nameSong, std::string(" "), std::string("#&@"));
	boost::replace_all(album, std::string(" "), std::string("#&@"));

	stream << location << ' ' << nameSong << ' ' << album << ' '
		<< C.dataRelease << ' ' << C.poet << ' ' << C.compositer << ' '
		<< C.executor << std::endl;
	return stream;
}

std::istream & operator>>(std::istream & stream, Song & C)
{
	stream >> C.location;
	stream >> C.nameSong;
	stream >> C.album;
	stream >> C.dataRelease;
	stream >> C.poet;
	stream >> C.compositer;
	stream >> C.executor;
	boost::replace_all(C.location, std::string("#&@"), std::string(" "));
	boost::replace_all(C.nameSong, std::string("#&@"), std::string(" "));
	boost::replace_all(C.album, std::string("#&@"), std::string(" "));
	return stream;
}

//void Song::OutSong(const std::string& str) const
//{
//	std::cout << str << std::endl;
//	std::cout << "Песня: " << nameSong << std::endl;
//	std::cout << "Альбом: " << album << std::endl;
//	if (!(poet.Name() == "Неизвестно")) {
//		std::cout << "Поэт: ";
//		poet.OutPerson();
//	}
//	if (!(compositer.Name() == "Неизвестно")) {
//		std::cout << "Композитор: ";
//		compositer.OutPerson();
//	}
//	if (!(executor.Name() == "Неизвестно")) {
//		std::cout << "Исполнитель: ";
//		executor.OutPerson();
//	}
//	if (!(dataRelease.Year() == 0)) {
//		std::cout << "Дата выхода песни: ";
//		dataRelease.OutData();
//	}
//}
