#include "Rectangle.h"
#include <iostream>

Rectangle::Rectangle() {
	x1 = 1; y1 = 1;
}

Rectangle::Rectangle(int x, int y, int x1, int y1) :Figure(x, y) {
	this->x1 = x1; this->y1 = y1;
}

void Rectangle::info() {
	Figure::info();
	std::cout << " a:" << fabs(x1 - x) << " b:" << fabs(y1 - y) << std::endl;
}

double Rectangle::perimeter() {
	return 2 * (fabs(x1 - x) + fabs(y1 - y));
}
double Rectangle::square() {
	return fabs(x1 - x) * fabs(y1 - y);
}