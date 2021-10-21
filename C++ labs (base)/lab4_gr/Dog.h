#pragma once
#include "Animal.h"
class Dog :
	public Animal
{
public:
	int size;
	Dog();
	Dog(int age, char* name, int weight, int size);
	void voice();
	void info();
};

