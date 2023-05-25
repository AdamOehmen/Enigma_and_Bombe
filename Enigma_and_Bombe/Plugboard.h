
#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>

#ifndef Plugboard_H
#define PlugBoard_H


using std::vector;
using std::string;

class Plugboard 
{

public:
	Plugboard();
	string encodeMessage(string input_message);
	void setPlugPos(int PlugPos[]);
	int PlugSwitch(int letter);
	~Plugboard();
	

protected:
	int connections[24];
};


#endif 
