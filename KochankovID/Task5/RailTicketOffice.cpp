#include "RailTicketOffice.h"
#include <ctime>
#include <Windows.h>
using namespace std;

RailTicketOffice::RailTicketOffice(std::string file_) : file(file_), in(file_, ios::app), out(file_, ios::app), R(30), KollOfTickets(0)
{
	ifstream f("KollOfTickets.txt", ios::in);
	f >> KollOfTickets;
	f.close();
	Ticket* arr = new Ticket[KollOfTickets];
	for (int i = 0; i < KollOfTickets; i++) {
		in >> arr[i];
		for (int j = 0; j < arr[i].KollOfPosition; j++) {
			R[arr[i].Positions[j].Day][arr[i].Positions[j].Train][arr[i].Positions[j].Vagon][arr[i].Positions[j].TypeOfPlace][arr[i].Positions[j].Place] = false;
		}
	}
}

void RailTicketOffice::BuyTicket(std::string Name_, std::string Female_)
{
	cout << "---------BuyTicket---------" << endl;
	Ticket T;
	T.id = time(0);

	T.Name = Name_;
	T.Female = Female_;
	T.KollOfPosition = 1;
	T.Positions = new onePosition[T.KollOfPosition];
	T.Amaunt = 0;
	bool flag = true;
	while (flag) {

		int day;
		int train;
		int vagon;
		int type_place;

		do {
			cout << "-----" << '\n';
			cout << "Days: " << ' ' << R.getNumsDay() << '\n';
			cout << "-----" << endl;
			cout << "Input day: ";
			cin >> day;
			if (!cin) {
				cin.clear();
				day = -1;
				cin.ignore(1);
			}
		} while ((day < 0) || (day >= R.getNumsDay()));

		T.Positions[T.KollOfPosition-1].Day = day;

		do {
			cout << "-----" << '\n';
			for (int j = 0; j < R[day].getNumTrains(); j++) {
				cout << j << ' ' << R[day][j].getName() << '\n';
			}
			cout << "-----" << endl;
			cout << "Input train number: ";
			cin >> train;
			if (!cin) {
				cin.clear();
				train = -1;
				cin.ignore(1);
			}
		} while ((train < 0) || (train >= R[day].getNumTrains()));

		T.Positions[T.KollOfPosition - 1].Train = train;
		T.Positions[T.KollOfPosition - 1].TypeOfTrain = R[day][train].getName();

		do {
			cout << "-----" << '\n';
			for (int j = 0; j < R[day][train].getNumVags(); j++) {
				cout << j << ' ' << R[day][train][j].GetType() << '\n';
			}
			cout << "-----" << endl;
			cout << "Input vagon number: ";
			cin >> vagon;
			if (!cin) {
				cin.clear();
				vagon = -1;
				cin.ignore(1);
			}
		} while ((vagon < 0) || (vagon >= R[day][train].getNumVags()));

		T.Positions[T.KollOfPosition - 1].Vagon = vagon;
		T.Positions[T.KollOfPosition - 1].TypeOfVagon = R[day][train][vagon].GetType();

		do {
			cout << "-----" << '\n';
			for (int j = 0; j < R[day][train][vagon].GetCouuntPlace(); j++) {
				cout << j << ' ' << R[day][train][vagon][j].GetType() << '\n';
			}
			cout << "-----" << endl;
			cout << "Input type of place: ";
			cin >> type_place;
			if (!cin) {
				cin.clear();
				type_place = -1;
				cin.ignore(1);
			}
		} while ((type_place < 0) || (type_place >= R[day][train][vagon].GetCouuntPlace()));

		T.Positions[T.KollOfPosition - 1].NamePlace = R[day][train][vagon][type_place].GetType();
		T.Positions[T.KollOfPosition - 1].TypeOfPlace = type_place;
		bool flag2 = true;
		int place;
		do {
			cout << "-----" << '\n';
			cout << "Places: " << ' ' << R[day][train][vagon][type_place].GetCouuntPlace() << '\n';
			cout << "-----" << endl;
			cout << "Input place: ";
			cin >> place;
			if (!cin) {
				cin.clear();
				place = -1;
				cin.ignore(1);
			}
		} while ((place < 0) || (place >= R[day][train][vagon][type_place].GetCouuntPlace()));
		if (R[day][train][vagon][type_place][place]) {
			T.Positions[T.KollOfPosition - 1].Place = place;
			T.Amaunt += R[day][train][vagon][type_place].GetAmaunt();
			KollOfTickets++;
		}
		else {
			cout << "This place have been already bought!" << endl;
			flag2 = false;
		}
		do {
			cin.clear();
			cin.ignore(1);
			cout << "Add other place? " << endl;
			cin >> flag;
		} while (!cin);

		if (flag) {
			onePosition* p = new onePosition[T.KollOfPosition];
			for (int i = 0; i < T.KollOfPosition; i++) {
				p[i] = T.Positions[i];
			}
			delete[] T.Positions;
			if (flag2) {
				T.KollOfPosition++;
			}
			T.Positions = new onePosition[T.KollOfPosition];
			for (int i = 0; i < T.KollOfPosition-1; i++) {
				T.Positions[i] = p[i];
			}
		}
		else {
			if (flag2) {
				out << T << endl;
				Sleep(200);
			}
		}
	}
}

