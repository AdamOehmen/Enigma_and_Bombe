#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>

#ifndef Class1_H
#define Class1_H


using std::vector;
using std::string;

class Plugboard
{

public:
	Plugboard();
	string encodeMessage(string input_message);
	void setPlugPos(int PlugPos[]);
	void getPlugPos();
	~Plugboard();


protected:
	int connections[2];
};


#endif 
