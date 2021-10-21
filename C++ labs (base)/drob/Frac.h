#pragma once
class Frac
{
public:
	int num, den;
	Frac();
	Frac(int n, int d);
	Frac operator*(Frac r);
	Frac operator/(Frac r);
	void info();
};

