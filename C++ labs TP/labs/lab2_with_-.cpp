// Lab 2 - polish notation, calculating
// Addition: calculating may be like example: - 3 + 5 ( - 5 * 6 )

#include <iostream>
#include <locale>
#include <queue>
#include <stack>
#include <string>
using namespace std;

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
	if (x == "/") {
		return a / b;
	}
	return 0;
}

int pr_s(string x) {
	if (isdigit(x.c_str()[0]) || x.c_str()[0] == '.') return 6;
	switch (x.c_str()[0]) {
	case '+':
	case '-':
		return 2;
	case '*':
	case '/':
		return 4;
	case '(':
		return 0;
	default:
		break;
	}
}

int pr_in(string x) {
	if (isdigit(x.c_str()[0]) || x.c_str()[0] == '.') return 5;
	switch (x.c_str()[0]) {
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 3;
	case '(':
		return 7;
	case ')':
		return 0;
	default:
		break;
	}
}
bool check_z(char a) {
	switch (a) {
	case '+':
	case '-':
	case '*':
	case '/':
		return true;
	default:
		return false;
	}
}

int main(int ac, char* av[]) {
	string* in;
	queue<string> str;
	queue<string> ps;
	stack<double> ans;
	stack<string> temp;  // stack
	int c = 1;
	
	if (ac < 2) {
		cout << "Need arguments. For example: 2 + 2\n";
		return 1;
	}

	str.push("(");
	for (int i = 1; i < ac; i++) {
		if (av[i][0] == '-' && str.back() == "(") {
			str.push("(");
			str.push("0");
			str.push(av[i]);
			str.push(av[++i]);
			str.push(")");
		}
		else {
			str.push(av[i]);
		}
	}
	str.push(")");
	in = new string[str.size()];
	c = str.size();
	for (int i = 0; i < c - 1; i++) {
		in[i] = str.front();
		str.pop();
	}
	in[c - 1] = str.front();

	// in/correct checker
	for (int i = 0; i < c - 1; i++) {
		if (((isdigit(in[i][0]) || in[i][0] == '.' || in[i][0] == ')') &&
			(isdigit(in[i + 1][0]) || in[i + 1][0] == '.' ||
				in[i + 1][0] == '(')) ||
				((check_z(in[i][0]) || in[i][0] == '(') &&
			(check_z(in[i + 1][0]) || in[i + 1][0] == ')'))) {
			cout << "wrong input" << endl;
			return 0;
		}
	}
	temp.push("(");

	for (int i = 1; i < c; i++) {
		int t = pr_s(temp.top()) - pr_in(in[i]);
		if (t < 0) {
			temp.push(in[i]);
		}
		else if (t > 0) {
			ps.push(temp.top());
			temp.pop();
			i--;
		}
		else {
			temp.pop();
		}
	}
	c = ps.size();

	for (int i = 0; i < c; i++) {
		string x = ps.front();
		if(i+1!=c) ps.pop();
		if (x == "+" || x == "-" || x == "*" || x == "/") {
			double a, b;
			a = ans.top();
			ans.pop();
			b = ans.top();
			ans.pop();
			ans.push(znak(b, a, x));

		}
		else {
			ans.push(atof(x.c_str()));
		}
	}
	cout << ans.top() << endl;

	//system("pause");
	return 0;
}