#pragma once
#include "Figure.h"
class Circle :
	public Figure
{
public:
	double radius;
	Circle();
	Circle(int x, int y, double radius);
	void info();
	double square();
	double perimeter();
};

