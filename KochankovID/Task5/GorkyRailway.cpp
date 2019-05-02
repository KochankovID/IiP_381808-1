#include "GorkyRailway.h"


GorkyRailway::GorkyRailway(const Day * days_, const int & lenth_) : KollOfDays(lenth_)
{
	days = new Day[KollOfDays];
	for (int i = 0; i < KollOfDays; i++) {
		days[i] = days_[i];
	}
}

GorkyRailway::GorkyRailway(const int & lenth_) : KollOfDays(lenth_)
{
	days = new Day[KollOfDays];
	Train Lastochka("Lastochka");
	Train FirmTrain("FirmTrain");
	Train Fast("FastTrain");

	Place LastochkaPlace("Simple_place", 100, 100);
	Vag VagLast("Simple_vagon", &LastochkaPlace, 1);

	Place* pl = new Place[2];
	Place h("Plats_Up_Place", 27, 160);
	Place hh("Plats_Down_Place", 27, 120);
	pl[0] = h;
	pl[1] = hh;
	Vag Plats("Platskart", pl, 2);

	Place* koop = new Place[2];
	koop[0] = Place("Koope_Up_Place", 18, 260);
	koop[1] = Place("Koope_Down_Place", 18, 220);
	Vag Koope("Koope", koop, 2);

	Place svpl("SV_Down_Place", 18, 110);
	Vag SV("SV", &svpl, 1);


	for (int i = 0; i < 8; i++) {
		Lastochka.addVagon(VagLast);
	}

	FirmTrain.addVagon(SV);
	FirmTrain.addVagon(SV);
	FirmTrain.addVagon(Koope);
	FirmTrain.addVagon(Koope);
	FirmTrain.addVagon(Koope);
	FirmTrain.addVagon(Koope);
	FirmTrain.addVagon(Koope);
	FirmTrain.addVagon(Koope);
	FirmTrain.addVagon(Plats);
	FirmTrain.addVagon(Plats);
	FirmTrain.addVagon(Plats);
	FirmTrain.addVagon(Plats);

	Fast.addVagon(Koope);
	Fast.addVagon(Koope);
	Fast.addVagon(Koope);
	Fast.addVagon(Koope);
	Fast.addVagon(Plats);
	Fast.addVagon(Plats);
	Fast.addVagon(Plats);
	Fast.addVagon(Plats);
	Fast.addVagon(Plats);
	Fast.addVagon(Plats);
	Fast.addVagon(Plats);
	Fast.addVagon(Plats);

	for (int i = 0; i < KollOfDays; i++) {
		days[i].addTrain(Lastochka);
		days[i].addTrain(Lastochka);
		days[i].addTrain(Lastochka);
		days[i].addTrain(FirmTrain);
		days[i].addTrain(Fast);
		days[i].addTrain(Lastochka);
		days[i].addTrain(Lastochka);
		days[i].addTrain(Lastochka);
		days[i].addTrain(FirmTrain);
		days[i].addTrain(Fast);
	}
	delete[] koop;
	delete[] pl;
}

void GorkyRailway::addDays(Day * v, const int & lenth)
{
	Day* copy = new Day[KollOfDays];
	for (int i = 0; i < KollOfDays; i++) {
		copy[i] = days[i];
	}
	delete[] days;
	days = new Day[KollOfDays + lenth];
	for (int i = 0; i < KollOfDays; i++) {
		days[i] = copy[i];
	}
	for (int i = KollOfDays; i < KollOfDays + lenth; i++) {
		days[i] = v[i];
	}
	KollOfDays += lenth;
}

void GorkyRailway::addDay(const Day & v)
{
	Day* copy = new Day[KollOfDays];
	for (int i = 0; i < KollOfDays; i++) {
		copy[i] = days[i];
	}
	delete[] days;
	days = new Day[KollOfDays + 1];
	for (int i = 0; i < KollOfDays; i++) {
		days[i] = copy[i];
	}
	days[KollOfDays] = v;
	KollOfDays++;
}

void GorkyRailway::removeDays(const int & first, const int & last)
{
	if ((first < 0) || (first > KollOfDays) || (last < first) || (last > KollOfDays)) {
		throw GorkyRailway::RailwayExeption("Задан неверный промежуток дней!");
	}
	for (int i = first; i < last; i++) {
		for (int j = first; j < KollOfDays-1; j++) {
			days[j] = days[j + 1];
		}
	}
}

Day & GorkyRailway::operator[](const int & i)
{
	if ((i < 0) || (i > KollOfDays)) {
		throw GorkyRailway::RailwayExeption("Индекс выходит за границы поездов!");
	}
	return days[i];
}

const Day & GorkyRailway::operator[](const int & i) const
{
	if ((i < 0) || (i > KollOfDays)) {
		throw GorkyRailway::RailwayExeption("Индекс выходит за границы поездов!");
	}
	return days[i];
}


GorkyRailway::~GorkyRailway()
{
	delete[] days;
	days = nullptr;
}

std::ostream & operator<<(std::ostream & stream, const GorkyRailway & C)
{
	stream << C.KollOfDays << std::endl;
	for (int i = 0; i < C.KollOfDays; i++) {
		stream << C.days[i] << " ";
	}
	stream << std::endl;
	return stream;
}

std::istream & operator>>(std::istream & stream, GorkyRailway & C)
{
	stream >> C.KollOfDays;
	for (int i = 0; i < C.KollOfDays; i++) {
		stream >> C.days[i];
	}
	return stream;
}
