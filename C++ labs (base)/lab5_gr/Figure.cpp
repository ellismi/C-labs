#include "Figure.h"
#include <iostream>
Figure::Figure() {
	x = 0; y = 0;
}

Figure::Figure(int x, int y) {
	this->x = x; this->y = y;
}

void Figure::info() {
	std::cout << "figure  x: " << x << " y: " << y;
}