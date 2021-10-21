//variant #5
#include <iostream>
#include "added.h"
int main() {
	vector a, b;
	std::cin >> a.x >> a.y >> b.x >> b.y;
	std::cout << "added ";
	show(added(a, b));
	std::cout << "minus ";
	show(minus(a, b));
	system("pause");
	return 0;
}