#pragma once
#include <vector>

using namespace std;

class Rotor
{
private:
	int position;
	int notch;
	vector<int> scramble;
	Rotor* reference;
public:
	Rotor();
	Rotor(int, int, Rotor*);
	void rotate();
	int getPos(int);

};