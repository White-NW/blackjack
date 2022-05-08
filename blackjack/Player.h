#include <iostream>
#include <vector>
#include <map>	

using namespace std;

class p {
public:
	vector <char> hand;
	int val;
	bool soft;
	bool bust;
	map <char, int> chart; // value chart
	//char gethand(int index);
	//bool getsoft();
	//int val();
	int size();
	void draw(char c);
	void clear();
	p();
};