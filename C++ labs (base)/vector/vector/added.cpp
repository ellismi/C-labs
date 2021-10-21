#include <iostream>
#include "added.h"
void show(vector a) {
	std::cout << "result:" << a.x << " " << a.y << "\n";
}
vector added(vector a, vector b) {
	a.x += b.x;
	a.y += b.y;
	return a;
}
vector minus(vector a, vector b) {
	a.x -= b.x;
	a.y -= b.y;
	return a;
}
