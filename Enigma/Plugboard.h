#pragma once

#include "pch.h"


class Plugboard
{

public:
	Plugboard();
	void createPlugboard();
	string returnPlugLet();
	void DB_Extract(string db_setting);
	int test_createPlugboard(int test_pos[10][2], char test_let[10][2]);
	void setPlugPos();
	int test_setPlugPos(int test_swap[26]);
	int PlugSwitch(int letter);
	~Plugboard();


protected:
	int connections[26];
};