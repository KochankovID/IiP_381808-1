1556771538#pragma once
#include <string>
#include "Day.h"
#include "Train.h"
#include "Vagon.h"
#include "Place.h"

struct onePosition {
	// День покупки биллета
	int Day;

	// Номер поезда
	int Train;

	// Название поезда
	string TypeOfTrain;

	// Номер вагона
	int Vagon;

	// Название типа вагона
	string TypeOfVagon;

	// Номер места
	int Place;

	// Номер типа места
	int TypeOfPlace;

	// Имя типа места
	string NamePlace;

	// Перегрузка операторов ----------------------------------------------------------
	// Перегрузка операции вывода в поток
	friend std::ostream& operator<< (std::ostream& stream, const onePosition& C);

	// Перегрузка операции ввода из потока
	friend std::istream& operator>> (std::istream& stream, onePosition& C);

	// Перегрузка оператора присваивания
	onePosition* operator= (const onePosition& copy);
};

// Структура билета
using std::string;
struct Ticket
{
	// Номер id
	int id;

	// Сумма билета
	int Amaunt;

	// Имя покупателя
	string Name;

	// Фамилия покупателя
	string Female;

	// Массив "позиций"
	onePosition* Positions;

	// Количество "позиций"
	int KollOfPosition;

	// Перегрузка операторов ----------------------------------------------------------
	// Перегрузка операции вывода в поток
	friend std::ostream& operator<< (std::ostream& stream, const Ticket& C);

	// Перегрузка операции ввода из потока
	friend std::istream& operator>> (std::istream& stream, Ticket& C);

	// Перегрузка оператора присваивания
	Ticket* operator= (const Ticket& copy);
};
