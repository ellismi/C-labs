#include <iostream>
#include "Cat.h"

int main() {
	int q, w, e, r;
	std::cout << "input  mass , strong, runtime, furry\n";
	std::cin >> q >> w >> e >> r;
	Cat vb(q, w, e, r);
	vb.CatRun();
	vb.CatVoice();
	vb.damage();
	vb.info();
	return 0;
}