#include "MyTime.h"
#include <iostream>

MyTime::MyTime() {
	h = 0; m = 0; s = 0;
}

MyTime::MyTime(int h, int m, int s) {
	this->h = h; this->m = m; this->s = s;
	// or MyTime::MyTime(int a, int b, int c)
	// or MyTime::MyTime(int h_, int m_, int s_)
	// not too much bad)
}

MyTime MyTime::add(MyTime t) {
	MyTime res;
	int q = 0;
	res.s = s + t.s;
	if (res.s >= 60) { 
		q = res.s / 60;
		res.s = res.s % 60;
	}
	res.m = m + t.m + q;
	q = 0;
	if (res.m >= 60) {
		q = res.m / 60;
		res.m = res.m % 60;
	}
	res.h = h + t.h + q;
	return res;
}
MyTime MyTime::operator+(MyTime t) {
	MyTime res;
	int q = 0;
	res.s = s + t.s;
	if (res.s >= 60) { 
		q = res.s / 60;
		res.s = res.s % 60;
	}
	res.m = m + t.m + q;
	q = 0;
	if (res.m >= 60) {
		q = res.m / 60;
		res.m = res.m % 60;
	}
	res.h = h + t.h + q;
	return res;
}

MyTime MyTime::operator-(MyTime t) {
	MyTime res;
	int q = 60;
	res.s = s - t.s;
	if (res.s < 0) {
		res.s = q + res.s;
		--res.m;
	}
	res.m = m - t.m;
	if (res.m < 0) {
		res.m = q + res.m;
		--res.h;
	}
	res.h = h - t.h;
	return res;
}

MyTime MyTime::operator*(int d) {
	MyTime res;
	int q = 0;
	res.s = s * d;
	if (res.s >= 60) {
		q = res.s / 60;
		res.s = res.s % 60;
	}
	res.m = m * d + q;
	q = 0;
	if (res.m >= 60) {
		q = res.m / 60;
		res.m = res.m % 60;
	}
	res.h = h * d + q;
	return res;
}
void MyTime::info() {
	std::cout << "time is " << h << "h " << m << "m " << s << "s. \n";
	std::cout << h << ":" << m << ":" << s << "\n";
}
MyTime operator*(int d, MyTime t1) {
	MyTime res;
	int q = 0;
	res.s = t1.s * d;
	if (res.s >= 60) {
		q = res.s / 60;
		res.s = res.s % 60;
	}
	res.m = t1.m * d + q;
	q = 0;
	if (res.m >= 60) {
		q = res.m / 60;
		res.m = res.m % 60;
	}
	res.h = t1.h * d + q;
	return res;
}