#ifndef Plugboard_H
#define PlugBoard_H

#include "pch.h"


class Plugboard
{

public:
	Plugboard();
	void createPlugboard();
	int test_createPlugboard(int test_pos[10][2], char test_let[10][2]);
	void setPlugPos();
	int test_setPlugPos(int test_swap[26]);
	int PlugSwitch(int letter);
	~Plugboard();


protected:
	int connections[26];
};


#endif 