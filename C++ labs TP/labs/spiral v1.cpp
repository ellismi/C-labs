#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <cmath>

using namespace std;

int h, t;
Fl_Input *inputN;
Fl_Input *inputM;
Fl_Input *inputH;
Fl_Input *inputT;
Fl_Button *buttons[26];

void spirall() {
	t = atoi(inputT->value());
	h = atoi(inputH->value());
	int x, y;
	int j = 0;
	double s;
	for (double i = 0; i < M_PI * 2; i +=0.5) {
		s = t * i;
		x = s * cos(i);
		y = s * sin(i);
		buttons[j] = new Fl_Button(x, y, 10, 10);
		j++;
	}
}

void secondWindow() {
	int n, m;
	n = atoi(inputN->value());
	m = atoi(inputM->value());
	Fl_Window *secondWindow = new Fl_Window(n, m, "second");	
	
	spirall();
	
	secondWindow->end();
	secondWindow->show();
}

void  mainCreateUI() {
	inputN = new Fl_Input(10, 10, 50, 30);
	inputM = new Fl_Input(80, 10, 50, 30);
	inputH = new Fl_Input(10, 60, 50, 30);
	inputT = new Fl_Input(80, 60, 50, 30);
	
	Fl_Button *button = new Fl_Button(45, 100, 50, 30);
	button->callback((Fl_Callback*)secondWindow);	
}

int main()
 {

	 Fl_Window *mainWindow = new Fl_Window(150, 200, "first");

	 mainCreateUI();
	 
	 mainWindow->end();
	 mainWindow->show();
	 return Fl::run();
 }
