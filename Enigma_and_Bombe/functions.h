#ifndef functions
#define functions

char letters[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

// returns uppercase letter for the input int, where 0 returns A and 25 returns Z
char numToLetter(int num) {
	return letters[num];
}

// returns int for the input letter (case insensitive), where A returns 0 and 25 returns Z
int letterToNum(char letter) {
	// convert input letter to uppercase
	letter = toupper(letter);

	// iterate thru letters array
	for (int i = 0; i < 25; i++) {
		if (letter == letters[i]) {
			// return correct num for the input letter and break
			return i;
			break;
		}
	}
}

#endif 
