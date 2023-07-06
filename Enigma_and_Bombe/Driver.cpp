#include "Driver.h"


string plaintext;

int main() //This is the main
{
	cout << "Welcome to Enigma" << endl;
	// Create plugboard with user inputs
	Plugboard plug{};
	plug.createPlugboard();
	plug.setPlugPos();

	cout << "What is the message you want to send?\n"; //get the message we want to encode
	getline(cin,plaintext);
	plaintext = delSpaces(plaintext);

	// put input string into array
	int messageSize = plaintext.size();
	vector<int> plainNum(messageSize);

	
	// Convert input message to array of numbers
	for (int i = 0; i < messageSize; i++)
	{
		plainNum[i] = letterToNum(plaintext[i]);
	}


	// Create reflector with hard-coded values
	Reflector reflector;

	int numRotors = 3;
	// Create a vector with all of the rotors so we can iterate through it
	// Each has hard-coded values for now
	vector<Rotor> rotors;
	for (int i = 0; i < numRotors; i++) {
		rotors.push_back(Rotor());
	}
	for (int i = 0; i < messageSize; i++)
	{
		cout << "Starting letter: " << numToLetter(plainNum[i]) << endl;

		// Send input through plugboard
		plainNum[i] = plug.PlugSwitch(plainNum[i]);

		// Send plugboard output through each rotor in sequence
		for (int j = 0; j < numRotors; j++) {
			plainNum[i] = rotors[j].getScramblePos(plainNum[i]);
		}
		
		// Send output of rotors through reflector
		plainNum[i] = reflector.reflect(plainNum[i]);

		// Send reflector output back through each rotor, in reverse sequential order
		for (int j = numRotors - 1; j >= 0; j--) {
			plainNum[i] = rotors[j].getReversePos(plainNum[i]);
		}

		cout << "Encrypted letter: " << numToLetter(plainNum[i]) << endl << endl;

		// Rotate rotor #1 after every encrypted input letter
		rotors[0].rotate();
		cout << "ROTATE ROTOR 1" << endl << endl;

		bool lastRotated = true;
		for (int k = 1; k < numRotors; k++) {
			// Rotate the next rotor IF the notch of the previous matches the current position, AND the previous just rotated
			if ((rotors[k - 1].getNotch() == rotors[k - 1].getPos()) && lastRotated) {
				rotors[k].rotate();
				cout << "ROTATE ROTOR " << (k + 1) << endl;
				lastRotated = true;
			}
			// Otherwise, update value of lastRotated
			else {
				lastRotated = false;
			}
		}
	}

	// Print the final encrypted message
	cout << "Final encrypted message: ";
	for (int i = 0; i < plainNum.size(); i++) {
		cout << numToLetter(plainNum[i]);
	}

	cout << endl;

	return 0;

}