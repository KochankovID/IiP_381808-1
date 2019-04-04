#include "ClassMenu.h"
#include <algorithm>
#include <iostream>
#include <limits>

using namespace std;

ClassMenu::ClassMenu() : kol_(0), last_clause_(-1), menu_()
{
}

ClassMenu::ClassMenu(int kol, const std::string * menu) : kol_(kol), last_clause_(-1), menu_(kol_)
{
	for (int i = 0; i < kol_; i++) {
		menu_[i] = menu[i];
	}
}

ClassMenu::ClassMenu(int kol) : kol_(kol), last_clause_(-1), menu_(kol)
{
	for (int i = 0; i < kol_; i++) {
		menu_[i] = ' ';
	}
}

ClassMenu::ClassMenu(const std::string menuStr) : last_clause_(-1), menu_(count(menuStr.begin(), menuStr.end(), '\n')), kol_(count(menuStr.begin(), menuStr.end(), '\n'))
{
	string menu = menuStr;
	menu += '\n';
	
	string::const_iterator b = menu.begin();
	string::const_iterator e = menu.end();
	for (int i = 0; i < kol_; i++) {
		menu_[i].resize(find(b, e, '\n') - b, ' ');
		copy(b, e = find(b, e, '\n'), menu_[i].begin());
		b = e+1;
		e = menu.end();
	}
}

ClassMenu::ClassMenu(const ClassMenu & m) : kol_(m.kol_), last_clause_(-1), menu_(kol_)
{
	for (int i = 0; i < kol_; i++) {
		menu_[i] = m.menu_[i];
	}
}

void ClassMenu::startMenu(int x, int y, void(ClassMenu::*paint)(HANDLE, COORD, const int&, const int&) const, const int& but1, const int& but2, const int& margin) // Функция рисует меню в заданных координатах консоли и обрабатывает нажатия клавиш
{
	//Проверка на правильность размера отступов
	if (margin < 1) { throw MenuExeption(InvalideMargine,"Неверный вормат отступов"); };

	// Не используемые в этой функции параметры, необходимые для работы функций
	DWORD d; 
	LPDWORD l = &d;

	// Структура координат
	COORD point;

	// Текущий "выбранный пункт меню"
	int k = 0;

	// Инициализация координат
	point.X = x; point.Y = y;
	
	// Инициализация дескриптора консоли
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	
	// Заголовок окна консоли
	//LPCWSTR title = L"Menu";
	//SetConsoleTitle(title);

	// Изменение кодовой страницы консоли вывода (нужно для вывода русских символов) 
	int cp = GetConsoleOutputCP();
	SetConsoleOutputCP(1251);

	// Настройка вывода консоли
	SetConsoleTextAttribute(hout, 0x0000|0x0070); // Настройка цвета и фона текста
	FillConsoleOutputAttribute(hout, 0, 10000, point, l); // Очистка консоли

	(this->*paint)(hout, point, k, margin); // Вызов функции прорисовки меню

	GetAsyncKeyState(VK_SPACE); // Перехват ранее нажатых клавиш
	Sleep(200); //  время "Дребезга" кнопки

	while (1) // цикл обработки нажатых клавиш
	{

		if (GetAsyncKeyState(but2)) { // если нажата стрелка вправо, перемещает текущий "выбранный пункт меню" вправо
			if (isInRangeNoThrowable(k + 2)) {
				(this->*paint)(hout, point, ++k, margin);
				while (GetAsyncKeyState(but2) & 0x8000) // Время дребезга кнопки
				{
				}
			}
		}
		if (GetAsyncKeyState(but1)) { // если нажата стрелка влево, перемещает текущий "выбранный пункт меню" влево
			if (isInRangeNoThrowable(k - 1)) {
				(this->*paint)(hout, point, --k, margin);
				while (GetAsyncKeyState(but1) & 0x8000) // Время дребезга кнопки
				{
				}
			}
		}
		if (GetAsyncKeyState(VK_RETURN)) { // если нажата клавиша Enter, то созраняет текущий "выбранный пункт меню" и выходит из цикла
			last_clause_ = k + 1;
			while (GetAsyncKeyState(VK_RETURN) & 0x8000) // Время дребезга кнопки
			{
			}
			break;
		}
	}

	SetConsoleTextAttribute(hout, 0x0007 | 0x0000); // Возврат текста к обычному виду
	FillConsoleOutputAttribute(hout, 0, 10000, point, l); // Очистка консоли

	// Перевод курсора в начало консоли
	point.X = 0; point.Y = 0;
	SetConsoleCursorPosition(hout, point);
	// Возврат кодовой страницы консоли вывода (нужно для вывода русских символов через cout поток) 
	SetConsoleOutputCP(cp);
}

