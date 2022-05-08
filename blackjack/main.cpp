#include <iostream>
#include <cstdlib>
#include <random>
#include <vector>
#include <map>
#include "Blackjack.h"
using namespace std;

int main() {
	bj game;
	cardcounting cc;
	int bank = 5000; // bankroll
	char deck[312];
	vector <char> sdeck; // shuffled deck
	char card[13] = { 'A','2','3','4','5','6','7','8','9','T','J','Q','K' };
	for (int i = 0; i < 13; ++i) { // filling the deck
		for (int o = 0; o < 24; ++o) {
			deck[i * 24 + o] = card[i];
		}
	}
	random_device rd; // obtain a random number from hardware
	mt19937 rng(rd()); // seed the generator
	for (int i = 0; i < 312; ++i) { // shuffle the deck
		uniform_int_distribution<int> uni(i, 311);
		auto randint = uni(rng);
		sdeck.emplace_back(deck[randint]);
		swap(deck[randint], deck[i]);
	}
	

	int tempint;
	while (1) { // game starts

		cout << "-------------------" << endl;
		game.init(); // reset value
		cc.display(); // display cardcounting value if on
		cout << "Starting stack: " << bank << endl;
		while (true) {
			cout << "Place your bet: ";
			cin >> tempint;
			if (tempint <= 0) {
				cout << "Your income today is: " << bank - 5000 << endl << "Bye" << endl;
				return 0;
			}
			else if (tempint > bank) {
				cout << "You are too poor for this." << endl;
			}
			else {
				break;
			}
		}
		bank -= tempint;
		game.bet(tempint);

		// draw first 2 cards
		game.draw('p',sdeck.back());
		cc.countcards(sdeck.back());
		sdeck.pop_back();
		game.draw('d', sdeck.back());
		cc.countcards(sdeck.back());
		sdeck.pop_back();
		game.draw('p', sdeck.back());
		cc.countcards(sdeck.back());
		sdeck.pop_back();
		game.draw('d', sdeck.back());
		cc.countcards(sdeck.back());
		sdeck.pop_back();

		switch (game.blackjackcheck()) {
			case -2:
				game.display(1);
				cout << "Dealer Blackjack!" << endl << "All Players Lost." << endl;
				break;
			case -1:
				game.display(1);
				cout << "Dealer Blackjack!" << endl << "Player Blackjack!" << endl << "Pushed." << endl;
				bank += tempint;
				break;
			case 1:
				game.display(1);
				cout  << "Player Blackjack!" << endl << "Player Won." << endl;
				bank += tempint * 5 / 2;
				break;
			default:
				tempint = -1;
				break;
		}
		if (tempint != -1) { // next game
			continue;
		}
		
		// game starts
		for (int i = 0; i < game.size(); ++i) { // how many players on table
			game.setcurplayer(i);
			game.option(i,&sdeck,&cc,bank);
		}
		game.setcurplayer(-1);
		game.compare(&sdeck, &cc, bank);
	}

	return 0;
}