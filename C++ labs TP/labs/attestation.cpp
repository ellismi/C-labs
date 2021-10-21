#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Int_Input.H>
#include <cmath>
using namespace std;

#define M_PI       3.14159265358979323846   // pi

Fl_Double_Window* w = new Fl_Double_Window(300, 300);
Fl_Double_Window* spiral;
Fl_Button* cr = new Fl_Button(5, 5, 40, 20, "create");
Fl_Int_Input* wh = new Fl_Int_Input(20, 45, 40, 20,"w");
Fl_Int_Input* lh = new Fl_Int_Input(75, 45, 40, 20, "h");
Fl_Int_Input* h = new Fl_Int_Input(20, 75, 40, 20, "h");
Fl_Int_Input* th = new Fl_Int_Input(75, 75, 40, 20, "t");
Fl_Button* az[26];

int n, m, t;

void drawing() {
	t = atoi(th->value());
	int x, y;
	double p;
	int c = 0;
	//char point = 'A';
	//string buf = &point;
	for (double i = 0; i < M_PI * 2; i += 0.5) {
		
		p = t * i;
		x = p * cos(i) + n/2;
		y = p * sin(i) + m/2;
		az[c] = new Fl_Button(x, y, 20, 20,"a");
		az[c]->box(FL_FLAT_BOX);
		//point++;
		c++;
	}
}

void ui() {
	//~Fl_Window;
	n = atoi(wh->value()); m = atoi(lh->value());
	spiral = new Fl_Double_Window(n, m);
	cr->deactivate();
	wh->deactivate();
	lh->deactivate();
	drawing();
	spiral->end();
	spiral->show();
}

int main() {
	wh->when(FL_WHEN_CHANGED);
	lh->when(FL_WHEN_CHANGED);
	cr->callback((Fl_Callback*)ui);
	w->end();
	w->show();
	return Fl::run();

}