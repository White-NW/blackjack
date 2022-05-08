#include "Player.h"
#include "Cardcounting.h"

class bj{
	p dealer; // dealer hand
	vector <p> player; // player hand
	p *cur_player; // pointer to current player
	vector <int> betamount;
	void quickdraw(vector <char>* sdeck, cardcounting* cc);
public:
	bj();
	int size();
	void init();
	void bet(int n);
	void draw(char c, char card);
	void display(bool d2);
	int blackjackcheck();
	void setcurplayer(int i);
	void option(int i, vector <char>* sdeck, cardcounting *cc, int &bank);
	void compare(vector <char>* sdeck, cardcounting* cc, int& bank);
};