#ifndef Plugboard_H
#define PlugBoard_H

#include "pch.h"

class Plugboard 
{

public:
	Plugboard();
	void setPlugPos(int PlugPos[]);
	int PlugSwitch(int letter);
	~Plugboard();
	

protected:
	int connections[26];
};


#endif 
