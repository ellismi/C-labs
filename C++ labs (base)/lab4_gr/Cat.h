#pragma once
#include "Animal.h"
class Cat :
	public Animal
{
public:
	int furry;
	Cat();
	Cat(int age, char* n, int w, int furry);
	void voice();
	void info();
};

