#pragma once
#include "pch.h"

class Rotor
{
private:
	int position = 0; // The current rotational position of the rotor. This changes when the rotor is rotated
	int notch; // The notch is a signle position that will tell the next rotor in line to rotate
	int scramble[26] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
							 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
		//= { 20, 13, 21, 18, 23, 1, 12, 14, 7, 10, 11, 25, 19,
		//					 4, 9, 2, 0, 17, 16, 15, 6, 22, 5, 4, 3, 8 }; // The order of the scrambled numbers on the rotor
public:
	Rotor();
	int getPosition();
	int getNotch();
	void rotate();
	int getScramblePos(int);
	int getReversePos(int);
	int getPos();
	void UI_Notch();
	void UI_Scramble();
	~Rotor();
};