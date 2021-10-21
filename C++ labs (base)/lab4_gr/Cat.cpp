#include "Cat.h"
#include <iostream>

Cat::Cat() :Animal() {
	furry = 0;
}

Cat::Cat(int age, char* name, int weight, int furry) :Animal(age,name,weight){
	this->furry = furry;
}

void Cat::voice() {
	std::cout << "meow meow" << std::endl;
}

void Cat::info() {
	std::cout << "name: " << name << ", age: " << age << ", weight " << weight << ", furry: " << furry << std::endl;
}