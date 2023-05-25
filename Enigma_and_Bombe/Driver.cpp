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

	int arry[10] = { 2, 7, 10, 5, 16, 20, 22, 12, 6, 23};
	Plugboard plug{};
	plug.setPlugPos(arry);
	int temp = plug.PlugSwitch(2);

	return 0;

}