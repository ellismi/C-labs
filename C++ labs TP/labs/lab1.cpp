// Lab 1 - polish notation

#include <iostream>
#include <string>
#include <stack>
#include <cmath>

#define M_PI       3.14159265358979323846   // pi
#define M_PI_2     1.57079632679489661923   // pi/2
using namespace std;

double check_s(string x, double in) {
	string s = "sin", c = "cos", t = "tan";
	if (x == s) {
		return sin(in);
	}
	if (x == c) {
		return cos(in);
	}
	if (x == t) {
		return sin(in)/cos(in);
	}
}

double znak(double a, double b, string x) {
	if (x == "+") {
		return a + b;
	}
	if (x == "-") {
		return a - b;
	}
	if (x == "*") {
		return a * b;
	}
	return 0;
}

int main() {
	stack <double> test;
	int i = 0;
	double temp = 0.5;
	cin >> i;
	do {
		test.push(temp);
		while (i--) {
			string x;
			cin >> x;
			double a, b;
			if (x == "+" || x == "-" || x == "*") {
				a = test.top();
				test.pop();
				b = test.top();
				test.pop();
				test.push(znak(b, a, x));
			}
			else if (x == "x") {
				test.push(temp);
			}
			else {
				a = test.top();
				test.pop();
				test.push(check_s(x, a));
			}
		}
		if (!test.top()) {
			cout << "Indentity";
		}
		else {
			cout << "Not an identity" << "\n";
		}
		test.pop();
		cin >> i;
	} while (i);
	return 0;
}