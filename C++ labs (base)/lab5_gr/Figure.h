#pragma once
class Figure
{
public:
	int x, y;
	Figure();
	Figure(int x, int y);
	virtual void info();
	virtual double square() = 0;
	virtual double perimeter() = 0;
};

