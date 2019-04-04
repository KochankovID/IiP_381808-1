#include "Person.h"
#include <boost_1_69_0/boost/algorithm/string/replace.hpp>


Person::Person(const std::string & Name_,
	const std::string & Female_,
	const std::string & Biography_,
	const int & age_) :
	name(Name_), female(Female_),
	biography(Biography_),
	age(age_)
{
	// Если возраст не в ходит в диопазон жизни человека вызывается исключение
	if ((age < 0) || (age > 200)) {
		throw AgeError("Задан невозможный возраст!");
	}
}

Person::Person(const Person & copy)
{
	name = copy.name;
	female = copy.female;
	biography = copy.biography;
	age = copy.age;
	std::cout << "Copy";
}

Person::~Person()
{
	age = 0;
}

Person::AgeError::AgeError(const std::string & Message_) : 
	out_of_range(Message_)
{
}

Person::AgeError::~AgeError()
{
}

std::ostream & operator<<(std::ostream & stream, const Person & C)
{
	std::string name = C.name;
	std::string female = C.female;
	std::string biography = C.biography;
	boost::replace_all(name, std::string(" "), std::string("#&@"));
	boost::replace_all(female, std::string(" "), std::string("#&@"));
	boost::replace_all(biography, std::string(" "), std::string("#&@"));

	stream << name << ' ' << female << ' ' << biography << ' ' 
		<< C.age <<std::endl;

	return stream;
}

std::istream & operator>>(std::istream & stream, Person & C)
{
	stream >> C.name;
	stream >> C.female;
	stream >> C.biography;
	stream >> C.age;
	if ((C.age < 0) || (C.age > 200)) {
		throw Person::AgeError("Задан невозможный возраст!");
	}
	boost::replace_all(C.name, std::string("#&@"), std::string(" "));
	boost::replace_all(C.female, std::string("#&@"), std::string(" "));
	boost::replace_all(C.biography, std::string("#&@"), std::string(" "));
	return stream;
}

Person * Person::operator=(const Person & copy)
{
	name = copy.name;
	female = copy.female;
	biography = copy.biography;
	age = copy.age;
	return this;
}

bool Person::operator==(const Person & p) const
{
	if ((name != p.name) || (female != p.female) || (biography != p.biography) || (age != age)) {
		return false;
	}
	return true;
}
