#ifndef functions
#define functions

#include "pch.h"
#include <iostream>
#include <algorithm>
using namespace std;

char letters[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

// returns uppercase letter for the input int (between 0-25, inclusive), where 0 returns A and 25 returns Z
char numToLetter(int num) {
	try {
		if (num >= 0 && num <= 25) {
			// grab the corresponding letter from letters[] and return
			return letters[num];
		}
		else {
			// throw error if input int isn't within 0-25
			throw (num);
		}
	}
	// print error message, return a blank character
	catch (int wrongNum) {
		cout << "Error in function numToLetter: Input num (" << wrongNum << ") outside of range 0-25\n";
		return ' ';
	}

}

// returns int for the input letter (A-Z, case insensitive), where A returns 0 and 25 returns Z
int letterToNum(char letter) {
	// convert input letter to uppercase
	letter = toupper(letter);

	try {
		// iterate thru letters array
		for (int i = 0; i <= 25; i++) {
			if (letter == letters[i]) {
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

string delSpaces(string str) {  // delete spaces
	str.erase(remove(str.begin(), str.end(), ' '), str.end());

	return str;
}

#endif 
