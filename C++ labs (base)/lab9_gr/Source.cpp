#include <iostream>
#include <deque>
#include <set>
using namespace std;

int main() {
	set<int> s1;
	deque <int> q1;
	for (int i = 0; i < 10; i++) {
		q1.push_back(10 - i);
	}
	for (deque<int>::iterator i = q1.begin(); i != q1.end(); i++) {
		cout << *i << " ";
	}
	cout << endl;
	for(deque<int>::iterator i = q1.begin(); i != q1.end(); i++){
		if (!(*i % 2)) {
			s1.insert(*i);
		}
	}
	for (set<int>::iterator i = s1.begin(); i != s1.end(); i++) {
		cout << *i << " ";
	}
	cout << endl;
	system("pause");
	return 0;
}