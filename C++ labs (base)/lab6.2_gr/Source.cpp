#include <iostream>
#include "Header.h"
#include <string>

int main() {
	Container <int> s;
	s.add(1); s.add(5);s.add(10); s.add(2); s.add(1);
	s.info();
	try {
		s.add(5);
	}
	catch (Container<int>::Full) {
		std::cout << "mas is full\n";
	}
	s.del(); s.del(); s.del(); s.del(); s.del();
	s.info();
	try {
		s.del();
	}
	catch (Container<int>::Empty) {
		std::cout << "mas is empty!\n";
	}
	s.add(1); s.add(1);
	s.info();
	try {
		s.adding();
	}
	catch (Container<int>::Less) {
		std::cout << "mas el less 3!\n";
	}
	s.add(5); s.info(); s.adding();
	
	return 0;
}

