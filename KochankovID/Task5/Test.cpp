#include <Windows.h>
#include <clocale>
#include "RailTicketOffice.h"

using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	RailTicketOffice R;
	// Тест покупки биллета
	R.BuyTicket("Ilya", "Kochankov");

	// Тест проверки свободных мест
	R.IsAvaible();
	
	// Тест отмены покупки биллета
	R.UnReserved(1556771538);
	return 0;
}
