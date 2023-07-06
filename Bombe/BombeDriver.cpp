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
		cout << "Starting num: " << plainNum[i] << endl;

		// Send input through each rotor in sequence
		for (int j = 0; j < numRotors; j++) {
			plainNum[i] = rotors[j].getScramblePos(plainNum[i]);
			cout << "After rotor " << j + 1 << ": " << plainNum[i] << endl;
		}

		// Send output of rotors through reflector
		plainNum[i] = reflector.reflect(plainNum[i]);
		cout << "After reflector: " << plainNum[i] << endl;

		// Send reflector through each rotor, in reverse sequential order
		for (int j = numRotors - 1; j >= 0; j--) {
			plainNum[i] = rotors[j].getReversePos(plainNum[i]);
			cout << "After rotor " << j + 1 << ": " << plainNum[i] << endl;
		}

		// Send through plugboard
		plainNum[i] = plug.PlugSwitch(plainNum[i]);
		cout << "After plugboard: " << plainNum[i] << endl;

		// Print final letter to screen
		cout << "Final Result: " << numToLetter(plainNum[i]) << endl;

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
		
		for (int i = 0; i < numRotors; i++) {
			cout << "Rotor " << i + 1 << " pos = " << rotors[i].getPos() << endl;
		}
		cout << endl;
	}

	return 0;
}