#include <iostream>
#include "Figure.h"
#include "Circle.h"
#include "Rectangle.h"

int main() {
	Figure* f1;
	Circle c1, c2(10, 10, 5);
	Rectangle p1, p2(1, 1, 4, 5);
	c1.info(); c2.info();
	/*std::cout << "p: " << c1.perimeter() << " s: " << c1.square() << std::endl;
	std::cout << "p: " << c2.perimeter() << " s: " << c2.square() << std::endl;*/
	f1 = &c1;
	f1->info();
	std::cout << "circle s:" << f1->square() << " p:" << f1->perimeter() << "\n";
	std::cout << "rectangle\n";
	p1.info(); p2.info();
	f1 = &p2;
	std::cout << "rectangle p2 s:" << f1->square() << " p:" << f1->perimeter() << "\n";

	system("pause");
	return 0;
}