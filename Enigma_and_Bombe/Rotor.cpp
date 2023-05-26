#include <vector>
#include <iostream>

#include "Rotor.h"

using namespace std;

Rotor::Rotor()
{
	this->position = 0;
	this->notch = 0;
}

Rotor::Rotor(int position, int notch, Rotor* reference)
{
	if(position >= 0 && position < 26)
	{
		this->position = position;
	}
	else
	{
		cout << "Invalid position value" << endl;
	}
	if (notch >= 0 && notch < 26)
	{
		this->notch = notch;
	}
	else
	{
		cout << "Invalid notch value" << endl;
	}
	this->reference = reference;
	}

void Rotor::rotate()
{
	if (this->position == 25)
	{
		this->position = 0;
	}
	else
	{
		position++;
	}
}

int Rotor::getScramblePos(int input)
{
	if (input >= 0 && input < 26)
	{
		return scramble[input];
	}
	else
	{
		cout << "Invalid position argument for Rotor::getPos" << endl;
		return -1;
	}
}