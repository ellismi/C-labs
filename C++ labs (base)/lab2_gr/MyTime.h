#pragma once
#ifndef MYTIME_H
#define MYTIME_H
class MyTime
{
public:
	int h, m, s;
	MyTime();
	MyTime(int h, int m, int s);
	MyTime add(MyTime t);
	MyTime operator+(MyTime t2);
	MyTime operator-(MyTime t2);
	MyTime operator*(int d);
	void info();
};
MyTime operator*(int d, MyTime t1);
#endif // !MYTIME_H