void RailTicketOffice::IsAvaible()
{
	cout << "---------IsAvaible---------" << endl;
	int day;
	int train;
	int vagon;
	do {
		cout << "-----" << '\n';
		cout << "Days: " << ' ' << R.getNumsDay() << '\n';
		cout << "-----" << endl;
		cout << "Input day: ";
		cin >> day;
		if (!cin) {
			cin.clear();
			day = -1;
			cin.ignore(1);
		}
	} while ((day < 0) || (day >= R.getNumsDay()));

	do {
		cout << "-----" << '\n';
		for (int j = 0; j < R[day].getNumTrains(); j++) {
			cout << j << ' ' << R[day][j].getName() << '\n';
		}
		cout << "-----" << endl;
		cout << "Input train number: ";
		cin >> train;
		if (!cin) {
			cin.clear();
			train = -1;
			cin.ignore(1);
		}
	} while ((train < 0) || (train >= R[day].getNumTrains()));

	do {
		cout << "-----" << '\n';
		for (int j = 0; j < R[day][train].getNumVags(); j++) {
			cout << j << ' ' << R[day][train][j].GetType() << '\n';
		}
		cout << "-----" << endl;
		cout << "Input vagon number: ";
		cin >> vagon;
		if (!cin) {
			cin.clear();
			vagon = -1;
			cin.ignore(1);
		}
	} while ((vagon < 0) || (vagon >= R[day][train].getNumVags()));

	cout << "-----" << '\n';
	for (int j = 0; j < R[day][train][vagon].GetCouuntPlace(); j++) {
		cout << j << ' ' << R[day][train][vagon][j].GetType() << '\n';
		for (int i = 0; i < R[day][train][vagon][j].GetCouuntPlace(); i++) {
			if(R[day][train][vagon][j][i])
				cout << "	 Place №" << i  << '\n';
		}
	}
	cout << "-----" << endl;
}

void RailTicketOffice::UnReserved(const int & id_)
{
	cout << "---------UnReserved---------" << endl;
	Ticket* arr = new Ticket[KollOfTickets];
	in.seekg(0, ios::beg);
	for (int i = 0; i < KollOfTickets; i++) {
		in >> arr[i];
	}
	bool flag = true;
	for (int i = 0; i < KollOfTickets; i++) {
		if (arr[i].id == id_) {
			flag = false;
			for (int j = i; j < KollOfTickets-1; j++) {
				arr[j] = arr[j + 1];
			}
			break;
		}
	}
	if (flag) {
		cout << "ID not found!" << endl;
	}
	else {
		cout << "Billet is unreserwed!" << endl;
		KollOfTickets--;
	}
	out.close();
	out.open(file, ios::out);
	for (int i = 0; i < KollOfTickets; i++) {
		out << arr[i];
	}
}

RailTicketOffice::~RailTicketOffice()
{
	ofstream f("KollOfTickets.txt");
	f << KollOfTickets;
	f.close();
	in.close();
	out.close();
}
