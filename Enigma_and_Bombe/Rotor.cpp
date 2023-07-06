#include <vector>
#include <iostream>

#include "Rotor.h"

// Default Constructor, sets start position and notch to '0' 
// and reference rotor to NULL if no values are given
Rotor::Rotor()
{
	this->notch = 0;
	this->reference = NULL;
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
	//this->reference = reference;
	}

int Rotor::getPosition()
{
	return this->position;
}

// Returns notch position
int Rotor::getNotch() 
{
	return this->notch;
}

Rotor* Rotor::getReference()
{
	return this->reference;
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
		return scramble[(input + position) % 26];
	}
	else
	{
		cout << "Invalid position argument for Rotor::getScramblePos" << endl;
		return -1;
	}
}

// Find the position of a value, to work through the rotor backwards
int Rotor::getReversePos(int input)
{
	if (input >= 0 && input < 26)
	{
		// (input + position) % 26 simulates the rotations
		int newInput = (input + this->position) % 26;
		// Check all positions on the rotor
		for (int i = 0; i <= 25; i++) {
			if (scramble[i] == newInput) {
				return i;
			}
		}
	}
	else {
		cout << "Invalid input value for Rotor::getReversePos" << endl;
		return -1;
	}
}

int Rotor::getPos() {
	return this->position;
}

Rotor::~Rotor()
{
}