#include <iostream> 
#include "Animal.h"
#include "Cat.h"
#include "Dog.h"

int main() {
	Animal aq;
	Animal w(2, (char*)"aea", 3);
	aq.info();
	w.info();
	Cat c1, c2(2, (char*)"mw", 4, 2);
	c1.info();
	c2.info();
	c1.voice();
	w.voice();
	Dog d1, d2(4, (char*)"Rig", 6, 4);
	d1.info();
	d2.info();
	d1.voice();
	system("pause");
	return 0;
}