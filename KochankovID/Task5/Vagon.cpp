#include "Vagon.h"


Vag::Vag(const string& Type_, Place * pl, const int & lenth) : type(Type_), TypesOfPlaces(lenth)
{
	places = new Place[TypesOfPlaces];
	for (int i = 0; i < TypesOfPlaces; i++) {
		places[i] = pl[i];
	}
}

Vag::Vag() : type(), TypesOfPlaces()
{
}

Vag::Vag(const Vag & copy)
{
	type = copy.type;
	TypesOfPlaces = copy.TypesOfPlaces;
	places = new Place[TypesOfPlaces];
	for (int i = 0; i < TypesOfPlaces; i++) {
		places[i] = copy.places[i];
	}
}

void Vag::addPlace(Place * p, const int & lenth)
{
	if (TypesOfPlaces != 0) {
		Place* copy = new Place[TypesOfPlaces];
		for (int i = 0; i < TypesOfPlaces; i++) {
			copy[i] = places[i];
		}
		delete[] places;
		places = new Place[TypesOfPlaces + lenth];
		for (int i = 0; i < TypesOfPlaces; i++) {
			places[i] = copy[i];
		}
		for (int i = TypesOfPlaces; i < TypesOfPlaces + lenth; i++) {
			places[i] = p[i];
		}
		TypesOfPlaces += lenth;
	}
	else {
		TypesOfPlaces += lenth;
		places = new Place[TypesOfPlaces + lenth];
		for (int i = 0; i < TypesOfPlaces + lenth; i++) {
			places[i] = p[i];
		}
	}
}
void Vag::addPlace(const Place & p)
{
	if (TypesOfPlaces != 0) {
		Place* copy = new Place[TypesOfPlaces];
		for (int i = 0; i < TypesOfPlaces; i++) {
			copy[i] = places[i];
		}
		delete[] places;
		places = new Place[TypesOfPlaces + 1];
		for (int i = 0; i < TypesOfPlaces; i++) {
			places[i] = copy[i];
		}
		places[TypesOfPlaces] = p;
		TypesOfPlaces++;
	}
	else {
		TypesOfPlaces++;
		places = new Place[TypesOfPlaces];
		places[TypesOfPlaces - 1] = p;
	}
}
void Vag::removePlaces(const string* s, const int & lenth)
{
	for (int i = 0; i < TypesOfPlaces; i++) {
		for (int u = 0; u < lenth; u++) {
			if (places[i].GetType() == s[u]) {
				for (int j = i; j < TypesOfPlaces - 1; j++) {
					places[j] = places[j + 1];
				}
				TypesOfPlaces--;
			}
		}
	}
}
void Vag::removePlacesAt(const int & n)
{
	if ((n < 0) || (n > TypesOfPlaces)) {
		throw Vag::VagonExeption("Задана неверная позиция удаления!");
	}
	for (int j = n; j < TypesOfPlaces - 1; j++) {
		places[j] = places[j + 1];
	}
	TypesOfPlaces--;
}
Place & Vag::operator[](const int & i)
{
	if ((i < 0) || (i > TypesOfPlaces)) {
		throw Vag::VagonExeption("Индекс выходит за границы поездов!");
	}
	return places[i];
}
const Place & Vag::operator[](const int & i) const
{
	if ((i < 0) || (i > TypesOfPlaces)) {
		throw Vag::VagonExeption("Индекс выходит за границы поездов!");
	}
	return places[i];
}
Vag * Vag::operator=(const Vag & copy)
{
	type = copy.type;
	TypesOfPlaces = copy.TypesOfPlaces;
	places = new Place[TypesOfPlaces];
	for (int i = 0; i < TypesOfPlaces; i++) {
		places[i] = copy.places[i];
	}
	return this;
}
Vag::~Vag()
{
	delete[] places;
	places = nullptr;
}
;

std::ostream & operator<<(std::ostream & stream, const Place & C)
{
	stream << C.typePlace << std::endl;
	stream << C.kolPlace << std::endl;
	stream << std::endl;
	return stream;
}

std::istream & operator>>(std::istream & stream, Place & C)
{
	stream >> C.typePlace;
	stream >> C.kolPlace;
	return stream;
}

std::ostream & operator<<(std::ostream & stream, const Vag & C)
{
	stream << C.type << std::endl;
	stream << C.TypesOfPlaces << std::endl;
	for (int i = 0; i < C.TypesOfPlaces; i++) {
		stream << C.places[i] << " ";
	}
	stream << std::endl;
	return stream;
}

std::istream & operator>>(std::istream & stream, Vag & C)
{
	stream >> C.type;
	stream >> C.TypesOfPlaces;
	for (int i = 0; i < C.TypesOfPlaces; i++) {
		stream >> C.places[i];
	}
	return stream;
}