void ClassMenu::startMenu(int x, int y, void(ClassMenu::* paint)(HANDLE, COORD, const int &, const int&, const int &, const int &,  const int*, const std::string*) const, const int & but1, const int & but2, const int & margin, const int & margin1, const int& kolclauses, const int* numOfClauses, const std::string* titles)
{
	//Проверка на правильность размера отступов
	if (margin < 1) { throw MenuExeption(InvalideMargine, "Неверный вормат отступов"); };

	// Не используемые в этой функции параметры, необходимые для работы функций
	DWORD d;
	LPDWORD l = &d;

	// Структура координат
	COORD point;

	// Текущий "выбранный пункт меню"
	int k = 0;

	// Инициализация координат
	point.X = x; point.Y = y;

	// Инициализация дескриптора консоли
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);

	// Заголовок окна консоли
	//LPCWSTR title = L"Menu";
	//SetConsoleTitle(title);

	// Настройка вывода консоли
	SetConsoleTextAttribute(hout, 0x0000 | 0x0070); // Настройка цвета и фона текста
	FillConsoleOutputAttribute(hout, 0, 10000, point, l); // Очистка консоли

	(this->*paint)(hout, point, k, margin, margin1, kolclauses, numOfClauses, titles); // Вызов функции прорисовки меню

	while (GetAsyncKeyState(VK_RETURN) & 0x8000) // Перехват ранее нажатых клавиш
	{
	}

	while (1) // цикл обработки нажатых клавиш
	{

		if (GetAsyncKeyState(but2)) { // если нажата стрелка вправо, перемещает текущий "выбранный пункт меню" вправо
			if (isInRangeNoThrowable(k + 2)) {
				(this->*paint)(hout, point, ++k, margin,margin1, kolclauses, numOfClauses,titles);
				while (GetAsyncKeyState(but2) & 0x8000) // Время дребезга кнопки
				{
				}
			}
		}
		if (GetAsyncKeyState(but1)) { // если нажата стрелка влево, перемещает текущий "выбранный пункт меню" влево
			if (isInRangeNoThrowable(k - 1)) {
				(this->*paint)(hout, point, --k, margin, margin1, kolclauses, numOfClauses, titles);
				while (GetAsyncKeyState(but1) & 0x8000) // Время дребезга кнопки
				{
				}
			}
		}
		if (GetAsyncKeyState(VK_RETURN)) { // если нажата клавиша Enter, то созраняет текущий "выбранный пункт меню" и выходит из цикла
			last_clause_ = k + 1;
			while (GetAsyncKeyState(VK_RETURN) & 0x8000) // Время дребезга кнопки
			{
			}
			break;
		}
	}

	SetConsoleTextAttribute(hout, 0x0007 | 0x0000); // Возврат текста к обычному виду
	FillConsoleOutputAttribute(hout, 0, 10000, point, l); // Очистка консоли

	// Перевод курсора в начало консоли
	point.X = 0; point.Y = 0;
	SetConsoleCursorPosition(hout, point);

	cin.ignore();
}

ClassMenu::~ClassMenu()
{
}

std::string& ClassMenu::operator[](int index)
{
	isInRange(index);
	return menu_[index];
}

const std::string& ClassMenu::operator[](int index) const
{
	isInRange(index);
	return menu_[index];
}

void ClassMenu::isInRange(int index) const
{
	if ((index < 0)||(index > kol_)) {
		throw MenuExeption(OutOfRange, "Введенное число превышает число команд меню!");
	}
}

bool ClassMenu::isInRangeNoThrowable(int index) const
{
	if ((index < 0) || (index > kol_)) {
		return false;
	}
	return true;
}

