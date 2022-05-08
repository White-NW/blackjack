#include "Blackjack.h"

bj::bj() :
	cur_player(NULL),
	dealer(),
	player{},
	betamount{}
	{}

int bj::size() {
	return player.size();
}

void bj::init() {
	dealer.clear();
	player.clear();
	player.emplace_back();
	betamount.clear();
	cur_player = &player[0];
}

void bj::bet(int n) {
	betamount.emplace_back(n);
}

void bj::draw(char c, char card) {
	if (c == 'd') { // draw for dealer
		dealer.draw(card);
	}
	else if (c == 'p') { // draw for player
		cur_player->draw(card);
	}
}

void bj::display(bool d2) { // Only shows dealer first card if d2 is false
	cout << endl;
	if (cur_player == &dealer) {
		cout << "* ";
	}
	cout << "Dealer:";
	if (d2) {
		for (int i = 0; i < dealer.size(); ++i) {
			cout << " " << dealer.hand[i];
		}
		cout << "      " << dealer.val;
		if (dealer.soft && dealer.val <= 11) { // soft value
			cout << " or " << dealer.val + 10;
		}
		cout << endl;
	}
	else {
		cout << " " << dealer.hand[0] << " ?" << endl;
	}

	for (int i = 0; i < player.size(); ++i) {
		if (cur_player == &player[i]) {
			cout << "* ";
		}
		cout << "$" << betamount[i] << " Player" << i + 1 << ":";
		for (int o = 0; o < player[i].size(); ++o) {
			cout << " " << player[i].hand[o];
		}
		cout << "      " << player[i].val;
		if (player[i].soft && player[i].val <= 11) { // soft value
			cout << " or " << player[i].val + 10;
		}
		cout << endl;
	}
}

void bj::setcurplayer(int i) {
	if (i == -1) {
		cur_player = &dealer;
		return;
	}
	cur_player = &player[i];
}

void bj::quickdraw(vector <char> *sdeck, cardcounting *cc) {
	draw('p', sdeck->back());
	cc->countcards(sdeck->back());
	sdeck->pop_back();
}

void bj::option(int i, vector <char> *sdeck, cardcounting *cc, int &bank) {
	bool firstdraw = 1;
	char s = 0;
	while (player[i].val <= 21) { // player[i]'s turn
		display(0);

		if (firstdraw) { // first draw : double down and split available
			if (player[i].size() == 1) { // just splitted, haven't draw the second card yet
				//cout << (&player[i] == cur_player) << endl;
				quickdraw(sdeck, cc);
				if (player[i].hand[0] == 'A') { // draw only 1 card on Aces split
					break;
				}
			}
			firstdraw = 0;

			if (player[i].hand[0] == player[i].hand[1]) { // pair pair
				cout << "hit/stand/double/split(h/s/d/p): ";
				cin >> s;

				if (s == 'p') { // split
					if (bank < betamount[i]) {
						cout << "You are too poor for this." << endl;
						firstdraw = 1;
						continue;
					}
					else {
						bank -= betamount[i];
						betamount.emplace_back(betamount[i]);
					}
					(player[i].hand).pop_back();
					//cout << (&player[i] == cur_player) << endl;
					player[i].val = player[i].chart[player[i].hand[0]];
					player.emplace_back(player[i]);
					cur_player = &player[i]; // reset cur_player due to deep copy*
					//cout << (&player[i] == cur_player) << endl;
					firstdraw = 1;
					continue; // draw again.
				}
				else if (s == 's') {
					break;
				}
				else if (s == 'h') {
					quickdraw(sdeck, cc); // draw a card
					if (player[i].val > 21) {
						cout << "Player Too Many" << endl;
						break;
					}
					else {
						continue;
					}
				}
				else if (s == 'd') {
					if (bank < betamount[i]) {
						betamount[i] += bank;
						cout << "Double for Less" << endl;
						bank = 0;
					}
					else {
						bank -= betamount[i];
						betamount[i] += betamount[i];
					}
					quickdraw(sdeck, cc); // draw a card

					if (player[i].val > 21) {
						cout << "Player Too Many" << endl;
					}
					break;
				}
				else {
					cout << "Invalid Input" << endl;
					firstdraw = 1;
					continue;
				}
			}

			cout << "hit/stand/double(h/s/d): ";
			cin >> s;
			if (s == 's') {
				break;
			}
			else if (s == 'h') {
				quickdraw(sdeck, cc); // draw a card
				if (player[i].val > 21) {
					cout << "Player Too Many" << endl;
					break;
				}
				else {
					continue;
				}
			}
			else if (s == 'd') {
				if (bank < betamount[i]) {
					betamount[i] += bank;
					cout << "Double for Less" << endl;
					bank = 0;
				}
				else {
					bank -= betamount[i];
					betamount[i] += betamount[i];
				}
				quickdraw(sdeck, cc); // draw a card
				if (player[i].val > 21) {
					cout << "Player Too Many" << endl;
				}
				break;
			}
			else {
				cout << "Invalid Input" << endl;
				firstdraw = 1;
				continue;
			}
		}
		else {
			cout << "hit/stand(h/s): ";
			cin >> s;
			if (s == 's') {
				break;
			}
			else if (s == 'h') {
				quickdraw(sdeck, cc); // draw a card
				if (player[i].val > 21) {
					cout << "Player Too Many" << endl;
					break;
				}
				else {
					continue;
				}
			}
			else {
				cout << "Invalid Input" << endl;
				continue;
			}
		}
	}
}

void bj::compare(vector <char>* sdeck, cardcounting* cc, int& bank) {
	display(1);
	for (int i = 0; i < player.size(); ++i) {
		if (!player[i].bust) {
			break;
		}
		else if (i == player.size() - 1) {
			cout << "All players lost." << endl;
			return;
		}
	}

	// Dealer turn
	while (!(dealer.val >= 17 || (dealer.val >= 8 && dealer.val <= 11 && dealer.soft))) {
		quickdraw(sdeck, cc); // draw a card
		display(1);
		if (dealer.val > 21) {
			cout << "Dealer Too Many" << endl << "Player Wins" << endl;
			break;
		}
	}
	

	if (dealer.bust) { // Dealer lost
		for (int i = 0; i < player.size(); ++i) {
			if (!player[i].bust) {
				bank += 2 * betamount[i];
			}
		}
		return;
	}

	// Counting Dealer number
	if (dealer.soft == 1 && dealer.val <= 11) {
		dealer.val += 10;
	}

	// Counting Players numbers
	for (int i = 0; i < player.size(); ++i) {

		if (player[i].soft == 1 && player[i].val <= 11) {
			player[i].val += 10;
		}

		cout << player[i].val << ":" << dealer.val << endl;
		if (player[i].val > dealer.val && player[i].val <= 21) {
			cout << "Player " << i+1 << " Won" << endl;
			bank += 2 * betamount[i];
		}
		else if (player[i].val < dealer.val || player[i].val > 21) {
			cout << "Player " << i+1 << " Lost" << endl;
		}
		else {
			cout << "Player " << i+1 << " Pushed" << endl;
			bank += betamount[i];
		}
	}
}


int bj::blackjackcheck() {
	if (dealer.val == 11 && dealer.soft) {
		if (player[0].val == 11 && player[0].soft) {
			return -1;
		}
		else {
			return -2;
		}
	}
	if (player[0].val == 11 && player[0].soft) {
		return 1;
	}
	return 0;
}