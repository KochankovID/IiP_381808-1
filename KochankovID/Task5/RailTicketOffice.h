#pragma once
#include "Ticket.h"
#include "GorkyRailway.h"
#include <fstream>
#include <iostream>

class RailTicketOffice
{
public:
	// Конструкторы ----------------------------------------------------------
	// Конструктор по умолчанию
	RailTicketOffice(std::string file_ = "Tickets.txt");

	RailTicketOffice(const RailTicketOffice&) = delete;
	// Методы класса ---------------------------------------------------------
	// Метод покупки биллета
	void BuyTicket(std::string Name_, std::string Female_);

	// Узнать количиство свободных мест
	void IsAvaible();

	// Отменить покупку билета
	void UnReserved(const int& id_);

	// Получить кол-во билетов
	int getKollOfTickets() { return KollOfTickets; }

	// Деструктор ------------------------------------------------------------
	~RailTicketOffice();
private:
	// Скрытые поля класса ------------------------------------------------------------
	// Объект железной дороги
	GorkyRailway R;

	// Поток ввода
	std::ifstream in;

	// Потов вывода
	std::ofstream out;

	// Колличество билетов
	int KollOfTickets;

	// Путь до файла хранящего биллета
	string file;
};

