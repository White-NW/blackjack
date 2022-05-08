#include "Player.h"

p::p(){
	hand.resize(0);
	val = 0;
	bust = 0;
	soft = 0;
	chart['A'] = 1;
	chart['2'] = 2;
	chart['3'] = 3;
	chart['4'] = 4;
	chart['5'] = 5;
	chart['6'] = 6;
	chart['7'] = 7;
	chart['8'] = 8;
	chart['9'] = 9;
	chart['T'] = 10;
	chart['J'] = 10;
	chart['Q'] = 10;
	chart['K'] = 10;
}

void p::clear() {
	hand.clear();
	val = 0;
	bust = 0;
	soft = 0;
}

void p::draw(char c) {
	//cout << c << endl;
	hand.emplace_back(c);
	//cout << "1" << endl;
	if (c == 'A') soft = 1;
	//cout << "2" << endl;
	val += chart[c];
	//cout << "3" << endl;
	if (val > 21) {
		bust = 1;
	}
}

int p::size() {
	return hand.size();
}

