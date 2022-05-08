#include <iostream>
#include <vector>
#include <map>
#include "Cardcounting.h"

using namespace std;

cardcounting::cardcounting() : number(0),deckremains(312),truenum(0),cheatingon(1) {}

void cardcounting::countcards(char c) {
	if (c == '2' || c == '3' || c == '4' || c == '5' || c == '6') {
		number++;
	}
	else if (c == '7' || c == '8' || c == '9') {
	}
	else {
		number--;
	}
	deckremains--;
	truenum = (double)(number * 52 / deckremains);
}

void cardcounting::display() {
	if (cheatingon) {
		cout << "Current true number: " << truenum << " " << number << " " << deckremains << endl;
	}
}