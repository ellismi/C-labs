#include <iostream>
#include <string>
#include <stack>
#include <cmath>

#define M_PI       3.14159265358979323846   // pi
//#define M_PI_2     1.57079632679489661923   // pi/2
using namespace std;

double check_s(string x, double in) {
	if (x == "sin") {
		return sin(in);
	}
	if (x == "cos") {
		return cos(in);
	}
	if (x == "tan") {
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
	stack <double> t1, t2, t3;
	int i = 0;
	double ts1 = 0.0, ts2 = 0.5, ts3 = M_PI;
	cin >> i;
	do {
		while (i--) {
			string x;
			cin >> x;
			double a, b;
			if (x == "+" || x == "-" || x == "*") {
				a = t1.top();
				t1.pop();
				b = t1.top();
				t1.pop();
				t1.push(znak(b, a, x));

				a = t2.top();
				t2.pop();
				b = t2.top();
				t2.pop();
				t2.push(znak(b, a, x));

				a = t3.top();
				t3.pop();
				b = t3.top();
				t3.pop();
				t3.push(znak(b, a, x));
			}
			else if (x == "x") {
				t1.push(ts1);
				t2.push(ts2);
				t3.push(ts3);
			}
			else {
				a = t1.top();
				t1.pop();
				t1.push(check_s(x, a));

				a = t2.top();
				t2.pop();
				t2.push(check_s(x, a));

				a = t3.top();
				t3.pop();
				t3.push(check_s(x, a));
			}
		}
		if (!t1.top() && !t2.top() && !t3.top()) {
			cout << "Indentity";
		}
		else {
			cout << "Not an identity" << "\n";
		}
		t1.pop();
		t2.pop();
		t3.pop();

		cin >> i;
	} while (i);
	//system("pause");
	//for windows
	return 0;
}