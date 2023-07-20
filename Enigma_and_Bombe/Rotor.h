#pragma once
#include "pch.h"

class Rotor
{
private:
	int position = 0; // The current rotational position of the rotor. This changes when the rotor is rotated
	int notch; // The notch is a signle position that will tell the next rotor in line to rotate
	int rtrName;
	string scramble = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
							 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };

public:
	Rotor();
	int getName();
	int getNotch();
	string getScramble();
	void rotate();
	int getYN();
	int getScramblePos(int);
	int getReversePos(int);
	int getPos();
	void UI_Notch();
	void UI_Scramble();
	~Rotor();
};