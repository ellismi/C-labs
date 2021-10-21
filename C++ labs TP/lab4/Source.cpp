#include <iostream>
#include <vector>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Light_Button.H>
using namespace std;
int n = 0;
Fl_Double_Window* window, * field;
Fl_Int_Input* text;
Fl_Button* create, * yy[40][40], * start;
Fl_Light_Button* lamp;
bool lifes[40][40];
bool ver = true;

// exit
static void restart() {
	if (window->visible()) {
		delete field;
		delete window;
		exit(0);
	}
}

//life of krestivi  born and die
static void life(void* d) {
	if (!lamp->value()) {
		Fl::remove_timeout(life, d);
	}
	else {
		Fl::repeat_timeout(.50, life, d);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int t;
			t = yy[(i - 1 + n) % n][(j - 1 + n) % n]->value() + yy[(i - 1 + n) % n][j]->value() +
				yy[(i - 1 + n) % n][(j + 1) % n]->value() + yy[i][(j + 1) % n]->value() + yy[(i + 1) % n][(j + 1) % n]->value() +
				yy[(i + 1) % n][j]->value() + yy[(i + 1) % n][(j - 1 + n) % n]->value() + yy[i][(j - 1 + n) % n]->value();
			if (yy[i][j]->value()) {
				if (t < 2 || t > 3) lifes[i][j] = false;
				else lifes[i][j] = true;
			}
			else {
				if (t == 3) lifes[i][j] = true;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (lifes[i][j]) {
				yy[i][j]->value(1);
				yy[i][j]->copy_label("X");
			}
			else {
				yy[i][j]->value(0);
				yy[i][j]->copy_label("");
			}
		}
	}
}

//update button  x or 0
static void update(Fl_Button* a) {
	if (a->value()) {
		a->copy_label("");
		a->value(0);
	}
	else {
		a->value(1);
		a->copy_label("X");
	}
}

//update field of krestiki
static void clicks(int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			yy[i][j] = new Fl_Button(i * 20, j * 20, 20, 20);
			yy[i][j]->callback((Fl_Callback*)update);
		}
	}
}

//create window with krestiki
static void cb_create() {
	n = atoi(text->value());
	if (n < 9 || n > 30) return;
	if (ver) {
		field = new Fl_Double_Window(n * 20, n * 20, "FIELD");
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				lifes[i][j] = false;
			}
		}
		field->begin();
		clicks(n);
		field->end();
		field->show();
		ver = false;
	}
	else {
		field->resize(200, 200, n * 20, n * 20);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				lifes[i][j] = false;
			}
		}
		field->begin();
		clicks(n);
		field->end();
		field->show();
	}
}

// create main window
static void making_ui() {
	text = new Fl_Int_Input(100, 10, 40, 20, "Size:");
	text->align(FL_ALIGN_LEFT);
	create = new Fl_Button(90, 45, 50, 20, "Create");
	create->callback((Fl_Callback*)cb_create);
	lamp = new Fl_Light_Button(90, 80, 50, 20, "Start");
	lamp->value(0);
	lamp->callback((Fl_Callback*)life);
	window->callback((Fl_Callback*)restart);
}

int main() {
	window = new Fl_Double_Window(200, 150, "LIFE");
	window->begin();
	making_ui();
	window->show();
	window->end();
	return Fl::run();
}