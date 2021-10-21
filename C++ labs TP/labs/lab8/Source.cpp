#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <string>
using namespace std;
Fl_Double_Window* window;
Fl_Button* andd, * andn, * ord, * orn, *b[40];
Fl_PNG_Image* a0, * an, * o0, * on;
int i = 0;
int type = 0;

struct nodes {
	Fl_Button& in1, & in2, & out;
};


static void removes() {
	cout << Fl::event_x() << " " << Fl::event_y() << endl;
}

static void upd_but(Fl_Button* a) {
	
	if(i < 39){
		b[i] = new Fl_Button(15 * i, 150, a->w(), a->h());
		if (andd->changed() == 128) {
			b[i]->image(a0);
			//b[i]->callback((Fl_Callback*)removes);
		}
		if (andn->changed() == 128) {
			b[i]->image(an);
			//b[i]->callback((Fl_Callback*)removes);
		}
		if (ord->changed() == 128) {
			b[i]->image(o0);
			//b[i]->callback((Fl_Callback*)removes);
		}
		if (orn->changed() == 128) {
			b[i]->image(on);
			//b[i]->callback((Fl_Callback*)removes);
		}
		window->add(b[i]);
		window->redraw();
		i++;
	}
}

static void making_ui() {
	a0 = new Fl_PNG_Image("and.png");
	an = new Fl_PNG_Image("andn.png");
	o0 = new Fl_PNG_Image("or.png");
	on = new Fl_PNG_Image("orn.png");

	andd = new Fl_Button(60, 20, a0->w(), a0->h());
	andn = new Fl_Button(140, 15, an->w(), an->h());
	ord = new Fl_Button(220, 20, o0->w(), o0->h());
	orn = new Fl_Button(300, 20, on->w(), on->h());
	andd->align(FL_ALIGN_CENTER);
	andn->align(FL_ALIGN_CENTER);
	ord->align(FL_ALIGN_CENTER);
	orn->align(FL_ALIGN_CENTER);


	andd->image(a0);
	andn->image(an);
	ord->image(o0);
	orn->image(on);
	andd->callback((Fl_Callback*)upd_but);
	andn->callback((Fl_Callback*)upd_but);
	ord->callback((Fl_Callback*)upd_but);
	orn->callback((Fl_Callback*)upd_but);

	//window->callback((Fl_Callback*)removes);
}


int main() {
	window = new Fl_Double_Window(420, 550);
	window->begin();
	making_ui();


	window->end();
	window->show();
	return Fl::run();
}
