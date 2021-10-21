#pragma once
#include "Figure.h"
class Rectangle :
	public Figure
{
public:
	int x1, y1;
	Rectangle();
	Rectangle(int x, int y, int x1, int y1);
	void info();
	double perimeter();
	double square();
};

