#include "Circle.h"
#include <iostream>
#define M_PI       3.14159265358979323846   // pi
Circle::Circle() {
	radius = 1.0;
}

Circle::Circle(int x, int y, double radius) :Figure(x,y) {
	this->radius = radius;
}

void Circle::info() {
	Figure::info();
	std::cout << " r: " << radius << std::endl;
}

double Circle::perimeter() {
	return 2*M_PI * radius;
}

double Circle::square() {
	return M_PI * radius * radius;
}