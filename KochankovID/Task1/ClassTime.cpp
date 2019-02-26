#include "ClassTime.h"
#include <iostream>

using namespace std;

// Конструктор поумолчанию
Time::Time()
{
	hou_ = min_ = sec_ = 0;
}

// Конструктор копирования
Time::Time(const Time& time)
{
	hou_ = time.getHou();
	min_ = time.getMin();
	sec_ = time.getSec();
}

// Конструктор инициплизатор
Time::Time(int hou, int min, int sec)
{
	hou_ = hou;
	if ((hou_ > 23) || (hou_ < 0)) {
		throw Time::exepOutOfRange("Число часов не может быть таким!", hou_);
	}
	min_ = min;
	if ((min_ > 59) || (min_ < 0)) {
		throw Time::exepOutOfRange("Число минут не может быть таким!", min_);
	}
	sec_ = sec;
	if ((sec_ > 59) || (sec_ < 0)) {
		throw Time::exepOutOfRange("Число секунд не может быть таким!", sec_);
	}
}

// Конструктор привидения типа
Time::Time(std::string data)
{
	hou_ = min_ = sec_ = 0;
	int sdvig = 0;
	if (((hou_ = strToInt(data,sdvig))>23)||(hou_ <0)) {
		throw exepOutOfRange("Число часов не может быть таким!", hou_);
	}
	if (sdvig >= data.length()) {
		throw exepNonAmount("Строка имеет неверный формат!");
	}
	if (((min_ = strToInt(data, sdvig)) > 59) || (min_ < 0)) {
		throw exepOutOfRange("Число минут не может быть таким!", min_);
	}
	if (sdvig >= data.length()) {
		throw exepNonAmount("Строка имеет неверный формат!");
	}
	if (((sec_ = strToInt(data, sdvig)) > 59) || (sec_ < 0)) {
		throw exepOutOfRange("Число секунд не может быть таким!", sec_);
	}
}


// Реализация методов водвращающих значение времени
// Реализация возвращения значения времени в строке
string Time::getTimeString() const
{
	string time("         ");
	int a = hou_, b = min_, c = sec_, kol = 0;
	while (a>0)
	{
		time[kol++] = ((a % 10) + '0');
		a = a / 10;
	}
	time[kol++] = '.';
	while (b > 0)
	{
		time[kol++] = (b % 10) + '0';
		b = b / 10;
	}
	time[kol++] = '.';
	while (c > 0)
	{
		time[kol++] = (c % 10) + '0';
		c = c / 10;
	}
	return time;
}

// Определение функции, которая используется в констркукторе приведения типов, для перевода из строки в число
int Time::strToInt(std::string data, int& sdvig)
{
	int i = 0, num = 0;
	while ((data[i + sdvig] != '.')&&((i + sdvig) < data.length())) {
		if ((data[i + sdvig] < '0') || (data[i + sdvig] > '9')) {
			throw exepNonNumber("Символ в строке не является цифрой!", i+sdvig);
		}
		num = (num * 10) + data[i + sdvig] - '0';
		i++;
	}
	if (i == 0) {
		throw exepNonAmount("Строка имеет неверный формат!");
	}
	sdvig = ++i + sdvig;
	return num;
}

// Определения перегрузок операторов
Time & Time::operator=(const Time & C)
{
	hou_ = C.getHou();
	min_ = C.getMin();
	sec_ = C.getSec();
	return *this;
}

Time Time::operator+(const Time & C)
{
	Time tmp;
	tmp.hou_ = hou_ + C.getHou();
	tmp.min_ = min_ + C.getMin();
	tmp.sec_ = sec_ + C.getSec();
	while (tmp.sec_ > 59) {
		tmp.sec_ = tmp.sec_ - 60;
		tmp.min_++;
	}
	while (tmp.min_ > 59) {
		tmp.min_ = tmp.min_ - 60;
		tmp.hou_++;
	}
	while (tmp.hou_ > 23) {
		tmp.hou_ = tmp.hou_ - 24;
	}

	return tmp;
}

