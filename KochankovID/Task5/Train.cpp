#include "Train.h"



Train::Train() : kollofVags(0), nameTrain()
{
	Vags = new Vag[0];
}

Train::Train(const string & name_, const int & count_) : kollofVags(count_), nameTrain(name_)
{
	Vags = new Vag[kollofVags];
}

Train::Train(const string & name_, const int & count_, Vag * Vags_) : kollofVags(count_), nameTrain(name_)
{
	Vags = new Vag[kollofVags];
	for (int i = 0; i < kollofVags; i++) {
		Vags[i] = Vags_[i];
	}
}

Train::Train(const Train & copy)
{
	nameTrain = copy.nameTrain;
	kollofVags = copy.kollofVags;
	Vags = new Vag[kollofVags];
	for (int i = 0; i < kollofVags; i++) {
		Vags[i] = copy.Vags[i];
	}
}


void Train::addVagon(Vag * v, const int & lenth)
{
	if (kollofVags != 0) {
		Vag* copy = new Vag[kollofVags];
		for (int i = 0; i < kollofVags; i++) {
			copy[i] = Vags[i];
		}
		delete[] Vags;
		Vags = new Vag[kollofVags + lenth];
		for (int i = 0; i < kollofVags; i++) {
			Vags[i] = copy[i];
		}
		for (int i = kollofVags; i < kollofVags + lenth; i++) {
			Vags[i] = v[i];
		}
		kollofVags += lenth;
	}
	else {
		kollofVags += lenth;
		Vags = new Vag[kollofVags];
		for (int i = 0; i < kollofVags; i++) {
			Vags[i] = v[i];
		}
	}
}

void Train::addVagon(const Vag & v)
{
	if (kollofVags != 0) {
		Vag* copy = new Vag[kollofVags];
		for (int i = 0; i < kollofVags; i++) {
			copy[i] = Vags[i];
		}
		delete[] Vags;
		Vags = new Vag[kollofVags + 1];
		for (int i = 0; i < kollofVags; i++) {
			Vags[i] = copy[i];
		}
		Vags[kollofVags] = v;
		kollofVags++;
	}
	else {
		kollofVags++;
		Vags = new Vag[kollofVags];
		Vags[kollofVags - 1] = v;
	}
}

void Train::removeVagon(const string * v, const int & lenth)
{
	for (int i = 0; i < kollofVags; i++) {
		for (int u = 0; u < lenth; u++) {
			if (Vags[i].GetType() == v[u]) {
				for (int j = i; j < kollofVags - 1; j++) {
					Vags[j] = Vags[j + 1];
				}
				kollofVags--;
			}
		}
	}
}

void Train::removeVagon(const int & v)
{
	if ((v < 0) || (v > kollofVags)){
		throw Train::TrainExeption("Задана неверная позиция удаления!");
	}
	for (int j = v; j < kollofVags - 1; j++) {
		Vags[j] = Vags[j + 1];
	}
	kollofVags--;
}

Vag & Train::operator[](const int & i)
{
	if ((i < 0) || (i > kollofVags)) {
		throw Vag::VagonExeption("Индекс выходит за границы поездов!");
	}
	return Vags[i];
}

const Vag & Train::operator[](const int & i) const
{
	if ((i < 0) || (i > kollofVags)) {
		throw Vag::VagonExeption("Индекс выходит за границы поездов!");
	}
	return Vags[i];
}

Train * Train::operator=(const Train & copy)
{
	nameTrain = copy.nameTrain;
	kollofVags = copy.kollofVags;
	Vags = new Vag[kollofVags];
	for (int i = 0; i < kollofVags; i++) {
		Vags[i] = copy.Vags[i];
	}
	return this;
}

Train::~Train()
{
	kollofVags = 0;
	delete[] Vags;
}

std::ostream & operator<<(std::ostream & stream, const Train & C)
{
	stream << C.nameTrain << std::endl;
	stream << C.kollofVags << std::endl;
	for (int i = 0; i < C.kollofVags; i++) {
		stream << C.Vags[i] << " ";
	}
	stream << std::endl;
	return stream;
}

std::istream & operator>>(std::istream & stream, Train & C)
{
	stream >> C.nameTrain;
	stream >> C.kollofVags;
	for (int i = 0; i < C.kollofVags; i++) {
		stream >> C.Vags[i];
	}
	return stream;
}
