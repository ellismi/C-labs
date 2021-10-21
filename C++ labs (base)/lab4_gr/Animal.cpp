#include "Animal.h"
#include <iostream>

Animal::Animal() {
	age = 0;
	weight = 0;
	sprintf_s(name, "no name");
}

Animal::Animal(int age, char* name, int weight) {
	this->age = age; this->weight = weight;
	sprintf_s(this->name, name);
}

void Animal::voice() {
	std::cout << "i'm animal!" << std::endl;
}

void Animal::info() {
	std::cout << "name: " << name << ", age: " << age << ", weight: " << weight << std::endl;
}
