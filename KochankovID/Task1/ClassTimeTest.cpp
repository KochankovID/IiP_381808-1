#include <iostream>
#include <locale>
#include <string>
#include "ClassTime.h"

using namespace std;
using namespace ClassTime;
int main()
{
	setlocale(LC_CTYPE, "Russian");

	// Конструктор по умлочанию
	Time t;
	cout << t << endl;
	// Конструктор инициализатор
	int a = 0, b = 0, c = 0;
	cin >> a >> b >> c;
	try {
		Time ti = Time(a, b, c);
		cout << ti << endl;
	}
	catch (Time::exepOutOfRange Range) {
		cout << Range.error << endl;
		cout << "Значение элемента : " << Range.amount << endl;
	}
	// Конструктор копирования
	Time tii(14, 15, 16);
	Time tcop(tii);
	cout << tcop << endl;

	// Конструктор преобразования типа
	string time; 
	cin >> time;
	try {
		Time tstr = Time (time);
		cout << tstr << endl;
	}
	catch (Time::exepNonNumber Num) {
		cout << Num.error << endl;
		cout << "Позиция элемента : " << Num.pos << endl;
	}
	catch (Time::exepOutOfRange Range) {
		cout << Range.error << endl;
		cout << "Значение элемента : " << Range.amount << endl;
	}catch (Time::exepNonAmount Amount) {
		cout << Amount.error << endl;
	}

	// Методы возвращения значений
	Time tstr("23.46.14");
	cout << tstr.getTimeString() << endl;
	cout << tstr.getHou() << endl;
	cout << tstr.getMin() << endl;
	cout << tstr.getSec() << endl;
	tstr.getTimeInt(a, b, c);
	cout << "Часы : " << a << " Минуты : " << b << " Секунды : " << c << endl;

	// Перегруженные методы
	cout << tstr + tii << endl;
	cout << tstr - tii << endl;
	cout << tstr + 70 << endl;
	cout << tstr - 70 << endl;
	tstr = tii;
	cout << tstr << endl;
	Time t1(15, 15, 15), t2(15, 15, 14);

	Time p = "14.15.19";  // неявное приведение типов (в силу конструктора преобразования типа)
	// Перегрузка операторов сравнения
	if (t1 > t2) {
		cout << "1)true" << endl;
	}
	else {
		cout << "1)false" << endl;
	}

	if (t1 >= t2) {
		cout << "2)true" << endl;
	}
	else {
		cout << "2)false" << endl;
	}

	if (t1 == t2) {
		cout << "3)true" << endl;
	}
	else {
		cout << "3)false" << endl;
	}

	if (t1 != t2) {
		cout << "4)true" << endl;
	}
	else {
		cout << "4)false" << endl;
	}
	system("pause");
}

