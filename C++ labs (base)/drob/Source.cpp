#include <iostream>
#include "Frac.h"

int main() {
	Frac f1, f2(3, 4), f3(5, 6);
	f1.info();
	f2.info();
	f3.info();
	f1 = f2 * f3;
	f1.info();
	f1 = f2 / f3;
	f1.info();
	system("pause");
	return 0;
}