Time Time::operator-(const Time & C)
{
	Time tmp;
	tmp.hou_ = hou_ - C.getHou();
	tmp.min_ = min_ - C.getMin();
	tmp.sec_ = sec_ - C.getSec();

	while (tmp.sec_ < 0) {
		tmp.sec_ = 60 + tmp.sec_;
		tmp.min_--;
	}
	while (tmp.min_ > 59) {
		tmp.min_ = 60 + tmp.min_;
		tmp.hou_--;
	}
	if (tmp.hou_ > 23) {
		tmp.hou_ = 24 - tmp.hou_;
	}

	return tmp;
}

Time Time::operator+(const int & sec)
{
	Time tmp(*this);

	tmp.sec_ += sec;
	if (tmp.sec_ > 59) {
		tmp.sec_ = tmp.sec_ - 60;
		tmp.min_++;
	}
	if (tmp.min_ > 59) {
		tmp.min_ = tmp.min_ - 60;
		tmp.hou_++;
	}
	if (tmp.hou_ > 23) {
		tmp.hou_ = tmp.hou_ - 24;
	}

	return tmp;
}

Time Time::operator-(const int & sec)
{
	Time tmp(*this);
	tmp.sec_ -= sec;

	while (tmp.sec_ < 0) {
		tmp.sec_ = 60 + tmp.sec_;
		tmp.min_--;
	}
	while (tmp.min_ > 59) {
		tmp.min_ = 60 + tmp.min_;
		tmp.hou_--;
	}
	if (tmp.hou_ > 23) {
		tmp.hou_ = 24 - tmp.hou_;
	}

	return tmp;
}

bool Time::operator==(const Time & C) const
{
	if ((hou_ == C.hou_) && (min_ == C.min_) && (sec_ == C.sec_)) {
		return true;
	}
	return false;
}

bool Time::operator!=(const Time & C) const
{
	if ((hou_ == C.hou_) && (min_ == C.min_) && (sec_ == C.sec_)) {
		return false;
	}
	return true;
}

bool Time::operator>(const Time & C) const
{
	int t1 = hou_ * 60 * 60 + min_ * 60 + sec_, t2 = C.hou_ * 60 * 60 + C.min_ * 60 + C.sec_;
	if (t1 > t2) {
		return true;
	}
	return false;
}

bool Time::operator<(const Time & C) const
{
	int t1 = hou_ * 60 * 60 + min_ * 60 + sec_, t2 = C.hou_ * 60 * 60 + C.min_ * 60 + C.sec_;
	if (t1 < t2) {
		return true;
	}
	return false;
}

bool Time::operator>=(const Time & C) const
{
	int t1 = hou_ * 60 * 60 + min_ * 60 + sec_, t2 = C.hou_ * 60 * 60 + C.min_ * 60 + C.sec_;
	if (t1 >= t2) {
		return true;
	}
	return false;
}

bool Time::operator<=(const Time & C) const
{
	int t1 = hou_ * 60 * 60 + min_ * 60 + sec_, t2 = C.hou_ * 60 * 60 + C.min_ * 60 + C.sec_;
	if (t1 <= t2) {
		return true;
	}
	return false;
}



ostream& operator<< (ostream& stream, const Time& C) {
	stream << "Hours : " << C.getHou() << endl;
	stream << "Minutes : " << C.getMin() << endl;
	stream << "Seconds : " << C.getSec() << endl;
	return stream;
}

istream& operator>> (istream& stream, Time& C)
{
	stream >> C.hou_;
	if ((C.hou_ > 23) || (C.hou_ < 0)) {
		throw Time::exepOutOfRange("Число часов не может быть таким!", C.hou_);
	}
	stream >> C.hou_;
	if ((C.min_ > 59) || (C.min_ < 0)) {
		throw Time::exepOutOfRange("Число минут не может быть таким!", C.min_);
	}
	if ((C.sec_ > 59) || (C.sec_ < 0)) {
		throw Time::exepOutOfRange("Число секунд не может быть таким!", C.sec_);
	}
	return stream;

}

// Деструктор
Time::~Time()
{
	hou_ = min_ = sec_ = 0;
}
