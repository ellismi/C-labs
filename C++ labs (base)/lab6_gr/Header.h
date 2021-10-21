#pragma once
#include <iostream>
template <class T>
T adder(T* ar, int n)
{
	T temp = ar[0];
	for (int i = 1; i < n; i++) {
		temp = ar[i] + temp;
	}
	return temp;
}

template <class T>
void obr(T* ar, int n) {
	for (int i = 0; i < n; i++) {
		ar[i] = ar[i] * (-1);
	}
}