#include "Dog.h"
#include <iostream>

Dog::Dog() :Animal() {
	size = 0;
}

Dog::Dog(int age, char* name, int weight, int size) : Animal(age, name, weight) {
	this->size = size;
}

void Dog::voice() {
	std::cout << "gou gou" << std::endl;
}

void Dog::info() {
	std::cout << "name: " << name << ", age: " << age << ", weight " << weight << ", size: " << size << std::endl;
}