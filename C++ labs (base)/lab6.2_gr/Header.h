#pragma once
const int MAX = 5;

template <class T>
class Container {
public:
	int n;
	T data[MAX];
	Container();
	void add(T x);
	void del();
	void adding();
	void info();
	class Full{};
	class Empty{};
	class Less{};
};

template <class T>
Container<T>::Container() {
	n = 0;
}

template <class T>
void Container<T>::add(T x) {
	if (n < MAX) {
		data[n] = x;
		n++;
	}
	else {
		throw Container<T>::Full();
	}
}

template <class T>
void Container<T>::del() {
	if (n > 0) {
		n--;
	}
	else {
		throw Container<T>::Empty();
	}
	
}

template <class T>
void Container<T>::adding() {
	T temp;
	temp = data[0];
	if (n < 3) {
		throw Container<T>::Less();
	}
	else {
		for (int i = 1; i < n; i++) {
			temp += data[i];
		}
	}
	std::cout << "adding: " << temp << "\n";
}

template <class T>
void Container<T>::info() {
	std::cout << "Mas: ";
	for (int i = 0; i < n; i++) {
		std::cout << data[i] << " ";
	}
	std::cout << "\n";
}
