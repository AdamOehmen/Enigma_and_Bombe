#include "Reflector.h"

Reflector::Reflector() {

}

Reflector::Reflector(int reflectorNum) {

}

int Reflector::reflect(int input) {
	try {
		for (int i = 0; i <= 12; i++) {
			if (pairings[i][0] == input) {
				return pairings[i][1];
			}
			else if (pairings[i][1] == input) {
				return pairings[i][0];
			}
		}
		throw(input);
	}
	catch (int wrongInput) {
		cout << "Error in Reflector::reflect: Input (" << wrongInput << ") not listed in reflector.\n";
	}
}
