#include "Day.h"



Day::Day() : KollOfTrains(0)
{
	trains = new Train[0];
}

Day::Day(const Train * trains_, const int & lenght) : KollOfTrains(lenght)
{
	trains = new Train[KollOfTrains];
	for (int i = 0; i < KollOfTrains; i++) {
		trains[i] = trains_[i];
	}
}

Day::Day(const Day & copy)
{
	KollOfTrains = copy.KollOfTrains;
	trains = new Train[KollOfTrains];
	for (int i = 0; i < KollOfTrains; i++) {
		trains[i] = copy.trains[i];
	}
}

void Day::addTrain(Train * v, const int & lenth)
{
	Train* copy = new Train[KollOfTrains];
	for (int i = 0; i < KollOfTrains; i++) {
		copy[i] = trains[i];
	}
	delete[] trains;
	trains = new Train[KollOfTrains + lenth];
	for (int i = 0; i < KollOfTrains; i++) {
		trains[i] = copy[i];
	}
	for (int i = KollOfTrains; i < KollOfTrains + lenth; i++) {
		trains[i] = v[i];
	}
	KollOfTrains += lenth;
}

void Day::addTrain(const Train & v)
{
	Train* copy = new Train[KollOfTrains];
	for (int i = 0; i < KollOfTrains; i++) {
		copy[i] = trains[i];
	}
	delete[] trains;
	trains = new Train[KollOfTrains + 1];
	for (int i = 0; i < KollOfTrains; i++) {
		trains[i] = copy[i];
	}
	trains[KollOfTrains] = v;
	KollOfTrains++;
}

void Day::removeTrain(const string * v, const int & lenth)
{
	for (int i = 0; i < KollOfTrains; i++) {
		for (int u = 0; u < lenth; u++) {
			if (trains[i].getName() == v[u]) {
				for (int j = i; j < KollOfTrains - 1; j++) {
					trains[j] = trains[j + 1];
				}
				KollOfTrains--;
			}
		}
	}
}

void Day::removeTrain(const int & v)
{
	if ((v < 0) || (v > KollOfTrains)) {
		throw Vag::VagonExeption("Задана неверная позиция удаления!");
	}
	for (int j = v; j < KollOfTrains - 1; j++) {
		trains[j] = trains[j + 1];
	}
	KollOfTrains--;
}


Train & Day::operator[](const int & i)
{
	if ((i < 0) || (i > KollOfTrains)) {
		throw Day::DayExeption("Индекс выходит за границы поездов!");
	}
	return trains[i];
}

const Train & Day::operator[](const int & i) const
{
	if ((i < 0) || (i > KollOfTrains)) {
		throw Day::DayExeption("Индекс выходит за границы поездов!");
	}
	return trains[i];
}

Day * Day::operator=(const Day & copy)
{
	delete[] trains;
	KollOfTrains = copy.KollOfTrains;
	trains = new Train[KollOfTrains];
	for (int i = 0; i < KollOfTrains; i++) {
		trains[i] = copy.trains[i];
	}
	return this;
}

Day::~Day()
{
	delete[] trains;
	trains = nullptr;
}

std::ostream & operator<<(std::ostream & stream, const Day & C)
{
	stream << C.KollOfTrains << std::endl;
	for (int i = 0; i < C.KollOfTrains; i++) {
		stream << C.trains[i] << " ";
	}
	stream << std::endl;
	return stream;
}

std::istream & operator>>(std::istream & stream, Day & C)
{
	stream >> C.KollOfTrains;
	for (int i = 0; i < C.KollOfTrains; i++) {
		stream >> C.trains[i];
	}
	return stream;
}
