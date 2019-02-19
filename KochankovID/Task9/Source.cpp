#include <iostream>
#include <locale>
#include <string>
#include "Triangle.h"

using namespace std;
int main()
{
	setlocale(LC_CTYPE, "Russian");
	Triangle t = Triangle(5, 3, 4);
	cout << "Существует? " << t.isExists() << endl;
	cout << "Тип: " << t.type() << endl;
	cout << "Площадь: " << t.S() << endl;
	cout << "Периметр: " << t.P() << endl;
	system("pause");
}

