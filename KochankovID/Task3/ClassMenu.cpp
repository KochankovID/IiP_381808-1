#include "ClassMenu.h"
#include <algorithm>
#include <iostream>


using namespace std;

ClassMenu::ClassMenu() : kol_(1), last_clause_(-1)
{
	menu_ = new string[1];
	*menu_ = ' ';
}

ClassMenu::ClassMenu(int kol, const std::string * menu) : kol_(kol), last_clause_(-1)
{
	menu_ = new string[kol_];
	for (int i = 0; i < kol_; i++) {
		menu_[i] = menu[i];
	}
}

ClassMenu::ClassMenu(int kol) : kol_(kol), last_clause_(-1)
{
	menu_ = new string[kol_];
	for (int i = 0; i < kol_; i++) {
		menu_[i] = ' ';
	}
}

ClassMenu::ClassMenu(const std::string menuStr) : last_clause_(-1)
{
	string menu = menuStr;
	menu += '\n';
	kol_ = count(menu.begin(), menu.end(), '\n');
	menu_ = new string[kol_];
	
	string::const_iterator b = menu.begin();
	string::const_iterator e = menu.end();
	for (int i = 0; i < kol_; i++) {
		menu_[i].resize(find(b, e, '\n') - b, ' ');
		copy(b, e = find(b, e, '\n'), menu_[i].begin());
		b = e+1;
		e = menu.end();
	}
}

ClassMenu::ClassMenu(const ClassMenu & m) : kol_(m.kol_), last_clause_(-1)
{
	menu_ = new string[kol_];
	for (int i = 0; i < kol_; i++) {
		menu_[i] = m.menu_[i];
	}
}

void ClassMenu::startMenu(int x, int y) // Функция рисует меню в заданных координатах консоли и обрабатывает нажатия клавиш
{
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
	LPCWSTR title = L"Menu";
	SetConsoleTitle(title);

	// Изменение кодовой страницы консоли вывода (нужно для вывода русских символов) 
	int cp = GetConsoleOutputCP();
	SetConsoleOutputCP(1251);

	// Настройка вывода консоли
	SetConsoleTextAttribute(hout, 0x0000|0x0070); // Настройка цвета и фона текста
	FillConsoleOutputAttribute(hout, 0, 10000, point, l); // Очистка консоли

	paint(hout, point, k); // Вызов функции прорисовки меню

	while (1) // цикл обработки нажатых клавиш
	{

		if (GetAsyncKeyState(VK_RIGHT)) { // если нажата стрелка вправо, перемещает текущий "выбранный пункт меню" вправо
			if (isInRangeNoThrowable(k + 2)) {
				paint(hout, point, ++k);
				Sleep(200); // время "дребезга" кнопки 
			}
		}
		if (GetAsyncKeyState(VK_LEFT)) { // если нажата стрелка влево, перемещает текущий "выбранный пункт меню" влево
			if (isInRangeNoThrowable(k - 1)) {
				paint(hout, point, --k);
				Sleep(200); // время "дребезга" кнопки 
			}
		}
		if (GetAsyncKeyState(VK_ESCAPE)) { // если нажата клавиша escape, то созраняет текущий "выбранный пункт меню" и выходит из цикла
			last_clause_ = k + 1;
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

	cout << "Выбранный пункт: " << last_clause_ << endl;
}

ClassMenu::~ClassMenu()
{
	delete []menu_;
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

void ClassMenu::paint(HANDLE hout, COORD point, int k) const
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
			point.X += 4;
			SetConsoleTextAttribute(hout, 0x0000 | 0x0070);
			continue;
		}

		// Остальные элементы рисуем с ярким фоном
		SetConsoleCursorPosition(hout, point);
		s = new char[menu_[i].size() + 1];
		copy(menu_[i].begin(), menu_[i].end(), s);
		WriteFile(hout, s, menu_[i].length(), l, NULL);
		point.X += menu_[i].length();
		point.X += 4;
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
	if (kol > m.kol_) {
		delete[]m.menu_;
	}
	m.kol_ = kol;
	m.menu_ = new string[kol];
	for (int i = 0; i < m.kol_; i++) {
		in >> m.menu_[i];
	}
	in >> m.last_clause_;
	return in;
}
