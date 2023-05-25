#pragma once
#include <vector>

using namespace std;

class Rotor
{
private:
	int position;
	vector<int> scramble;
	Rotor* reference;
public:
	Rotor();
	Rotor(int);
	void rotate();
	int getPos(int);

};