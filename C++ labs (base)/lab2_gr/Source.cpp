#include <iostream>
#include "MyTime.h"
#include <algorithm>

int main() {
	MyTime t1, t2(2, 30, 10), t3(1, 8, 50);
	int r = 3;
	t1.info(); t2.info(); t3.info();
	t1 = t2.add(t3);
	t1.info();
	t1 = t2 + t3;
	t1.info();
	t1 = t2 - t3;
	t1.info();
	t1 = t2 * r;
	t1.info();
	t1 = 5 * t2;
	t1.info();
	system("pause");
	return 0;
}