#pragma once
#include <vector>

using namespace std;

class Rotor
{
private:
	int position; // The current rotational position of the rotor. This changes when the rotor is rotated
	int notch; // The notch is a signle position that will tell the next rotor in line to rotate
	vector<int> scramble; // The order of the scrambled numbers on the rotor
	Rotor* reference; // A reference Rotor. Will use its notch value to determine when to rotate
public:
	Rotor();
	Rotor(int, int, Rotor*);
	void rotate();
	int getScramblePos(int);

};