void ClassMenu::paintH(HANDLE hout, COORD point, const int& k, const int& margin) const
{
	// Строка перевода
	char* s;

	// Не используемые в этой функции параметры, необходимые для работы функций
	DWORD d;
	LPDWORD l = &d;

	// Цикл переисовки меню
	for (int i = 0; i < kol_; i++) {

		if (i == k) { // Если текцщий элемент в фокусе, то выделяем фон текста
			SetConsoleTextAttribute(hout, 0x0000 | 0x0080);
			SetConsoleCursorPosition(hout, point);
			s = new char[menu_[i].size() + 1];
			copy(menu_[i].begin(), menu_[i].end(), s);
			WriteFile(hout, s, menu_[i].length(), l, NULL);
			point.X += menu_[i].length();
			point.X += margin;
			SetConsoleTextAttribute(hout, 0x0000 | 0x0070);
			continue;
		}

		// Остальные элементы рисуем с ярким фоном
		SetConsoleCursorPosition(hout, point);
		s = new char[menu_[i].size() + 1];
		copy(menu_[i].begin(), menu_[i].end(), s);
		WriteFile(hout, s, menu_[i].length(), l, NULL);
		point.X += menu_[i].length();
		point.X += margin;
		delete[]s;
	}
}

void ClassMenu::paintW(HANDLE hout, COORD point, const int& k, const int& margin) const
{
	// Строка перевода
	char* s;

	// Не используемые в этой функции параметры, необходимые для работы функций
	DWORD d;
	LPDWORD l = &d;

	// Цикл переисовки меню
	for (int i = 0; i < kol_; i++) {

		if (i == k) { // Если текцщий элемент в фокусе, то выделяем фон текста
			SetConsoleTextAttribute(hout, 0x0000 | 0x0080);
			SetConsoleCursorPosition(hout, point);
			s = new char[menu_[i].size() + 1];
			copy(menu_[i].begin(), menu_[i].end(), s);
			WriteFile(hout, s, menu_[i].length(), l, NULL);
			point.Y += margin;
			SetConsoleTextAttribute(hout, 0x0000 | 0x0070);
			continue;
		}

		// Остальные элементы рисуем с ярким фоном
		SetConsoleCursorPosition(hout, point);
		s = new char[menu_[i].size() + 1];
		copy(menu_[i].begin(), menu_[i].end(), s);
		WriteFile(hout, s, menu_[i].length(), l, NULL);
		point.Y += margin;
		delete[]s;
	}
}

void ClassMenu::paintCompositMenu(HANDLE hout, COORD point, const int & k, const int & margin, const int & margin1, const int & kolclauses, const int* numOfClauses, const std::string* titles) const
{
	// Строка перевода
	char* s;

	// Не используемые в этой функции параметры, необходимые для работы функций
	DWORD d;
	LPDWORD l = &d;
	int j = 0;
	// Цикл переисовки меню
	for (int i = 0; i < kol_; i++) {
		if((j < kolclauses)&&(i == numOfClauses[j])) {
			j == 0 ? 0 : point.Y += margin1;
			SetConsoleCursorPosition(hout, point);
			SetConsoleTextAttribute(hout, FOREGROUND_GREEN | 0x0000);
			s = new char[titles[j].size() + 1];
			copy(titles[j].begin(), titles[j].end(), s);
			WriteFile(hout, s, titles[j].length(), l, NULL);
			point.Y += (margin1);
			SetConsoleTextAttribute(hout, 0x0000 | 0x0070);
			j++;
			i--;
			continue;
		}
		if (i == k) { // Если текцщий элемент в фокусе, то выделяем фон текста
			SetConsoleTextAttribute(hout, 0x0000 | 0x0080);
			SetConsoleCursorPosition(hout, point);
			s = new char[menu_[i].size() + 1];
			copy(menu_[i].begin(), menu_[i].end(), s);
			WriteFile(hout, s, menu_[i].length(), l, NULL);
			point.Y += margin;
			SetConsoleTextAttribute(hout, 0x0000 | 0x0070);
			continue;
		}
		// Остальные элементы рисуем с ярким фоном
		SetConsoleCursorPosition(hout, point);
		s = new char[menu_[i].size() + 1];
		copy(menu_[i].begin(), menu_[i].end(), s);
		WriteFile(hout, s, menu_[i].length(), l, NULL);
		point.Y += margin;
		delete[]s;
	}
}



std::ostream& operator<<(std::ostream& out, const ClassMenu& m)
{
	out << m.kol_ << endl;
	for (int i = 0; i < m.kol_; i++) {
		out << m.menu_[i] << endl;
	}
	out << m.last_clause_ << endl;
	return out;
}

istream& operator>>(istream& in, ClassMenu& m)
{
	int kol;
	in >> kol;
	m.kol_ = kol;
	m.menu_ = Collection<string>(kol);
	for (int i = 0; i < m.kol_; i++) {
		in >> m.menu_[i];
	}
	in >> m.last_clause_;
	return in;
}
