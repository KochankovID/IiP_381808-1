#include "Triangle.h"
#define SQ(x) (x*x)


Triangle::Triangle()
{
	a = 0;
	b = 0;
	c = 0;
}

Triangle::Triangle(int a, int b, int c)
{
	this->a = a;
	this->b = b;
	this->c = c;
}

Triangle::Triangle(const Triangle & t)
{
	a = (const_cast <Triangle&> (t)).A();
	b = (const_cast <Triangle&> (t)).B();
	c = (const_cast <Triangle&> (t)).C();
}

bool Triangle::isExists()
{
	int s1 = a + b;
	int s2 = a + c;
	int s3 = b + c;

	if (s1 < c) {
		return false;
	}
	if (s2 < b) {
		return false;
	}
	if (s3 < a) {
		return false;
	}

	return true;
}

string Triangle::type()
{

	if ((SQ(c) == (SQ(a) + SQ(b))) || (SQ(a) == (SQ(c) + SQ(b))) || (SQ(b) == (SQ(a) + SQ(c)))) {
		return "Прямой";
	}
	if ((SQ(c) < (SQ(a) + SQ(b))) || (SQ(a) < (SQ(c) + SQ(b))) || (SQ(b) < (SQ(a) + SQ(c)))) {
		return "Острый";
	}
	if ((SQ(c) > (SQ(a) + SQ(b))) || (SQ(a) > (SQ(c) + SQ(b))) || (SQ(b) > (SQ(a) + SQ(c)))) {
		return "Тупой";
	}
	return 0;
}

int Triangle::S()
{
	int p = P() / 2;
	return sqrt(p*(p - a)*(p - b)*(p - c));
}

int Triangle::P()
{
	return a + b + c;
}

int & Triangle::A()
{
	return a;
}

int & Triangle::B()
{
	return b;
}

int & Triangle::C()
{
	return c;
}


Triangle::~Triangle()
{
	a = 0; b = 0; c = 0;
}
