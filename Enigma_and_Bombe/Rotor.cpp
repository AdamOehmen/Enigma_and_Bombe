#include <vector>
#include <iostream>

#include "Rotor.h"

using namespace std;

// Default Constructor, sets start position and notch to '0' if no values are given
Rotor::Rotor()
{
	this->notch = 0;
}

// Overloaded Rotor constructor that sets notch, and reference to user specified values.
Rotor::Rotor(int notch, Rotor* reference)
{
	if (notch >= 0 && notch < 26)
	{
		this->notch = notch;
	}
	else
	{
		cout << "Invalid notch value" << endl;
		this->notch = 0;
	}
	this->reference = reference;
	}

// Simulates a rotation of the Rotor by incrementing its position 
// value and wrapping around to 0 when the position hits 25
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

// Returns the Rotors new value based on the previous Rotor's output
// param input: the position outputted by the previous output
// returns output: the new scrambled position value
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