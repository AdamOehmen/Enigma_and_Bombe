#include <iostream>
#include <string>
#include "Plugboard.h"
#include "functions.h"
#include "Reflector.h"


using namespace std;
string plaintext;

int main() //This is the main
{
	
	cout << "What is the message you want to send\n"; //get the massage we want to encode
	getline(cin,plaintext);
	int messageSize = plaintext.size();
	vector<int> plainNum(messageSize);

	for (int i = 0; i < messageSize; i++)
	{
		plainNum[i] = letterToNum(plaintext[i]);
	}

	int arry[10] = { 2, 7, 10, 5, 16, 20, 22, 12, 6, 23};
	Plugboard plug{};
	plug.setPlugPos(arry);
	for (int i = 0; i < messageSize; i++)
	{
		plainNum[i] = plug.PlugSwitch(plainNum[i]);
	}

	return 0;

}