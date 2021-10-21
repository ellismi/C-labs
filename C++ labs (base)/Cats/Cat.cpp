#include "Cat.h"
#include <iostream>

Cat::Cat() { mass = 2; strong = 1; runtime = 1; furry = 2; }

Cat::Cat(int mass, int strong, int runtime, int furry) {
	this->mass = mass; this->strong = strong; this->runtime = runtime; this->furry = furry;
}

void Cat::press() {
	int t = mass * furry;
	if (t < 3) std::cout << "your cat is so small" << "\n";
	else if (t >= 3 && t < 6) std::cout << "your cat is usual cat" << "\n";
	else std::cout << "your cat is fat" << "\n";
}
void Cat::damage() {
	int t = 100/(runtime * strong);
	std::cout << "You are died since " << t << "sec" << "\n";
}

void Cat::CatVoice() {
	std::cout << "Meow ... meow ... MEOW!	" << "\n";
}

void Cat::CatRun() {
	int h = strong * runtime * runtime / mass;
	while (h--){
		std::cout << " ('-')-__   ";
	}
	std::cout << "\n";
}
	
void Cat::info(){
	std::cout << "Your cat is " << mass << " kg and " << strong << " strong " << "and ";
	press();
}