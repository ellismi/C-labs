#pragma once
class Frac
{
public:
	int num, den;
	Frac();
	Frac(int n, int d);
	int operator<(Frac f2);
	Frac operator+(Frac r);
	Frac operator*(Frac r);
	Frac operator/(Frac r);
	Frac operator*(int t);
	void info();
};

