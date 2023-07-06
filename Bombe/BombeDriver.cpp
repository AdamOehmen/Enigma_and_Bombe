#include "../Enigma_and_Bombe/pch.h"
#include "../Enigma_and_Bombe/Reflector.h"
#include "../Enigma_and_Bombe/Plugboard.h"
#include "../Enigma_and_Bombe/Rotor.h"
#include "../Enigma_and_Bombe/functions.h"


int main() {
	cout << "Welcome to Bombe." << endl;
	// Create plugboard with user inputs
	Plugboard plug{};
	plug.createPlugboard();
	plug.setPlugPos();
	
	// TEMP - eventually will only pull from previousmessages database
	cout << "What message would you like to decode?" << endl;
	string encodedMessage;
	getline(cin, encodedMessage);
	encodedMessage = delSpaces(encodedMessage);

	// Map encoded message string to a vector
	int messageSize = encodedMessage.size();
	vector <int> plainNum(messageSize);

	// Convert input message to array of numbers
	for (int i = 0; i < messageSize; i++)
	{
		plainNum[i] = letterToNum(encodedMessage[i]);
	}
	
	// Create reflector with hardcoded values
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
		cout << "Encrypted letter: " << numToLetter(plainNum[i]) << endl;

		// Send input through each rotor in sequence
		for (int j = 0; j < numRotors; j++) {
			plainNum[i] = rotors[j].getScramblePos(plainNum[i]);
		}

		// Send output of first pass thru rotors through reflector
		plainNum[i] = reflector.reflect(plainNum[i]);

		// Send reflector output through each rotor, in reverse sequential order
		for (int j = numRotors - 1; j >= 0; j--) {
			plainNum[i] = rotors[j].getReversePos(plainNum[i]);
		}

		// Send through plugboard
		plainNum[i] = plug.PlugSwitch(plainNum[i]);

		// Print final letter to screen
		cout << "Unencrypted letter: " << numToLetter(plainNum[i]) << endl << endl;

		// Rotate rotor #1 after every decrypted input letter
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
		cout << endl;
	}

	cout << "Final decrypted message: ";
	for (int i = 0; i < plainNum.size(); i++) {
		cout << numToLetter(plainNum[i]);
	}

	return 0;
}