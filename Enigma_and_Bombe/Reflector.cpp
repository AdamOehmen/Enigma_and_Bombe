#include "Reflector.h"

// Default constructor, uses hardcoded reflector vals
Reflector::Reflector() {

}

Reflector::Reflector(int reflectorNum) {
	// TODO: Add multiple reflectors, change pairings[13][2] to match new reflector in this constructor

}

int Reflector::reflect(int input) {
	try {
		for (int i = 0; i <= 12; i++) {
			// Check left side of the pairings array for input
			if (pairings[i][0] == input) {
				// Return paired int if found
				return pairings[i][1];
			}
			// Check right side of the pairings array
			else if (pairings[i][1] == input) {
				// Return paired int if found
				return pairings[i][0];
			}
		}
		// Throw error if input is not in pairings array
		throw(input);
	}
	// Print error msg
	catch (int wrongInput) {
		cout << "Error in Reflector::reflect: Input (" << wrongInput << ") not listed in reflector.\n";
	}
}
