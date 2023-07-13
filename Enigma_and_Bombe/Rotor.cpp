#include <vector>
#include <iostream>

#include "Rotor.h"
int lettersToNum(char letter);
char Alp[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
// Default Constructor, sets start position and notch to '0' 
// and reference rotor to NULL if no values are given
Rotor::Rotor()
{
	cout << "These are your rotors, would you like to create a new one?";
	string CLearWhenAddingDataBase;
	cin >> CLearWhenAddingDataBase;
	cin.ignore();
	this->notch = 0;

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
		cout << "Invalid position argument for Rotor::getPos" << endl;
		return -1;
	}
}

// Find the position of a value, to work through the rotor backwards
int Rotor::getReversePos(int input)
{
	if (input >= 0 && input < 26)
	{
		// Check all positions on the rotor
		for (int i = 0; i < 25; i++) {
			// (input - position) % 26 simulates the rotations
			if (scramble[i] == ((input - position) % 26)) {
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

void Rotor::UI_Notch()
{
	string temp;
	cout << "What letter is the notch at: ";
	getline(cin, temp);
	char notch_Let = temp[0];
	notch = lettersToNum(notch_Let);
	if (notch >= 0 && notch < 26)
	{
		this->notch = notch;
	}
	else
	{
		cout << "Invalid notch value" << endl;
		this->notch = 0;
	}
}

void Rotor::UI_Scramble()
{
	for (int i = 0; i < 26; i++)
	{
		char ctemp;
		int itemp, ytemp;
		string sttemp;
		cout << Alp[i] << " is link to: ";
		getline(cin, sttemp);
		ctemp = sttemp[0];
		ctemp = toupper(ctemp);
		itemp = lettersToNum(ctemp);
		for (int j = 0; j < 26; j++)
		{
			if (itemp == scramble[j])
			{
				cout << ctemp << " is already attached";
				i--;
				break;
			}
			if (j == 25)
			{
				scramble[i] = itemp;
			}
		}
		//Add stuff for db
	}
}



Rotor::~Rotor()
{
}


int lettersToNum(char letter) {
	// convert input letter to uppercase
	letter = toupper(letter);

	try {
		// iterate thru letters array
		for (int i = 0; i <= 25; i++) {
			if (letter == Alp[i]) {
				// return correct num for the input letter
				return i;
			}
		}
		// throw error if input letter isn't between A-Z
		throw(letter);
	}
	// print error message, return 99 (code for a blank space)
	catch (char wrongChar) {
		cout << "Error in function letterToNum: Input char (" << wrongChar << ") not in alphabet\n";
		return 99;
	}
}