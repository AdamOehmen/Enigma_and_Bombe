#include "Driver.h"


string plaintext;

int main() //This is the main
{
	cout << "Welcome to Enigma" << endl;
	Plugboard plug{};
	plug.createPlugboard();
	plug.setPlugPos();
	cout << "What is the message you want to send\n"; //get the massage we want to encode
	getline(cin,plaintext);
	plaintext = delSpaces(plaintext);  // comment
	int messageSize = plaintext.size();
	vector<int> plainNum(messageSize);

	
	// Convert input message to array of numbers
	for (int i = 0; i < messageSize; i++)
	{
		plainNum[i] = letterToNum(plaintext[i]);
	}


	// Create plugboard with 5 hard-coded pairs of numbers
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
		// Send input through plugboard
		plainNum[i] = plug.PlugSwitch(plainNum[i]);
		cout << "After plugboard: " << plainNum[i] << endl;;

		// Send plugboard output through each rotor in sequence
		for (int j = 0; j < numRotors; j++) {
			plainNum[i] = rotors[j].getScramblePos(plainNum[i]);
			cout << "After rotor " << j+1 << ": " << plainNum[i] << endl;
		}
		
		// Send output of rotors through reflector
		plainNum[i] = reflector.reflect(plainNum[i]);
		cout << "After reflector: " << plainNum[i] << endl;

		// Send reflector back through each rotor, in reverse sequential order
		for (int j = numRotors - 1; j >= 0; j--) {
			plainNum[i] = rotors[j].getScramblePos(plainNum[i]);
			cout << "After rotor " << j + 1 << ": " << plainNum[i] << endl;
		}

		// Rotate rotor #1 after every encrypted input
		rotors[0].rotate();
		cout << "ROTATE ROTOR 1" << endl;

		
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
		// Print final letter to screen
		cout << numToLetter(plainNum[i]) << endl;
	}

	return 0;

}