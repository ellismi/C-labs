#include <iostream>
#include <string>
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Int_Input.H>
#include <sstream>

using namespace std;

Fl_Double_Window* window; // main window
Fl_Button* A, * B, * C, * CR, * op, * eq, * sc;
Fl_Light_Button* a[16], * b[16], * c[16]; 
Fl_Int_Input* AA, * BB, * CC; // textbox
int znak = 0, scd = 0;
int ad = 0, bd = 0, cd = 0; // integer
bool fl = false; // CR
static void update_dec();

//from light but to textinput
static void cb_ad() {
	int t = 0;
	for (int i = 0; i < 16; i++) {
		if (a[i]->value()) {
			t += pow(2, i);
		}
	}
	ad = t;
	stringstream ss;
	switch (scd)
	{
	case 0:
		ss << dec << ad;
		break;
	case 1:
		ss << oct << ad;
		break;
	case 2:
		ss << hex << ad;
		break;
	default:
		break;
	}
	string str = ss.str();
	AA->value(str.c_str());
}
static void cb_bd() {
	int t = 0;
	for (int i = 0; i < 16; i++) {
		if (b[i]->value()) {
			t += pow(2, i);
		}
	}
	bd = t;
	stringstream ss;
	switch (scd)
	{
	case 0:
		ss << dec << bd;
		break;
	case 1:
		ss << oct << bd;
		break;
	case 2:
		ss << hex << bd;
		break;
	default:
		break;
	}
	string str = ss.str();
	BB->value(str.c_str());
}
static void cb_cd() {
	for (int i = 0; i < 16; i++) {
		c[i]->value(cd & (1 << i));
	}
}

//from textinput to light button
static void cb_ta() {
	int t = atoi(AA->value());
	ad = t;
	for (int i = 0; i < 16; i++) {
		a[i]->value(ad & (1 << i));
	}
}
static void cb_tb() {
	int t = atoi(BB->value());
	bd = t;
	for (int i = 0; i < 16; i++) {
		b[i]->value(bd & (1 << i));
	}
}

//change operation
static void update_znak(Fl_Button*) {
	znak++;
	if (znak == 9) znak = 0;
	switch (znak)
	{
	case 0:
		op->label("+");
		break;
	case 1:
		op->label("-");
		break;
	case 2:
		op->label("*");
		break;
	case 3:
		op->label("/");
		break;
	case 4:
		op->label("<<");
		break;
	case 5:
		op->label(">>");
		break;
	case 6:
		op->label("&");
		break;
	case 7:
		op->label("|");
		break;
	case 8:
		op->label("~");
		break;
	}
}

//change system chars
static void update_dec() {
	scd++;
	if (scd == 3) scd = 0;
	switch (scd)
	{
	case 0:
		sc->label("10");
		break;
	case 1:
		sc->label("8");
		break;
	case 2:
		sc->label("16");
		break;
	}
	stringstream sa, sb, sc;
	switch (scd)
	{
	case 0:
		sa << dec << ad;
		sb << dec << bd;
		sc << dec << cd;
		break;
	case 1:
		sa << oct << ad;
		sb << oct << bd;
		sc << oct << cd;
		break;
	case 2:
		sa << hex << ad;
		sb << hex << bd;
		sc << hex << cd;
		break;
	default:
		break;
	}
	string str = sa.str();
	AA->value(str.c_str());
	sa.clear(); str.clear();
	str = sb.str();
	BB->value(str.c_str());
	sb.clear(); str.clear();
	str = sc.str();
	CC->value(str.c_str());
	sc.clear(); str.clear();

}

// cb for ==
static void counter() {
	fl = false;
	int n = 16;
	short int temp = ad;
	switch (znak)
	{
	case 0:
		cd = ad + bd;
		if (ad > SHRT_MAX - bd) fl = true;
		break;
	case 1:
		cd = ad - bd;
		if (ad < SHRT_MAX + bd) fl = true;
		break;
	case 2:
		cd = ad * bd;
		if (ad > SHRT_MAX / bd) fl = true;
		if (ad < SHRT_MIN / bd) fl = true;
		break;
	case 3:
		if (bd != 0) cd = ad / bd;
		break;
	case 4:
		cd = ad << bd;
		while (--n && !(temp & SHRT_MIN)) temp <<= 1;
		if (n + bd >= 16)
			fl = true;
		break;
	case 5:
		cd = ad >> bd;
		break;
	case 6:
		cd = ad & bd;
		break;
	case 7:
		cd = ad | bd;
		break;
	case 8:
		cd = ~ad;
		break;
	default:
		break;
	}
	
	for (int i = 0; i < 16; i++) {
		c[i]->value(cd & (1 << i));
	}
	stringstream ss;
	switch (scd)
	{
	case 0:
		ss << dec << cd;
		break;
	case 1:
		ss << oct << cd;
		break;
	case 2:
		ss << hex << cd;
		break;
	default:
		break;
	}
	string str = ss.str();
	CC->value(str.c_str());
	if (fl) CR->label("1");
	else CR->label("0");
}

// create interface
void making_ui() {
	A = new Fl_Button(570 - 30 * 17, 75, 30, 30, "A");
	B = new Fl_Button(570 - 30 * 17, 175, 30, 30, "B");
	C = new Fl_Button(570 - 30 * 17, 275, 30, 30, "C");
	CR = new Fl_Button(570 - 30 * 18, 275, 30, 30, "0");
	op = new Fl_Button(570 - 490, 125, 30, 30, "+");
	eq = new Fl_Button(570 - 490, 225, 30, 30, "=");
	sc = new Fl_Button(570 + 55, 25, 40, 30, "10");
	AA = new Fl_Int_Input(570 + 50, 75, 50, 30);
	BB = new Fl_Int_Input(570 + 50, 175, 50, 30);
	CC = new Fl_Int_Input(570 + 50, 275, 50, 30);
	A->box(FL_FLAT_BOX); B->box(FL_FLAT_BOX); C->box(FL_FLAT_BOX); CR->box(FL_FLAT_BOX); op->box(FL_FLAT_BOX); //dec->box(FL_FLAT_BOX);

	for (int i = 0; i < 16; i++) {
		string q = to_string(i);
		a[i] = new Fl_Light_Button(570 - 30 * i, 75, 15, 35);
		a[i]->labelsize(13);
		a[i]->align(FL_ALIGN_TOP);
		a[i]->copy_label(q.c_str());
		a[i]->callback((Fl_Callback*)cb_ad);

		b[i] = new Fl_Light_Button(570 - 30 * i, 175, 15, 35);
		b[i]->labelsize(13);
		b[i]->align(FL_ALIGN_TOP);
		b[i]->copy_label(q.c_str());
		b[i]->callback((Fl_Callback*)cb_bd);

		c[i] = new Fl_Light_Button(570 - 30 * i, 275, 15, 35);
		c[i]->labelsize(13);
		c[i]->align(FL_ALIGN_TOP);
		c[i]->copy_label(q.c_str());
		c[i]->callback((Fl_Callback*)cb_cd);
	}
	AA->insert("0"); BB->insert("0"); CC->insert("0"); CR->label("0");
	AA->callback((Fl_Callback*)cb_ta);
	BB->callback((Fl_Callback*)cb_tb);
	op->callback((Fl_Callback*)update_znak);
	sc->callback((Fl_Callback*)update_dec);
	eq->callback((Fl_Callback*)counter);
	CC->readonly(1);
}

int main() {
	window = new Fl_Double_Window(700, 400);
	window->begin();
	making_ui();
	window->end();
	window->show();
	return Fl::run();
}