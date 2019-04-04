#include <fstream>
#include <iostream>
#include <locale>
#include <string>
#include "ClassMenu.h"
#define OUT(X) cout <<"Вывод : "<< #X << endl << (X)  << endl 

using namespace std;
int main()
{
	setlocale(LC_CTYPE, "Russian");

	// Тест конструктора по умолчанию
	ClassMenu m;
	OUT(m);

	string t[2] = { "asf", "asdfadfs" };

	// Тест конструктора инициализатора
	ClassMenu m1(2, t);
	OUT(m1);

	// Тест конструктора инициализатора
	ClassMenu m2(5);
	OUT(m2);

	// Тест конструктора инициализатора
	ClassMenu m3("one\nFile\nСохранить\nВыделить"); 
	OUT(m3);

	// Тест конструктора копирования
	ClassMenu m4(m3);
	OUT(m4);

	// Тест методов класса
	OUT(m4.getKol());
	m4.setKol(2);
	OUT(m4.getKol());
	
	getchar();

	// Тест меню
	string s[] = { "asdfasd" };
	int a[] = { 0 };
	m3.DrawCMenu(1, a, s);
	OUT(m3.getLastClause());

	// Тест записи в файл и считывание из него 
	ofstream file;
	file.open("Text.txt");
	file << m4;
	file.close();
	ifstream file1;
	file1.open("Text.txt");
	ClassMenu m5;
	file1 >> m5;
	file1.close();

	OUT(m5);

	system("pause");
}

