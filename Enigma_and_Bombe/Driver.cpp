#include <iostream>
#include <string>
#include "Plugboard.h"
#include "functions.h"


using namespace std;
string planetext;

int main() //This is the main
{
	
	cout << "What is the message you want to send\n"; //get the massage we want to encode
	getline(cin,planetext);

	int arry[2] = { 2,7 };
	Plugboard plug{};
	plug.setPlugPos(arry);
	plug.getPlugPos();

	char input_char;
	cout << "Enter input char: ";
	cin >> input_char;
	cout << letterToNum(input_char);
	

	return 0;

}