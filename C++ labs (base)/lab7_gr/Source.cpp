#include <iostream>
#include "Header.h"

int main() {
	Store <int> s1;
	s1.add(4);
	s1.add(6);
	s1.add(165);
	s1.add(26);
	s1.add(343);
	Store<int>::iterator i;
	for (i = s1.begin(); i != s1.end(); i++) {
		std::cout << *i << " ";
	}

	system("pause");
	return 0;
}