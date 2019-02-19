#pragma once
#include <string>

using namespace std;
class Triangle
{
public:
	//конструкторы
	Triangle();
	Triangle(int a, int b, int c);
	Triangle(const Triangle &);

	//методы
	bool isExists();
	string type();
	int S();
	int P();

	//методы доступа
	int& A();
	int& B();
	int& C();

	//деструкторы
	~Triangle();
private:
	int a, b, c;
};

