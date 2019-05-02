#include "Ticket.h"

std::ostream & operator<<(std::ostream & stream, const Ticket & C)
{
	stream << C.id << ' ' << C.Amaunt << '\n';
	stream << C.Name << ' ' << C.Female << '\n';
	stream << C.KollOfPosition << '\n';
	for (int i = 0; i < C.KollOfPosition; i++) {
		stream << C.Positions[i] << '\n';
	}
	return stream;
}

std::istream & operator>>(std::istream & stream, Ticket & C)
{
	stream >> C.id;
	stream >> C.Amaunt;
	stream >> C.Name;
	stream >> C.Female;
	stream >> C.KollOfPosition;
	C.Positions = new onePosition[C.KollOfPosition];
	for (int i = 0; i < C.KollOfPosition; i++) {
		stream >> C.Positions[i];
	}
	return stream;
}

std::ostream & operator<<(std::ostream & stream, const onePosition & C)
{
	stream << C.Day << ' ' << C.Train << ' ' << C.TypeOfTrain << '\n';
	stream << C.Vagon << ' ' << C.TypeOfVagon << '\n';
	stream << C.Place << ' ' << C.TypeOfPlace << ' ' << C.NamePlace << '\n';
	return stream;
}

std::istream & operator>>(std::istream & stream, onePosition & C)
{
	stream >> C.Day;
	stream >> C.Train;
	stream >> C.TypeOfTrain;
	stream >> C.Vagon;
	stream >> C.TypeOfVagon;
	stream >> C.Place;
	stream >> C.TypeOfPlace;
	stream >> C.NamePlace;
	return stream;
}

Ticket * Ticket::operator=(const Ticket & copy)
{
	id = copy.id;
	Amaunt = copy.Amaunt;
	Name = copy.Name;
	Female = copy.Female;
	KollOfPosition = copy.KollOfPosition;
	for (int i = 0; i < KollOfPosition; i++) {
		Positions[i] = copy.Positions[i];
	}
	return this;
}

onePosition * onePosition::operator=(const onePosition & copy)
{
	Day = copy.Day;
	Train = copy.Train;
	TypeOfTrain = copy.TypeOfTrain;
	Vagon = copy.Vagon;
	TypeOfVagon = copy.TypeOfVagon;
	Place = copy.Place;
	TypeOfPlace = copy.TypeOfPlace;
	NamePlace = copy.NamePlace;
	return this;
}
