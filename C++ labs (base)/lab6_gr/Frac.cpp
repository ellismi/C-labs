#include "Frac.h"
#include <iostream>

int gcd(int a, int b)
{
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

Frac::Frac() {
	num = 1; den = 1;
}

Frac::Frac(int n, int d) {
	num = n; den = d;
}

int Frac::operator<(Frac f2) {
	return (num * f2.den) < (f2.num * den);
}

Frac Frac::operator+(Frac r) {
	Frac res;
	int t;
	res.den = den * r.den;
	res.num = num * r.den + den * r.num;
	t = gcd(res.num, res.den);
	res.num /= t;
	res.den /= t;
	return res;
}

Frac Frac::operator*(Frac r) {
	Frac res;
	int t;
	res.num = num * r.num;
	res.den = den * r.den;
	t = gcd(res.num, res.den);
	res.num /= t;
	res.den /= t;
	return res;
}

Frac Frac::operator*(int t) {
	Frac res;
	res.den = den;
	res.num = t * num;
	return res;
}

Frac Frac::operator/(Frac r) {
	Frac res;
	int t;
	t = r.den;
	r.den = r.num;
	r.num = t;
	t = 0;
	res.num = num * r.num;
	res.den = den * r.den;
	t = gcd(res.num, res.den);
	res.num /= t;
	res.den /= t;
	return res;
}
void Frac::info() {
	std::cout << num << " / " << den << "\n";
}