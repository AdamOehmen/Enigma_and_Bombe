#include <iostream>
#include <string>
#include "Plugboard.h"


using namespace std;
string planetext;

int main() //This is the main
{
	int arry[2] = { 2,7 };
	Plugboard plugboard{};
	//plugboard.setPlugPos(arry);
	//plugboard.getPlugPos();
	cout << "What is the message you want to send\n"; //get the massage we want to encode
	getline(cin,planetext);

	return 0;

}