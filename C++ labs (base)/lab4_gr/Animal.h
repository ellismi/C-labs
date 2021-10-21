#pragma once
class Animal
{
public:
	int age;
	char name[20];
	int weight;
	Animal();
	Animal(int age, char* name, int weight);
	void voice();
	void info();
};

