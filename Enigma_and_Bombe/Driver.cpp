#include "Driver.h"


string plaintext;

int main() //This is the main
{
	cout << "Welcome to Enigma" << endl;
	Plugboard plug{};
	plug.createPlugboard();
	cout << "What is the message you want to send\n"; //get the massage we want to encode
	getline(cin,plaintext);
	plaintext = delSpaces(plaintext);  // comment
	int messageSize = plaintext.size();
	vector<int> plainNum(messageSize);

	
	for (int i = 0; i < messageSize; i++)
	{
		plainNum[i] = letterToNum(plaintext[i]);
	}

	
	plug.setPlugPos();
	for (int i = 0; i < messageSize; i++)
	{
		plainNum[i] = plug.PlugSwitch(plainNum[i]);
	}

	return 0;

}