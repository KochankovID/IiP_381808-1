#include "Place.h"



Place::Place() : typePlace(), kolPlace()
{
	plc = new bool[0];
}

Place::Place(const string & name_, const int & count_, const int & amaunt_) : typePlace(name_), kolPlace(count_), amaunt(amaunt_)
{
	plc = new bool[kolPlace];
	for (int i = 0; i < kolPlace; i++) {
		plc[i] = true;
	}
}

Place::Place(const Place & copy)
{
	typePlace = copy.typePlace;
	amaunt = copy.amaunt;
	kolPlace = copy.kolPlace;
	plc = new bool[kolPlace];
	for (int i = 0; i < kolPlace; i++) {
		plc[i] = copy.plc[i];
	}
}

void Place::BuyPlace(const int & p)
{
	if ((p < 0) || (p > kolPlace)) {
		throw Place::PlaceExeption("»ндекс выодит за границы массива!");
	}
	if (!plc[p]) {
		throw Place::PlaceExeption("ћесто уже купленно!");
	}
	plc[p] = false;
}

void Place::UnreservedPlace(const int & p)
{
	if ((p < 0) || (p > kolPlace)) {
		throw Place::PlaceExeption("»ндекс выодит за границы массива!");
	}
	if (!plc[p]) {
		throw Place::PlaceExeption("ћесто не купленно!");
	}
	plc[p] = true;
}

void Place::removePlaces(const int & n)
{
	if ((kolPlace - n) < 0) {
		throw Place::PlaceExeption("—уществующих мест меньше чем удал¤емых мест!");
	}
	kolPlace -= n;
	bool* copy = new bool[kolPlace];
	for (int i = 0; i < kolPlace; i++) {
		copy[i] = plc[i];
	}
	delete[] plc;
	plc = copy;
}

bool & Place::operator[](const int & i)
{
	if ((i < 0) || (i > kolPlace)) {
		throw Place::PlaceExeption("»ндекс выодит за границы массива!");
	}
	return plc[i];
}

const bool & Place::operator[](const int & i) const
{
	if ((i < 0) || (i > kolPlace)) {
		throw Place::PlaceExeption("»ндекс выодит за границы массива!");
	}
	return plc[i];
}

Place * Place::operator=(const Place & copy)
{
	delete[] plc;
	typePlace = copy.typePlace;
	amaunt = copy.amaunt;
	kolPlace = copy.kolPlace;
	plc = new bool[kolPlace];
	for (int i = 0; i < kolPlace; i++) {
		plc[i] = copy.plc[i];
	}
	return this;
}


Place::~Place()
{
	delete[] plc;
	plc = nullptr;
}
