#include "Data.h"

Data::Data(const int& day_, const int& month_, const int& year_) : day(day_),
month(month_), year(year_) {
	IsRight();
}


Data * Data::operator=(const Data & copy)
{
	year = copy.year;
	month = copy.month;
	day = copy.day;
	IsRight();
	return this;
}

bool Data::operator==(const Data & p) const
{
	if ((day == p.day) && (month == p.month) && (year == p.year)) {
		return true;
	}
	return false;
}

Data::~Data()
{
	day = 0; month = 0; year = 0;
}

void Data::IsRight() const
{
	if ((day < 0) || (day > 31)) {
		throw Data::InvalideData("Неверный формат дней!");
	}
	if ((month < 0) || (month > 12)) {
		throw Data::InvalideData("Неверный формат месяцев!");
	}
	if (year < 0) {
		throw Data::InvalideData("Неверный формат годов!");
	}
}

std::ostream & operator<<(std::ostream & stream, const Data & C)
{
	stream << C.day << ' ' << C.month << ' ' << C.year << std::endl;
	return stream;
}

std::istream & operator>>(std::istream & stream, Data & C)
{
	stream >> C.day;
	stream >> C.month;
	stream >> C.year;
	C.IsRight();
	return stream;
}

Data::InvalideData::InvalideData(const std::string& Message_) : out_of_range(Message_)
{
}

Data::InvalideData::~InvalideData()
{
}
