#include "Driver.h"


string plaintext;

int main() //This is the main
{
	
	cout << "What is the message you want to send\n"; //get the massage we want to encode
	getline(cin,plaintext);
	plaintext = delSpaces(plaintext);  // comment
	int messageSize = plaintext.size();
	vector<int> plainNum(messageSize);

	
	for (int i = 0; i < messageSize; i++)
	{
		plainNum[i] = letterToNum(plaintext[i]);
	}

	
	int arry[10] = { 2, 7, 10, 5, 16, 20, 22, 12, 6, 23};
	Plugboard plug{};
	plug.setPlugPos(arry);


	int numRotors = 3;
	Rotor rotors[3] = { Rotor(), Rotor(), Rotor() };
	for (int i = 0; i < messageSize; i++) {
		plainNum[i] = plug.PlugSwitch(plainNum[i]);
		cout << "After plugboard: " << plainNum[i] << endl;;

		for (int j = 0; j < numRotors; j++) {
			plainNum[i] = rotors[j].getScramblePos(plainNum[i]);
			cout << "After rotor " << j+1 << ": " << plainNum[i] << endl;
		}

		cout << "ROTATE ROTOR 1" << endl;
		rotors[0].rotate();
		bool lastRotated = true;
		for (int k = 1; k < numRotors; k++) {
			if ((rotors[k - 1].getNotch() == rotors[k - 1].getPos()) && lastRotated) {
				rotors[k].rotate();
				cout << "ROTATE ROTOR " << (k + 1) << endl;
				lastRotated = true;
			}
			else {
				lastRotated = false;
			}
		}
		cout << numToLetter(plainNum[i]) << endl;
	}

	return 0;

}