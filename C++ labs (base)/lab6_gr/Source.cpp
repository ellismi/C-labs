#include <iostream>
#include <ctime>
#include "Header.h"
#include "Frac.h"
using namespace std;

int main() {
	int array[5];
	Frac ar[5];
	srand(time(0));
	cout << "array before: ";
	for (int i = 0; i < 5; i++) {
		array[i] = rand() % 10;
		cout << array[i] << " ";
	}
	cout << "\nadd after: "<<adder(array, 5) << endl;
	obr(array, 5);
	cout << "obr after: ";
	for (int i = 0; i < 5; i++) {
		cout << array[i] << " ";
	}
	cout << endl;
	cout << "check right: " << adder(array, 5) << endl;
	cout << "array before: ";
	for (int i = 0; i < 5; i++) {
		ar[i].num = rand() % 10;
		ar[i].den = rand() % 10;
		cout << ar[i].num << "/" << ar[i].den << " ";
	}
	cout << "\nadd after: ";
	Frac d = adder(ar, 5), y;
	d.info();
	cout << "obr after: ";
	obr(ar, 5);
	for(int i = 0; i < 5; i++) {
		cout << array[i] << " ";
		cout << ar[i].num << "/" << ar[i].den << " ";
	}
	d = adder(ar, 5);
	cout << "\ncheck right: ";
	d.info();
	
	
	return 0;
}